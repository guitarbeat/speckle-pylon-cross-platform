#include <QDebug>
#include "openCVGrabber.h"
/***************************************************************************/
OpenCVGrabber::OpenCVGrabber(int devNumber)
{
    // note that members of Camera are defined initialized in the defaul Camera constructor which is called first
    deviceNumber=devNumber;
}
/***************************************************************************/
void OpenCVGrabber::openCamera(int devNum)
{
    deviceNumber=devNum;

    qDebug().nospace() << "Opening USB video device (usb/" << deviceNumber << ")";

    capture_device.open(deviceNumber);
    if(!capture_device.isOpened())
    {
        qDebug().nospace() << "Unable to open USB video device usb/" << deviceNumber;
        return;
    }

    // try forcing video size to HD
    //capture_device.set(CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M','J','P','G'));
    //capture_device.set(CAP_PROP_FPS, 30);
    capture_device.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    capture_device.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);

    im_w = capture_device.get(cv::CAP_PROP_FRAME_WIDTH);
    im_h = capture_device.get(cv::CAP_PROP_FRAME_HEIGHT);

    bit_depth=8;
    SetBytesPerPixel();
    color_planes=3;
    color_camera=true;
    camera_type = CAMERA_FRAMEGRABBER;

    qDebug().noquote() << "Name:" << camera_name;
    qDebug().noquote() << "Dimensions:" << im_w << "x" << im_h;
    qDebug().noquote() << "frames/sec:" << capture_device.get(CAP_PROP_FPS);
}
/***************************************************************************/
bool OpenCVGrabber::isOpened(void)
{
    return(capture_device.isOpened());
}
/***************************************************************************/
void OpenCVGrabber::cleanup(void)
{
    qDebug().nospace() << "Closing USB video device (usb/" << deviceNumber << ")";
    if(capture_device.isOpened())
        capture_device.release();
}
/***************************************************************************/
int OpenCVGrabber::initialize_acquisition(AcquisitionClass *acq, unsigned char **buffer_list,
                                          QVector<float> *acq_t)
{
    //SetCameraExposureTime(exp_time);
    //setCameraAOI();
    img_acquired=0;
    buffers=buffer_list;
    acq_times = acq_t;
    acq_settings = acq;

    return(1);
}
/*******************************************************/
void OpenCVGrabber::acquireImagesAsync(void)
{
    ImgAcquireThread = new OpenCVAcquireAsync(acq_settings);
    ImgAcquireThread->initialize(&capture_device, buffers, acq_times, &img_acquired);
    connect(ImgAcquireThread, &OpenCVAcquireAsync::finished,
            this, &Camera::acquireAsyncCompleted);
    ImgAcquireThread->start();
}
/***************************************************************************/
void OpenCVGrabber::acquireImage(CImg<unsigned char> *img)
{
    Mat frame;
    capture_device >> frame;
    *img = CImg<uchar>::_cvmat2cimg(frame);
}
/***************************************************************************/
void OpenCVGrabber::stopAcquisition(void)
{
    if(ImgAcquireThread)
    {
        ImgAcquireThread->stopAcquisition();
        ImgAcquireThread->wait();
        delete ImgAcquireThread;
    }
}
/***************************************************************************/
QString OpenCVGrabber::getCameraInfo(void)
{
    QString msg;
    msg += QString("<table cellpadding=5>");
    msg += QString("<tr><td><b>Device</b></td><td>usb/%1</td></tr>").arg(deviceNumber);
    msg += QString("<tr><td><b>Camera Name</b></td><td>%1</td></tr>").arg(camera_name);
    msg += QString("<tr><td><b>Resolution</b></td><td>%1x%2</td></tr>").arg(im_w).arg(im_h);
    msg += QString("</table>");
    return msg;
}
/***************************************************************************/
