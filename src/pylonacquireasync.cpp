#include "pylonacquireasync.h"
#include <QDebug>

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
    CImg<unsigned char> tmp_image;

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
                // re-order pixels in CImg format (not interleaved)
                tmp_image.assign(buffers[*img_acquired % MAX_NUMBER_IMG_BUFFERS],3, width, height, 1);
                tmp_image.permute_axes("yzcx");
                memcpy((void *)(buffers[*img_acquired % MAX_NUMBER_IMG_BUFFERS]), tmp_image.data(), width*height*color_planes);
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
