#include <string.h>
#include <windows.h>
#include "WriteThread.h"
#include "speckle.h"
extern SpeckleClass *speckle;
/********************************************************************************************/
WriteThread::WriteThread(QObject *parent)
: QThread(parent)
{

}
/********************************************************************************************/
void WriteThread::run()
{
	int keep_going=1;
	unsigned short foo;
	int files_used=0;
    //int seq_per_file;
    int img_per_file, img_left;
    int img_in_first_file;
    float t;
	int img_written_in_this_file=0;
    speckle->img_written = 0;
	char err_str[512];
	char tmp_str[512];
	QString tmp_fname;
    raw_write_fps = 0;
    qint64 time_last = 0;

    force_stop=false;

    img_per_file = (int)(MAX_FILE_SIZE/(speckle->theCamera->im_w*speckle->theCamera->im_h));

    sprintf(tmp_str,".%05i",files_used);
	tmp_fname=QString(speckle->filename+tmp_str);
	//sprintf(fname,"%s.%04i",qPrintable(speckle->filename),files_used);

	QFile file(tmp_fname);
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);
	out.writeRawData((const char *)(&(speckle->theCamera->im_h)), sizeof(unsigned short));
	out.writeRawData((const char *)(&(speckle->theCamera->im_w)), sizeof(unsigned short));
    img_in_first_file = img_per_file;
    if((speckle->acquisition->stop_condition == AcquisitionClass::STOP_NUMBER) &&
        (speckle->acquisition->img_to_acquire < img_per_file))
            img_in_first_file = speckle->acquisition->img_to_acquire;

    out.writeRawData((const char *)(&(img_in_first_file)), sizeof(unsigned short)); // Placeholder
    out.writeRawData((const char *)(&(speckle->theCamera->exp_time)), sizeof(unsigned short));
	
    // get timing file ready
    timing_file.setFileName((QString(speckle->filename + ".timing")));
    timing_file.open(QIODevice::WriteOnly);
    timing_file_output.setDevice(&timing_file);

    raw_write_timer.start();
	while(keep_going)
	{
        if(speckle->theCamera->img_acquired > speckle->img_written)
		{
            out.writeRawData((const char *)(speckle->raw_images[speckle->img_written]),
                             speckle->theCamera->im_w*speckle->theCamera->im_h*speckle->theCamera->bytes_pixel*speckle->theCamera->color_planes);
			// write next image
			speckle->img_written++;
			img_written_in_this_file++;

            // add time stamp of this image to timing file
            t = speckle->acquisition_times.at(speckle->img_written - 1);
            timing_file_output.writeRawData(reinterpret_cast<const char*>(&t), sizeof(float));

            if(speckle->img_written % 100 == 0)
            {
                raw_write_fps = static_cast<int>(100 * 1000.0 / (raw_write_timer.elapsed() - time_last));
                time_last = raw_write_timer.elapsed();
            }

			// see if we need to open a new file
			if(img_written_in_this_file>=img_per_file)
			{
                // Update header with correct number of frames written
                file.seek(2*sizeof(unsigned short));
                out.writeRawData((const char *)(&(img_written_in_this_file)), sizeof(unsigned short));

                file.close();

				img_written_in_this_file=0;
				files_used++;
                sprintf(tmp_str,".%05i",files_used);
				tmp_fname=QString(speckle->filename+tmp_str);
				file.setFileName(tmp_fname);
				file.open(QIODevice::WriteOnly);
				out.setDevice(&file);
				out.writeRawData((const char *)(&(speckle->theCamera->im_h)), sizeof(unsigned short));
				out.writeRawData((const char *)(&(speckle->theCamera->im_w)), sizeof(unsigned short));
                out.writeRawData((const char *)(&(img_per_file)), sizeof(unsigned short)); // Placeholder
				out.writeRawData((const char *)(&(speckle->theCamera->exp_time)), sizeof(unsigned short));
			}
		}
		else
			msleep(10);

        if(speckle->theCamera->img_acquired-speckle->img_written > speckle->Nimg_per_buffer-10)
		{
			// acquisition has gotten too far ahead. Pause while writing catches up
			if(speckle->pause_acquisition==0) // first pause
			{	
				speckle->pause_acquisition=1;
                qDebug() << QString("Acquisition paused: img_acqd=%1, img_written=%1, img_per_buf=%1").
                    arg(speckle->theCamera->img_acquired).arg(speckle->img_written).arg(speckle->Nimg_per_buffer);
			}
			speckle->pause_acquisition=1;
            qDebug() << QString("Acquisition paused: img_acqd=%1, img_written=%2, img_per_buf=%3")
                    .arg(speckle->theCamera->img_acquired).arg(speckle->img_written).arg(speckle->Nimg_per_buffer);
		}

		// stop if stop button was pressed and all acquired images have been written
        if( (speckle->acquire_flag == IDLE_MODE) && (speckle->theCamera->img_acquired == speckle->img_written))
			keep_going=0;
        if(force_stop)
            keep_going=0;
	}

    // Update header with correct number of frames written
    file.seek(2*sizeof(unsigned short));
    out.writeRawData((const char *)(&(img_written_in_this_file)), sizeof(unsigned short));

	file.close();
    timing_file.close();
}
/********************************************************************************************/
void WriteThread::stopWriting(void)
{
    // force writing thread to stop when stop button is pressed even if some frames haven't been written
    force_stop=true;
}
