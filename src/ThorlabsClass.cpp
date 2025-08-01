#include "ThorlabsClass.h"
#include "camera.h"

ThorlabsClass::ThorlabsClass(QObject *parent) : QObject(parent) {

}
/*******************************************************/
int ThorlabsClass::initialize(unsigned short *width, unsigned short *height,
                            unsigned short *top, unsigned short *left, float *exposure_time,
                            unsigned short *max_w, unsigned short *max_h, unsigned short *bits_per_pixel,
                           QString *name, QString *descr, unsigned short *cam_type, int *color_planes)
{

    // Initializes dll
    if (tl_camera_sdk_dll_initialize())
    {
            qDebug() << "Failed to initialize thorlabs dll!";
            return 0;
    }
    else
        qDebug() << "Successfully initialized thorlabs dll";


    // Open the SDK
    if (tl_camera_open_sdk())
    {
            qDebug() << "Failed to open thorlabs SDK!\n";
            tl_camera_sdk_dll_terminate();
            return 0;
    }
    else
        qDebug() << "Successfully opened thorlabs SDK";

    char camera_ids[1024];

    camera_handle = 0;

    // Discover cameras.
    if (tl_camera_discover_available_cameras(camera_ids, 1024))
    {
        qDebug() << "Failed to get available cameras!\n";
        close_sdk_dll();
        return 0;
    }
    else
        qDebug() << "camera IDs: " << QString(camera_ids);

    // Check for no cameras.
    if (!strlen(camera_ids))
    {
        qDebug() << "Error: did not find any cameras!";
        close_sdk_dll();
        return 0;
    }

    // Camera IDs are separated by spaces.
    char* p_space = strchr(camera_ids, ' ');
    if (p_space)
    {
        *p_space = '\0'; // isolate the first detected camera
    }

    char first_camera[256];

    // Copy the ID of the first camera to separate buffer (for clarity)
    strcpy_s(first_camera, 256, camera_ids);

    qDebug() << "First camera_id = " << first_camera;

    // Connect to the camera (get a handle to it).
    if (tl_camera_open_camera(first_camera, &camera_handle))
    {
        qDebug() << "Failed to open camera!";
        tl_camera_close_sdk();
        return 0;
    }

    qDebug() << "Camera handle = " << camera_handle;

    char tmp_name[512];
    if(tl_camera_get_name(camera_handle, tmp_name, 512))
    {
        qDebug() << "could not determine camera name";
    }


    this->camera_name = name; // set pointer between parent class
    this->camera_description = descr;
    name->append(QString(tmp_name));
    descr->append(QString(tmp_name));

    qDebug() << "Camera Name:" << name;

    this->top = top;
    this->left = left;
    *top = 0;
    *left = 0;

    this->max_height = max_h; // set pointer in this class to parent
    this->max_width = max_w;

    int tmp_w, tmp_h;
    tl_camera_get_sensor_height(camera_handle, &tmp_h);
    tl_camera_get_sensor_width(camera_handle, &tmp_w);
    *max_w = tmp_w;
    *max_h = tmp_h;
    //int tmp_w_min, tmp_w_max, tmp_h_min, tmp_h_max;
    //tl_camera_get_image_width_range(camera_handle, &tmp_w_min, &tmp_w_max);
    //tl_camera_get_image_height_range(camera_handle, &tmp_h_min, &tmp_h_max);

    //min_width = tmp_w_min;
    //min_height =tmp_w_max;
    //qDebug() << "Max width, height:" << *max_w << *max_h;

    this->im_h = height;
    this->im_w = width;
    *height = *max_h;
    *width = *max_w;
    qDebug() << "Current width, height:" << *width << *height;

    // read bit depth
    bit_depth = bits_per_pixel; // set pointer to parent
    int tmp_bit_depth;
    tl_camera_get_bit_depth(camera_handle, &tmp_bit_depth);
    *bit_depth = tmp_bit_depth;
    this->color_planes = color_planes;
    *color_planes = 1;
    if(*bit_depth > 8)
        bytes_pixel=2;
    else
        bytes_pixel=1;

    qDebug() << "Setting Exposure Time";
    this->exp_time = exposure_time;
    //tl_camera_get_exposure_range(camera_handle, &exp_min, &exp_max);
    SetExposureTime(*exposure_time);

    // check gain of camera??

    // set up triggers

    // set up exposure output lines??

    this->camera_type = cam_type;
    *cam_type = CAMERA_THORLABS;

    qDebug() << "Thorlabs initialization complete";
    return(1);
}
/***************************************************************************/
void ThorlabsClass::GetPixelFormats(QStringList *pix_list)
{
    //node_vector node_list;

    pix_list->clear();
    qDebug() << "GetPixelFormats not implemented yet";

}
/*******************************************************/
void ThorlabsClass::SetBitDepth(QString bit_depth_str)
{
    qDebug() << "Thorlabs bit depth is fixed at " << *bit_depth;
    *color_planes = 1;

}
/*******************************************************/
void ThorlabsClass::SetExposureTime(float exp_ms)
{

    long long exposure_time;
    exposure_time = (long long)(exp_ms*1000);
    if(tl_camera_set_exposure_time(camera_handle, exposure_time))
        qDebug() << "Error setting exposure time to " << exposure_time;

}
/*******************************************************/
void ThorlabsClass::SetAOI(unsigned short top, unsigned short left,
                        unsigned short width, unsigned short height) {

    int upper_left_x = left;
    int upper_left_y = top;
    int lower_right_x = left + width - 1;
    int lower_right_y = top + height - 1;
    tl_camera_set_roi(camera_handle, upper_left_x, upper_left_y, lower_right_x, lower_right_y);

    // now check to make sure roi was set properly
    int ul_x, ul_y, lr_x, lr_y;
    tl_camera_get_roi(camera_handle, &ul_x, &ul_y, &lr_x, &lr_y);

    if( (ul_x!=upper_left_x) || (ul_y!=upper_left_y) || (lr_x!=lower_right_x) || (lr_y!=lower_right_y) )
        qDebug() << "Error setting AOI. Requested and returned ROIs do not match";

    emit postSpeckleMessage(QString("Set Camera AOI (x1 = %1, y1 = %2, x2 = %3, y2 = %4)")
                            .arg(ul_x).arg(ul_y).arg(lr_x).arg(lr_y));
}
/*******************************************************/
void ThorlabsClass::SetTrigger(QString trigger_str) {

    qDebug() << "hardware triggering not set up yet. Fix me!";
}
/*******************************************************/
int ThorlabsClass::InitializeAcquisition(int Nframes) {

    unsigned int frames_per_trigger;
    unsigned int extra_frames;

    // set to continuous acquisition for now
    tl_camera_set_frames_per_trigger_zero_for_unlimited(camera_handle, 0);

    //tl_camera_get_frames_per_trigger_zero_for_unlimited(camera_handle, &frames_per_trigger);

   // if(frames_per_trigger != Nframes+extra_frames)
   // {
   //     qDebug() << "Error setting frames/trigger. Requested " << Nframes << "but returned " << frames_per_trigger;
   //     return(0);
   // }

    int image_poll_timeout_ms = 100;
    int ret_val = 0;
    ret_val = tl_camera_set_image_poll_timeout(camera_handle, image_poll_timeout_ms);
    int image_poll_timeout_ms_set_value = 0;
    ret_val = tl_camera_get_image_poll_timeout(camera_handle, &image_poll_timeout_ms_set_value);
    if (image_poll_timeout_ms != image_poll_timeout_ms_set_value)
    {
        qDebug() << "timeout was not set correctly!";
        return(0);
    }

    // Start image acquisition
    if(tl_camera_arm(camera_handle, 2)) // 2 is recommended buffers, but seems too low
    {
        qDebug() << "error in tl_camera_arm";
        return(0);
    }

    qDebug() << "Thorlabs initialization complete";
    return(1);
}

