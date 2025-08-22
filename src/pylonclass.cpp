#include <QDebug>
//#include <iostream>
//#include <string>
//#include <sstream>
//using namespace std;
#include "pylonclass.h"
//#include "camera.h"
#include <vector>
#include <cstring>

PylonClass::PylonClass(int devNumber)
{
    // note that members of Camera are defined initialized in the defaul Camera constructor which is called first
    deviceNumber=devNumber;
    //if(initializePylon())
    //    setupCamera();
    //else
    //    camera_type=CAMERA_NONE;
}
/*******************************************************/
bool PylonClass::initializePylon(void)
{
    // PylonInitialize() called in main

    if(CTlFactory::GetInstance().EnumerateDevices(devices) == 0) {
        qDebug() << "No Pylon devices found";
        return(false);
    } else {
#ifdef PYLON_USE_GIGE
        if(!(ip_address.isEmpty())) {
            CDeviceInfo di;
            di.SetIpAddress(String_t(ip_address.toUtf8()));
            pylonCamera.Attach((CTlFactory::GetInstance().CreateDevice(di)));
        } else {
#endif            
        CDeviceInfo info;
       // info.SetDeviceClass(Camera_t::DeviceClass()); // Match correct camera type in device list
        pylonCamera.Attach((CTlFactory::GetInstance().CreateDevice(devices[deviceNumber])));

#ifdef PYLON_USE_GIGE
        }
#endif
        pylonCamera.Open(); // This step is important since Attach doesn't automatically Open!!
    }

    if(pylonCamera.IsOpen())
        return(true);
    else
    {
        qDebug() << "Pylon device failed to open";
        return(false);
    }
}
/*******************************************************/
void PylonClass::openCamera(int devNum)
{
    deviceNumber=devNum;
    qDebug().nospace() << "Opening Pylon device (pylon/" << deviceNumber << ")";
    if(initializePylon())
        setupCamera();
}
/*******************************************************/
void PylonClass::cleanup(void)
{
    qDebug().nospace() << "Closing Pylon device (pylon/" << deviceNumber << ")";
    pylonCamera.Close();
}
/*******************************************************/
void PylonClass::setupCamera(void)
{
    camera_name = QString(pylonCamera.GetDeviceInfo().GetModelName());

    qDebug().noquote() << "Name:" << camera_name;
    qDebug() << "Serial Number:" << pylonCamera.GetDeviceInfo().GetSerialNumber() << "\n";

    // make sure top, left are set to 0 to get full chip size
    // Maximize the image area of interest (Image AOI).
    if (GenApi::IsWritable(pylonCamera.OffsetX))
        pylonCamera.OffsetX.SetValue(pylonCamera.OffsetX.GetMin());
    if (GenApi::IsWritable(pylonCamera.OffsetY))
        pylonCamera.OffsetY.SetValue(pylonCamera.OffsetY.GetMin());
    top=0;
    left=0;

    pylonCamera.Width.SetValue(pylonCamera.Width.GetMax());
    pylonCamera.Height.SetValue(pylonCamera.Height.GetMax());
    max_width = pylonCamera.Width.GetMax();
    max_height = pylonCamera.Height.GetMax();
    min_width = pylonCamera.Width.GetMin();
    min_height = pylonCamera.Height.GetMin();
    im_w = max_width;
    im_h = max_height;

    offsetX_inc = pylonCamera.OffsetX.GetInc();
    offsetY_inc = pylonCamera.OffsetY.GetInc();
    width_inc = pylonCamera.Width.GetInc();
    height_inc = pylonCamera.Height.GetInc();

    pylonCamera.ExposureAuto.SetValue(ExposureAuto_Off);
    pylonCamera.ExposureMode.SetValue(ExposureMode_Timed);

    //pylonCamera.PixelFormat.SetValue(PixelFormat_Mono8);
    PixelFormatEnums Format = pylonCamera.PixelFormat.GetValue();
    if(Format == PixelFormat_Mono8)
    {
        bit_depth = 8;
        SetBytesPerPixel();
        color_planes=1;
    }
    else
    {
#ifdef PYLON_USE_USB3
       pylonCamera.PixelFormat.SetValue(PixelFormat_RGB8);
#endif
        qDebug() << "Pixel format set to " << pylonCamera.PixelFormat.ToString();
        //pylonCamera.ExposureAuto.SetValue(ExposureAuto_Continuous);
        color_planes=3;
    }

#ifdef PYLON_USE_USB3
    if(color_planes==1)
        pylonCamera.ExposureTime.SetValue(5000);

    // Disable maximum bandwidth limit on USB connection
    if (GenApi::IsWritable(pylonCamera.DeviceLinkThroughputLimitMode))
        pylonCamera.DeviceLinkThroughputLimitMode.SetValue(DeviceLinkThroughputLimitMode_Off);
#else
    if(GenApi::IsAvailable(pylonCamera.ExposureTimeAbs))
        pylonCamera.ExposureTimeAbs.SetValue(5000);
#endif

    // Set Gain Raw All
    pylonCamera.GainAuto.SetValue(GainAuto_Off);
    pylonCamera.GainSelector.SetValue(GainSelector_All);
    // Override factory-set defaults to allow gain to be set to 0 for all cameras
#ifdef PYLON_USE_USB3
    pylonCamera.Gain.SetValue(0);
#else
    pylonCamera.ParameterSelector.SetValue(ParameterSelector_Gain);
    pylonCamera.RemoveLimits.SetValue(true);
    pylonCamera.GainRaw.SetValue(0);
#endif

#ifndef PYLON_USE_USB3
    // only do this for non-usb cameras
    //Check if the device supports multiple gain taps
    if(GenApi::IsAvailable(pylonCamera.GainSelector.GetEntry(GainSelector_Tap1)))
    {
        qDebug() << "Setting gain tap 1";
        pylonCamera.GainSelector.SetValue(GainSelector_Tap1);
        pylonCamera.GainRaw.SetValue(0);
        qDebug() << "Gain tap 1 set to " << pylonCamera.GainRaw.GetValue();
    }

    if(GenApi::IsAvailable(pylonCamera.GainSelector.GetEntry(GainSelector_Tap2)))
    {
        qDebug() << "Setting gain tap 2";
        pylonCamera.GainSelector.SetValue(GainSelector_Tap2);
        pylonCamera.GainRaw.SetValue(0);
        qDebug() << "Gain tap 2 set to " << pylonCamera.GainRaw.GetValue();
    }
#endif
#ifdef PYLON_USE_GIGE
    if(GenApi::IsAvailable(pylonCamera.GainSelector.GetEntry(GainSelector_Tap3)))
    {
        qDebug() << "Setting gain tap 3";
        pylonCamera.GainSelector.SetValue(GainSelector_Tap3);
        pylonCamera.GainRaw.SetValue(0);
        qDebug() << "Gain tap 3 set to " << pylonCamera.GainRaw.GetValue();
    }

    if(GenApi::IsAvailable(pylonCamera.GainSelector.GetEntry(GainSelector_Tap4)))
    {
        qDebug() << "Setting gain tap 4";
        pylonCamera.GainSelector.SetValue(GainSelector_Tap4);
        pylonCamera.GainRaw.SetValue(0);
        qDebug() << "Gain tap 4 set to " << pylonCamera.GainRaw.GetValue();
    }
#endif

    qDebug() << "Setting Black Level All";

    // Set Black Level Raw All
    // Black level is the average image value at no light intensity - set to 0
#ifdef PYLON_USE_USB3

    pylonCamera.BlackLevelSelector.SetValue(BlackLevelSelector_All);
    pylonCamera.BlackLevel.SetValue(0);
    qDebug() << "Black level all set to "<<pylonCamera.BlackLevel.GetValue();
#else
    pylonCamera.BlackLevelSelector.SetValue(BlackLevelSelector_All);
    pylonCamera.BlackLevelRaw.SetValue(0);
    //emit postSpeckleMessage(QString("Black level all set to %1").arg(Camera.BlackLevelRaw.GetValue()));

    //Check if the device supports multiple black level taps
    if(GenApi::IsAvailable(pylonCamera.BlackLevelSelector.GetEntry(BlackLevelSelector_Tap1)))
    {
        qDebug() << "Setting black level tap 1";
        pylonCamera.BlackLevelSelector.SetValue(BlackLevelSelector_Tap1);
        pylonCamera.BlackLevelRaw.SetValue(0);
        qDebug() << "Black level tap 1 set to "<< pylonCamera.BlackLevelRaw.GetValue();
    }

    if(GenApi::IsAvailable(pylonCamera.BlackLevelSelector.GetEntry(BlackLevelSelector_Tap2)))
    {
        qDebug() << "Setting black level tap 2";
        pylonCamera.BlackLevelSelector.SetValue(BlackLevelSelector_Tap2);
        pylonCamera.BlackLevelRaw.SetValue(0);
        qDebug() << "Black level tap 2 set to "<< pylonCamera.BlackLevelRaw.GetValue();
    }
#endif
#ifdef PYLON_USE_GIGE
    if(GenApi::IsAvailable(pylonCamera.BlackLevelSelector.GetEntry(BlackLevelSelector_Tap3)))
    {
        qDebug() << "Setting black level tap 3";
        pylonCamera.BlackLevelSelector.SetValue(BlackLevelSelector_Tap3);
        pylonCamera.BlackLevelRaw.SetValue(0);
        qDebug() << "Black level tap 3 set to "<< pylonCamera.BlackLevelRaw.GetValue();
    }

    if(GenApi::IsAvailable(pylonCamera.BlackLevelSelector.GetEntry(BlackLevelSelector_Tap4)))
    {
        qDebug() << "Setting black level tap 4";
        pylonCamera.BlackLevelSelector.SetValue(BlackLevelSelector_Tap4);
        pylonCamera.BlackLevelRaw.SetValue(0);
        qDebug() << "Black level tap 4 set to "<<pylonCamera.BlackLevelRaw.GetValue();
    }
#endif

    camera_type=CAMERA_PYLON;

#ifdef PYLON_USE_USB3
    if(color_planes==1) // need to fix this
    {
        try {
            qDebug() << "Enabling camera exposure active output on Line 3";
            pylonCamera.LineSelector.SetValue(LineSelector_Line3);
            LineSelectorEnums LineSelectorValue = pylonCamera.LineSelector.GetValue();
            if (LineSelectorValue == LineSelector_Line3)
                qDebug() << "Line Selector: Line 3";

            pylonCamera.LineMode.SetValue(LineMode_Output);
            LineModeEnums LineModeValue = pylonCamera.LineMode.GetValue();
            if (LineModeValue == LineMode_Output)
                qDebug() << "Line Mode: Output";

            pylonCamera.LineSource.SetValue(LineSource_ExposureActive);
            LineSourceEnums LineSourceValue = pylonCamera.LineSource.GetValue();
            if (LineSourceValue == LineSource_ExposureActive)
                qDebug() << "Line Source: Exposure Active";

            pylonCamera.LineInverter.SetValue(true);
            if (pylonCamera.LineInverter.GetValue())
                qDebug() << "Line Inverter: On";

            qDebug() << "Setting camera trigger input to Line 4";
            pylonCamera.LineSelector.SetValue(LineSelector_Line4);
            LineSelectorValue = pylonCamera.LineSelector.GetValue();
            if (LineSelectorValue == LineSelector_Line4)
                qDebug() << "Line Selector: Line 4";

            pylonCamera.LineMode.SetValue(LineMode_Input);
            LineModeValue = pylonCamera.LineMode.GetValue();
            if (LineModeValue == LineMode_Input)
                qDebug() << "Line Mode: Input";

            pylonCamera.LineInverter.SetValue(false);
            if (!pylonCamera.LineInverter.GetValue())
                qDebug() << "Line Inverter: Off";

        } catch(...) {
            qDebug() << "Error setting camera digital I/O";
        }
    }

#elif PYLON_USE_GIGE

    try {

        qDebug() << "Setting camera trigger input to Line 1";
        pylonCamera.LineSelector.SetValue(LineSelector_Line1);
        pylonCamera.LineInverter.SetValue(false);

        qDebug() << "Enabling camera exposure active on Out1";
        pylonCamera.LineSelector.SetValue(LineSelector_Out1);
        pylonCamera.LineSource.SetValue(LineSource_ExposureActive);
        pylonCamera.LineInverter.SetValue(true);

    } catch(...) {
        qDebug() << "Error setting camera digital I/O";
    }

#endif

}
/***************************************************************************/
void PylonClass::GetPixelFormats(QStringList *pix_list)
{

    pix_list->clear();
    qDebug() << "GetPixelFormats not implemented yet";

}
/***************************************************************************/
QString PylonClass::getCameraInfo(void)
{
    QString vendor = QString(pylonCamera.GetDeviceInfo().GetVendorName());
    QString serial = QString(pylonCamera.GetDeviceInfo().GetSerialNumber());
    QString pixel_format = QString(pylonCamera.PixelFormat.ToString());

    QString msg;
    msg += QString("<table cellpadding=5>");
    msg += QString("<tr><td><b>Device</b></td><td>pylon/%1</td></tr>").arg(deviceNumber);
    msg += QString("<tr><td><b>Camera Name</b></td><td>%1 %2</td></tr>").arg(vendor).arg(camera_name);
    msg += QString("<tr><td><b>Serial Number</b></td><td>%1</td></tr>").arg(serial);
    msg += QString("<tr><td><b>Resolution</b></td><td>%1x%2</td></tr>").arg(im_w).arg(im_h);
    msg += QString("<tr><td><b>Max Resolution</b></td><td>%1x%2</td></tr>").arg(max_width).arg(max_height);
    msg += QString("<tr><td><b>Pixel Format</b></td><td>%1</td></tr>").arg(pixel_format);

#ifdef PYLON_USE_USB3
    QString guid = QString(pylonCamera.GetDeviceInfo().GetDeviceGUID());
    msg += QString("<tr><td><b>GUID</b></td><td>%1</td></tr>").arg(guid);
    msg += QString("<tr><td><b>Exposure Active</b></td><td>Pin 1</td></tr>");
    msg += QString("<tr><td><b>Trigger Input</b></td><td>Pin 3</td></tr>");
#endif

#ifdef PYLON_USE_GIGE
    QString ip_address = QString(pylonCamera.GetDeviceInfo().GetAddress());
    QString mac_address = QString(pylonCamera.GetDeviceInfo().GetMacAddress());
    msg += QString("<tr><td><b>IP Address</b></td><td>%1</td></tr>").arg(ip_address);
    msg += QString("<tr><td><b>MAC Address</b></td><td>%1</td></tr>").arg(mac_address);
#endif

    msg += QString("<tr><td><b>Driver</b></td><td>Pylon v%1</td></tr>").arg(Pylon::GetPylonVersionString());
    msg += QString("</table>");
    return msg;
}
/***************************************************************************/
bool PylonClass::isOpened(void)
{
    return(pylonCamera.IsOpen());
}
/***************************************************************************/
void PylonClass::acquireImages(int Nframes, unsigned char **image_buffers)
{
    // acquired Nframes into image_buffers.
    // this call is blocking
    if(!(pylonCamera.IsGrabbing()))
        pylonCamera.StartGrabbing();

    CGrabResultPtr ptrGrabResult;
    for(int i=0;i<Nframes; i++)
    {
        // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
        pylonCamera.RetrieveResult( 5000, ptrGrabResult, TimeoutHandling_ThrowException);
        if (ptrGrabResult->GrabSucceeded())
        {
            const uint8_t *pImageBuffer = (uint8_t *) ptrGrabResult->GetBuffer();
            memcpy((void *)(image_buffers[i]), pImageBuffer, im_w*im_h*color_planes);
            if(ptrGrabResult->GetPixelType() == Pylon::PixelType_RGB8packed)
            {
                unsigned char *dst = image_buffers[i];
                const size_t plane_size = static_cast<size_t>(im_w) * im_h;
                std::vector<unsigned char> tmp(dst, dst + plane_size * color_planes);
                for (size_t j = 0; j < plane_size; ++j)
                {
                    dst[j] = tmp[j * 3];
                    dst[plane_size + j] = tmp[j * 3 + 1];
                    dst[2 * plane_size + j] = tmp[j * 3 + 2];
                }
            }
        }
        img_acquired++;
    }
}
/*******************************************************/
void PylonClass::SetBitDepth(QString bit_depth_str)
{
    if(camera_type!=CAMERA_PYLON)
        return;

    if(bit_depth_str.contains("Mono8",Qt::CaseInsensitive))
    {        
        pylonCamera.PixelFormat.SetValue(PixelFormat_Mono8);
        if(pylonCamera.PixelFormat.GetValue() == PixelFormat_Mono8)
        {
            bit_depth=8;
            color_planes=1;
            bayer_setting = false;
            qDebug() << "pixel format set to mono8";
        }
        else
            qDebug() << "error setting pixel format";
    }
    if(bit_depth_str.contains("BayerBG8",Qt::CaseInsensitive))
    {
        pylonCamera.PixelFormat.SetValue(PixelFormat_BayerBG8);
        if(pylonCamera.PixelFormat.GetValue() == PixelFormat_BayerBG8)
        {
            bit_depth=8;
            color_planes=1;
            bayer_setting = true;
            qDebug() << "pixel format set to BayerBG8";
        }
        else
            qDebug() << "error setting pixel format";
    }
}
/*******************************************************/
void PylonClass::SetCameraExposureTime(float exp_ms)
{
    exp_time=exp_ms;

    try {
#ifdef PYLON_USE_USB3
        pylonCamera.ExposureTime.SetValue(exp_ms*1000);
        qDebug() <<"camera exposure time is " << pylonCamera.ExposureTime.GetValue();
#else
        pylonCamera.ExposureTimeAbs.SetValue(exp_ms*1000);
        qDebug() << "camera exposure time is " << pylonCamera.ExposureTimeAbs.GetValue();
 #endif
    }
    catch ( GenICam::GenericException& e)
    {
      qDebug() << "Failed to set the exposure time. Reason: "<< e.GetDescription();
    }

}
/*******************************************************/
void PylonClass::setAOI(int t, int l, int w, int h) {

    top=t;
    left=l;
    im_w=w;
    im_h=h;
    // send current AOI settings to camera
    setCameraAOI();
}
/*******************************************************/
void PylonClass::setCameraAOI(void) {

    qDebug() << QString("Attempting to set Camera AOI to (top = %1, left = %2, width = %3, height = %4)")
                .arg(top).arg(left).arg(im_w).arg(im_h);

    // from ParameterizeCamera_NativeParameterAccess.cpp example. Will be simpler when switch to UniversalCamera
    if (IsWritable(pylonCamera.OffsetX))
        pylonCamera.OffsetX.SetValue(pylonCamera.OffsetX.GetMin());
    if (IsWritable(pylonCamera.OffsetY))
        pylonCamera.OffsetY.SetValue(pylonCamera.OffsetY.GetMin());

    // Some properties have restrictions. Use GetInc/GetMin/GetMax to make sure you set a valid value.
    int64_t newWidth = im_w;
    newWidth = Adjust(newWidth, pylonCamera.Width.GetMin(), pylonCamera.Width.GetMax(), pylonCamera.Width.GetInc());
    int64_t newHeight = im_h;
    newHeight = Adjust(newHeight, pylonCamera.Height.GetMin(), pylonCamera.Height.GetMax(), pylonCamera.Height.GetInc());
    pylonCamera.Width.SetValue(newWidth);
    pylonCamera.Height.SetValue(newHeight);

    if (IsWritable(pylonCamera.OffsetX))
    {
        int64_t newLeft = left;
        newLeft = Adjust(newLeft, pylonCamera.OffsetX.GetMin(), pylonCamera.OffsetX.GetMax(), pylonCamera.OffsetX.GetInc());
        pylonCamera.OffsetX.SetValue(newLeft);
    }

    if (IsWritable(pylonCamera.OffsetY))
    {
        int64_t newTop = top;
        newTop = Adjust(newTop, pylonCamera.OffsetY.GetMin(), pylonCamera.OffsetY.GetMax(), pylonCamera.OffsetY.GetInc());
        pylonCamera.OffsetY.SetValue(newTop);
    }

    im_w = pylonCamera.Width.GetValue();
    im_h = pylonCamera.Height.GetValue();
    top = pylonCamera.OffsetY.GetValue();
    left = pylonCamera.OffsetX.GetValue();

    qDebug() << QString("Set Camera AOI (top = %1, left = %2, width = %3, height = %4)")
                            .arg(pylonCamera.OffsetY.GetValue()).arg(pylonCamera.OffsetX.GetValue())
                            .arg(pylonCamera.Width.GetValue()).arg(pylonCamera.Height.GetValue());
}

