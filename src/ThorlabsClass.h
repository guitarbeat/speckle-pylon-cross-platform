#ifndef THORLABSCLASS_H
#define THORLABSCLASS_H

#include <QObject>
#include <QElapsedTimer>
#include "tl_camera_sdk.h"
#include "tl_camera_sdk_load.h"

#ifdef USE_MESI
#include <numeric>
#endif


#include "CImg.h"
using namespace cimg_library;

#include "speckle_defines.h"

#define NUM_GRAB_BUFFERS 100


class ThorlabsClass : public QObject {

    Q_OBJECT

public:
    explicit ThorlabsClass(QObject *parent = 0);

    unsigned short *im_w, *im_h;
    unsigned short *top, *left;
    unsigned short *max_width, *max_height, min_width, min_height;
    unsigned short offsetX_inc, offsetY_inc, width_inc, height_inc;
    unsigned short *bit_depth;
    int bytes_pixel;
    int *color_planes;
    unsigned short *camera_type;
    float *exp_time;
    QString *camera_name, *camera_description;
    bool bayer_setting;

    //int num_grab_buffers;
   // CImgList<unsigned char> buffer_list;
    //const int num_grab_buffers = 10;

    int initialize(unsigned short *width, unsigned short *height,
                   unsigned short *top, unsigned short *left, float *exposure_time,
                   unsigned short *max_w, unsigned short *max_h, unsigned short *bits_per_pixel,
                    QString *name, QString *descr, unsigned short *cam_type, int *color_planes);
    void SetExposureTime(float exp_ms);
    void SetAOI(unsigned short top, unsigned short left,
                unsigned short width, unsigned short height);
    void SetTrigger(QString trigger_str);
    int InitializeAcquisition(int Nframes);
    void AcquireImages(int Nframes, long *img_acquired,
                       unsigned char **raw_images,
                       float *acquisition_times,
                       int write_mode, int acquire_flag, QElapsedTimer *timer);
#ifdef USE_MESI
    bool CalibrateExposures(unsigned char **raw_mesi_calib_images,
                                   float *acquisition_times,
                                   QVector<int> exposures,
                                   QVector<float> AOMvoltages);
#endif
    /*void CalibrateExposures(unsigned char **raw_mesi_calib_images,
                                   float *acquisition_times,
                                   QVector<int> exposures,
                                   QVector<float> AOMvoltages;
                                   QElapsedTimer *timer);*/
    void finish_acquisition(void);
    void GetPixelFormats(QStringList *pix_list);
    void SetBitDepth(QString bit_depth_str);

signals:
    void postSpeckleMessage(QString);

private:
    void *camera_handle;
    char camera_ids[1024];

    int ThorlabsClass::close_sdk_dll(void);

};

#endif // THORLABSCLASS_H
