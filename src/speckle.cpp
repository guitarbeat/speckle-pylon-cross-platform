#include "speckle.h"
#include "jet_colormap.h"
#include "cool_colormap.h"
#include "hot_colormap.h"
#include "autumn_colormap.h"
#include "pmkmp_colormap.h"
#include "greens_colormap.h"

//Q_DECLARE_METATYPE(QCameraInfo)

/***************************************************************************/
SpeckleClass::SpeckleClass()
{
    acquisition = new AcquisitionClass;

    findAvailableCameras();
}
/***************************************************************************/
void SpeckleClass::setRawColormap(int idx)
{
    switch(idx) {
    case 0:
        live_palette = gray_palette;
        break;
    case 1:
        live_palette = jet_palette;
        break;
    case 2:
        live_palette = reverse_jet_palette;
        break;
    case 3:
        live_palette = hot_palette;
        break;
    case 4:
        live_palette = cool_palette;
        break;
    case 5:
        live_palette = autumn_palette;
        break;
    case 6:
        live_palette = pmkmp_palette;
        break;
    case 7:
        live_palette = greens_palette;
        break;
    }

}
/***************************************************************************/
void SpeckleClass::setRawColormap(QString cmap_string)
{
    // fill in colormap by string matching
    if(cmap_string.contains("gray", Qt::CaseInsensitive))
        live_palette = gray_palette;

    if(cmap_string.contains("reverse jet", Qt::CaseInsensitive))
        live_palette = reverse_jet_palette;
    else if(cmap_string.contains("jet",Qt::CaseInsensitive))
        live_palette = jet_palette;

    if(cmap_string.contains("hot", Qt::CaseInsensitive))
        live_palette = hot_palette;
    if(cmap_string.contains("cool", Qt::CaseInsensitive))
        live_palette = cool_palette;
    if(cmap_string.contains("autumn", Qt::CaseInsensitive))
        live_palette = autumn_palette;
    if(cmap_string.contains("pmkmp", Qt::CaseInsensitive))
        live_palette = pmkmp_palette;
    if(cmap_string.contains("green", Qt::CaseInsensitive))
        live_palette = greens_palette;
}
/***************************************************************************/
void SpeckleClass::setSCColormap(QString cmap_string)
{
    // fill in colormap by string matching
    if(cmap_string.contains("gray", Qt::CaseInsensitive))
        sc_palette = gray_palette;

    if(cmap_string.contains("reverse jet", Qt::CaseInsensitive))
        sc_palette = reverse_jet_palette;
    else if(cmap_string.contains("jet",Qt::CaseInsensitive))
        sc_palette = jet_palette;

    if(cmap_string.contains("hot", Qt::CaseInsensitive))
        sc_palette = hot_palette;
    if(cmap_string.contains("cool", Qt::CaseInsensitive))
        sc_palette = cool_palette;
    if(cmap_string.contains("autumn", Qt::CaseInsensitive))
        sc_palette = autumn_palette;
    if(cmap_string.contains("pmkmp", Qt::CaseInsensitive))
        sc_palette = pmkmp_palette;
    if(cmap_string.contains("green", Qt::CaseInsensitive))
        sc_palette = greens_palette;
    if(cmap_string.contains("reverse gray", Qt::CaseInsensitive))
        sc_palette = reverse_gray_palette;
}
/***************************************************************************/
void SpeckleClass::setSCControlPoints(QPolygonF poly)
{
    int i;

    sc_ctrl_pts.clear();
    for(i=0;i<3; i++)
    {
        const QPointF p = poly[i];
        {
            CImg<float> vec(1,1,1,2);
            vec(0,0,0,0) = static_cast<float>(p.x());
            vec(0,0,0,1) = static_cast<float>(p.y());
            sc_ctrl_pts.insert(vec,i);
        }
    }

    if(sc_ctrl_pts.size()>2 && video_in_ctrl_pts.size()>2)
        overlays.ComputeTransform(video_in_ctrl_pts, sc_ctrl_pts, &VideoTform);
    if(!VideoTform.is_empty())
        overlays.GeneratePixelMapping(captured_rgb, sc_imgf,
                                      VideoTform, &VideoPixelMapping);

}
/***************************************************************************/
void SpeckleClass::setVideoInControlPoints(QPolygonF poly)
{
    int i;

    video_in_ctrl_pts.clear();
    for(i=0;i<3; i++)
    {
        const QPointF p = poly[i];
        {
            CImg<float> vec(1,1,1,2);
            vec(0,0,0,0) = static_cast<float>(p.x());
            vec(0,0,0,1) = static_cast<float>(p.y());
            video_in_ctrl_pts.insert(vec,i);
        }
    }

    if(sc_ctrl_pts.size()>2 && video_in_ctrl_pts.size()>2)
        overlays.ComputeTransform(video_in_ctrl_pts, sc_ctrl_pts, &VideoTform);
    if(!VideoTform.is_empty())
        overlays.GeneratePixelMapping(captured_rgb, sc_imgf,
                                      VideoTform, &VideoPixelMapping);

}
/***************************************************************************/
#ifdef SPECKLE_USE_OPENCV
void SpeckleClass::registerCamerasFromQRCodes(void)
{
    bool overlayQR_detected=false;
    bool liveQR_detected=false;
    bool scQR_detected=false;
    QPolygonF overQR_poly, liveQR_poly, scQR_poly;

    // make sure images have been created
    if(overlay_img_rgb.width()<10)
        return;
    if(sc_img_rgb.width()<10 || live_img_rgb.width()<10)
        return;

    // create opencv Mat copy of overlay image
    Mat overImage, over_bbox;
    overImage = overlay_img_rgb._cimg2cvmat();

    // check for QR code
    QRCodeDetector qrDecoder;
    if(qrDecoder.detect(overImage, over_bbox))
    {
        // QR code was found
        overlayQR_detected=true;

        overQR_poly << QPointF(over_bbox.at<float>(0),over_bbox.at<float>(1))
                    << QPointF(over_bbox.at<float>(2),over_bbox.at<float>(3))
                    << QPointF(over_bbox.at<float>(4),over_bbox.at<float>(5));
        qDebug() << "found QR in overImage. ";
   }

    // create opencv Mat copy of sc image
    Mat liveImage, live_bbox;
    liveImage = live_img_rgb._cimg2cvmat();

    // check for QR code
    QRCodeDetector qrDecoder_live;
    if(qrDecoder_live.detect(liveImage, live_bbox))
    {
        // QR code was found
        liveQR_detected=true;
        // subtract half of NxN width to map onto SC image dimensions
        live_bbox = live_bbox - NxN/2;
        liveQR_poly << QPointF(live_bbox.at<float>(0),live_bbox.at<float>(1))
                    << QPointF(live_bbox.at<float>(2),live_bbox.at<float>(3))
                    << QPointF(live_bbox.at<float>(4),live_bbox.at<float>(5));
        qDebug() << "found QR in liveImage. ";
    }

    // check sc image for QR code
    Mat scImage, sc_bbox;
    scImage = sc_img_rgb._cimg2cvmat();

    // check for QR code
    QRCodeDetector qrDecoder_sc;
    if(qrDecoder_sc.detect(scImage, sc_bbox))
    {
        // QR code was found
        scQR_detected=true;
        scQR_poly << QPointF(sc_bbox.at<float>(0),sc_bbox.at<float>(1))
                  << QPointF(sc_bbox.at<float>(2),sc_bbox.at<float>(3))
                  << QPointF(sc_bbox.at<float>(4),sc_bbox.at<float>(5));
        qDebug() << "found QR in scImage. ";
    }

    if(overlayQR_detected && (liveQR_detected || scQR_detected))
    {
        if(scQR_detected)
            setSCControlPoints(scQR_poly);
        else if(liveQR_detected)
            setSCControlPoints(liveQR_poly);

        setVideoInControlPoints(overQR_poly);
        emit videoInCtrlPointsChangedFromQR(overQR_poly);
        emit scCtrlPointsChangedFromQR(liveQR_poly);
    }
}
#endif
/***************************************************************************/
void SpeckleClass::findAvailableCameras(void)
{
    int num_cameras=0;
    cameras_available.clear();
    cameraDescription tmp_camera;

    qDebug() << "==============================================";
    qDebug() << "LOOKING FOR CAMERA DEVICES";

    // compile a list of all available cameras and populate list

    // look for pylon devices
#ifdef USE_PYLON
    CTlFactory& tlFactory = CTlFactory::GetInstance();
    // Get all attached devices and exit application if no device is found.
    DeviceInfoList_t devices;
    if ( tlFactory.EnumerateDevices(devices) >0 )
    {
        for ( size_t i = 0; i < devices.size(); ++i)
        {
            CInstantCamera camera(tlFactory.CreateDevice(devices[i]));
            qDebug().nospace() << num_cameras << ": Pylon Device: "
                               << camera.GetDeviceInfo().GetModelName()
                               << " (pylon/" << i << ")";
            tmp_camera.camera_type=CAMERA_PYLON;
            tmp_camera.description=QString(camera.GetDeviceInfo().GetModelName());
            tmp_camera.local_index=i;
            cameras_available.insert(num_cameras, tmp_camera);
            num_cameras++;
        }
    }
#endif

    // need to figure out why this doesnt work any more
#ifdef NO
    // usb cameras
    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    int usb_count=0;
    for (const QCameraInfo &cameraInfo : cameras)
    {
        qDebug().nospace() << num_cameras << ": USB Device: "
                           << cameraInfo.description()
                           << " (usb/" << usb_count << ")";
        tmp_camera.camera_type=CAMERA_FRAMEGRABBER;
        tmp_camera.description=cameraInfo.description();
        tmp_camera.local_index=usb_count;
        cameras_available.insert(num_cameras, tmp_camera);
        num_cameras++;
        usb_count++;
    }
#endif

#ifdef SPECKLE_USE_OPENCV

    // Get friendly names for USB video devices
    QStringList videoDeviceNames = getVideoDeviceNames();

    // usb cameras - check first 3 devices
    VideoCapture test_cam;
    int cv_count=0;
    for(cv_count=0;cv_count<3;cv_count++)
    {
        test_cam.open(cv_count);
        if(test_cam.isOpened())
        {
            qDebug().nospace().noquote() << num_cameras << ": USB Device: "
                                         << videoDeviceNames[cv_count]
                                         << " (usb/" << cv_count << ")";
            test_cam.release();

            // manually add a usb camera
            tmp_camera.camera_type=CAMERA_FRAMEGRABBER;
            tmp_camera.description=videoDeviceNames[cv_count];
            tmp_camera.local_index=cv_count;
            cameras_available.insert(num_cameras, tmp_camera);
            num_cameras++;
        }
    }
#endif

    // last camera in list is simulated camera
    qDebug().nospace() << num_cameras << ": Simulated Camera";
    tmp_camera.camera_type=CAMERA_NONE;
    tmp_camera.description=QString("Simulated Camera");
    tmp_camera.local_index=0;
    cameras_available.insert(num_cameras, tmp_camera);
    num_cameras++;

    qDebug() << "==============================================";
}
/***************************************************************************/
#ifdef SPECKLE_USE_OPENCV
QStringList SpeckleClass::getVideoDeviceNames(void)
{
    // Based on Microsoft documentation for "Selecting a Capture Device"
    // https://docs.microsoft.com/en-us/windows/win32/directshow/selecting-a-capture-device

    QStringList devices;
    IEnumMoniker *pEnum = nullptr;
    ICreateDevEnum *pDevEnum;

    HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, nullptr,
        CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));

    if (SUCCEEDED(hr))
    {
        // Create an enumerator for the category.
        hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
        if (hr == S_FALSE)
            return devices;
        pDevEnum->Release();
    }

    IMoniker *pMoniker = nullptr;
    while (pEnum->Next(1, &pMoniker, nullptr) == S_OK)
    {
        IPropertyBag *pPropBag;
        HRESULT hr = pMoniker->BindToStorage(nullptr, nullptr, IID_PPV_ARGS(&pPropBag));
        if (FAILED(hr))
        {
            pMoniker->Release();
            continue;
        }

        VARIANT var;
        VariantInit(&var);

        // Get friendly name.
        hr = pPropBag->Read(L"FriendlyName", &var, nullptr);
        if (SUCCEEDED(hr))
        {
            devices << QString::fromUtf16(reinterpret_cast<ushort*>(var.bstrVal));
            VariantClear(&var);
        }

        pPropBag->Release();
        pMoniker->Release();
    }

    return devices;
}
#endif
/***************************************************************************/
void SpeckleClass::setCamera(cameraDescription c)
{
    qDebug() << "\nSETTING CAMERA:";

    if(theCamera)
        theCamera->cleanup();
#ifdef USE_PYLON
    if(c.camera_type==CAMERA_PYLON)
        theCamera = &pylonCamera;
#endif
#ifdef SPECKLE_USE_OPENCV
    if(c.camera_type==CAMERA_FRAMEGRABBER)
    {
        theCamera = &openCVCamera;
        theCamera->camera_name = c.description;
    }
#endif
    if(c.camera_type==CAMERA_NONE)
        theCamera = &simulatedCamera;
    theCamera->openCamera(c.local_index);
}
/***************************************************************************/
void SpeckleClass::init_colormaps(void)
{
	int i;
	long count;
	unsigned char red[256], green[256], blue[256];

	jet_palette.resize(256,1,1,3);
    reverse_jet_palette.resize(256,1,1,3);
    gray_palette.resize(256,1,1,3);
	gray_sat_palette.resize(256,1,1,3);
	cool_palette.resize(256,1,1,3);
	hot_palette.resize(256,1,1,3);
	autumn_palette.resize(256,1,1,3);
    pmkmp_palette.resize(256,1,1,3);
    greens_palette.resize(256,1,1,3);
    neon_palette.resize(256,1,1,3);
    reverse_gray_palette.resize(256,1,1,3);

	sc_palette.resize(256,1,1,3);
	live_palette.resize(256,1,1,3);
	tc_palette.resize(256,1,1,3);

    // set up jet colormap
	count=0;
	for(i=0;i<256;i++)
	{
		red[i]=jet_colormap1D[count]; //jet_colormap[i].R;
		green[i]=jet_colormap1D[count+1]; //jet_colormap[i].G;
		blue[i]=jet_colormap1D[count+2]; //jet_colormap[i].B;
		count+=3;
	}

	cimg_forX(jet_palette,x) { 
	jet_palette(x,0) = red[x]; 
	jet_palette(x,1) = green[x]; 
	jet_palette(x,2) = blue[x]; 
	}

    // set up hot colormap
	count=0;
	for(i=0;i<256;i++)
	{
		red[i]=hot_colormap1D[count]; //jet_colormap[i].R;
		green[i]=hot_colormap1D[count+1]; //jet_colormap[i].G;
		blue[i]=hot_colormap1D[count+2]; //jet_colormap[i].B;
		count+=3;
	}

	cimg_forX(hot_palette,x) { 
	hot_palette(x,0) = red[x]; 
	hot_palette(x,1) = green[x]; 
	hot_palette(x,2) = blue[x]; 
	}

    // set up cool colormap
	count=0;
	for(i=0;i<256;i++)
	{
		red[i]=cool_colormap1D[count]; //jet_colormap[i].R;
		green[i]=cool_colormap1D[count+1]; //jet_colormap[i].G;
		blue[i]=cool_colormap1D[count+2]; //jet_colormap[i].B;
		count+=3;
	}

	cimg_forX(cool_palette,x) { 
	cool_palette(x,0) = red[x]; 
	cool_palette(x,1) = green[x]; 
	cool_palette(x,2) = blue[x]; 
	}

    // set up autumn colormap
	count=0;
	for(i=0;i<256;i++)
	{
		red[i]=autumn_colormap1D[count]; //jet_colormap[i].R;
		green[i]=autumn_colormap1D[count+1]; //jet_colormap[i].G;
		blue[i]=autumn_colormap1D[count+2]; //jet_colormap[i].B;
		count+=3;
	}

	cimg_forX(autumn_palette,x) { 
	autumn_palette(x,0) = red[x]; 
	autumn_palette(x,1) = green[x]; 
	autumn_palette(x,2) = blue[x]; 
	}

	// set up gray palette
	for(i=0;i<256;i++)
	{
		red[i]=i;
		blue[i]=i;
		green[i]=i;
	}
	cimg_forX(gray_palette,x) { 
	gray_palette(x,0) = red[x]; 
	gray_palette(x,1) = green[x]; 
	gray_palette(x,2) = blue[x]; 
	}

    // set up pmkmp palette
    count=0;
    for(i=0;i<256;i++)
    {
        red[i]=pmkmp_colormap1D[count];
        green[i]=pmkmp_colormap1D[count+1];
        blue[i]=pmkmp_colormap1D[count+2];
        count+=3;
    }
    cimg_forX(pmkmp_palette,x) {
    pmkmp_palette(x,0) = red[x];
    pmkmp_palette(x,1) = green[x];
    pmkmp_palette(x,2) = blue[x];
    }

    // set up greens palette
    count=0;
    for(i=0;i<256;i++)
    {
        red[i]=greens_colormap1D[count];
        green[i]=greens_colormap1D[count+1];
        blue[i]=greens_colormap1D[count+2];
        count+=3;
    }
    cimg_forX(greens_palette,x) {
    greens_palette(x,0) = red[x];
    greens_palette(x,1) = green[x];
    greens_palette(x,2) = blue[x];
    }

    // set up single-color neon palette
    count=0;
    for(i=0;i<256;i++)
    {
        red[i]=0;
        green[i]=255;
        blue[i]=0;
        count+=3;
    }
    cimg_forX(neon_palette,x) {
    neon_palette(x,0) = red[x];
    neon_palette(x,1) = green[x];
    neon_palette(x,2) = blue[x];
    }

	// saturated gray palette
	gray_sat_palette=gray_palette;
    gray_sat_palette(255,0)=red_chan;
    gray_sat_palette(255,1)=green_chan;
    gray_sat_palette(255,2)=blue_chan;

    // flip jet palette
    cimg_forX(reverse_jet_palette,x) {
    reverse_jet_palette(x,0) = jet_palette(256-x,0);
    reverse_jet_palette(x,1) = jet_palette(256-x,1);
    reverse_jet_palette(x,2) = jet_palette(256-x,2);
    }

    // reverse gray palette
    cimg_forX(reverse_gray_palette,x) {
    reverse_gray_palette(x,0) = gray_palette(256-x,0);
    reverse_gray_palette(x,1) = gray_palette(256-x,1);
    reverse_gray_palette(x,2) = gray_palette(256-x,2);
    }
}
/******************************************************************************************/
void SpeckleClass::SetupMemoryBuffers(void)
{
    int i,j, ii;
    int img_posn;

    Nimg_per_buffer=(int)(1e6*MAX_BUFFER_MEMORY/((float)(theCamera->im_w*theCamera->im_h*theCamera->bytes_pixel)));

    if(write_mode==WRITE_CONTINUOUS && acquire_flag==ACQUISITION_MODE)
    {
        if(theCamera->bytes_pixel>1)
        {
            //raw_list16.clear();
            if(raw_list16.size()>1)
                raw_list16.remove(1, raw_list16.size()-1);
            raw_list16.insert(Nimg_per_buffer-1, 1);
            for(j=0;j<Nimg_per_buffer;j++)
            {
                raw_list16[j].resize(theCamera->im_w, theCamera->im_h,1,-1);
            }
            //raw_buf=(unsigned char *)(raw_list16[0].data());
            // set up pointers that wrap around
            for(ii=0; ii<MAX_NUMBER_IMG_BUFFERS;ii++)
            {
                img_posn=ii%(Nimg_per_buffer);
                raw_images[ii]= (unsigned char *)(raw_list16[img_posn].data()); // &(speckle->raw_buf[img_posn*speckle->theCamera->im_h*speckle->theCamera->im_w*speckle->theCamera->bytes_pixel]);
            }
        }
        else
        {            
            raw_list.clear();
            raw_list.assign(Nimg_per_buffer, theCamera->im_w, theCamera->im_h, 1, theCamera->color_planes);
#ifdef NO
            if(raw_list.size()>1)
                raw_list.remove(1,raw_list.size()-1);
            raw_list.insert(Nimg_per_buffer-1, 1);
            qDebug() << "Nimg_per_buf= " << Nimg_per_buffer << ". MAX= " << MAX_NUMBER_IMG_BUFFERS << "raw_list.size= " << raw_list.size();
            for(j=0;j<Nimg_per_buffer;j++)
            {
                raw_list[j].resize(theCamera->im_w, theCamera->im_h,1,-1);
            }
#endif
            //raw_buf=(unsigned char *)(raw_list[0].data());
            // set up pointers that wrap around
            for(ii=0; ii<MAX_NUMBER_IMG_BUFFERS;ii++)
            {
                img_posn=ii%(Nimg_per_buffer);
                raw_images[ii]= raw_list[img_posn].data(); // &(speckle->raw_buf[img_posn*speckle->theCamera->im_h*speckle->theCamera->im_w*speckle->theCamera->bytes_pixel]);
            }
        }
    }
    else
    {     
        if(theCamera->bytes_pixel>1)
        {
            //raw_list16.clear();
            if(raw_list16.size()>1)
                raw_list16.remove(1,raw_list16.size()-1);
            raw_list16.insert(MAX_NUMBER_IMG_BUFFERS-1, 1);
            for(i=0;i<MAX_NUMBER_IMG_BUFFERS;i++)
            {
                raw_list16[i].resize(theCamera->im_w, theCamera->im_h, 1, theCamera->color_planes);
                raw_images[i] = (unsigned char *)(raw_list16[i].data());
            }
        }
        else
        {
            raw_list.clear();
            raw_list.assign(Nimg_per_buffer, theCamera->im_w, theCamera->im_h, 1, theCamera->color_planes);
            for(i=0;i<MAX_NUMBER_IMG_BUFFERS;i++)
                raw_images[i] = raw_list[i%raw_list.size()].data();
        }
    }

    // set up circular list of all possible image pointers for live mode
    if(acquire_flag==FOCUS_MODE && theCamera->bytes_pixel==1)
        for(i=0;i<MAX_NUMBER_IMG_BUFFERS;i++)
            raw_images[i] = raw_list[i%raw_list.size()].data();

    if(write_mode==WRITE_AFTER_SEQUENCE && acquire_flag==ACQUISITION_MODE && theCamera->bytes_pixel==1)
        for(i=0;i<MAX_NUMBER_IMG_BUFFERS;i++)
            raw_images[i] = raw_list[i%raw_list.size()].data();

    if(write_mode==WRITE_CONTINUOUS && acquire_flag==ACQUISITION_MODE && save_overlay_video)
    {
        overlay_frames_to_write.clear();
        overlay_frames_to_write.insert(NUM_VIDEO_FRAME_BUFFERS); // inserts this many empty buffers
    }
    if(write_mode==WRITE_CONTINUOUS && acquire_flag==ACQUISITION_MODE && save_sc_video)
    {
        sc_frames_to_write.clear();
        sc_frames_to_write.insert(NUM_VIDEO_FRAME_BUFFERS); // inserts this many empty buffers
    }

    if(acquire_flag==ACQUISITION_MODE && save_input_video && overlays.bg_src == SRC_VIDEO)
    {
        video_in_frames_to_write.clear();
        video_in_frames_to_write.insert(NUM_VIDEO_FRAME_BUFFERS); // inserts this many empty buffers
    }

    acquisition_times = QVector<float>();
    acquisition_times.reserve(1e5);

    sc_acquisition_times = QVector<float>();
    sc_acquisition_times.reserve(1e5);

    video_in_acquisition_times = QVector<float>();
    video_in_acquisition_times.reserve(1e5);
}
/******************************************************************************************/
void SpeckleClass::Write_SpeckleContrast(QString fname)
{
  unsigned short foo;

  QFile file(fname);
  file.open(QIODevice::WriteOnly);
  QDataStream out(&file);
  out.writeRawData((const char *)(&sc_h), sizeof(unsigned short));
  out.writeRawData((const char *)(&sc_w), sizeof(unsigned short));
  foo=1;
  out.writeRawData((const char *)(&foo), sizeof(unsigned short));
  out.writeRawData((const char *)SC, sc_w*sc_h*sizeof(float));
  file.close();
  
  // post a message to update list of sc files
  // string must be defined as CString *, and allocated within the function for this to work!!
  //if(pParam != NULL)
	//::PostMessage((HWND)pParam, WM_ADD_TO_SC_LIST,0,(LPARAM)s);

}
/******************************************************************************************/
void SpeckleClass::Write_TC(QString fname)
{
  unsigned short foo;

  QFile file(fname);
  file.open(QIODevice::WriteOnly);
  QDataStream out(&file);
  out.writeRawData((const char *)(&sc_h), sizeof(unsigned short));
  out.writeRawData((const char *)(&sc_w), sizeof(unsigned short));
  foo=1;
  out.writeRawData((const char *)(&foo), sizeof(unsigned short));
  out.writeRawData((const char *)rTC, sc_w*sc_h*sizeof(float));
  file.close();

}

