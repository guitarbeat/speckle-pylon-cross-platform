#include "ProcessingThread.h"
#include "speckle.h"
extern SpeckleClass *speckle; 
/*****************************************************************/
ProcessingThread::ProcessingThread(QObject *parent)
: QThread(parent)
{

}
/*****************************************************************/
void ProcessingThread::run()
{
	int keep_going=1;
    bool processed_an_image = false;
	int raw_img_acquired;
    processing_fps = 0;
		
	if(InitializeProcessing() < 0)
	{
		qDebug() << "error allocating sc buffers. Disabling processing.";
		return;
	}
    
	while(keep_going)
	{

        raw_img_acquired = speckle->theCamera->img_acquired;
		if(speckle->process_mode == PROCESS_MOST_RECENT)
		{
            // Process the most recent raw frames in order to avoid the processing
            // falling behind the acquisition. Can result in skipped raw frames and
            // an irregular number of saved speckle contrast frames.
            if((raw_img_acquired - speckle->last_raw_processed) >= speckle->num_sc_to_avg)
            {
                ProcessImages(raw_img_acquired-speckle->num_sc_to_avg);
				processed_an_image = true;
			}
			else
                processed_an_image = false;
		}
		
		if(speckle->process_mode == PROCESS_PARALLEL)	
		{
            // Process the next iteration of raw frames even if processing has
            // fallen behind the acquisition. Always processes all acquired frames.
            if((raw_img_acquired - speckle->num_raw_processed) >= speckle->num_sc_to_avg)
			{
                ProcessImages(speckle->num_raw_processed);
				processed_an_image = true;
			}
			else
				processed_an_image = false;
		}

		if(!processed_an_image) // nothing was done. rest
			msleep(5);
		
        if(speckle->acquire_flag==IDLE_MODE)
		{
			// make sure all acquired images have been processed (to within # averaged together)
            if((speckle->process_mode == PROCESS_PARALLEL) && (speckle->theCamera->img_acquired-speckle->num_raw_processed < speckle->num_sc_to_avg))
				keep_going=0;
			// just stop if we're only doing most recent
			if(speckle->process_mode == PROCESS_MOST_RECENT)
				keep_going=0;
		}
	}
}
/*****************************************************************/
int ProcessingThread::InitializeProcessing(void)
{
    int num_to_allocate=0;
	int i;

	// initialize counters
	speckle->last_raw_processed=0;
	speckle->num_sc_processed=0;
    speckle->num_raw_processed=0;

	// initialize flsci
     unsigned short width = speckle->theCamera->im_w;
     unsigned short height = speckle->theCamera->im_h;
     unsigned short window = speckle->NxN;
#ifdef USE_FLSCI
     flsci_sc_end(&(speckle->sc_calc));
     speckle->sc_calc = flsci_sc_init(width, height, window, speckle->num_processing_threads);
     flsci_rct_end(&(speckle->rct_calc));
     if(speckle->show_rTC || speckle->show_overlay)
     	speckle->rct_calc = flsci_rct_init(speckle->rct_table, TC_TABLE_SIZE, width, height, speckle->num_processing_threads);
#endif

     // make extra sure that sc_w and sc_h have been updated
     speckle->Set_sc_width_height();

	// allocate sc buffers
     num_to_allocate = 1e6*MAX_BUFFER_MEMORY/(speckle->sc_w*speckle->sc_h*sizeof(float)) + 1;

     // first free preiously allocated buffers
     for(i=0; i<speckle->num_sc_buffers_allocated; i++)
#ifdef _MSC_VER
     	_aligned_free(speckle->sc_images[i]);
#else
     	free(speckle->sc_images[i]);
#endif

#ifdef _MSC_VER
        _aligned_free(speckle->sc_moving);
#else
        free(speckle->sc_moving);
#endif

     // allocate new buffers
     for(i=0; i<num_to_allocate; i++)
#ifdef _MSC_VER
		speckle->sc_images[i]= (float *)_aligned_malloc(speckle->sc_w*speckle->sc_h*sizeof(float), 32);
#else
		speckle->sc_images[i] = static_cast<float*>(aligned_alloc(32, speckle->sc_w*speckle->sc_h*sizeof(float)));
#endif

    //qDebug() << "allocated " << num_to_allocate << " sc buffers";
	speckle->num_sc_buffers_allocated = num_to_allocate;

#ifdef _MSC_VER
        speckle->sc_moving= (float *)_aligned_malloc(speckle->sc_w*speckle->sc_h*sizeof(float), 32);
#else
        		speckle->sc_moving = static_cast<float*>(aligned_alloc(32, speckle->sc_w*speckle->sc_h*sizeof(float)));
#endif

    processing_timer.start();
    return(0);

}
/*****************************************************************/
void ProcessingThread::ProcessImages(int start_idx)
{
	int i;
    qint64 t1, t2;

    t1=processing_timer.elapsed();
	// set up raw image pointers 
	if(speckle->num_sc_to_avg>10000)
	{
		qDebug() << "too many frames to process at once";
		return;
	}
	for(i=0;i<speckle->num_sc_to_avg;i++)
		images_to_process[i] = speckle->raw_images[start_idx + i];

	// process images into correct sc buffer
	int sc_buf_idx = speckle->num_sc_processed % speckle->num_sc_buffers_allocated;
#ifdef USE_FLSCI   
            //
    // speckle->sc_images[sc_buf_idx]
    // speckle->num_sc_to_avg
    flsci_sc_process(speckle->sc_calc,  images_to_process, speckle->num_sc_to_avg, speckle->sc_images[sc_buf_idx]);
#endif	

	// update processing counters 
	speckle->num_sc_processed++;
	speckle->num_raw_processed += speckle->num_sc_to_avg;
	speckle->last_raw_processed = start_idx + speckle->num_sc_to_avg;

    //qDebug() << QString("num_sc_pocessed=%1, num_raw_processed=%2, last_raw_processed=%3").arg(speckle->num_sc_processed)
    //            .arg(speckle->num_raw_processed).arg(speckle->last_raw_processed);

    // perform moving average if necessary
    int iframe, idx;
    if(speckle->moving_avg_width>1 && speckle->num_sc_processed>speckle->moving_avg_width)
    {
        float scale = 1.0/((float)(speckle->moving_avg_width));
        for(i=0;i<speckle->sc_h*speckle->sc_w;i++)
            speckle->sc_moving[i]=0.0;
        for (iframe=0;iframe<speckle->moving_avg_width;iframe++) {
            idx=(speckle->num_sc_processed-1-iframe) % speckle->num_sc_buffers_allocated;
            //qDebug() << "averaging " << idx << " for " << sc_buf_idx;
            for(i=0;i<speckle->sc_h*speckle->sc_w;i++)
                speckle->sc_moving[i] += speckle->sc_images[idx][i];
        }
        for(i=0;i<speckle->sc_h*speckle->sc_w;i++)
            speckle->sc_moving[i] *= scale;
        memcpy((void *)(speckle->sc_imgf.data()), (void *)(speckle->sc_moving), speckle->sc_w*speckle->sc_h*sizeof(float));
    }
    else
        memcpy((void *)(speckle->sc_imgf.data()), (void *)(speckle->sc_images[sc_buf_idx]), speckle->sc_w*speckle->sc_h*sizeof(float));

    if(speckle->compute_SC)
        speckle->sc_ready_for_display = 1;
    if(speckle->show_overlay)
        speckle->overlay_ready_for_display = true;

	// save timestamp of processed image (avg of raw acquisition times)
     float tmp_acq_times = 0.0;
     for(i = start_idx; i < start_idx + speckle->num_sc_to_avg; i++)
        tmp_acq_times += speckle->acquisition_times.at(i);
     speckle->sc_acquisition_times.append(tmp_acq_times / speckle->num_sc_to_avg);

     t2=processing_timer.elapsed();
     processing_fps = static_cast<int>(speckle->num_sc_to_avg * 1000.0 / (t2 - t1));
}
/*****************************************************************/
