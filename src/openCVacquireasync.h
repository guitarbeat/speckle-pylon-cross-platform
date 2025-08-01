#ifndef OPENCVACQUIREASYNC_H
#define OPENCVACQUIREASYNC_H

#include <QObject>
#include <QThread>
#include "speckle_defines.h"
#include "imagegenerator.h"

#ifdef SPECKLE_USE_OPENCV
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
using namespace cv;
#endif

class OpenCVAcquireAsync : public ImageGenerator
{
    Q_OBJECT

public:
    OpenCVAcquireAsync(AcquisitionClass *acquisition);
    void initialize(VideoCapture *camera, unsigned char **buf, QVector<float> *acq_t, int *Nacquired);

private:
    void run();
    VideoCapture *openCVCamera;

};

#endif // OPENCVACQUIREASYNC_H
