#ifndef PYLONACQUIREASYNC_H
#define PYLONACQUIREASYNC_H

#include <QObject>
#include <QThread>
#include "speckle_defines.h"
#include "imagegenerator.h"

#include <pylon/PylonIncludes.h>
using namespace Pylon;

#if defined ( PYLON_USE_GIGE )
// Settings to use Basler GigE cameras.

#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <pylon/gige/PylonGigEIncludes.h>
typedef Pylon::CBaslerGigEInstantCamera Camera_t;
using namespace Basler_GigECameraParams;
#elif defined ( PYLON_USE_USB3 )
// Settings to use Basler USB cameras.
#include <pylon/usb/BaslerUsbInstantCamera.h>
typedef Pylon::CBaslerUsbInstantCamera Camera_t;
using namespace Basler_UsbCameraParams;
#endif

#if defined ( PYLON_USE_UNIVERSAL )
#include <pylon/BaslerUniversalInstantCamera.h>
typedef Pylon::CBaslerUniversalInstantCamera Camera_t;
using namespace Basler_UniversalCameraParams;
#endif

class PylonAcquireAsync  : public ImageGenerator
{
    Q_OBJECT

public:
    PylonAcquireAsync(AcquisitionClass *acquisition);
    void initialize(Camera_t *camera, unsigned char **buf, QVector<float> *acq_t, int *Nacquired);

private:
    void run();
    Camera_t *pylonCamera;
};

#endif // PYLONACQUIREASYNC_H
