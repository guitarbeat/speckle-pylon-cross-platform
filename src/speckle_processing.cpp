#include <assert.h>
#include "speckle.h"
extern SpeckleClass *speckle;

/***********************************************************************************************************/
#ifdef USE_FLSCI
void set_baseline(float *sc_image, float *baseline_image, float *table) {
    // converts the image in sc to a tc image and inverts the tc values for baseline
	flsci_rct x;
	unsigned int i;
	unsigned int width = (unsigned int)(speckle->theCamera->im_w);
	unsigned int height = (unsigned int)(speckle->theCamera->im_h);
    unsigned int window = (unsigned int)(speckle->NxN);

	for(i=0; i<width*height; i++)
		baseline_image[i]=1.0;

	x = flsci_rct_init(table, TC_TABLE_SIZE, width, height, 2);
	flsci_rct_process(x, sc_image, baseline_image, baseline_image);
	flsci_rct_end(&x);

	for(i=0; i<width*height; i++)
		baseline_image[i]=1/baseline_image[i]; 
}
/***********************************************************************************************************/
#endif
void Save_Raw(QString fname)
{
	//HANDLE hFile;
	unsigned short foo;
	int i;
	//DWORD bytes_written;
	//char fname[256];

	//if(speckle->filename_format==SEQ_REP)
	//	sprintf(fname,"%s.%04i",speckle->filename,speckle->sets_acquired-1);
	//else
	//	sprintf(fname,"%s",speckle->filename);

	QFile file(fname);
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);
	out.writeRawData((const char *)(&(speckle->theCamera->im_h)), sizeof(unsigned short));
	out.writeRawData((const char *)(&(speckle->theCamera->im_w)), sizeof(unsigned short));
	out.writeRawData((const char *)(&(speckle->Nframes)), sizeof(unsigned short));
	foo=(unsigned short)(speckle->theCamera->exp_time);
	out.writeRawData((const char *)(&foo), sizeof(unsigned short));
        for(i=0;i<speckle->Nframes;i++)
            out.writeRawData((const char *)(speckle->raw_images[i]),
                                            speckle->theCamera->im_h*speckle->theCamera->im_w*speckle->theCamera->bytes_pixel*speckle->theCamera->color_planes);
        //out.writeRawData((const char *)(speckle->raw_buf),
        //	speckle->Nframes*speckle->theCamera->im_h*speckle->theCamera->im_w*speckle->theCamera->bytes_pixel*speckle->theCamera->color_planes);
	file.close();

	//hFile=CreateFile(fname.utf16(), 
	//			GENERIC_WRITE, 0,
	//		      NULL, CREATE_ALWAYS,
	//		      FILE_ATTRIBUTE_NORMAL,     // normal file 
	//		      NULL);
	//foo=(unsigned short)(speckle->theCamera->im_h);
	//WriteFile(hFile,&(foo),sizeof(unsigned short),
	//	    &bytes_written, NULL);
	//foo=(unsigned short)(speckle->theCamera->im_w);
	//WriteFile(hFile,&(foo),sizeof(unsigned short),
	//	    &bytes_written, NULL);
	//foo=(unsigned short)(speckle->Nframes);
	//WriteFile(hFile,&(foo),sizeof(unsigned short),
	//	    &bytes_written, NULL);
	//foo=(unsigned short)(speckle->theCamera->exp_time);
	//WriteFile(hFile,&(foo),sizeof(unsigned short),
	//	    &bytes_written, NULL);

	//for(i=0;i<speckle->Nframes;i++)
	//	WriteFile(hFile,speckle->raw_images[i],
	//	speckle->theCamera->im_h*speckle->theCamera->im_w*speckle->theCamera->bytes_pixel,
	//	    &bytes_written, NULL);

	//CloseHandle(hFile);
}
/*********************************************************************************/
int ReadSCFile(QString fname, float *sc)
{
	int ret=0;	
	unsigned short width, height, N;

	QFile file(fname);
	if (!file.open(QIODevice::ReadOnly))
         return(0);

	QDataStream in(&file);
	
	in.readRawData((char *)(&height), sizeof(unsigned short));
	in.readRawData((char *)(&width), sizeof(unsigned short));
	in.readRawData((char *)(&N), sizeof(unsigned short));
	in.readRawData((char *)(sc), sizeof(float)*width*height);

	speckle->sc_w = width;
	speckle->sc_h = height;

	file.close();

	return(1);
}
/*************************************************************************************/
int read_raw_image_file(QString fname, CImgList<unsigned char> *img_list, unsigned short *width, unsigned short *height,
						unsigned short *Nframes, unsigned short *exp_time)
{
	int read_count=0;        

	QFile file(fname);
	if (!file.open(QIODevice::ReadOnly))
         return(-1);

	QDataStream in(&file);
	
	in.readRawData((char *)(height), sizeof(unsigned short));
	in.readRawData((char *)(width), sizeof(unsigned short));
	in.readRawData((char *)(Nframes), sizeof(unsigned short));
	in.readRawData((char *)(exp_time), sizeof(unsigned short));

        // make sure img_list is big enough to hold the images
        if(img_list->size() < *Nframes)
            img_list->insert((*Nframes) - img_list->size(), img_list->size());


        for(int i=0;i< *Nframes; i++)
        {            
            img_list->at(i).resize(*width, *height, -1);
            //read_count=in.readRawData((char *)(buf), sizeof(unsigned char)*(*width)*(*height)*(*Nframes));
            read_count += in.readRawData((char *)(img_list->at(i).data()), sizeof(unsigned char)*(*width)*(*height));
        }
	file.close();

	if(read_count==(*width)*(*height)*(*Nframes))
		return(1);
	else
		return(-1);

}
/*************************************************************************************/
int read_raw_image_file_header(QString fname, unsigned short *width, unsigned short *height, 
						unsigned short *Nframes, unsigned short *exp_time)
{
	int read_count=0;

	QFile file(fname);
	if (!file.open(QIODevice::ReadOnly))
         return(-1);

	QDataStream in(&file);
	
	in.readRawData((char *)(height), sizeof(unsigned short));
	in.readRawData((char *)(width), sizeof(unsigned short));
	in.readRawData((char *)(Nframes), sizeof(unsigned short));
	in.readRawData((char *)(exp_time), sizeof(unsigned short));
	file.close();
	return(1);
}
/*************************************************************************************/
double SystemTime_to_Seconds(SYSTEMTIME st)
{
	double t;
	// returns the time in seconds (plus ms) as a double
	t=st.wHour*60.0*60.0 + st.wMinute*60.0 + st.wSecond + st.wMilliseconds/1000.0;
	return(t);
}
/*************************************************************************************/
void rescale_roi(CImg<int> roi, double zoom)
{
	// rescale an roi back to its full size
	// assumes that zoom is a percentage

	roi *= (float)(zoom)/100.0;
	//roi[0] = (int)(roi[0]/(zoom/100.0));
	//roi[1] = (int)(roi[1]/(zoom/100.0));
	//roi[3] = (int)(roi[3]/(zoom/100.0));
	//roi[4] = (int)(roi[4]/(zoom/100.0));
}
/*************************************************************************************/
void compute_sc16(CImgList<unsigned short> input, int window, int Nframes, float *sc)
{
	int i, im;
        int width = input[0].width();
        int height = input[0].height();
        CImg<float> raw(width, height);

        //cimg_forXYZ(raw,x,y,z){ raw(x,y,z)=input(x,y,z);}
	//for(i=0;i<width*height*Nframes;i++)
	//	raw.data(i)=(float)(input[i]);

	CImg<float> mask(window,window);
	mask.fill(1.0); ///((float)(window*window)));

	CImg<float> I(width, height);
	CImg<float> I2(width, height);
	CImg<float> sc_out(width, height);
	sc_out.fill(0.0);
	float N=(float)(window*window);
	for(im=0;im<Nframes;im++)
	{
            cimg_forXY(raw,x,y){ raw(x,y)=input[im](x,y);}
                //memcpy(I.data(), raw.data(0,0,im), width*height*sizeof(float));
        I=raw;
		I2=I;
		I2.sqr();
		I.convolve(mask,0);
		I2.convolve(mask,0);
		cimg_forXY(sc_out,x,y){
			sc_out(x,y) += sqrt((N*I2(x,y)-I(x,y)*I(x,y))/(N*(N-1)))/(I(x,y)/N);
		}
	}
	sc_out *= 1.0/((float)(Nframes));

	speckle->sc_w = width;
	speckle->sc_h = height;
    if((speckle->sc_imgf.width() != speckle->sc_w) || (speckle->sc_imgf.height() != speckle->sc_h))
        speckle->sc_imgf.resize(speckle->sc_w, speckle->sc_h, 1, 1, 0);

	int count=0;
	cimg_forXY(sc_out,x,y){
		sc[count]=sc_out(x,y);
		count++;
	}
	//for(i=0;i<width*height;i++)
	//	sc[i]=sc_out.data[i];

}
/*************************************************************************************/
void compute_sc8(CImgList<unsigned char> input, int window, int Nframes, float *sc)
{
    int i, im;
        int width = input[0].width();
        int height = input[0].height();
        CImg<float> raw(width, height);

        //cimg_forXYZ(raw,x,y,z){ raw(x,y,z)=input(x,y,z);}
    //for(i=0;i<width*height*Nframes;i++)
    //	raw.data(i)=(float)(input[i]);

    CImg<float> mask(window,window);
    mask.fill(1.0); ///((float)(window*window)));

    CImg<float> I(width, height);
    CImg<float> I2(width, height);
    CImg<float> sc_out(width, height);
    sc_out.fill(0.0);
    float N=(float)(window*window);
    for(im=0;im<Nframes;im++)
    {
            cimg_forXY(raw,x,y){ raw(x,y)=input[im](x,y);}
                //memcpy(I.data(), raw.data(0,0,im), width*height*sizeof(float));
        I=raw;
        I2=I;
        I2.sqr();
        I.convolve(mask,0);
        I2.convolve(mask,0);
        cimg_forXY(sc_out,x,y){
            sc_out(x,y) += sqrt((N*I2(x,y)-I(x,y)*I(x,y))/(N*(N-1)))/(I(x,y)/N);
        }
    }
    sc_out *= 1.0/((float)(Nframes));

    speckle->sc_w = width;
    speckle->sc_h = height;
    if((speckle->sc_imgf.width() != speckle->sc_w) || (speckle->sc_imgf.height() != speckle->sc_h))
        speckle->sc_imgf.resize(speckle->sc_w, speckle->sc_h, 1, 1, 0);

    int count=0;
    cimg_forXY(sc_out,x,y){
        sc[count]=sc_out(x,y);
        count++;
    }
    //for(i=0;i<width*height;i++)
    //	sc[i]=sc_out.data[i];

}
/*************************************************************************************/
void compute_sc_temporal(CImgList<unsigned char> input, int Nframes, float *sc)
{
    int width = input[0].width();
    int height = input[0].height();
    int im;
    double variance;
    double mean;
    CImg<double> stats;

    // Create new copy of raw data for processing (this might be unnecessary?
    CImg<unsigned char> raw_temporal(width,height,Nframes,1); // resize below
    CImg<float> sc_out(width,height);

	// copy pixel values from image 
    for(im=0;im<Nframes;im++)
    {
        cimg_forXY(raw_temporal,x,y) raw_temporal(x,y,im)=input[im](x,y);
    }

    // loop through z axis and calculate temporal contrast
    cimg_forXY(raw_temporal, x, y)
    {
        stats = raw_temporal.get_crop(x,y,0,x,y,Nframes-1).get_stats();
        sc_out(x,y) = sqrt(stats(3))/stats(2);
    }

    speckle->sc_w = width;
    speckle->sc_h = height;
    if((speckle->sc_imgf.width() != speckle->sc_w) || (speckle->sc_imgf.height() != speckle->sc_h))
        speckle->sc_imgf.resize(speckle->sc_w, speckle->sc_h, 1, 1, 0);

    int count=0;
    cimg_forXY(sc_out,x,y){
        sc[count]=sc_out(x,y);
        count++;
    }

}
/*************************************************************************************/
#ifdef USE_FLSCI
void compute_sc16_approx(CImgList<unsigned short> input, int window, int Nframes, float *sc,
						 flsci_sc sc_calc, int Imax, int Imin)
{
        CImgList<unsigned char> input_8;
        unsigned char *raw[100000];
        int ii;

        input_8.insert(Nframes);
        for(ii=0; ii<Nframes;ii++)
        {
            input_8[ii].resize(input[0].width(), input[0].height());
            raw[ii]= input_8[ii].data(); // pointer list to pass to flsci

            // truncate the input image to 8 bits
            cimg_forXY(input[ii],x,y)
            {
                if(input[ii](x,y)<Imin)
                    input_8[ii](x,y)=0;
                else if(input[ii](x,y)>Imax)
                    input_8[ii](x,y)=255;
		else
                    input_8[ii](x,y)=(unsigned char)(((float)(input[ii](x,y))-Imin)/((float)((Imax-Imin)))*255.0);
            }
        }       
	flsci_sc_process(sc_calc, raw, Nframes, sc);
}
#endif
/*************************************************************************************/
void ExtractRedChannel(CImgList<unsigned char> input, CImg<unsigned char> *red, unsigned char **output)
{
    // pulls out the red channel of the color input image (RGBA with R=B=G) from Bayer mask
    int i,j, iimg;
    int N = input.size();
    int w = input[0].width();
    int h = input[0].height();


    CImg<unsigned char> tmp_red(w, h, N);

    // extract red channel data
    for(i=0;i<input.size();i++)
    {
        cimg_forXY(input[i],x,y)
        {
            tmp_red(x,y,i) = input[i](x,y,0);
        }
    }

    // resize output now that we know how many red pixels there are
    red->resize(w, h, N);
    // fill in output
    cimg_forXYZ(*red,x,y,z)
    {
        *(red->data(x,y,z)) = tmp_red(x,y,z);
    }

    // fill in pointers to output for speckle processing
    for(i=0;i<N;i++)
    {
        output[i] = red->data(0,0,i);
    }

}
/*************************************************************************************/
void ExtractRedPixelsFromBayer(CImgList<unsigned char> input, CImg<unsigned char> *red, unsigned char **output)
{
    // pulls out the red channel of the color input image (RGBA with R=B=G) from Bayer mask
    int i,j, iimg;
    int N = input.size();
    int w = input[0].width();
    int h = input[0].height();


    CImg<unsigned char> tmp_red(w, h, N);
    CImg<unsigned char> tmp_red_sm((int)(w/2)+10, (int)(h/2)+10, N); // this will be properly resized later

    // extract red channel data
    for(i=0;i<input.size();i++)
    {
        cimg_forXY(input[i],x,y)
        {
            tmp_red(x,y,i) = input[i](x,y,0);
        }
    }

    // now extract red pixels from Bayer mask
    // matlab equivalent of tmp_red_sm = tmp_red(1:2:end, 1:2:end, :)
    int icount=0;
    int jcount=0;
    for(iimg=0;iimg<N;iimg++)
    {
        icount=0;
        jcount=0;
        for(j=0;j<h;j+=2)
        {
            icount=0;
            for(i=0;i<w;i+=2)
            {
                tmp_red_sm(icount, jcount, iimg) = tmp_red(i,j,iimg);
                icount++;
            }
            jcount++;
        }
    }

    // resize output now that we know how many red pixels there are
    red->resize(icount, jcount, N);
    // fill in output
    cimg_forXYZ(*red,x,y,z)
    {
        *(red->data(x, y, z)) = tmp_red_sm(x,y,z);
    }

    // fill in pointers to output for speckle processing
    for(i=0;i<N;i++)
    {
        output[i] = red->data(0,0,i);
    }

}
#ifdef SPECKLE_USE_OPENCV
/*****************************************************************/
void OpenCVMat_to_CImg(Mat *cv_in, CImg<unsigned char> *cimg_out)
{
    // converts the OpenCV mat input to a CImg
    // input mat is assumed to be 24-bit BGR format
    // output is 24-bit RGB CImg format
    int idx;
    int w = cv_in->cols;
    int h = cv_in->rows;
    cimg_out->resize(w, h, 1, 3);

    //unsigned char *p = cv_in->data;
    //cout << "starting loop" << endl;
    //qDebug() << "w,h = " << w<<h<< " channels= " << cv_in->at<cv::Vec3b>(900,500)<< endl;
    cimg_forXY(*cimg_out,x,y)
    {
        //idx = 3*w*x*y + 3*x;
        // opencv pixel access code from https://stackoverflow.com/questions/8932893/accessing-certain-pixel-rgb-value-in-opencv
        *cimg_out->data(x,y,0,0) = cv_in->at<cv::Vec3b>(y,x)[2]; // why are x and y reversed???
        *cimg_out->data(x,y,0,1) = cv_in->at<cv::Vec3b>(y,x)[1];
        *cimg_out->data(x,y,0,2) = cv_in->at<cv::Vec3b>(y,x)[0];
    }
    //cout << "done";

}
/*****************************************************************/
void CImg_to_OpenCVMat(CImg<unsigned char> *cimg_in, Mat *cv_out)
{
    // converts the CImg rgb to OpenCV mat
    // input CImg is assumed to be 24-bit RGB format
    // output is 24-bit BGR Opencv mat format

    if(cimg_in->width()!=cv_out->cols || cimg_in->height()!=cv_out->rows)
    {
        qDebug() << "image size mismatch in CImg_to_OpenCVMat. Input= " << cimg_in->width()<< "x"<<cimg_in->height() <<
                 ". Ouptut= " << cv_out->cols << "x" << cv_out->rows;
        return;
    }

    cimg_forXY(*cimg_in,x,y)
    {
        //idx = 3*w*x*y + 3*x;
        // opencv pixel access code from https://stackoverflow.com/questions/8932893/accessing-certain-pixel-rgb-value-in-opencv
        cv_out->at<cv::Vec3b>(y,x)[2] = *cimg_in->data(x,y,0,0);
        cv_out->at<cv::Vec3b>(y,x)[1] = *cimg_in->data(x,y,0,1);
        cv_out->at<cv::Vec3b>(y,x)[0] = *cimg_in->data(x,y,0,2);
    }
}
#endif
/******************************************************/
void CImg_to_QImage(CImg<unsigned char> *cimg_in, QImage *qi_out)
{
    // converts the CImg rgb to QImage
    // input CImg is assumed to be 24-bit RGB format

    if(cimg_in->width()!=qi_out->width() || cimg_in->height()!=qi_out->height())
    {
        qDebug() << "image size mismatch in CImg_to_QImage. Input= " << cimg_in->width()<< "x"<<cimg_in->height() <<
                 ". Ouptut= " << qi_out->width() << "x" << qi_out->height() ;
        return;
    }

    const unsigned char * srcR = cimg_in->data(0, 0, 0, 0);
    const unsigned char * srcG = cimg_in->data(0, 0, 0, 1);
    const unsigned char * srcB = cimg_in->data(0, 0, 0, 2);
    int height = qi_out->height();
    for (int y = 0; y < height; ++y) {
          int n = cimg_in->width();
          unsigned char * dst = qi_out->scanLine(y);
          while (n--) {
            dst[0] = (*srcR++);
            dst[1] = (*srcG++);
            dst[2] = (*srcB++);
            dst += 3;
          }
        }

}
/********************************************************************/
void ScaleToMinMax(float *buf, CImg<unsigned char> *img, float min, float max)
{
    // copies the data in buf to img and maps the range [min, max] to 8 bits
    // assumes that img is the correct size to accomodate data in buf

    int count=0;
    cimg_forXY(*img,x,y)
    {
        if(buf[count]>max)
            *(img->data(x,y))=255;
        else if(buf[count]<min)
            *(img->data(x,y))=0;
        else
            *(img->data(x,y))=(unsigned char)((buf[count]-min)/(max-min)*255.0);
        count++;
    }
}
/********************************************************************/
void AddColorbarToImage(CImg<unsigned char> *rgb_img, CImg<unsigned char> colormap,
                                         float min, float max)
{
    CImg<unsigned char> cbar(50,(int)(rgb_img->height()/2),1,3);
    CImg<float> cbar_labels(3);
    unsigned char black[]={0,0,0};

    cimg_forXY(cbar,x,y){
        cbar(x,y,0)=colormap(y,0);
        cbar(x,y,1)=colormap(y,1);
        cbar(x,y,2)=colormap(y,2);
    }
    cbar.mirror('y'); // flip colorbar
    cbar_labels(0)=min; cbar_labels(1)=(max+min)/2.0; cbar_labels(2)=max;
    cbar.draw_axis(0,cbar_labels,black);
    rgb_img->draw_image(rgb_img->width()-30,0,cbar);
}
/********************************************************************/
void createColormapImage(CImg<unsigned char> *cmap_img, CImg<unsigned char> colormap,
                                         int width, int height, float min, float max)
{

    *cmap_img=colormap;
    cmap_img->permute_axes("yxzc");
    cmap_img->mirror('y');
    cmap_img->resize(width,height,1,3);


}
/*************************************************************************************/
void compute_sc_color() {
    unsigned char *red_channel_p[1000];
    CImg<unsigned char> red_channel;

#ifdef USE_NIIMAQDX
    // Extract red pixels and reinitilize dimensions
        if(speckle->theCamera->camera_type==CAMERA_NIIMAQDX && speckle->theCamera->camera_description.contains("Webcam", Qt::CaseInsensitive) && speckle->theCamera->logitech_camera.bayer_setting == true)
        {
            ExtractRedPixelsFromBayer(speckle->raw_list, &red_channel, red_channel_p);
            speckle->sc_w = red_channel.width() - speckle->NxN + 1;
            speckle->sc_h = red_channel.height() - speckle->NxN + 1;
        }
        else
        {
            ExtractRedChannel(speckle->raw_list, &red_channel, red_channel_p);
            speckle->sc_w = red_channel.width() - speckle->NxN + 1;
            speckle->sc_h = red_channel.height() - speckle->NxN + 1;
        }
#endif

#ifdef USE_PYLON
        if(speckle->theCamera->camera_type == CAMERA_PYLON && speckle->theCamera->bayer_setting == true)
        {
            ExtractRedPixelsFromBayer(speckle->raw_list, &red_channel, red_channel_p);
            speckle->sc_w = red_channel.width() - speckle->NxN + 1;
            speckle->sc_h = red_channel.height() - speckle->NxN + 1;
        }
        else
        {
            ExtractRedChannel(speckle->raw_list, &red_channel, red_channel_p);
            speckle->sc_w = red_channel.width() - speckle->NxN + 1;
            speckle->sc_h = red_channel.height() - speckle->NxN + 1;
        }
#endif

#ifdef USE_FLSCI
    speckle->sc_calc = flsci_sc_init(red_channel.width(), red_channel.height(),
                                     speckle->NxN, speckle->num_processing_threads);
#endif

#ifdef USE_NIIMAQDX
    if(speckle->theCamera->camera_type==CAMERA_NIIMAQDX && speckle->theCamera->camera_description.contains("Webcam", Qt::CaseInsensitive) && speckle->theCamera->logitech_camera.bayer_setting == true)
        flsci_sc_process(speckle->sc_calc, red_channel_p, speckle->Nframes, speckle->SC);
    else
        flsci_sc_process(speckle->sc_calc, red_channel_p, speckle->Nframes, speckle->SC);
#else
    #ifdef USE_FLSCI
        flsci_sc_process(speckle->sc_calc, red_channel_p, speckle->Nframes, speckle->SC);
    #else
        compute_sc8(speckle->raw_list, speckle->NxN, speckle->Nframes, speckle->SC);
    #endif
#endif
}
/***********************************************************************************************************/
void CalculateSpeckleContrast(void) {
    unsigned int width, height, window;
    QElapsedTimer t;

    width = speckle->theCamera->im_w;
    height = speckle->theCamera->im_h;
    window = speckle->NxN;

    if((speckle->theCamera->bit_depth > 8) && !(speckle->fast_sc))
        compute_sc16(speckle->raw_list16, speckle->NxN, speckle->Nframes, speckle->SC);

#ifdef USE_FLSCI
    else if((speckle->theCamera->bit_depth > 8) && (speckle->fast_sc))
        compute_sc16_approx(speckle->raw_list16, speckle->NxN, speckle->Nframes, speckle->SC,
                            speckle->sc_calc, speckle->Imax, speckle->Imin);
#endif

    else if(speckle->temporal_sc)
        compute_sc_temporal(speckle->raw_list, speckle->Nframes, speckle->SC);
    else {
        if(width != speckle->theCamera->im_w || height != speckle->theCamera->im_h || window != speckle->NxN) {
            width = speckle->theCamera->im_w;
            height = speckle->theCamera->im_h;
            window = speckle->NxN;

#ifdef USE_FLSCI
            flsci_sc_end(&(speckle->sc_calc));
            speckle->sc_calc = flsci_sc_init(width, height, window, speckle->num_processing_threads);
            if(speckle->show_rTC || speckle->show_overlay) {
                flsci_rct_end(&(speckle->rct_calc));
                speckle->rct_calc = flsci_rct_init(speckle->rct_table, TC_TABLE_SIZE, width, height, 2);
            }
#endif

        }

        t.start();
        if(speckle->theCamera->color_planes > 1)
            compute_sc_color();
        else {

#ifdef USE_FLSCI
            if((speckle->write_mode == WRITE_CONTINUOUS) && (speckle->acquire_flag == ACQUISITION_MODE)) {
                unsigned char *images_to_process[1000];
                for(int i = 0; i < speckle->Nframes; i++)
                    images_to_process[i] = speckle->raw_images[speckle->theCamera->img_acquired - speckle->Nframes + i];
                flsci_sc_process(speckle->sc_calc, images_to_process, speckle->Nframes, speckle->SC);
            } else
                flsci_sc_process(speckle->sc_calc, speckle->raw_images, speckle->Nframes, speckle->SC);
#else
                compute_sc8(speckle->raw_list, speckle->NxN, speckle->Nframes, speckle->SC);
#endif

        }
        qDebug() << "Approximate processing rate =" << speckle->Nframes*1000/(t.elapsed()) << "fps";
    }
    memcpy((void *)(speckle->sc_imgf.data()), (void *)(speckle->SC), speckle->sc_w*speckle->sc_h*sizeof(float));
}
/*************************************************************************************/
