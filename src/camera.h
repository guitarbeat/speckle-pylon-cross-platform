#ifndef CAMERACLASS_H
#define CAMERACLASS_H

#include <QObject>
#include <QString>
#include <QList>
#include <QDebug>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "cameradescription.h"

#define CAMERA_NONE 0
#define CAMERA_PYLON 1
#define CAMERA_NIIMAQDX 2
#define CAMERA_NI 3
#define CAMERA_FRAMEGRABBER 4
#define CAMERA_THORLABS 5

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera();
    int initialize(unsigned short *width, unsigned short *height,
                            unsigned short *top, unsigned short *left, float *exposure_time,
                            unsigned short *max_w, unsigned short *max_h, unsigned short *bits_per_pixel,
                           QString *name, QString *descr, unsigned short *cam_type, int *color_depth);
    void SetExposureTime(float exp_ms);
    void SetAOI(unsigned short AOI_top, unsigned short AOI_left,
                        unsigned short AOI_width, unsigned short AOI_height);
    void SetTrigger(QString trigger_str);
    void SetBitDepth(QString bit_depth_str);
    int InitializeAcquisition(int Nframes);
    void AcquireImages(int Nframes, long *img_acquired,
                               unsigned char **raw_images,
                               float *acquisition_times,
                               int write_mode, int acquire_flag, QElapsedTimer *timer);
    void finish_acquisition(void);
    void GetPixelFormats(QStringList *pix_list);
    void SetDeviceNumber(int dev_num);

    unsigned short *im_w, *im_h, *im_top, *im_left;
    float *exp_time;
    unsigned short *max_width, *max_height;
    unsigned short *bit_depth;
    QString *camera_name, *camera_description;
    unsigned short *cam_type;
    int *color_planes;
    bool camera_specified;
    QString ip_address;

signals:
    void postSpeckleMessage(QString msg);

public slots:

private:

};

#endif // CAMERACLASS_H


