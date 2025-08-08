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

// Forward declare CImg types to avoid heavy include
namespace cimg_library {
    template<typename T> class CImg;
    template<typename T> class CImgList;
}
using cimg_library::CImg;
using cimg_library::CImgList;
#include "CImg.h"

#define CAMERA_NONE 0
#define CAMERA_PYLON 1
#define CAMERA_NIIMAQDX 2
#define CAMERA_NI 3
#define CAMERA_FRAMEGRABBER 4
#define CAMERA_THORLABS 5

class AcquisitionClass;
class ImageGenerator;

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera();

    // Base API (virtual so derived classes can override)
    virtual void openCamera(int devNum = 0);
    virtual void initialize(void);
    virtual bool isOpened(void);
    virtual void setAOI(int top, int left, int width, int height);
    virtual void SetCameraROI(void);
    virtual void SetCameraExposureTime(float exp_ms);
    virtual void SetCameraTrigger(QString trigger_str);
    virtual void SetBitDepth(unsigned short new_bit_depth);
    virtual void SetBitDepth(QString bit_depth_str);
    virtual void SetCameraGain(void);
    void setMaxNumBuffers(int n);

    virtual int initialize_acquisition(AcquisitionClass *acq, unsigned char **buffer_list, QVector<float> *acq_t);
    virtual void acquireImages(int Nframes);
    virtual void acquireImages(int Nframes, unsigned char **image_buffers);
    virtual void acquireImage(CImg<unsigned char> *img);
    virtual void acquireImages(CImgList<unsigned char> *img_list);
    virtual void acquireImagesAsync(void);
    virtual void stopAcquisition(void);
    virtual void cleanup(void);
    void acquireAsyncCompleted(void);

    void finish_acquisition(unsigned char *buf);
    void save_acquisition_timing(QString fname, float *acq_times, int N);
    virtual QString getCameraInfo(void);
    void GetPixelFormats(QStringList *pix_list);
    void SetBytesPerPixel();

    // Public state
    bool color_camera;
    int color_planes;
    QString camera_name, camera_description;
    int camera_type;

    int max_width, max_height;
    int top, left;
    int im_w, im_h;
    int bit_depth;
    int bytes_pixel;
    float exp_time;
    int num_live_buffers;

    int img_acquired;
    float acquire_fps;

    bool camera_specified;
    QString ip_address;

signals:
    void postSpeckleMessage(QString msg);
    void acquisitionFinished();

protected:
    int max_buffers;
    AcquisitionClass *acq_settings;
    unsigned char **buffers;
    QVector<float> *acq_times;
    ImageGenerator *ImgGeneratorThread;
};

#endif // CAMERACLASS_H


