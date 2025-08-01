#include "videointhread.h"
#include "speckle.h"
#include "speckle_processing.h"
extern SpeckleClass *speckle;

VideoInThread::VideoInThread(QObject *parent):
    QThread(parent)
{
    num_buffers=20;
}
/*****************************************************************/
void VideoInThread::run()
{
    bool keep_going=true;
    qint64 t_elapsed;
    qint64 t_last = 0;
    acquire_fps = 0;
    uint list_idx, idx;

    speckle->video_in_frames_acquired=0;
    OpenCaptureDevice();

    // setup for asynchronous acquisition
    image_list.assign(num_buffers, videoInCamera->im_w, videoInCamera->im_h, 1, videoInCamera->color_planes);
    speckle->captured_rgb.resize(videoInCamera->im_w, videoInCamera->im_h, 1, videoInCamera->color_planes, -1);
    while(keep_going)
    {
        if((speckle->overlays.bg_src == SRC_VIDEO) && !(videoInCamera->isOpened())) // try opening if it's closed
            OpenCaptureDevice();
        if((speckle->overlays.bg_src == SRC_VIDEO) && videoInCamera->isOpened())
        {
            list_idx = speckle->video_in_frames_acquired % num_buffers;
            videoInCamera->acquireImage(&(image_list[list_idx]));
            memcpy(speckle->captured_rgb.data(), image_list[list_idx].data(), videoInCamera->im_w*videoInCamera->im_h*videoInCamera->color_planes);

            // create pixmap and send to display
            if( (rgb_qi.width()!=speckle->captured_rgb.width()) || (rgb_qi.height()!=speckle->captured_rgb.height()) )
                rgb_qi = QImage(speckle->captured_rgb.width(), speckle->captured_rgb.height(), QImage::Format_RGB888);
            CImg_to_QImage(&(speckle->captured_rgb), &rgb_qi);
            video_in_qp = QPixmap::fromImage(rgb_qi); //QImage::Format_RGB888
            emit videoinImageReady(&video_in_qp, acquire_fps);

            // save time stamp
            t_elapsed = speckle->acquisition->getTimeElapsed();
            speckle->video_in_acquisition_times.append(t_elapsed);

            if(speckle->acquire_flag == ACQUISITION_MODE && speckle->save_input_video)
            {
                idx = speckle->video_in_frames_acquired % NUM_VIDEO_FRAME_BUFFERS;
                speckle->video_in_frames_to_write(idx) = image_list.at(list_idx);
            }

            speckle->video_in_frames_acquired++;

            if(speckle->video_in_frames_acquired % 30 == 0) {
                acquire_fps = static_cast<int>(30 * 1000.0 / (t_elapsed - t_last));
                t_last = t_elapsed;
            }
        }
        else {
            Sleep(5);
        }

        if(speckle->acquire_flag==IDLE_MODE)
            keep_going=false;
    }
    videoInCamera->cleanup();
}
/*****************************************************************/
void VideoInThread::setCamera(cameraDescription c)
{
    camera_descr = c;
#ifdef USE_PYLON
    if(c.camera_type==CAMERA_PYLON)
        videoInCamera = &baslerCamera;
#endif
    if(c.camera_type==CAMERA_FRAMEGRABBER)
    {
        videoInCamera = &openCVCamera;
        videoInCamera->camera_name = c.description;
    }
}
/*****************************************************************/
void VideoInThread::OpenCaptureDevice()
{
    if(videoInCamera->isOpened())
        return;

    videoInCamera->openCamera(camera_descr.local_index);
    if(!videoInCamera->isOpened())
        qDebug() << "error opening " << camera_descr.description << ", device number " << camera_descr.local_index;
    else
        setCameraExposure(exposure_time);

}
/*****************************************************************/
void VideoInThread::setCameraExposure(float exp_time)
{
    // set exposure time of color camera
    exposure_time=exp_time;
    if(videoInCamera->isOpened())
        videoInCamera->SetCameraExposureTime(exp_time);
}
