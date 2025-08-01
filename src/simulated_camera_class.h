#ifndef SIMULATEDCAMERACLASS_H
#define SIMULATEDCAMERACLASS_H

#include <QObject>
#include <QElapsedTimer>

#include "CImg.h"

#include "speckle_defines.h"

class SimulatedCameraClass : public QObject
{
    Q_OBJECT
public:
    explicit SimulatedCameraClass(QObject *parent = 0);

    unsigned short *im_w, *im_h;
    unsigned short *top, *left;
    unsigned short *max_width, *max_height;
    unsigned short *bit_depth;
    int *color_planes;
    unsigned short *cam_type;
    float *exp_time;
    QString *camera_name, *camera_description;

    int initialize(unsigned short *width, unsigned short *height,
                   unsigned short *top, unsigned short *left, float *exposure_time,
                   unsigned short *max_w, unsigned short *max_h, unsigned short *bits_per_pixel,
                    QString *name, QString *descr, unsigned short *cam_type, int *color_planes);
    void SetExposureTime(float exp_ms);
    void SetTrigger(QString trigger_str);
    int InitializeAcquisition(int Nframes);
    void AcquireImages(int Nframes, long *img_acquired,
                       unsigned char **raw_images,
                       float *acquisition_times,
                       int write_mode, int acquire_flag, QElapsedTimer *timer);
    void finish_acquisition(void);
    void GetPixelFormats(QStringList *pix_list);
    void SetBitDepth(QString bit_depth_str);

signals:
        void postSpeckleMessage(QString);

public slots:

private:


};

#endif // SIMULATEDCAMERACLASS_H
