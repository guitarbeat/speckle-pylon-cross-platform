#include "pylonacquireasync.h"
#include <QDebug>
#include <vector>
#include <cstring>

/**************************************************************/
PylonAcquireAsync::PylonAcquireAsync(AcquisitionClass *acquisition)
    :ImageGenerator(acquisition)
{

}
/**************************************************************/
void PylonAcquireAsync::initialize(Camera_t *camera, unsigned char **buf,
                                   QVector<float> *acq_t, int *Nacquired)
{
    pylonCamera = camera;
    buffers = buf;
    acq_times = acq_t;
    img_acquired = Nacquired;
    *img_acquired = 0;

    height = static_cast<int>(pylonCamera->Height.GetValue());
    width = static_cast<int>(pylonCamera->Width.GetValue());

    PixelFormatEnums Format = pylonCamera->PixelFormat.GetValue();
    if(Format == PixelFormat_Mono8)
        color_planes=1;
    else
        color_planes=3;

    if(GenApi::IsAvailable(pylonCamera->AcquisitionMode))
        pylonCamera->AcquisitionMode.SetValue(AcquisitionMode_Continuous);
    if(GenApi::IsAvailable(pylonCamera->TriggerMode))
        pylonCamera->TriggerMode.SetValue(TriggerMode_Off);
    if(GenApi::IsAvailable(pylonCamera->AcquisitionFrameRateEnable))
        pylonCamera->AcquisitionFrameRateEnable.SetValue(false);

}
/**************************************************************/
void PylonAcquireAsync::run()
{
    pylonCamera->StartGrabbing();

    acquisition->startTimer();
    keep_going = true;
    CGrabResultPtr ptrGrabResult;
    while(pylonCamera->IsGrabbing() && keep_going)
    {
        // Get Image - Timeout needs to accomodate hardware triggering intervals
        pylonCamera->RetrieveResult(10000, ptrGrabResult, TimeoutHandling_ThrowException);

        if (ptrGrabResult->GrabSucceeded())
        {
            memcpy(buffers[*img_acquired % MAX_NUMBER_IMG_BUFFERS], ptrGrabResult->GetBuffer(),
                   static_cast<size_t>(height*width*color_planes));
            acq_times->append(acquisition->getTimeElapsed());

            if(color_planes>1)
            {
                unsigned char *dst = buffers[*img_acquired % MAX_NUMBER_IMG_BUFFERS];
                const size_t plane_size = static_cast<size_t>(width) * height;
                std::vector<unsigned char> tmp(dst, dst + plane_size * color_planes);
                for (size_t i = 0; i < plane_size; ++i)
                {
                    dst[i] = tmp[i * 3];
                    dst[plane_size + i] = tmp[i * 3 + 1];
                    dst[2 * plane_size + i] = tmp[i * 3 + 2];
                }
            }

            (*img_acquired)++;
            acquisition->img_acquired = *img_acquired;
            acquisition->updateFPS();
        }
        else
        {
            std::cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << std::endl;
        }

        if(acquisition->isFinished())
            keep_going = false;
    }

    pylonCamera->StopGrabbing();
}
/**************************************************************/
