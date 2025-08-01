#ifndef FRAMEGRABBERCLASS_H
#define FRAMEGRABBERCLASS_H

#include <QObject>
#include <QElapsedTimer>

#include "CImg.h"

#ifdef SPECKLE_USE_OPENCV
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
using namespace cv;
#endif

#include "speckle_defines.h"

class FrameGrabberClass : public QObject
{
    Q_OBJECT
public:
    explicit FrameGrabberClass(QObject *parent = 0);

    unsigned short *im_w, *im_h;
    unsigned short *top, *left;
    unsigned short *max_width, *max_height;
    unsigned short *bit_depth;
    int *color_planes;
    unsigned short *cam_type;
    float *exp_time;
    QString *camera_name, *camera_description;

    cv::VideoCapture capture_device;
    int video_in_device_number;

    int initialize(unsigned short *width, unsigned short *height,
                   unsigned short *top, unsigned short *left, float *exposure_time,
                   unsigned short *max_w, unsigned short *max_h, unsigned short *bits_per_pixel,
                    QString *name, QString *descr, unsigned short *cam_type, int *color_planes);
    void SetExposureTime(float exp_ms);
    void SetAOI(unsigned short AOI_top, unsigned short AOI_left,
                unsigned short AOI_width, unsigned short AOI_height);
    void SetTrigger(QString trigger_str);
    int InitializeAcquisition(int Nframes);
    void AcquireImages(int Nframes, long *img_acquired,
                       unsigned char **raw_images,
                       float *acquisition_times,
                       int write_mode, int acquire_flag, QElapsedTimer *timer);
    void finish_acquisition(void);
    void GetPixelFormats(QStringList *pix_list);
    void SetBitDepth(QString bit_depth_str);
    void SetDeviceNumber(int);

signals:
        void postSpeckleMessage(QString);

public slots:

private:


};

#endif // FrameGrabberCLASS_H
