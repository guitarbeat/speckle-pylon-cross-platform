#include "openCVacquireasync.h"
#include <QDebug>

/**************************************************************/
OpenCVAcquireAsync::OpenCVAcquireAsync(AcquisitionClass *acquisition)
    :ImageGenerator(acquisition)
{

}
/**************************************************************/
void OpenCVAcquireAsync::initialize(VideoCapture *camera, unsigned char **buf,
                                    QVector<float> *acq_t, int *Nacquired)
{
    openCVCamera = camera;
    buffers = buf;
    acq_times = acq_t;
    img_acquired = Nacquired;
    *img_acquired = 0;

    height = openCVCamera->get(cv::CAP_PROP_FRAME_HEIGHT);
    width = openCVCamera->get(cv::CAP_PROP_FRAME_WIDTH);
    color_planes = 3;
}
/**************************************************************/
void OpenCVAcquireAsync::run()
{
    Mat frame;
    CImg<unsigned char> img;

    acquisition->startTimer();
    keep_going = true;
    while(keep_going)
    {
        *openCVCamera >> frame;
        img = CImg<uchar>::_cvmat2cimg(frame);
        memcpy(buffers[*img_acquired % MAX_NUMBER_IMG_BUFFERS], img.data(),
               static_cast<size_t>(height*width*color_planes));
        acq_times->append(acquisition->getTimeElapsed());

        (*img_acquired)++;
        acquisition->img_acquired = *img_acquired;
        acquisition->updateFPS();

        if(acquisition->isFinished())
            keep_going = false;
    }
}
/**************************************************************/
