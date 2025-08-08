#include "camera.h"
#include "imagegenerator.h"

/***************************************************************************/
Camera::Camera()
{
    // default is greyscale camera
    color_camera=false;
    color_planes=1;
    camera_name = "Simulated Camera";
    max_width=1920;
    max_height=1080;
    top=0;
    left=0;
    im_w = max_width;
    im_h = max_height;
    bit_depth=8;
    SetBytesPerPixel();
    exp_time=5; // ms
    img_acquired=0;
    camera_type=CAMERA_NONE;

    num_live_buffers=100;
}
/***************************************************************************/
void Camera::openCamera(int devNum) {
    qDebug() << "Opening Simulated Camera";
}
/***************************************************************************/
void Camera::initialize(void) {
    int ret = 0;
}
/***************************************************************************/
bool Camera::isOpened(void) {
    return(true); // always true for simulated camera
}
/***************************************************************************/
void Camera::setAOI(int t, int l, int w, int h)
{
    int old_top=top;
    int old_left=left;

    top = old_top + t;
    left = old_left + l;
    im_w = w;
    im_h = h;

    qDebug() << "new AOI= " << QString("l=%1, t=%2, w=%3, h=%4").arg(left).arg(top).arg(im_w).arg(im_h);
}
/***************************************************************************/
void Camera::SetCameraROI(void)
{

}
/***************************************************************************/
void Camera::SetCameraExposureTime(float exp_ms)
{
    exp_time = exp_ms;

}
/***************************************************************************/
void Camera::SetCameraTrigger(QString trigger_str) {


}
/***************************************************************************/
void Camera::SetBitDepth(unsigned short new_bit_depth)
{
    bit_depth = new_bit_depth;
    SetBytesPerPixel();
}
/***************************************************************************/
void Camera::SetBitDepth(QString bit_depth_str)
{
    if(bit_depth_str.contains("8-bit",Qt::CaseInsensitive))
        bit_depth=8;
    else if(bit_depth_str.contains("10-bit",Qt::CaseInsensitive))
        bit_depth=10;
    else if(bit_depth_str.contains("12-bit",Qt::CaseInsensitive))
        bit_depth=12;
    else if(bit_depth_str.contains("16-bit",Qt::CaseInsensitive))
        bit_depth=16;

    SetBytesPerPixel();
}
/***************************************************************************/
void Camera::SetCameraGain(void) {

}
/***************************************************************************/
void Camera::setMaxNumBuffers(int n) {
    max_buffers=n;
}
/***************************************************************************/
int Camera::initialize_acquisition(AcquisitionClass *acq, unsigned char **buffer_list,
                                   QVector<float> *acq_t)
{
    img_acquired=0;
    buffers=buffer_list;
    acq_times = acq_t;
    acq_settings = acq;
    acquire_fps = 0;
    //setMaxNumBuffers(Nframes); //

    return(1);
}
/***************************************************************************/
void Camera::acquireImages(int Nframes)
{
    // acquired Nframes into buffers, which is stored internally (just the pointers).
    acquireImages(Nframes, buffers);
}
/***************************************************************************/
void Camera::acquireImages(int Nframes, unsigned char **image_buffers)
{
    // acquired Nframes into image_buffers. Note that initialize_acquisition must be called first!
    // this call is blocking
    CImg<unsigned char> tmp_img(im_w, im_h, 1, color_planes);
    for(int i=0;i<Nframes; i++)
    {
        // Fill with random bytes for simulation
        for (int y = 0; y < im_h; ++y) {
            for (int x = 0; x < im_w; ++x) {
                tmp_img(x, y) = static_cast<unsigned char>(std::rand() % 256);
            }
        }
        memcpy((void *)(image_buffers[i]), tmp_img.data(), im_w*im_h*color_planes);
        img_acquired++;
    }
}
/***************************************************************************/
void Camera::acquireImage(CImg<unsigned char> *img)
{
    unsigned char *tmp_buf[1];
    if(img->width()!=im_w || img->height()!=im_h || img->spectrum()!=color_planes)
        img->resize(im_w, im_h, 1, color_planes, -1);
    tmp_buf[0]=img->data();
    acquireImages(1, tmp_buf);
}
/***************************************************************************/
void Camera::acquireImages(CImgList<unsigned char> *img_list)
{
    if(img_list->size()==0)
        return;

    if(img_list->at(0).width()!=im_w || img_list->at(0).height()!=im_h || img_list->at(0).spectrum()!=color_planes)
        for(int i=0; i<img_list->size(); i++)
            img_list->at(i).resize(im_w, im_h, 1, color_planes, -1);

    unsigned char *tmp_buf[100000]; // fix this
    for(int i=0; i<img_list->size(); i++)
        tmp_buf[i]=img_list->at(i).data();
    acquireImages(img_list->size(), tmp_buf);
}
/***************************************************************************/
void Camera::acquireImagesAsync(void)
{
    ImgGeneratorThread = new ImageGenerator(acq_settings);
    ImgGeneratorThread->initialize(im_w, im_h, buffers, acq_times, &img_acquired);
    connect(ImgGeneratorThread, &ImageGenerator::finished,
            this, &Camera::acquireAsyncCompleted);
    ImgGeneratorThread->start();
}
/***************************************************************************/
void Camera::stopAcquisition(void)
{
    if(ImgGeneratorThread)
    {
        // note that this only works if ImgGeneratorThread is defined as a QPointer rather than *
        ImgGeneratorThread->stopAcquisition();
        ImgGeneratorThread->wait();
        delete ImgGeneratorThread;
    }

}
/***************************************************************************/
void Camera::acquireAsyncCompleted(void) {

    // pass signal back to main window
    emit acquisitionFinished();

}
/***************************************************************************/
void Camera::cleanup(void) {
    qDebug() << "Closing Simulated Camera";
}
/***************************************************************************/
void Camera::finish_acquisition(unsigned char *buf) {

}
/***************************************************************************/
void Camera::save_acquisition_timing(QString fname, float *acq_times, int N)
{
    QFile file(fname);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out.writeRawData((const char *)(acq_times), sizeof(float)*N);
    file.close();
}
/***************************************************************************/
QString Camera::getCameraInfo(void) {
    QString msg;
    msg += QString("<table cellpadding=5>");
    msg += QString("<tr><td><b>Camera</b></td><td>Simulated Camera</td></tr>");
    msg += QString("<tr><td><b>Resolution</b></td><td>%1x%2</td></tr>").arg(im_w).arg(im_h);
    msg += QString("<tr><td><b>Max Resolution</b></td><td>%1x%2</td></tr>").arg(max_width).arg(max_height);
    msg += QString("</table>");
    return msg;
}
/***************************************************************************/
void Camera::GetPixelFormats(QStringList *pix_list) {   
    pix_list->clear();

    pix_list->append(QString("8-bit"));
    pix_list->append(QString("10-bit"));
    pix_list->append(QString("12-bit"));
}
/***************************************************************************/
void Camera::SetBytesPerPixel() {
    if(bit_depth == 8)
        bytes_pixel = 1;
    else
        bytes_pixel = 2;
}
/***************************************************************************/
//
//
// BEGIN NI-IMAQ CODE
//
#ifdef USE_NIIMAQ
/***************************************************************************/
int Camera::init_niimaq(void) {
    char ni_names[512];
    char err_text[1024];
    Int32 retval;
    uInt32 foo;

    // fixme- run through list
    imgInterfaceQueryNames(0, ni_names);
    qDebug() << "name 0 = " << ni_names;

    if(!camera_specified)
        camera_name="img0.iid";

    //if(imgInterfaceOpen(camera_name.toUtf8(), &Iid) != 0)
    if(retval=imgInterfaceOpen(ni_names, &Iid) != 0)
    {
        imgShowError(retval, err_text);
        qDebug() << "error in imgInterfaceOpen()" << err_text;
        return(0);
    }
    if(imgSessionOpen(Iid, &Sid) != 0)
        return(0);

    //imgGetAttribute (Sid, IMG_ATTR_ROI_WIDTH, &foo);
    //max_width=foo;
    //imgGetAttribute (Sid, IMG_ATTR_ROI_HEIGHT, &foo);
    //max_height=foo;
    binning=1;
    top=0;
    left=0;
    SetBinning();
    im_w=max_width;
    im_h=max_height;
    //imgGetAttribute (Sid, IMG_ATTR_BITSPERPIXEL, &foo);
    //bit_depth=foo;
    //imgGetAttribute (Sid, IMG_ATTR_BYTESPERPIXEL, &foo);
    //bytes_pixel=foo;
    bit_depth=12;
    bytes_pixel=2;

    camera_name=ni_names;
    camera_description=ni_names;
    trigger=NO_TRIGGER;
    camera_type=CAMERA_NI;

    SetExposureMode(2);
    qDebug() << "im_w, im_h= " << im_w << im_h << endl;
    return(1);
}
/***************************************************************************/
int Camera::initialize_NI_acquisition(int Nframes, unsigned char **buffer_list) {

    // Note: for this section to utilize all commands to control the Dalsa camera,
    // the camera must use a "blank" camera file to ignore all default values setup by the
    // camera manufacturer.  Use the "Dalsa 1M60 AD 05232016.icd" file for this!

    int i;
    IMG_ERR errCode;
    uInt32 *skip_buf;
    unsigned char **tmp_buf;
    char send_buf[512], buf2[16384];
    char err_msg[512];
    uInt32 buf_size;
    Int32 ret;
    char cmd_string[512];
    char rec_buf[16384];

    // set dual output
    SetNIOutputMode();
    //sprintf(cmd_string, "sos %i\n\0",OutputMode);
    //Write_IMAQ_Serial(cmd_string, rec_buf, 16384);

    // set exposure mode
    SetExposureMode(exposure_mode);
    //sprintf(cmd_string, "sem %i\n\0",exposure_mode);
    //Write_IMAQ_Serial(cmd_string, rec_buf, 16384);


    // set exposure time
    //sprintf(send_buf, "set %f\n", (float)(exp_time)*1000.0); // exp time in us
    //buf_size=strlen(send_buf);
    //ret=imgSessionSerialWrite(Sid, send_buf, &buf_size, 50);
    //if(ret != 0)
    //{
    //	imgShowError(ret, send_buf);
    //	emit postSpeckleMessage(QString("error in imgSessionSerialWrite (set): %1").arg(send_buf));
    //}

    // set bit depth
    SetBitDepth(bit_depth);
    //sprintf(cmd_string, "oms %i\n\0", bit_depth);
    //Write_IMAQ_Serial(cmd_string, rec_buf, 16384);

    // route I/O line for strobing LED's
    //imgSessionTriggerDrive2(Sid, IMG_SIGNAL_EXTERNAL, 1,
    //	IMG_TRIG_POLAR_ACTIVEH, IMG_TRIG_DRIVE_FRAME_START);
    imgPulseDispose(plsID);
    uInt32 pulse_width = (uInt32)(OutputPulseDuration*50e6);
    uInt32 pulse_src;
    if(OutputPulseSource == FRAME_START_PULSE)
        pulse_src = IMG_FRAME_START;
    else if(OutputPulseSource == FRAME_STOP_PULSE)
        pulse_src = IMG_FRAME_DONE;
    if(OutputPulseSource != NO_PULSE)
    {
        ret=imgPulseCreate2(PULSE_TIMEBASE_50MHZ, 0, pulse_width,
            IMG_SIGNAL_STATUS, pulse_src, IMG_TRIG_POLAR_ACTIVEH,
            IMG_SIGNAL_EXTERNAL, 1, IMG_PULSE_POLAR_ACTIVEH,
            PULSE_MODE_SINGLE_REARM, &plsID);
        if(ret != 0)
        {
            imgShowError(ret, send_buf);
            emit postSpeckleMessage(QString("error in imgPulseCreate2: %1").arg(send_buf));
        }
    }


    // set binning - NOTE: this is not redundant with the serial command for binning below
    SetBinning();

    // set AOI
    SetCameraROI();

    // set exposure time
    sprintf(cmd_string, "set %.2f\n\0", (float)(exp_time)*1000.0); // exp time in us
    Write_IMAQ_Serial(cmd_string, rec_buf, 16384);
    // set frame rate
    SetDalsaFrameRate();
    // set exposure time
    sprintf(cmd_string, "set %.2f\n\0", (float)(exp_time)*1000.0); // exp time in us
    Write_IMAQ_Serial(cmd_string, rec_buf, 16384);

    skip_buf = new uInt32[Nframes];
    for(i=0;i<Nframes;i++)
        skip_buf[i]=0;

    if(OutputPulseSource != NO_PULSE)
    {
        ret = imgPulseStart(plsID, Sid);
        if(ret != 0)
        {
            imgShowError(ret, send_buf);
            emit postSpeckleMessage(QString("error in imgPulseStart: %1").arg(send_buf));
            return(0);
        }
    }

    emit postSpeckleMessage(QString("initializing NI acquisition"));
    qDebug() << "initializing with, Nframes= "<<Nframes<<endl;
    errCode = imgSequenceSetup(Sid, Nframes, (void **)buffer_list,skip_buf , 0, 1);
    emit postSpeckleMessage(QString("errCode=%1").arg(errCode));
    if(errCode != 0)
    {
        if(imgShowError(errCode, err_msg))
            emit postSpeckleMessage(QString("error in imgSequenceSetup, err = %1").arg(err_msg));
        return(0);
    }
    else
    {
        emit postSpeckleMessage(QString("initization complete"));
        return(1);
    }
    emit postSpeckleMessage(QString("imgSequenceSetup complete"));
}
/***************************************************************************/
void Camera::AcquireImagesNI(int Nframes, long *img_acquired, unsigned char **raw_images,
                             float *acquisition_times, int write_mode, int acquire_flag) {

    static int error,  i;
    uInt32 status, currBufNum;
    int keep_going=1;
    char err_msg[512];

    uInt32 ret;
    ret=imgSessionStartAcquisition(Sid);
    if(ret != 0)
    {
        imgShowError(ret, err_msg);
        emit postSpeckleMessage(QString("error in imgSessionStartAcquisition: %1").arg(err_msg));
        return;
    }
    while(keep_going)
    {
        imgSessionStatus (Sid, &status, &currBufNum);
        if(status==0)
            keep_going=0;
        //else
        //	Sleep(2);
    }
    *img_acquired += currBufNum;
    imgSessionStopAcquisition(Sid);
}
/***************************************************************************/
void Camera::SetNIOutputMode(void) {
    char cmd_string[512];
    char rec_buf[16384];

    sprintf(cmd_string, "sos %i\n\0",OutputMode);
    Write_IMAQ_Serial(cmd_string, rec_buf, 16384);
}
/***************************************************************************/
void Camera::Write_IMAQ_Serial(char *send_buf, char *rec_buf, uInt32 rec_buf_size) {
    uInt32 buf_size;
    int ret;
    char err_msg[4096];

    buf_size=strlen(send_buf);
    ret=imgSessionSerialWrite(Sid, send_buf, &buf_size, 500);
    if(ret != 0)
    {
        imgShowError(ret, err_msg);
        emit postSpeckleMessage(QString("error in imgSessionSerialWrite: %1").arg(err_msg));
    }
    imgSessionSerialFlush(Sid);

        // now read response
    ret=imgSessionSerialRead(Sid, rec_buf, &rec_buf_size, 5000);
    if(ret != 0)
    {
        imgShowError(ret, err_msg);
        emit postSpeckleMessage(QString("error in imgSessionSerialRead: %1").arg(err_msg));
    }
    imgSessionSerialFlush(Sid);

    emit postSpeckleMessage(QString("command %1 returned %2").arg(send_buf).arg(rec_buf));
}
/***************************************************************************/
void Camera::SetDalsaFrameRate(void) {
    char cmd_string[512];
    char rec_buf[16384];

    if(exposure_mode==2) { // (exposure_mode==2 || exposure_mode==6)
        sprintf(cmd_string, "ssf %i\n\0",frame_rate);
        Write_IMAQ_Serial(cmd_string, rec_buf, 16384);
    }
}
/***************************************************************************/
void Camera::SetExposureMode(int mode) {
    char cmd_string[512];
    char rec_buf[16384];
    sprintf(cmd_string, "sem %i\n\0", mode);
    Write_IMAQ_Serial(cmd_string, rec_buf, 16384);
}
/***************************************************************************/
void Camera::SetBinning(void) {
    char attributeString[512], attributeStringVal[512];
    char send_buf[512];
    char cmd_string[512];
    char rec_buf[16384];

    // now check max image size
    max_width=DALSA_NUM_PIXELS_W/binning;
    max_height=DALSA_NUM_PIXELS_H/binning;

    emit postSpeckleMessage(QString("max_width=%1").arg(max_width));

    qDebug() << "max_width= " << max_width << "max_height= " << max_height;

    sprintf(cmd_string, "sbm %i %i\n\0",binning, binning); // fix later for asymmetric binning
    Write_IMAQ_Serial(cmd_string, rec_buf, 16384);
}
/***************************************************************************/
void Camera::finish_ni_acquisition(void) {
    uInt32 idx;
    imgPulseStop(plsID);
    imgSessionAbort(Sid, &idx);
}
/***************************************************************************/
void Camera::SetFrameRate(int rate) {
    if(camera_type == CAMERA_NI) {
        frame_rate = rate;
    }
}
/***************************************************************************/
#endif
//
// END NI-IMAQ CODE
//
//
/***************************************************************************/
//
//
// BEGIN NI-IMAQdx CODE
//
#ifdef USE_NIIMAQDX
/******************************************************************************************/
int Camera::init_niimaqdx(void) {
    char buf[512];

    if(!camera_specified)
        camera_name="cam0";

    IMAQdxError statusOpen;
    statusOpen=IMAQdxOpenCamera(camera_name.toUtf8(), IMAQdxCameraControlModeController, &ni_session);
    if(statusOpen != IMAQdxErrorSuccess)
    {
        qDebug() << "Camera could not be opened";
        ShowNIIMAQdxError((int)(statusOpen));
        return(0);
    }
    //if(IMAQdxOpenCamera(camera_name.toUtf8(), IMAQdxCameraControlModeController, &ni_session) != IMAQdxErrorSuccess)
    //{
    //    qDebug() << "Camera could not be opened";
    //    return(0);
    //}

    top=0;
    left=0;

    if(IMAQdxGetAttribute(ni_session, IMAQdxAttributeVendorName, IMAQdxValueTypeString, (void *)buf) != IMAQdxErrorSuccess)
    {
        qDebug() << "Could not get vendor name";
        return(0);
    }
    camera_name=buf;
    camera_description.append(buf);
    if(IMAQdxGetAttribute(ni_session, IMAQdxAttributeModelName, IMAQdxValueTypeString, (void *)buf) == IMAQdxErrorSuccess)
        camera_description.append(QString(" ")+QString(buf));
    uInt32 foo_u32;
    if(IMAQdxGetAttribute(ni_session, IMAQdxAttributeWidth, IMAQdxValueTypeU32, (void *)(&foo_u32)) != IMAQdxErrorSuccess)
    {
        qDebug() << "Could not get camera width";
        return(0);
    }
    im_w=foo_u32;
    if(IMAQdxGetAttribute(ni_session, IMAQdxAttributeHeight, IMAQdxValueTypeU32, (void *)(&foo_u32)) != IMAQdxErrorSuccess)
    {
        qDebug() << "Could not get camera width";
        return(0);
    }
    im_h=foo_u32;
    max_height = im_h;
    max_width = im_w;
        if((max_height<16) || (max_width<16))
        {
            qDebug() << "max height or max width < 16";
            return(0);
        }

    char bus_type[512];
    if(IMAQdxGetAttribute(ni_session, IMAQdxAttributeBusType, IMAQdxValueTypeString, (void *)(bus_type)) != IMAQdxErrorSuccess)
    {
        qDebug() << "Could not get camera bus type";
        return(0);
    }
    else
    {
        bus_type_string = QString(bus_type);
    }

    GetNIIMAQdx_bit_depth();

    //return(0);
    // check exposure range
    bool32* writable;
    if(IMAQdxIsAttributeWritable(ni_session, "ExposureTimeAbs", (bool32*)(&writable)) == IMAQdxErrorSuccess)
    {
        char exp_descr[512];
        QString exp_string;
        IMAQdxGetAttributeDescription(ni_session, "ExposureTimeAbs", exp_descr, 512);
        exp_string=QString(exp_descr);
        if(exp_string.contains("micro", Qt::CaseInsensitive))
            exp_scale_factor=1000; // 1000us/ms
        else if((exp_string.contains("milli", Qt::CaseInsensitive)) || (exp_string.contains("ms", Qt::CaseInsensitive)))
            exp_scale_factor=1;
        else
            exp_scale_factor=1;
    }

    // set Basler 602f scale factor. Exp range is 0-4095
    if(camera_description.contains("602f", Qt::CaseInsensitive))
    {
        exp_scale_factor=0.02; // used in SetCameraExposureTime
        exp_max=4095;
    }

    trigger=NO_TRIGGER;
    camera_type=CAMERA_NIIMAQDX;
    return(1);
}
/******************************************************************************************/
void Camera::SetNIIMAQdxTrigger(QString trigger_str) {
    char tmp_str[512];
    IMAQdxError status;
    if(camera_description.contains("Photonfocus",Qt::CaseInsensitive))
    {
        status=IMAQdxSetAttribute(ni_session, "Trigger_Source",IMAQdxValueTypeString, (const char *)(trigger_str.toUtf8()));
        if(status != IMAQdxErrorSuccess)
        {
            char err_msg[1024];
            IMAQdxGetErrorString(status, err_msg, 1024);
            emit postSpeckleMessage(QString("error in setting trigger: %1\n").arg(err_msg));
        }
        IMAQdxGetAttribute(ni_session,"Trigger_Source", IMAQdxValueTypeString, tmp_str);
        emit postSpeckleMessage(QString("Trigger is set to: %1, should be %2").arg(tmp_str).arg(trigger_str));
    }
}
/******************************************************************************************/
void Camera::GetNIIMAQdx_bit_depth(void) {
    IMAQdxEnumItem pix_format;
    if(IMAQdxGetAttribute(ni_session, IMAQdxAttributePixelFormat, IMAQdxValueTypeEnumItem, (void *)(&pix_format)) != IMAQdxErrorSuccess)
        return;
    // now try to decipher bit depth from format
    QString pix_format_str;
    pix_format_str=QString(pix_format.Name);
    if(pix_format_str.contains("mono8", Qt::CaseInsensitive))
        bit_depth=8;
    else if(pix_format_str.contains("mono10", Qt::CaseInsensitive))
        bit_depth=10;
    else if(pix_format_str.contains("mono12", Qt::CaseInsensitive))
        bit_depth=12;
    else if(pix_format_str.contains("mono16", Qt::CaseInsensitive))
        bit_depth=16;
    else
        bit_depth=8;

    if(bit_depth>8)
        bytes_pixel=2;
    else
        bytes_pixel=1;

    // see if we have a color camera
    char mode_descr[512];
    QString mode_string;
    IMAQdxGetAttributeDescription(ni_session, "VideoMode", mode_descr,512);
    mode_string=QString(mode_descr);
    //if(mode_string.contains("YUV", Qt::CaseInsensitive) || pix_format_str.contains("BGRA", Qt::CaseInsensitive))
    if(pix_format_str.contains("BGRA", Qt::CaseInsensitive))
    {
        color_camera=true;
        color_planes=4;
    }
    else if(pix_format_str.contains("BG8", Qt::CaseInsensitive))
    {
        color_camera=false;
        color_planes=1;
        bit_depth=8;
    }
    else
    {
        color_camera=false;
        color_planes=1;
    }

    //if(camera_description.contains("UI122xLE-M", Qt::CaseInsensitive))
    //{
    //    color_planes=1;
    //    bit_depth=8;
    //}
    emit postSpeckleMessage(QString("reported pixel format = %1. choosing %2 bits/pixel").arg(pix_format.Name).arg(bit_depth));
}
/******************************************************************************************/
int Camera::initialize_NIIMAQdx_acquisition(int Nframes) {
    IMAQdxError err;
    err=IMAQdxConfigureAcquisition(ni_session, 0, Nframes);
    if(err == IMAQdxErrorSuccess) {
        emit postSpeckleMessage(QString("configured acquisition of %1 frames.").arg(Nframes));
        return(1);
    } else {
        char msg[512];
        IMAQdxGetErrorString(err, msg, 512);
        emit postSpeckleMessage(QString("error in IMAQdxConfigureAcquisition: %1").arg(msg));
        return(0);
    }
}
/******************************************************************************************/
void Camera::AcquireImagesNIIMAQdx(int Nframes, long *img_acquired,
                                   unsigned char **raw_images,
                                   float *acquisition_times,
                                   int write_mode, int acquire_flag,
                                   QElapsedTimer *timer) {
    char msg[512];
    uInt32 actual_buffer_number;
    int ii, ista;

    IMAQdxError ret;

    ret=IMAQdxStartAcquisition(ni_session);
    if(ret != IMAQdxErrorSuccess)
    {
        IMAQdxGetErrorString(ret, msg, 512);
        emit postSpeckleMessage(QString("error in IMAQdxStartAcquisition: %1").arg(msg));
        return;
    }

    if((write_mode == WRITE_CONTINUOUS) && (acquire_flag==ACQUISITION_MODE))
        ista=*img_acquired;
    else
        ista=0;

    QTime t;
    t.start();
    for(ii=ista;ii<ista+Nframes;ii++)
    {
        ret=IMAQdxGetImageData(ni_session, raw_images[ii], im_w*im_h*bytes_pixel*color_planes,
            IMAQdxBufferNumberModeBufferNumber, ii-ista, &actual_buffer_number);
        *img_acquired += 1;
        acquisition_times[*img_acquired-1]=(float)(timer->elapsed());
        if(ret != IMAQdxErrorSuccess)
        {
            IMAQdxGetErrorString(ret, msg, 512);
            emit postSpeckleMessage(QString("error in IMAQdxGetImageData: %1").arg(msg));
            //return;
        }
        //else
        //emit postSpeckleMessage(QString("actual_buffer_number=%1, other=%2").arg(actual_buffer_number).arg(ii-ista+1));
    }
    emit postSpeckleMessage(QString("approx acquisition frame rate=%1 fps").arg(Nframes*1000/(t.elapsed())));

        if(color_planes>1)
                ConvertBGRAtoCImg(Nframes, raw_images);

    //*img_acquired += actual_buffer_number;
    IMAQdxStopAcquisition (ni_session);


    //// temporarily write to image to check color
    //QFile file("test_images.dat");
    //file.open(QIODevice::WriteOnly);
    //QDataStream out(&file);
    //out.writeRawData((const char *)(&(color_planes)), sizeof(int));
    //out.writeRawData((const char *)(&(raw_images[0][0])), im_w*im_h*bytes_pixel*4);
    //file.close();
}
/******************************************************************************************/
void Camera::ShowNIIMAQdxError(int status) {
    char err_msg[1024];
    IMAQdxGetErrorString((IMAQdxError)(status), err_msg, 1024);
    emit postSpeckleMessage(QString("NIIMAQdx error: %1\n").arg(err_msg));
}
/******************************************************************************************/
int Camera::NIIMAQdx_UseDefaultParameters(void) {

    // Reset to default parameters
    if(IMAQdxReadAttributes(ni_session, NULL) == IMAQdxErrorSuccess)
        emit postSpeckleMessage(QString("Using default IMAQdx parameters"));

    // Set exposure time to manual
    char actual_mode[512];
    if(camera_description.contains("Unibrain", Qt::CaseInsensitive))
    {
         if(IMAQdxSetAttribute(ni_session, "CameraAttributes::AutoExposure::Mode", IMAQdxValueTypeString, "Relative") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::AutoExposure::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("AutoExposure mode set to %1").arg(actual_mode));

        uInt32 vid_mode = 3;
        if(IMAQdxSetAttribute(ni_session, IMAQdxAttributeVideoMode, IMAQdxValueTypeU32, vid_mode) != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, IMAQdxAttributeVideoMode, IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
             emit postSpeckleMessage(QString("VideoMode set to %1").arg(actual_mode));

        if(IMAQdxSetAttribute(ni_session, IMAQdxAttributeBayerPattern, IMAQdxValueTypeString, "None") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, IMAQdxAttributeBayerPattern, IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
             emit postSpeckleMessage(QString("Bayer Patter set to %1").arg(actual_mode));

        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Shutter::Mode", IMAQdxValueTypeString, "Ignored") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Shutter::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Shutter mode set to %1").arg(actual_mode));

    }
    if(camera_description.contains("Point Grey Research", Qt::CaseInsensitive))
    {
        float64 max_shutter_value;
        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Shutter::Mode", IMAQdxValueTypeString, "Absolute") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Shutter::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Shutter mode set to %1").arg(actual_mode));

        if(IMAQdxGetAttributeMaximum(ni_session, "CameraAttributes::Shutter::Value", IMAQdxValueTypeF64, (void *)(&max_shutter_value)) == IMAQdxErrorSuccess)
        {   if(max_shutter_value < 1)
                 exp_scale_factor = 0.001;
        }
        else
            return(0);

        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::AutoExposure::Mode", IMAQdxValueTypeString, "Off") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::AutoExposure::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("AutoExposure mode set to %1").arg(actual_mode));
    }

    char mode_descr[512];
    if(camera_description.contains("UI122xLE-M", Qt::CaseInsensitive))
    {
        uInt32 setval_int32_1 = 6;
        if(IMAQdxSetAttribute(ni_session, "AcquisitionAttributes::VideoMode", IMAQdxValueTypeU32, setval_int32_1) != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "AcquisitionAttributes::VideoMode", IMAQdxValueTypeString, mode_descr) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("VideoMode set to %1").arg(mode_descr));
    }

    if(camera_description.contains("Webcam", Qt::CaseInsensitive))
    {
        uInt32 max_value_int;
        if(IMAQdxGetAttributeMaximum(ni_session, IMAQdxAttributeVideoMode, IMAQdxValueTypeU32, (void *)(&max_value_int)) != IMAQdxErrorSuccess)
            return(0);

        if(IMAQdxSetAttribute(ni_session, IMAQdxAttributeVideoMode, IMAQdxValueTypeU32, max_value_int) != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, IMAQdxAttributeVideoMode, IMAQdxValueTypeString, mode_descr) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("VideoMode set to %1").arg(mode_descr));
    }

    if(bus_type_string.contains("DirectShow", Qt::CaseInsensitive))
    {
            char exp_descr_DS[512];
            QString exp_string_DS;
            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Exposure::Mode", IMAQdxValueTypeString, "Manual") != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Exposure::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("Exposure mode set to %1").arg(actual_mode));
            if(IMAQdxGetAttributeUnits(ni_session, "CameraAttributes::Exposure::Value", exp_descr_DS, 512) == IMAQdxErrorSuccess)
            {
                exp_string_DS=QString(exp_descr_DS);
                if(exp_string_DS.contains("Seconds", Qt::CaseInsensitive))
                    exp_scale_factor = 0.001;

            }
            else
                return(0);

            bool32* writable;
            uInt64 actual_value_int;
            char actual_mode[512];
            uInt64 setval_int0 = 0;
            if(camera_description.contains("UI122xLE-M", Qt::CaseInsensitive))
            {
                exp_scale_factor = 0.001;
            }

            if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::Focus::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
            {
                if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Focus::Mode", IMAQdxValueTypeString, "Manual") != IMAQdxErrorSuccess)
                    return(0);
                if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Focus::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
                    emit postSpeckleMessage(QString("Focus mode set to %1").arg(actual_mode));

                if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Focus::Value", IMAQdxValueTypeI64, setval_int0) != IMAQdxErrorSuccess)
                    return(0);
                if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Focus::Value", IMAQdxValueTypeI64, (void *)(&actual_value_int)) == IMAQdxErrorSuccess)
                    emit postSpeckleMessage(QString("Focus mode set to %1").arg(actual_value_int));
            }

            if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::WhiteBalance::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
            {
                if(IMAQdxSetAttribute(ni_session, "CameraAttributes::WhiteBalance::Mode", IMAQdxValueTypeString, "Manual") != IMAQdxErrorSuccess)
                    return(0);
                if(IMAQdxGetAttribute(ni_session, "CameraAttributes::WhiteBalance::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
                    emit postSpeckleMessage(QString("WhiteBalance mode set to %1").arg(actual_mode));

                if(IMAQdxSetAttribute(ni_session, "CameraAttributes::WhiteBalance::Value", IMAQdxValueTypeI64, setval_int0) != IMAQdxErrorSuccess)
                    return(0);
                if(IMAQdxGetAttribute(ni_session, "CameraAttributes::WhiteBalance::Value", IMAQdxValueTypeI64, (void *)(&actual_value_int)) == IMAQdxErrorSuccess)
                    emit postSpeckleMessage(QString("WhiteBalance mode set to %1").arg(actual_value_int));
            }
    }
}
/******************************************************************************************/
int Camera::NIIMAQdx_SetParameters(void) {
    bool32* writable;

    // Set other parameters
    char actual_mode[512];
    if(camera_description.contains("Unibrain", Qt::CaseInsensitive) || camera_description.contains("Point Grey Research", Qt::CaseInsensitive))
    {
        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Brightness::Mode", IMAQdxValueTypeString, "Ignored") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Brightness::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Brightness mode set to %1").arg(actual_mode));

        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Gain::Mode", IMAQdxValueTypeString, "Ignored") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Gain::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Gain mode set to %1").arg(actual_mode));
    }
    if(camera_description.contains("Unibrain", Qt::CaseInsensitive))
    {
        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Gamma::Mode", IMAQdxValueTypeString, "Ignored") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Gamma::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Gamma mode set to %1").arg(actual_mode));

        if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::Iris::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
        {
            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Iris::Mode", IMAQdxValueTypeString, "Ignored") != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Iris::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("Iris mode set to %1").arg(actual_mode));
        }
        if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::Sharpness::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
        {
            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Sharpness::Mode", IMAQdxValueTypeString, "Ignored") != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Sharpness::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("Sharpness mode set to %1").arg(actual_mode));
        }
        if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::WhiteBalance::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
        {
            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::WhiteBalance::Mode", IMAQdxValueTypeString, "Ignored") != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::WhiteBalance::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("WhiteBalance mode set to %1").arg(actual_mode));
        }
    }
    if(camera_description.contains("Point Grey Research", Qt::CaseInsensitive))
    {
        float64 max_fr_value;
        float64 actual_fr_value;

        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::FrameRate::Mode", IMAQdxValueTypeString, "Absolute") != IMAQdxErrorSuccess)
                return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::FrameRate::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("FrameRate mode set to %1").arg(actual_mode));

        if(IMAQdxGetAttributeMaximum(ni_session, "CameraAttributes::FrameRate::Value", IMAQdxValueTypeF64, (void *)(&max_fr_value)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("FrameRate max is %1").arg(max_fr_value));
        else
            return(0);

        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::FrameRate::Value", IMAQdxValueTypeF64, max_fr_value) != IMAQdxErrorSuccess)
                return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::FrameRate::Value", IMAQdxValueTypeF64, (void *)(&actual_fr_value)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("FrameRate value set to %1").arg(actual_fr_value));

        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Gamma::Mode", IMAQdxValueTypeString, "Off") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Gamma::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Gamma mode set to %1").arg(actual_mode));

        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Pan::Mode", IMAQdxValueTypeString, "Ignored") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Pan::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Pan mode set to %1").arg(actual_mode));
    }

    if(bus_type_string.contains("DirectShow", Qt::CaseInsensitive))
    {
        float64 actual_value_fl;
        uInt64 actual_value_int;
        bool32 actual_bool;
        uInt64 setval_int0 = 0;
        float64 setval_f0 = 0;
        float64 setval_f1 = 1;
        bool32 setval_b0 = 0;

        if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::Brightness::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
        {
        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Brightness::Mode", IMAQdxValueTypeString, "Manual") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Brightness::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Brightness mode set to %1").arg(actual_mode));

        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Brightness::Value", IMAQdxValueTypeI64, setval_int0) != IMAQdxErrorSuccess)
            return(0);

        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Brightness::Value", IMAQdxValueTypeI64, (void *)(&actual_value_int)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Brightness value set to %1").arg(actual_value_int));
        }

        if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::Gain::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
        {
        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Gain::Mode", IMAQdxValueTypeString, "Manual") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Gain::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Gain mode set to %1").arg(actual_mode));

        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Gain::Value", IMAQdxValueTypeI64, setval_int0) != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Gain::Value", IMAQdxValueTypeI64, (void *)(&actual_value_int)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Gain value set to %1").arg(actual_value_int));
        }
        if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::Gamma::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
        {
            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Gamma::Mode", IMAQdxValueTypeString, "Manual") != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Gamma::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("Gamma mode set to %1").arg(actual_mode));

            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Gamma::Value", IMAQdxValueTypeF64, setval_f1) != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Gamma::Value", IMAQdxValueTypeF64, (void *)(&actual_value_fl)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("Gamma value set to %1").arg(actual_value_fl));
        }

        if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::Sharpness::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
        {
        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Sharpness::Mode", IMAQdxValueTypeString, "Manual") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Sharpness::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Sharpness mode set to %1").arg(actual_mode));

        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Sharpness::Value", IMAQdxValueTypeI64, setval_int0) != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Sharpness::Value", IMAQdxValueTypeI64, (void *)(&actual_value_int)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Sharpness value set to %1").arg(actual_value_int));
        }

        if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::Contrast::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
        {
        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Contrast::Mode", IMAQdxValueTypeString, "Manual") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Contrast::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Contrast mode set to %1").arg(actual_mode));

        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Contrast::Value", IMAQdxValueTypeF64, setval_f0) != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Contrast::Value", IMAQdxValueTypeF64, (void *)(&actual_value_fl)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Contrast value set to %1").arg(actual_value_fl));
        }

        if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::BacklightCompensation::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
        {
        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::BacklightCompensation::Mode", IMAQdxValueTypeString, "Manual") != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::BacklightCompensation::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Backlight compensation mode set to %1").arg(actual_mode));

        if(IMAQdxSetAttribute(ni_session, "CameraAttributes::BacklightCompensation::Value", IMAQdxValueTypeBool, setval_b0) != IMAQdxErrorSuccess)
            return(0);
        if(IMAQdxGetAttribute(ni_session, "CameraAttributes::BacklightCompensation::Value", IMAQdxValueTypeBool, (void *)(&actual_bool)) == IMAQdxErrorSuccess)
            emit postSpeckleMessage(QString("Backlight compensation mode set to %1").arg(actual_bool));
        }

        if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::WhiteBalance::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
        {
            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::WhiteBalance::Mode", IMAQdxValueTypeString, "Manual") != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::WhiteBalance::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("WhiteBalance mode set to %1").arg(actual_mode));

            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::WhiteBalance::Value", IMAQdxValueTypeI64, setval_int0) != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::WhiteBalance::Value", IMAQdxValueTypeI64, (void *)(&actual_value_int)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("WhiteBalance mode set to %1").arg(actual_value_int));
        }

        if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::Saturation::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
        {
            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Saturation::Mode", IMAQdxValueTypeString, "Manual") != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Saturation::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("Saturation mode set to %1").arg(actual_mode));

            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Saturation::Value", IMAQdxValueTypeI64, setval_int0) != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Saturation::Value", IMAQdxValueTypeI64, (void *)(&actual_value_int)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("Saturation mode set to %1").arg(actual_value_int));
        }

        if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::Focus::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
        {
            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Focus::Mode", IMAQdxValueTypeString, "Manual") != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Focus::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("Focus mode set to %1").arg(actual_mode));

            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Focus::Value", IMAQdxValueTypeI64, setval_int0) != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Focus::Value", IMAQdxValueTypeI64, (void *)(&actual_value_int)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("Focus mode set to %1").arg(actual_value_int));
        }

        if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::Pan::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
        {
            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Pan::Mode", IMAQdxValueTypeString, "Manual") != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Pan::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("Pan mode set to %1").arg(actual_mode));

            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Pan::Value", IMAQdxValueTypeI64, setval_int0) != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Pan::Value", IMAQdxValueTypeI64, (void *)(&actual_value_int)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("Pan mode set to %1").arg(actual_value_int));
        }

        if(IMAQdxIsAttributeWritable(ni_session, "CameraAttributes::Tilt::Mode", (bool32*)(&writable)) == IMAQdxErrorSuccess)
        {
            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Tilt::Mode", IMAQdxValueTypeString, "Manual") != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Tilt::Mode", IMAQdxValueTypeString, (void *)(&actual_mode)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("Tilt mode set to %1").arg(actual_mode));

            if(IMAQdxSetAttribute(ni_session, "CameraAttributes::Tilt::Value", IMAQdxValueTypeI64, setval_int0) != IMAQdxErrorSuccess)
                return(0);
            if(IMAQdxGetAttribute(ni_session, "CameraAttributes::Tilt::Value", IMAQdxValueTypeI64, (void *)(&actual_value_int)) == IMAQdxErrorSuccess)
                emit postSpeckleMessage(QString("Tilt mode set to %1").arg(actual_value_int));
        }
    }
}
/******************************************************************************************/
void Camera::ConvertBGRAtoCImg(int Nframes, unsigned char **raw_images) {
    int i;
    long pix_idx;

    CImg<unsigned char> foo_uc(im_w, im_h, 1, color_planes); // temp image buffer
    for(i=0;i<Nframes;i++) {
        // fill in tmp image buffer in rrrrr..bbbbb..ggggg format
        cimg_forXY(foo_uc,x,y) {
            pix_idx=4*(im_w*y+x);
            foo_uc(x,y,0)=raw_images[i][pix_idx+2]; // r
            foo_uc(x,y,1)=raw_images[i][pix_idx+1]; // g
            foo_uc(x,y,2)=raw_images[i][pix_idx];   // b
        }
        // now copy back to raw_images and overwrite original
        memcpy(raw_images[i], foo_uc.data(), im_w*im_h*color_planes);
    }
}
/******************************************************************************************/
#endif
//
// END NI-IMAQdx CODE
//
//
/******************************************************************************************/
