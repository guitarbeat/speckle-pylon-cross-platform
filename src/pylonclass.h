#ifndef PYLONCLASS_H
#define PYLONCLASS_H

#include <QObject>
#include <QElapsedTimer>
#include "camera.h"
#include <pylon/PylonIncludes.h>
using namespace Pylon;
#include "pylonacquireasync.h"

#ifdef USE_MESI
#include <numeric>
#endif

#if defined ( PYLON_USE_GIGE )
// Settings to use Basler GigE cameras.
#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <pylon/gige/PylonGigEIncludes.h>
using namespace Basler_GigECameraParams;
#elif defined ( PYLON_USE_USB3 )
// Settings to use Basler USB cameras.
#include <pylon/usb/BaslerUsbInstantCamera.h>
typedef Pylon::CBaslerUsbInstantCamera Camera_t;
using namespace Basler_UsbCameraParams;
#else
#error Camera type is not specified. For example, define USE_GIGE for using GigE cameras
#endif

#if defined ( PYLON_USE_UNIVERSAL )
#include <pylon/BaslerUniversalInstantCamera.h>
typedef Pylon::CBaslerUniversalInstantCamera Camera_t;
using namespace Basler_UniversalCameraParams;
#endif

#include "speckle_defines.h"

#define NUM_GRAB_BUFFERS 100


class PylonClass : public Camera
{
    Q_OBJECT

public:
    PylonClass(int devNum=0);

    // pylon specific variables
    int min_width, min_height;
    int offsetX_inc, offsetY_inc, width_inc, height_inc;
    bool bayer_setting;

    //QPointer<PylonAcquireAsync> PylonAcquireAsyncThread;

    StreamBufferHandle handles[NUM_GRAB_BUFFERS];

    void SetCameraExposureTime(float exp_ms) override;
    void setAOI(int top, int left, int width, int height) override;
    void SetCameraTrigger(QString trigger_str) override;
    void acquireImagesAsync(void) override;
    int InitializeAcquisition(int Nframes);
    int initialize_acquisition(AcquisitionClass *acq, unsigned char **buffer_list, QVector<float> *acq_times) override;
    void acquireImages(int Nframes, unsigned char **images) override;
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
    QString getCameraInfo(void) override;
    void GetPixelFormats(QStringList *pix_list);
    void SetBitDepth(QString bit_depth_str);
    void stopAcquisition(void) override;
    bool isOpened(void) override;
    void openCamera(int dev=0) override;
    void cleanup(void) override;

signals:
    void postSpeckleMessage(QString);

private:
    Camera_t pylonCamera;
    ITransportLayer *pTl;
    DeviceInfoList_t devices;
    int deviceNumber;

    bool initializePylon(void);
    void setupCamera(void);
    void setCameraAOI(void);
    QPointer<PylonAcquireAsync> ImgAcquireThread;

    int64_t Adjust(int64_t val, int64_t minimum, int64_t maximum, int64_t inc);

};

#endif // PYLONCLASS_H