/*************************************************************************/
void SpeckleClass::AddToLogFile(char *str)
{
//	char tmpname[512];
//	FILE *fp;
//	time_t rawtime;
//	struct tm * timeinfo;

//    sprintf(tmpname,"%s.log",filename.toUtf8());
//	fp=fopen(tmpname,"a");

//	time ( &rawtime );
//	timeinfo = localtime ( &rawtime );
//	fprintf(fp, "%s", asctime(timeinfo));
//	fprintf(fp, "%s\n\n", str);
//	fclose(fp);

    AddToLogFile(QString::fromUtf8(str));

}
/*************************************************************************/
void SpeckleClass::AddToLogFile(QString str)
{
    QFile file(filename+".log");

    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    QTextStream out(&file);

    out << QDateTime::currentDateTime().toString()  << ", " << str << "\n";
    file.close();
}
/*************************************************************************/
QString SpeckleClass::GetDateTimeFilename(void)
{
    char tmp_str[512];
    // Use Qt date-time on all platforms
    const QDateTime now = QDateTime::currentDateTime();
    const QString stamp = now.toString("yyyyMMddhhmmsszzz");
    snprintf(tmp_str, sizeof(tmp_str), "img.%s", stamp.toUtf8().constData());
    return(QString(tmp_str));
}
/*************************************************************************/
void SpeckleClass::Set_sc_width_height(void)
{
    sc_w = theCamera->im_w - NxN + 1;
    sc_h = theCamera->im_h - NxN + 1;

    sc_img.resize(sc_w, sc_h, 1, 1);
    sc_imgf.resize(sc_w, sc_h, 1, 1);
    sc_img_rgb.resize(sc_w, sc_h, 1, 3);
}
/*************************************************************************/
void SpeckleClass::setupCameraAOI(QRectF rect)
{
    int selected_top = (int)(rect.top());
    int selected_left = (int)(rect.left());
    int selected_width = (int)(rect.width());
    int selected_height = (int)(rect.height());
    if(acquire_flag==IDLE_MODE)
    {
        theCamera->setAOI(selected_top, selected_left, selected_width, selected_height);
        emit speckleAOIChanged();
    }
}
/*************************************************************************/
bool SpeckleClass::saveAnything(void)
{
    return (save_raw || save_SC || save_sc_video || save_overlay_video || save_input_video);
}
