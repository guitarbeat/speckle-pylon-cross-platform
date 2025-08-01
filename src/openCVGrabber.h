#ifndef OPENCVGRABBERCLASS_H
#define OPENCVGRABBERCLASS_H

#include <QObject>
#include "camera.h"
#include "openCVacquireasync.h"

#include "CImg.h"
using namespace cimg_library;

#ifdef SPECKLE_USE_OPENCV
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
using namespace cv;
#endif

class OpenCVGrabber : public Camera
{
    Q_OBJECT

public:
    OpenCVGrabber(int devNum=0);

    bool isOpened(void) override;
    void openCamera(int devNum=0) override;
    void cleanup(void) override;
    void acquireImage(CImg<unsigned char> *img) override;
    int initialize_acquisition(AcquisitionClass *acq, unsigned char **buffer_list, QVector<float> *acq_times) override;
    void acquireImagesAsync(void) override;
    void stopAcquisition(void) override;
    QString getCameraInfo(void) override;

signals:

private:
    VideoCapture capture_device;
    int deviceNumber;
    QPointer<OpenCVAcquireAsync> ImgAcquireThread;

    void setupCamera(void);
    void setCameraAOI(void);
};

#endif // OPENCVGRABBERCLASS_H
