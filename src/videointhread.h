#ifndef VIDEOINTHREAD_H
#define VIDEOINTHREAD_H

#include <QThread>
#include "cameradescription.h"
#ifdef USE_PYLON
#include "pylonclass.h"
#endif
#ifdef SPECKLE_USE_OPENCV
#include "openCVGrabber.h"
#endif

class VideoInThread :  public QThread
{
    Q_OBJECT

public:
    VideoInThread(QObject *parent = 0);
    void OpenCaptureDevice(void);
    void setCamera(cameraDescription c);

    int acquire_fps;

signals:
    void videoinImageReady(QPixmap *, int fps);

public slots:
    void setCameraExposure(float exp_time);

protected:
    void run();

private:
    Camera *videoInCamera;
    cameraDescription camera_descr;
    float exposure_time=50; // initialize to 50 ms exposure
    CImgList<unsigned char> image_list;
    int num_buffers;
    QImage rgb_qi;
    QPixmap video_in_qp;

#ifdef USE_PYLON
    PylonClass baslerCamera;
#endif
#ifdef SPECKLE_USE_OPENCV
    OpenCVGrabber openCVCamera;
#endif

//private slots:
//    void processVideoInFrame(QVideoFrame);

};

#endif // VIDEOINTHREAD_H