/*******************************************************/
void PylonClass::SetCameraTrigger(QString trigger_str) {

    if(camera_type!=CAMERA_PYLON)
        return;

    // disable triggering of color cameras for now. Fix later
    if(color_planes>1)
    {
        qDebug() << "disabling trigger on color cameras for now..";
        return;
    }

#ifdef PYLON_USE_USB3

    pylonCamera.AcquisitionMode.SetValue(AcquisitionMode_Continuous);
    pylonCamera.AcquisitionFrameRateEnable.SetValue(false);

    if (GenApi::IsWritable(pylonCamera.TriggerDelay))
        pylonCamera.TriggerDelay.SetValue(0);

    if(trigger_str == "Frame Trigger") {

        pylonCamera.TriggerMode.SetValue(TriggerMode_Off);
        pylonCamera.TriggerSelector.SetValue(TriggerSelector_FrameStart);
        pylonCamera.TriggerMode.SetValue(TriggerMode_On);
        pylonCamera.TriggerSource.SetValue(TriggerSource_Line4);
        pylonCamera.TriggerActivation.SetValue(TriggerActivation_RisingEdge);
        pylonCamera.ExposureMode.SetValue(ExposureMode_Timed);
        qDebug() << "Enabled single frame fixed exposure triggering";

    } else if(trigger_str == "Exposure Width") {

        pylonCamera.TriggerSelector.SetValue(TriggerSelector_FrameBurstStart);
        pylonCamera.TriggerMode.SetValue(TriggerMode_Off);
        pylonCamera.TriggerSelector.SetValue(TriggerSelector_FrameStart);
        pylonCamera.TriggerMode.SetValue(TriggerMode_On);
        pylonCamera.TriggerSource.SetValue(TriggerSource_Line4);
        pylonCamera.TriggerActivation.SetValue(TriggerActivation_RisingEdge);
        pylonCamera.ExposureMode.SetValue(ExposureMode_TriggerWidth);
        qDebug() <<"Enabled exposure width triggering";

    } else {

        pylonCamera.TriggerSelector.SetValue(TriggerSelector_FrameBurstStart);
        pylonCamera.TriggerMode.SetValue(TriggerMode_Off);
        pylonCamera.TriggerSelector.SetValue(TriggerSelector_FrameStart);
        pylonCamera.TriggerMode.SetValue(TriggerMode_Off);
        pylonCamera.ExposureMode.SetValue(ExposureMode_Timed);
        qDebug() << "Camera trigger disabled";

    }


#elif PYLON_USE_GIGE

    if(trigger_str == "Frame Trigger") {

        pylonCamera.AcquisitionMode.SetValue(AcquisitionMode_Continuous);
        pylonCamera.TriggerSelector.SetValue(TriggerSelector_FrameStart);
        pylonCamera.TriggerMode.SetValue(TriggerMode_On);
        pylonCamera.TriggerSource.SetValue (TriggerSource_Line1);
        pylonCamera.TriggerActivation.SetValue(TriggerActivation_RisingEdge);
        pylonCamera.AcquisitionFrameRateEnable.SetValue(false);
        pylonCamera.ExposureMode.SetValue(ExposureMode_Timed);
        qDebug() <<QString("Enabled single frame fixed exposure triggering");

    } else if(trigger_str == "Sequence Trigger") {

        qDebug() <<QString("Sequence triggering is not supported by GigE Pylon cameras");

    } else if(trigger_str == "Exposure Width") {

        try {

            pylonCamera.AcquisitionMode.SetValue(AcquisitionMode_Continuous);
            pylonCamera.TriggerSelector.SetValue(TriggerSelector_FrameStart);
            pylonCamera.TriggerMode.SetValue(TriggerMode_On);
            pylonCamera.TriggerSource.SetValue (TriggerSource_Line1);
            pylonCamera.TriggerActivation.SetValue(TriggerActivation_RisingEdge);
            pylonCamera.ExposureMode.SetValue(ExposureMode_TriggerWidth);
            pylonCamera.AcquisitionFrameRateEnable.SetValue(false);
            pylonCamera.ExposureOverlapTimeMaxAbs.SetValue(10);
            qDebug() <<QString("Enabled exposure width triggering");

        } catch(...) {
            qDebug() <<QString("%1 does not support exposure width triggering").arg(QString(pylonCamera.GetDeviceInfo().GetModelName()));
        }

    } else {

        pylonCamera.AcquisitionMode.SetValue(AcquisitionMode_Continuous);
        pylonCamera.TriggerSelector.SetValue(TriggerSelector_AcquisitionStart);
        pylonCamera.TriggerMode.SetValue(TriggerMode_Off);
        pylonCamera.TriggerSelector.SetValue(TriggerSelector_FrameStart);
        pylonCamera.TriggerMode.SetValue(TriggerMode_Off);
        pylonCamera.AcquisitionFrameRateEnable.SetValue(false);
        pylonCamera.ExposureMode.SetValue(ExposureMode_Timed);
        qDebug() <<QString("Camera trigger disabled");

    }

#endif

}
/*******************************************************/
void PylonClass::acquireImagesAsync(void)
{
    ImgAcquireThread = new PylonAcquireAsync(acq_settings);
    ImgAcquireThread->initialize(&pylonCamera, buffers, acq_times, &img_acquired);
    connect(ImgAcquireThread, &PylonAcquireAsync::finished,
            this, &Camera::acquireAsyncCompleted);
    ImgAcquireThread->start();
}
/***************************************************************************/
void PylonClass::stopAcquisition(void)
{
    if(ImgAcquireThread)
    {
        ImgAcquireThread->stopAcquisition();
        ImgAcquireThread->wait();
        delete ImgAcquireThread;
    }
}
/***************************************************************************/
int PylonClass::initialize_acquisition(AcquisitionClass *acq, unsigned char **buffer_list,
                                       QVector<float> *acq_t)
{
    SetCameraExposureTime(exp_time);
    setCameraAOI();
    img_acquired=0;
    buffers=buffer_list;
    acq_times = acq_t;
    acq_settings = acq;
    acquire_fps = 0;

    //Camera::initialize_acquisition(acq, buffer_list, acq_t);
    return(1);
}
/***************************************************************************/
// Adjust value so it complies with range and increment passed.
//
// The parameter's minimum and maximum are always considered as valid values.
// If the increment is larger than one, the returned value will be: min + (n * inc).
// If the value doesn't meet these criteria, it will be rounded down so that it does.
int64_t PylonClass::Adjust(int64_t val, int64_t minimum, int64_t maximum, int64_t inc)
{
    // Check the input parameters.
    if (inc <= 0)
    {
        // Negative increments are invalid.
        throw LOGICAL_ERROR_EXCEPTION("Unexpected increment %d", inc);
    }
    if (minimum > maximum)
    {
        // Minimum must not be bigger than or equal to the maximum.
        throw LOGICAL_ERROR_EXCEPTION("minimum bigger than maximum.");
    }

    // Check the lower bound.
    if (val < minimum)
    {
        return minimum;
    }

    // Check the upper bound.
    if (val > maximum)
    {
        return maximum;
    }

    // Check the increment.
    if (inc == 1)
    {
        // Special case: all values are valid.
        return val;
    }
    else
    {
        // The value must be min + (n * inc).
        // Due to the integer division, the value will be rounded down.
        return minimum + ( ((val - minimum) / inc) * inc );
    }
}
/*******************************************************/
int PylonClass::InitializeAcquisition(int Nframes) {
    int i;

    // this function should not be necessary

    pylonCamera.MaxNumBuffer=NUM_GRAB_BUFFERS;

#ifdef PYLON_USE_USB3
    // Define the number of frames to collect per frame burst
    if(pylonCamera.TriggerSelector.GetValue() == TriggerSelector_FrameBurstStart)
        pylonCamera.AcquisitionBurstFrameCount.SetValue(Nframes);
#endif

#ifdef NO
    emit postSpeckleMessage(QString("initializing pylon acquisition"));
    //Set acquisition mode
    //Camera.AcquisitionMode.SetValue(AcquisitionMode_MultiFrame);
    Camera.AcquisitionMode.SetValue(AcquisitionMode_Continuous);

    if(!(StreamGrabber.IsAttached()))
        StreamGrabber.Attach(Camera.GetStreamGrabber(0));
    // First open the stream grabber
    StreamGrabber.Open();
    // Set the maximum buffer size according to the amount of data
    // the camera will send
    StreamGrabber.MaxBufferSize = Camera.PayloadSize();
    // We are going to use 10 buffers
    const int bufferSize = (int) Camera.PayloadSize();

    StreamGrabber.MaxNumBuffer = NUM_GRAB_BUFFERS;
    StreamGrabber.PrepareGrab();

    // allocate the acquisition buffers
    buffer_list.clear();
    buffer_list.insert(NUM_GRAB_BUFFERS);
    for(i=0;i<NUM_GRAB_BUFFERS;i++)
        buffer_list[i].resize(*im_w, *im_h);

    MyContext context[NUM_GRAB_BUFFERS];

    for ( i = 0; i < NUM_GRAB_BUFFERS; ++i )
    {
           handles[i] = StreamGrabber.RegisterBuffer( buffer_list[i].data(), bufferSize);
           StreamGrabber.QueueBuffer( handles[i], &context[i] );
    }
#endif
    emit postSpeckleMessage(QString("initialization complete"));

    return(1);
}