/***************************************************************************/
void ThorlabsClass::AcquireImages(int Nframes, long *img_acquired,
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

#ifdef NO
    // Start image acquisition
    if(tl_camera_arm(camera_handle, 2)) // 2 is recommended buffers, but seems too low
    {
        qDebug() << "error in tl_camera_arm";
        return;
    }
#endif

    if(*img_acquired==0)
    {
        if(tl_camera_issue_software_trigger(camera_handle))
        {
            qDebug() << "Error in tl_camera_issue_software_triger";
            return;
        }
    }

    //initialize frame variables
    unsigned short *image_buffer = 0;
    int frame_count = 0;
    unsigned char *metadata = 0;
    int metadata_size_in_bytes = 0;

    int count=0;
    int ret_val=0;
    QTime t;
    t.start();
     while (count < Nframes )
     {
         ret_val = tl_camera_get_pending_frame_or_null(camera_handle, &image_buffer, &frame_count, &metadata, &metadata_size_in_bytes);
         if (ret_val != 0) // error codes are nonzero values
         {
             qDebug() << "Error while trying to get pending frame!";
             break;
         }
         if (!image_buffer)
         {
             //qDebug() << "image_buffer==NULL in AcquireImages()";
             continue; //timeout
         }
         // Grabbing was successful. Process the image.
            memcpy(raw_images[count+ista], image_buffer,(*im_w)*(*im_h)*bytes_pixel);
            *img_acquired += 1;
            acquisition_times[*img_acquired-1]=(float)(timer->elapsed());

            // figure out how to use metadata
            //qDebug() << "Pointer to image: " << image_buffer;
            //qDebug() << "Frame count: " << frame_count << " Images acquired: " << *img_acquired;
            //printf("Pointer to metadata: 0x%p\n", metadata);
            //printf("Metadata size in bytes: %d\n", metadata_size_in_bytes);

            count++;

    }
     //emit postSpeckleMessage(QString("approx acquisition frame rate=%1 fps").arg(Nframes*1000/(t.elapsed())));
     qDebug() << "approx acquisition frame rate= " << Nframes*1000/(t.elapsed()) << " fps";


}
/***************************************************************************/
/***************************************************************************/
void ThorlabsClass::finish_acquisition(void)
{
    // The camera is in continuous mode, stop image acquisition
     // Stop the camera.
     if (tl_camera_disarm(camera_handle))
     {
         qDebug() << "Failed to stop the camera!";
     }
}

/***************************************************************************/
int ThorlabsClass::close_sdk_dll(void)
{
// Close the SDK, then the dll
    int ret = 0;

    if (tl_camera_close_sdk())
    {
        printf("Failed to close SDK!\n");
        ret = 1;
    }

    if (tl_camera_sdk_dll_terminate())
    {
        printf("Failed to close dll!\n");
        ret = 1;
    }

    if (!ret) printf("SDK & dll closed\n");

    return ret;
}
