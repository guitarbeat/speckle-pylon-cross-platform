#include "FrameGrabberClass.h"
#include "camera.h"
#include "speckle_processing.h"

FrameGrabberClass::FrameGrabberClass(QObject *parent) :
    QObject(parent)
{   
    video_in_device_number=0;
    // added comment here
}

/*******************************************************/
int FrameGrabberClass::initialize(unsigned short *width, unsigned short *height,
                            unsigned short *top, unsigned short *left, float *exposure_time,
                            unsigned short *max_w, unsigned short *max_h, unsigned short *bits_per_pixel,
                           QString *name, QString *descr, unsigned short *cam_type, int *color_depth)
{
    qDebug() << "opening frame grabber" << endl;

    capture_device.open(video_in_device_number);
    if (!capture_device.isOpened()) {
            qDebug() << "ERROR! Unable to open video input\n";
            return(0);
           // keep_going=false;
    }

    this->camera_name = name; // set pointer between parent class
    this->camera_description = descr;
    name->append(QString("Frame Grabber"));
    descr->append(name);

    this->max_height = max_h; // set pointer in this class to parent
    this->max_width = max_w;
    *max_w = 1920;
    *max_h = 1080;

    capture_device.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    capture_device.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
    // now check frame size
    double w = capture_device.get(cv::CAP_PROP_FRAME_WIDTH);
    double h = capture_device.get(cv::CAP_PROP_FRAME_HEIGHT);
    double fps = capture_device.get(cv::CAP_PROP_FPS);
    if(w!=1920 || h!=1080)
    {
        qDebug() << "could not set width and height to HD video. New values are: "
                 << w << " x " << h << endl;
    }

    this->im_h = height;
    this->im_w = width;
    *height = *max_h;
    *width = *max_w;

    this->top = top;
    this->left = left;
    *top = 0;
    *left = 0;

    // figure out bit depth
    bit_depth = bits_per_pixel; // set pointer to parent
        *bits_per_pixel = 8;

    this->color_planes = color_depth;
    *color_depth = 1;

    this->exp_time = exposure_time;
    *exposure_time = 5;

    this->cam_type = cam_type;
    *cam_type=CAMERA_FRAMEGRABBER;

    return(1);
}
/***************************************************************************/
void FrameGrabberClass::GetPixelFormats(QStringList *pix_list)
{
    //node_vector node_list;

    pix_list->clear();

    pix_list->append(QString("8-bit"));
    pix_list->append(QString("10-bit"));
    pix_list->append(QString("12-bit"));
}

/*******************************************************/
void FrameGrabberClass::SetExposureTime(float exp_ms)
{

    *exp_time = exp_ms;
}
/*******************************************************/
void FrameGrabberClass::SetAOI(unsigned short AOI_top, unsigned short AOI_left,
                        unsigned short AOI_width, unsigned short AOI_height)
{
    emit postSpeckleMessage(QString("setting AOI"));
    *top = AOI_top;
    *left = AOI_left;
    *im_w = AOI_width;
    *im_h = AOI_height;
    emit postSpeckleMessage(QString("ok"));
}
/*******************************************************/
void FrameGrabberClass::SetTrigger(QString trigger_str)
{
    emit postSpeckleMessage(QString("forcing disabling external triggering - fix me"));

}
/*******************************************************/
void FrameGrabberClass::SetBitDepth(QString bit_depth_str)
{
    if(bit_depth_str.contains("8-bit",Qt::CaseInsensitive))
        *bit_depth=8;
    else if(bit_depth_str.contains("10-bit",Qt::CaseInsensitive))
        *bit_depth=10;
    else if(bit_depth_str.contains("12-bit",Qt::CaseInsensitive))
        *bit_depth=12;
}

/*******************************************************/
int FrameGrabberClass::InitializeAcquisition(int Nframes)
{
    int i;

    if(capture_device.isOpened())
        return(1);

        capture_device.open(video_in_device_number); // + cv::CAP_DSHOW);
        if (!capture_device.isOpened()) {
                qDebug() << "ERROR! Unable to open video input\n";
                return(0);
               // keep_going=false;
        }
        else {
            capture_device.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
            capture_device.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
            capture_device.set(cv::CAP_PROP_FPS, 60);
        }

        // now check frame size
        double w = capture_device.get(cv::CAP_PROP_FRAME_WIDTH);
        double h = capture_device.get(cv::CAP_PROP_FRAME_HEIGHT);
        double fps = capture_device.get(cv::CAP_PROP_FPS);
        if(w!=1920 || h!=1080)
        {
            qDebug() << "could not set width and height to HD video. New values are: "
                     << w << " x " << h << endl;
        }

    return(1);
}
/*******************************************************/
void FrameGrabberClass::SetDeviceNumber(int dev_num)
{
    video_in_device_number = dev_num;
}
/***************************************************************************/
void FrameGrabberClass::AcquireImages(int Nframes, long *img_acquired,
                               unsigned char **raw_images,
                               float *acquisition_times,
                               int write_mode, int acquire_flag, QElapsedTimer *timer)
{  
    int ista;
    int iframe,i,j,foo;
    long count;
    double foo2;
    unsigned short *p;
    int stat=0;
    int stat2=0;
    if((write_mode == WRITE_CONTINUOUS) && (acquire_flag==ACQUISITION_MODE))
        ista=*img_acquired;
    else
        ista=0;

    if(!capture_device.isOpened())
        return;

    Mat frame;
    CImg<uchar> tmp_img;

    for(iframe=ista; iframe<ista+Nframes; iframe++)
    {
        capture_device >> frame;
        tmp_img = CImg<uchar>::_cvmat2cimg(frame);

        count=0;
        cimg_forXY(tmp_img,x,y)
        {
           // raw_images[iframe][count]=(unsigned char)((tmp_img(x,y,0) + tmp_img(x,y,1) + tmp_img(x,y,2))/3.0);
            raw_images[iframe][count]=(unsigned char)(tmp_img(x,y,0));
            count++;
        }
        *img_acquired += 1;
        acquisition_times[*img_acquired-1]=(float)(timer->elapsed());
    }
}
/***************************************************************************/
void FrameGrabberClass::finish_acquisition(void)
{
    capture_device.release();
}
/***************************************************************************/
