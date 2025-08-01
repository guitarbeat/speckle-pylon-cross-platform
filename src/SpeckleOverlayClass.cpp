#include "SpeckleOverlayClass.h"
#include <iostream>
#include "speckle.h"
extern SpeckleClass *speckle;

/*******************************************************/
SpeckleOverlayClass::SpeckleOverlayClass(void) {
    threshold_type = THRESH_BETWEEN;

    bg_src = SRC_RAW;
    bg_min = 0;
    bg_max = 255;

    over_src = SRC_SC;
    over_min = 0.0;
    over_max = 0.5;

    use_alpha=false;
    alpha_min=0.0;
    alpha_max=1.0;
    Kmid=0.0;

}
/*******************************************************/
void SpeckleOverlayClass::CreateOverlayImage(CImg<unsigned char> raw_img,
                                             CImg<float> sc_img,
                                             CImg<float> tc_img) {

    float scaled, max_thresh, min_thresh;
	int color_ind;

    // Resize images
   // bg_img.resize(sc_img.width(), sc_img.height());
   // over_img.resize(sc_img.width(), sc_img.height());
   // output_img.resize(sc_img.width(), sc_img.height(), 1, 3); // rgb image

    // Select background image
    if(bg_src == SRC_RAW)
        bg_img = raw_img.resize(sc_img);
    else if(bg_src == SRC_SC)
		bg_img = sc_img;
	else if(bg_src == SRC_TC)
		bg_img = tc_img;
    else if(bg_src == SRC_NONE)
        bg_img.resize(sc_img.width(), sc_img.height(),1,1,-1).fill(0);

    // Threshold background image and convert to RGB
    if(bg_src != SRC_VIDEO)
    {
        output_img.resize(bg_img.width(), bg_img.height(), 1, 3, -1);
        cimg_forXY(bg_img,x,y) {
            if(bg_img(x,y) <= bg_min)
                scaled = 0;
            else if(bg_img(x,y) >= bg_max)
                scaled = 255;
            else
                scaled = (bg_img(x,y) - bg_min) / (bg_max - bg_min) * 255;

            color_ind = (int)(fabs(scaled + 0.5));

            if(color_ind < 0)
                color_ind = 0;
            if(color_ind > 255)
                color_ind = 255;

            output_img(x,y,0) = bg_cmap(color_ind,0);
            output_img(x,y,1) = bg_cmap(color_ind,1);
            output_img(x,y,2) = bg_cmap(color_ind,2);
        }
    }

    if(bg_src==SRC_VIDEO && speckle->captured_rgb.width()>0)
        output_img = speckle->captured_rgb;
    if(bg_src==SRC_VIDEO && speckle->captured_rgb.width()<10)
    {
         bg_img.resize(sc_img.width(), sc_img.height(),1,1,-1).fill(0);
         output_img.resize(bg_img.width(), bg_img.height(), 1, 3, -1); // rgb image
    }

    // Set absolute overlay thresholds
    if(threshold_type == THRESH_BETWEEN) {
		max_thresh = over_max;
		min_thresh = over_min;
    } else if(threshold_type == THRESH_SAT_ABOVE) {
        max_thresh = 1e30f;
		min_thresh = over_min;
    } else if(threshold_type == THRESH_SAT_BELOW) {
		max_thresh = over_max;
        min_thresh = -1e30f;
	}

    // Select overlay image
    if(over_src == SRC_RAW)
        over_img = raw_img.resize(over_img);
    else if(over_src == SRC_SC)
		over_img = sc_img;
	else if(over_src == SRC_TC)
		over_img = tc_img;
    else if(over_src == SRC_NONE)
        return;
       // over_img.resize(output_img.width(), output_img.height(),1,1,-1);

    // Blur overlay
    if(blur_width>1 && bg_src!=SRC_VIDEO) // video overlay gets blured below
    {
        over_img.blur((float)blur_width);
    }

    // apply transform here
    if(bg_src == SRC_VIDEO)
    {
        if(speckle->mask_dark_areas_threshold>0)
        {
            CImg<unsigned char> live_threshold = speckle->live_img;
            live_threshold.crop(speckle->NxN/2, speckle->NxN/2, speckle->NxN/2+speckle->sc_w, speckle->NxN/2+speckle->sc_h);
            live_threshold.resize(speckle->sc_img, -1);
            //live_threshold.blur_median(5);
            live_threshold.blur(speckle->mask_blur_width);
            cimg_forXY(sc_img,x,y) {
                if(live_threshold(x,y) <= speckle->mask_dark_areas_threshold)
                    sc_img(x,y)=-1;
            }
        }
        if(blur_width>1)
        {
            sc_img.blur((float) blur_width);
        }
        if(speckle->VideoPixelMapping.width()>0)
        {
            //img_gen_timer.restart();
            RegisterImages(sc_img, &over_img, speckle->VideoPixelMapping);
           // img_gen_time=img_gen_timer.elapsed();
          //  if(QRandomGenerator::global()->generateDouble() < 0.05)
            //        qDebug() << "img gen time: " << img_gen_time;
        }
        else
        {
            // no transform defined. Just resize            
            over_img=sc_img;
            over_img.resize(output_img.width(),output_img.height());
        }
        //qDebug() << "size= " << speckle->captured_rgb.width() << " , " << over_img.width() << endl;
    }

    // Threshold overlay and add to output image
    //float alpha_min = speckle->SC_min;
    //float alpha_max = speckle->SC_max;
    float dalpha = alpha_max-alpha_min;
    float dK = Kmid-over_max;
    float alpha;
    cimg_forXY(over_img,x,y) {
        scaled = (over_img(x,y) - over_min) / (over_max - over_min);
        color_ind = (int)(fabs(scaled*255 + 0.5));
        if(color_ind < 0)
            color_ind = 0;
        if(color_ind > 255)
            color_ind = 255;
        if(over_img(x,y) >= min_thresh && over_img(x,y) <= max_thresh) {
            if(!use_alpha)
            {
                output_img(x,y,0) = over_cmap(color_ind,0);
                output_img(x,y,1) = over_cmap(color_ind,1);
                output_img(x,y,2) = over_cmap(color_ind,2);
            }
            else {
                if(over_img(x,y)<Kmid) // assumes that over_img=sc and low values=high flow. Need to generalize later
                    alpha = alpha_max;
                else
                {
                    alpha = dalpha/dK*over_img(x,y) + alpha_max - dalpha/dK*Kmid;
                    //scaled = (over_img(x,y) - over_min) / (over_max - Kmid);
                    //alpha = alpha_min + (1.0-scaled)*dalpha;
                }
                output_img(x,y,0) = (1-alpha)*output_img(x,y,0) + (alpha)*over_cmap(color_ind,0);
                output_img(x,y,1) = (1-alpha)*output_img(x,y,1) + (alpha)*over_cmap(color_ind,1);
                output_img(x,y,2) = (1-alpha)*output_img(x,y,2) + (alpha)*over_cmap(color_ind,2);
            }
        }
	}
}
/*******************************************************/
void SpeckleOverlayClass::setBackgroundSource(int src) {
    bg_src = src;
}
/*******************************************************/
void SpeckleOverlayClass::setBackgroundVideoSource(cameraDescription video_src) {
    bg_video_src = video_src;
}
/*******************************************************/
void SpeckleOverlayClass::setOverlaySource(int src) {
    over_src = src;
}
/*******************************************************/
void SpeckleOverlayClass::setThresholdType(int idx) {
    switch(idx) {
    case 0:
        threshold_type = THRESH_BETWEEN;
        break;
    case 1:
        threshold_type = THRESH_SAT_ABOVE;
        break;
    case 2:
        threshold_type = THRESH_SAT_BELOW;
        break;
    }
}
/*******************************************************/
void SpeckleOverlayClass::setUseAlpha(bool alpha_check) {
    use_alpha=alpha_check;
}
/*******************************************************/
void SpeckleOverlayClass::setKmid(float x) {
    Kmid = x;
}
/*******************************************************/
void SpeckleOverlayClass::setAlphaMin(float x) {
    alpha_min = x;
}
/*******************************************************/
void SpeckleOverlayClass::setAlphaMax(float x) {
    alpha_max = x;
}
/*******************************************************/
void SpeckleOverlayClass::ComputeTransform(CImgList<float> pts1, CImgList<float> pts2,
                                           CImg<float> *tform)
{

    if(pts1.size()<3 || pts2.size()<3)
    {
        qDebug() << "control points must have at least 3 points";
       // speckle->VideoTform
        return;
    }
#ifdef SPECKLE_USE_OPENCV
    // copy control points to opencv Mat variables
    Point2f srcTri[3];
    srcTri[0] = Point2f( pts1[0](0), pts1[0](1));
    srcTri[1] = Point2f( pts1[1](0), pts1[1](1));
    srcTri[2] = Point2f( pts1[2](0), pts1[2](1));
    Point2f dstTri[3];
    dstTri[0] = Point2f( pts2[0](0), pts2[0](1));
    dstTri[1] = Point2f( pts2[1](0), pts2[1](1) );
    dstTri[2] = Point2f( pts2[2](0), pts2[2](1) );
    Mat warp_mat = getAffineTransform( srcTri, dstTri );

    // now copy transform to CImg format
    tform->resize(3,2);
    *(tform->data(0,0)) = warp_mat.at<double>(0,0); // note that getAffineTransform returns doubles
    *(tform->data(1,0)) = warp_mat.at<double>(0,1);
    *(tform->data(2,0)) = warp_mat.at<double>(0,2);
    *(tform->data(0,1)) = warp_mat.at<double>(1,0);
    *(tform->data(1,1)) = warp_mat.at<double>(1,1);
    *(tform->data(2,1)) = warp_mat.at<double>(1,2);

    //std::cout << "opencv tform= " << warp_mat << endl;
    //std::cout << "CImg tform = " << *tform->data() << endl;
    // qDebug() << "first= " << warp_mat.at<double>(0,0) << ", second= " << warp_mat.at<double>(0,1);
     qDebug() << "a00, a01, b00 = " << *(tform->data(0,0))<< " , " << *(tform->data(1,0)) << " , " << *(tform->data(2,0)) ;
     qDebug() << "a10, a11, b10 = " << *(tform->data(0,1))<< " , " << *(tform->data(1,1)) << " , " << *(tform->data(2,1)) ;

#endif

}
/*******************************************************/
void SpeckleOverlayClass::GeneratePixelMapping(CImg<unsigned char> img1, CImg<unsigned char> img2,
                                               CImg<float> tform, CImg<int> *pixel_mapping)
{
    // compute pixel mapping from img2 to img1. For each pixel in img1 (eg video in), determine
    // the corresponding pixel in img2 (eg, speckle contrast). Output is same size as img1 with 2 planes.
    // input tform should map img1 to img2

    if(tform.width()!=3 || tform.height()!=2)
    {
        qDebug() << "GeneratePixelMapping error: input tform must be 3x2" ;
        return;
    }

    // initialize bounding box values
    speckle->VideoPixel_min_w = img1.width()-1;
    speckle->VideoPixel_max_w = 0;
    speckle->VideoPixel_min_h = img1.height()-1;
    speckle->VideoPixel_max_h = 0;

    pixel_mapping->resize(img1.width(), img1.height(), 2);
    pixel_mapping->fill(-1);

    // extract matrix elements
    float a00 = tform(0,0);
    float a01 = tform(1,0);
    float b00 = tform(2,0);
    float a10 = tform(0,1);
    float a11 = tform(1,1);
    float b10 = tform(2,1);

    int new_x, new_y;
     cimg_forXY(img1,x,y) { // loop over video in (img1)
         new_x = round(a00*x + a01*y + b00); // coordinates in img2 (speckle contrast)
         new_y = round(a10*x + a11*y + b10);
         if(new_x>=0 && new_x<img2.width() && new_y>=0 && new_y<img2.height())
         {
             *(pixel_mapping->data(x,y,0)) = new_x;
             *(pixel_mapping->data(x,y,1)) = new_y;

             if(x < speckle->VideoPixel_min_w)
                 speckle->VideoPixel_min_w = x;
             if(x > speckle->VideoPixel_max_w)
                 speckle->VideoPixel_max_w = x;
             if(y < speckle->VideoPixel_min_h)
                 speckle->VideoPixel_min_h = y;
             if(y > speckle->VideoPixel_max_h)
                 speckle->VideoPixel_max_h = y;
         }
     }

   //  qDebug() << "bounding box: " << speckle->VideoPixel_min_w <<", " << speckle->VideoPixel_max_w<<", " << speckle->VideoPixel_min_h<<", " << speckle->VideoPixel_max_h;
}
/*******************************************************/
void SpeckleOverlayClass::RegisterImages(CImg<float> old_img, CImg<float> *new_img,
                                               CImg<int> pixel_mapping)
{
    if(pixel_mapping.width()==0 || pixel_mapping.height()==0 || pixel_mapping.depth()!=2)
    {
        qDebug() << "pixel mapping not defined properly in RegisterImages " ;
        return;
    }
    // apply lookup to populate new_img with old_img values based on pixel_mapping
    new_img->resize(pixel_mapping.width(),pixel_mapping.height());
    new_img->fill(-1);
   // cimg_forXY(*new_img,x,y) {
    cimg_for_inXY(*new_img,speckle->VideoPixel_min_w, speckle->VideoPixel_min_h, speckle->VideoPixel_max_w, speckle->VideoPixel_max_h, x, y) {
        if(pixel_mapping(x,y,0)>0 && pixel_mapping(x,y,1)>0 && pixel_mapping(x,y,0)<old_img.width() &&
                pixel_mapping(x,y,1)<old_img.height())
        {
           *(new_img->data(x,y)) = old_img(pixel_mapping(x,y,0), pixel_mapping(x,y,1)) ;
        }

    }
}
/*******************************************************/
void SpeckleOverlayClass::setBlur(int x)
{
    blur_width = x;
}
/***************************************************************************/
void SpeckleOverlayClass::setOverlayColormap(QString cmap_string)
{

        // fill in colormap by string matching
    if(cmap_string.contains("reverse gray", Qt::CaseInsensitive))
        over_cmap = speckle->reverse_gray_palette;
    else if(cmap_string.contains("gray", Qt::CaseInsensitive))
        over_cmap = speckle->gray_palette;

    if(cmap_string.contains("reverse jet", Qt::CaseInsensitive))
        over_cmap = speckle->reverse_jet_palette;
    else if(cmap_string.contains("jet",Qt::CaseInsensitive))
        over_cmap = speckle->jet_palette;

    if(cmap_string.contains("hot", Qt::CaseInsensitive))
        over_cmap = speckle->hot_palette;
    if(cmap_string.contains("cool", Qt::CaseInsensitive))
        over_cmap = speckle->cool_palette;
    if(cmap_string.contains("autumn", Qt::CaseInsensitive))
        over_cmap = speckle->autumn_palette;
    if(cmap_string.contains("pmkmp", Qt::CaseInsensitive))
        over_cmap = speckle->pmkmp_palette;
    if(cmap_string.contains("green", Qt::CaseInsensitive))
        over_cmap = speckle->greens_palette;

}
/***************************************************************************/
bool SpeckleOverlayClass::setTransformFromFile(QString fname) {
    // Loads transformation matrix from file
    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    float a00, a01, b00, a10, a11, b10;
    QTextStream in(&file);
    in >> a00 >> a01 >> b00 >> a10 >> a11 >> b10;
    file.close();

    speckle->VideoTform.resize(3,2);
    speckle->VideoTform(0,0) = a00;
    speckle->VideoTform(1,0) = a01;
    speckle->VideoTform(2,0) = b00;
    speckle->VideoTform(0,1) = a10;
    speckle->VideoTform(1,1) = a11;
    speckle->VideoTform(2,1) = b10;

   // emit transformUpdated();
    emit postSpeckleMessage(QString("%1: sx=%2, rx=%3, ry=%4, sy=%5, tx=%6, ty=%7").arg(fname).
                            arg(a00).arg(a10).arg(b00).arg(a10).arg(a11).arg(b10));
    return true;
}
/*******************************************************/
