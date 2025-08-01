#include "WriteSCThread.h"
#include "speckle.h"
extern SpeckleClass *speckle;
/********************************************************************************************/
WriteSCThread::WriteSCThread(QObject *parent)
    : QThread(parent)
{

}
/********************************************************************************************/
void WriteSCThread::run()
{
    int keep_going=1;
    int files_used=0;
    //int seq_per_file;
    int img_per_file;
    float t;
    int img_written_in_this_file=0;
    speckle->sc_img_written=0;
    char tmp_str[512];
    QString tmp_fname;
    sc_write_fps = 0;
    qint64 time_last = 0;

    force_stop=false;

    img_per_file = (int)(MAX_FILE_SIZE/(speckle->sc_w*speckle->sc_h*sizeof(float)));

    sprintf(tmp_str,".%05i",files_used);
    tmp_fname=QString(speckle->filename+tmp_str+".sc");

    QFile file(tmp_fname);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out.writeRawData((const char *)(&(speckle->sc_h)), sizeof(unsigned short));
    out.writeRawData((const char *)(&(speckle->sc_w)), sizeof(unsigned short));

    //if(speckle->Nframes*speckle->Nreps > img_per_file)
    //    img_in_first_file = img_per_file;
    //else {
    //    img_in_first_file = speckle->Nreps*speckle->Nframes;
    //}

    // write placeholder of # images. Fix once we know how many are in the file
    out.writeRawData((const char *)(&(img_written_in_this_file)), sizeof(unsigned short));

    // get timing file ready
    sc_timing_file.setFileName((QString(speckle->filename + "_sc.timing")));
    sc_timing_file.open(QIODevice::WriteOnly);
    sc_timing_file_output.setDevice(&sc_timing_file);

    sc_write_timer.start();
    while(keep_going)
    {
        if(speckle->num_sc_processed > speckle->sc_img_written)
        {
            int idx = speckle->sc_img_written % speckle->num_sc_buffers_allocated;
            out.writeRawData((const char *)(speckle->sc_images[idx]),
                    speckle->sc_w*speckle->sc_h*sizeof(float));
            // write next image
            speckle->sc_img_written++;
            img_written_in_this_file++;

            // add time stamp of this image to timing file
            t = speckle->sc_acquisition_times.at(speckle->sc_img_written - 1);
            sc_timing_file_output.writeRawData(reinterpret_cast<const char*>(&t), sizeof(float));

            if(speckle->sc_img_written % 10 == 0)
            {
                sc_write_fps = static_cast<int>(10 * 1000.0 / (sc_write_timer.elapsed() - time_last));
                time_last = sc_write_timer.elapsed();
            }

            // see if we need to open a new file
            if(img_written_in_this_file>=img_per_file)
            {
                // fix header with correct number written
                file.seek(2*sizeof(unsigned short));
                out.writeRawData((const char *)(&(img_written_in_this_file)), sizeof(unsigned short));
                file.close();

                img_written_in_this_file=0;
                files_used++;
                sprintf(tmp_str,".%05i",files_used);
                tmp_fname=QString(speckle->filename+tmp_str+".sc");
                file.setFileName(tmp_fname);
                file.open(QIODevice::WriteOnly);
                out.setDevice(&file);
                out.writeRawData((const char *)(&(speckle->sc_h)), sizeof(unsigned short));
                out.writeRawData((const char *)(&(speckle->sc_w)), sizeof(unsigned short));
                // insert placeholder - will be updated later
                out.writeRawData((const char *)(&(img_written_in_this_file)), sizeof(unsigned short));
            }
        }
        else
            msleep(10);

        if(speckle->num_sc_processed-speckle->sc_img_written > speckle->num_sc_buffers_allocated-5)
        {
            // acquisition has gotten too far ahead. Pause while writing catches up
            if(speckle->pause_acquisition==0) // first pause
            {
                speckle->pause_acquisition=1;
                qDebug() << QString("SC: Acquisition paused: sc_img_acqd=%1, img_written=%2, img_per_buf=%3").arg(
                        speckle->num_sc_processed).arg(speckle->sc_img_written).arg(speckle->num_sc_buffers_allocated);
            }
            speckle->pause_acquisition=1;
            qDebug() << QString("SC: Acquisition paused: sc_img_acqd=%1, img_written=%2, img_per_buf=%3").arg(
                    speckle->num_sc_processed).arg(speckle->sc_img_written).arg(speckle->num_sc_buffers_allocated);
        }


        // stop if stop button was pressed and all acquired images have been written
        if( (speckle->acquire_flag == IDLE_MODE) && (speckle->num_sc_processed == speckle->sc_img_written))
            keep_going=0;
        if(force_stop)
            keep_going=0;
       // qDebug() << "acquired " << speckle->img_acquired << ", wrote " << speckle->img_written << endl;
    }
    // fix header with correct number written
    file.seek(2*sizeof(unsigned short));
    out.writeRawData((const char *)(&(img_written_in_this_file)), sizeof(unsigned short));
    qDebug() << "closing files";
    file.close();
    sc_timing_file.close();
}
/********************************************************************************************/

void WriteSCThread::stopWriting(void)
{
    // force writing thread to stop when stop button is pressed even if some frames haven't been written
    force_stop=true;
}
