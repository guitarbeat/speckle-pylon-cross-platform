#include "simulated_camera_class.h"
#include "camera.h"

SimulatedCameraClass::SimulatedCameraClass(QObject *parent) :
    QObject(parent)
{   
    int junk=0;
    // added comment here
}

/*******************************************************/
int SimulatedCameraClass::initialize(unsigned short *width, unsigned short *height,
                            unsigned short *top, unsigned short *left, float *exposure_time,
                            unsigned short *max_w, unsigned short *max_h, unsigned short *bits_per_pixel,
                           QString *name, QString *descr, unsigned short *cam_type, int *color_depth)
{

    this->camera_name = name; // set pointer between parent class
    this->camera_description = descr;
    name->append(QString("Simulated Camera"));
    descr->append(*name);

    this->max_height = max_h; // set pointer in this class to parent
    this->max_width = max_w;
    *max_w = 1920;
    *max_h = 1080;

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
    *cam_type=CAMERA_NONE;

    return(1);
}
/***************************************************************************/
void SimulatedCameraClass::GetPixelFormats(QStringList *pix_list)
{
    //node_vector node_list;

    pix_list->clear();

    pix_list->append(QString("8-bit"));
    pix_list->append(QString("10-bit"));
    pix_list->append(QString("12-bit"));
}

/*******************************************************/
void SimulatedCameraClass::SetExposureTime(float exp_ms)
{

    *exp_time = exp_ms;
}
/*******************************************************/
void SimulatedCameraClass::SetTrigger(QString trigger_str)
{
    emit postSpeckleMessage(QString("forcing disabling external triggering - fix me"));

}
/*******************************************************/
void SimulatedCameraClass::SetBitDepth(QString bit_depth_str)
{
    if(bit_depth_str.contains("8-bit",Qt::CaseInsensitive))
        *bit_depth=8;
    else if(bit_depth_str.contains("10-bit",Qt::CaseInsensitive))
        *bit_depth=10;
    else if(bit_depth_str.contains("12-bit",Qt::CaseInsensitive))
        *bit_depth=12;
}

/*******************************************************/
int SimulatedCameraClass::InitializeAcquisition(int Nframes)
{
    int i;

    return(1);
}

/***************************************************************************/
void SimulatedCameraClass::AcquireImages(int Nframes, long *img_acquired,
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

#ifdef NO
    CImg<unsigned char> img_tmp;
    unsigned short w_tmp, h_tmp, Nframes_tmp, exp_tmp;
    stat=read_raw_image_file_header(QString("sample_raw2.0000"), &w_tmp, &h_tmp, &Nframes_tmp, &exp_tmp);
    if((stat == 1) && (*bit_depth==8))
    {
            img_tmp.resize(w_tmp, h_tmp, Nframes_tmp);
            stat2=read_raw_image_file(QString("sample_raw2.0000"), img_tmp.data(),
                    &w_tmp, &h_tmp, &Nframes_tmp, &exp_tmp);
            if(stat2==1)
            {
                    img_tmp.resize(im_w, im_h, Nframes);
                    memcpy(&(raw_images[0][0]), img_tmp.data(), im_w*im_h*Nframes);
                    *img_acquired += Nframes;
            }
    }
    if(stat2==1)
            return;
#endif


    CImg<unsigned char> tmp_img;
    tmp_img.resize(*im_w, *im_h);
    for(iframe=ista; iframe<ista+Nframes; iframe++)
    {
        tmp_img.rand(0,255);
        count=0;
        for(j=0;j< *im_h;j++)
            for(i=0;i< *im_w;i++)
            {
                raw_images[iframe][count]=tmp_img(i,j);
                count++;
            }
        *img_acquired += 1;
        acquisition_times[*img_acquired-1]=(float)(timer->elapsed());
    }

#ifdef NO
    for(iframe=ista;iframe<ista+Nframes;iframe++)
    {
            if(rand() < RAND_MAX/2)
                    foo=0;
            else
                    foo=1;
            count=0;
            p=(unsigned short *)(&(raw_images[iframe][0]));
            for(j=0;j< *im_h;j++)
            for(i=0;i< *im_w;i++)
            {
                    //if(foo==1)
                    //	speckle->raw_images[iframe][count]=(unsigned char)((double)(i)/640*256);
                    //else
                    //  speckle->raw_images[iframe][count]=(unsigned char)((double)(640-i)/640*256);
                    //foo2=(double)(rand())/RAND_MAX;
                    foo2 = QRandomGenerator::global()->generateDouble();
                    //foo2=foo2/5.0+(double)(i)/(255.0*4);
                    //foo2=double(i)/640;
                    // fill a rectangle with values of 255
                    if(i<60 & j<60)
                            foo2=1.0;
                    if(*bit_depth==8)
                            raw_images[iframe][count]=(unsigned char)(foo2*255);
                    else
                    {
                            //p=(unsigned short *)(&(raw_images[iframe][count*2]));
                            *p=(unsigned short)(foo2*(1<<(*bit_depth)));
                            //*p=(unsigned short)((double)(i)/((double)(im_w))*(1<<bit_depth));
                            //*p=i;
                            p++;
                    }
                    count++;
            }
            *img_acquired += 1;
            acquisition_times[*img_acquired-1]=(float)(timer->elapsed());            
           // acquisition_times[*img_acquired]=GetTickCount();
    }
#endif

}
/***************************************************************************/
void SimulatedCameraClass::finish_acquisition(void)
{
    int i;
}