/***************************************************************************/
void PylonClass::AcquireImages(int Nframes, long *img_acquired,
                               unsigned char **raw_images,
                               float *acquisition_times,
                               int write_mode, int acquire_flag,
                               QElapsedTimer *timer)
{
    int ista;
    if((write_mode == WRITE_CONTINUOUS) && (acquire_flag==ACQUISITION_MODE))
        ista=*img_acquired;
    else
        ista=0;

    // Start image acquisition
   // qDebug() << "Trigger State AA: " << Camera.TriggerMode.GetValue() << " at beginnin of acq";
    if (pylonCamera.TriggerMode.GetValue()){// Added by SK 5/19/15
       // qDebug() << "Trigger State BB" << Camera.TriggerMode.GetValue() << " at beginnin of acq";
#ifdef PYLON_USE_USB3
        pylonCamera.AcquisitionStart.Execute();   // Added by SK 5/19/15
#endif
    }
   // qDebug() << "Trigger State CC" << Camera.TriggerMode.GetValue() << " at beginnin of acq";

    pylonCamera.StartGrabbing(Nframes);

    CGrabResultPtr ptrGrabResult;
    int num_timeouts=0;
    int i=0;
   // QTime t;
   // t.start();
     while ( pylonCamera.IsGrabbing())
     {
        // Wait for the grabbed image and then retrieve it. A timeout of 5000 ms is used.
         pylonCamera.RetrieveResult( 100000, ptrGrabResult, TimeoutHandling_ThrowException);
         // Image grabbed successfully?
         if (ptrGrabResult->GrabSucceeded())
         {           
             // Grabbing was successful. Process the image.
                memcpy(raw_images[i+ista], ptrGrabResult->GetBuffer(),(im_w)*(im_h));
                *img_acquired += 1;
                acquisition_times[*img_acquired-1]=(float)(timer->elapsed());
                i++;
        }
         else
         {
            emit postSpeckleMessage(QString("Grab failed with error code %1 and description %2").arg(int(ptrGrabResult->GetErrorCode())).arg(QString(ptrGrabResult->GetErrorDescription())));
        }
    }
     //emit postSpeckleMessage(QString("approx acquisition frame rate=%1 fps").arg(Nframes*1000/(t.elapsed())));

    // The camera is in continuous mode, stop image acquisition
    //Camera.AcquisitionStop.Execute();
  //   qDebug() << "Trigger State " << Camera.TriggerMode.GetValue() << " at end of acq";
#ifdef PYLON_USE_USB3
    if (pylonCamera.TriggerMode.GetValue())// Added by SK 5/19/15
               pylonCamera.AcquisitionStop.Execute();   // Added by SK 5/19/15
#endif

    // Flush the input queue, grabbing may have failed
    //StreamGrabber.CancelGrab();

}
/***************************************************************************/
/***************************************************************************/
#ifdef NO
bool PylonClass::CalibrateExposures(unsigned char **raw_mesi_calib_images,
                               float *acquisition_times,
                               QVector<int> exposures,
                               QVector<float> AOMvoltages)
{
    int nImages_to_grab=exposures.size();
    bool Calibration_Successful=false;
    // Start image acquisition
    qDebug() << "Trigger State AA: " << Camera.TriggerMode.GetValue() << " at beginnin of acq";
    if (Camera.TriggerMode.GetValue()){// Added by SK 5/19/15
        qDebug() << "Trigger State BB" << Camera.TriggerMode.GetValue() << " at beginnin of acq";
#ifdef PYLON_USE_USB3
        Camera.AcquisitionStart.Execute();   // Added by SK 5/19/15
#endif
    }
    qDebug() << "Trigger State CC" << Camera.TriggerMode.GetValue() << " at beginnin of acq";
    //Grab One Frame at a time
    Camera.StartGrabbing(GrabStrategy_OneByOne);
            double ReadouTime=Camera.ReadoutTimeAbs.GetValue();
    double TrigDelay=45; //Camera dependent value
    double WaitTime=ReadouTime+TrigDelay;

    CGrabResultPtr ptrGrabResult;
    int num_timeouts=0;
    int i=0;
   // QTime t;

    //for (int i=0; i<nImages_to_grab; ++i) {
    int i=0;
    QTime dieTime=QTime::currentTime();
    QVector<unsigned char> sum_pixels;
    do{
        AOMout->stopDAQmxTask();
        //t.start();
        AOMout->set_AOM_Output_Voltage(AOMvoltage[i]);
#ifdef PYLON_USE_USB3
        Camera.ExposureTime.SetValue(exposures[i]);
#else
        Camera.ExposureTimeAbs.SetValue(exposures[i]);
        #endif

          if ( Camera.WaitForFrameTriggerReady( 200, TimeoutHandling_ThrowException))
            {
               Camera.ExecuteSoftwareTrigger();
           }
         // Wait for the grabbed image and then retrieve it. A timeout of 5000 ms is used.
         Camera.RetrieveResult( 100000, ptrGrabResult, TimeoutHandling_ThrowException);
         // Image grabbed successfully?
         if (ptrGrabResult->GrabSucceeded())
         {
             // Grabbing was successful. Process the image.
                memcpy(raw_mesi_calib_images[i+ista], ptrGrabResult->GetBuffer(),(*im_w)*(*im_h));
                  sum_pixels[i]=std::accumulate(raw_mesi_calib_images[i].begin(),raw_mesi_calib_images[i].end(),0);

             //   acquisition_times[*img_acquired-1]=(float)(timer->elapsed());

        }
         else
         {
            emit postSpeckleMessage(QString("Grab failed with error code %1 and description %2").arg(QString(ptrGrabResult->GetErrorCode())).arg(QString(ptrGrabResult->GetErrorDescription())));
        }

         dieTime = QTime::currentTime().addMSecs((exposures[i]+WaitTime)/1000 );
        i++;
    }while((i<=nImages_to_grab) && (QTime::currentTime() > dieTime));
     emit postSpeckleMessage(QString("Done with MESI Calibration!").arg(t.elapsed()));

    // The camera is in continuous mode, stop image acquisition
    //Camera.AcquisitionStop.Execute();
     qDebug() << "Trigger State " << Camera.TriggerMode.GetValue() << " at end of acq";
#ifdef PYLON_USE_USB3
    if (Camera.TriggerMode.GetValue())// Added by SK 5/19/15
               Camera.AcquisitionStop.Execute();   // Added by SK 5/19/15
#endif

    // Flush the input queue, grabbing may have failed
    //StreamGrabber.CancelGrab();

}
#endif
/***************************************************************************/
void PylonClass::finish_acquisition(void)
{
#ifdef NO
    GrabResult Result;

    StreamGrabber.CancelGrab();

    emit postSpeckleMessage(QString("finishing pylon acquisition..."));
    // Consume all items from the output queue
    while ( StreamGrabber.GetWaitObject().Wait(0) ) {
        StreamGrabber.RetrieveResult( Result );
        //if ( Result.Status() == Canceled )
        //    emit postSpeckleMessage(QString("Got canceled buffer"));
    }

    emit postSpeckleMessage(QString("de-registering buffers"));
    // Deregister and free buffers
    for ( int i = 0; i < NUM_GRAB_BUFFERS; ++i ) {
        StreamGrabber.DeregisterBuffer(handles[i]);
    }

    // Clean up
    StreamGrabber.FinishGrab();
    StreamGrabber.Close();
#endif
}
