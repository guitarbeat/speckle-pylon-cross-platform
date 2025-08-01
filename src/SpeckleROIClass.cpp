#include "SpeckleROIClass.h"
/*******************************************************/
SpeckleROIClass::SpeckleROIClass(void) {
    show = true;
    opacity = 0.5;
    white[0] = 255; white[1] = 255; white[2] = 255;
    black[0] = 0; black[1] = 0; black[2] = 0;
}
/*******************************************************/
void SpeckleROIClass::set_color(QColor c) {
	int r, g, b;

	color_q=c;
	c.getRgb(&r,&g,&b);
	color_rgb[0]=r;
	color_rgb[1]=g;
	color_rgb[2]=b;
}
/*******************************************************/
void SpeckleROIClass::set_mask(CImg<unsigned char> img) {
    mask.resize(img.width(),img.height());
    mask.fill(0);

    if(type == RECT_ROI)
        mask.draw_rectangle(points(0),points(1),points(3),points(4),white,1.0);
    else if (type == POLY_ROI)
        mask.draw_polygon(points,white,1.0);

    calculateMaskSize();
}
/*******************************************************/
void SpeckleROIClass::set_points(void) {
    // Convert CImgList of selected points to CImg

    CImg<float> foo;

	points.resize(points_list.size(),2);
    for(int i = 0; i < (signed int) points_list.size(); i++) {
        foo = points_list(i);
        points(i,0) = foo(0);
        points(i,1) = foo(1);
	}
}
/*******************************************************/
void SpeckleROIClass::calculateMaskSize(void) {
    mask_size = 0;
    cimg_forXY(mask,x,y) {
        if(mask(x,y) > 0) {
            mask_size += 1;
        }
    }
}
/*******************************************************/
void SpeckleROIClass::calculateMean(CImg<float> *sc) {
    if(type == RECT_ROI) {
        CImg<float> tmp = sc->get_crop(points(0),points(1),points(3),points(4));
        this_sc_mean = tmp.mean();
    } else if(type == POLY_ROI) {
        float m = 0.0;
        cimg_forXY(mask,x,y)
            if(mask(x,y) > 0)
                m += sc->atXY(x,y);
        this_sc_mean = m/mask_size;
    }
}
/*******************************************************/
void SpeckleROIClass::setDefaultBaseline(void) {
    // Default baseline uses first frame of data
    // This will only be called at start of an acquisition
    sc_baseline = this_sc_mean;
}
/*******************************************************/
void SpeckleROIClass::calculateBaseline(int idx_start, int idx_end) {
    QVector<double> vector = sc_mean.mid(idx_start,idx_end - idx_start);
    sc_baseline = std::accumulate(vector.begin(),vector.end(),0.0)/vector.size();
}
/*******************************************************/
void SpeckleROIClass::recalcRelative(void) {
    // Recalculates the relative flow vector using new baseline
    for (int i = 0; i < sc_mean.size(); i++) {
        double sc_baseline_squared = sc_baseline*sc_baseline;
        double this_sc_squared = sc_mean.at(i)*sc_mean.at(i);
        sc_mean_norm.replace(i,sc_baseline_squared/this_sc_squared);
    }
}
/*******************************************************/
void SpeckleROIClass::updateSC(void) {
    // Appends current SC mean to vector and calculates
    // relative flow vector using baseline
    sc_mean.append(this_sc_mean);
    sc_mean_norm.append((sc_baseline*sc_baseline)/(this_sc_mean*this_sc_mean));
}
/*******************************************************/
void SpeckleROIClass::lateROIUpdate(int currentSize) {
    // ROI added after start of acquisition needs to be
    // caught up to other ROIs. Replicates first acquired
    // sc value for entire vector.
    QVector<double> vector(currentSize,this_sc_mean);
    sc_mean = vector;
    sc_mean_norm = vector.fill(1);
}
/*******************************************************/
QImage convert_mask_to_1bit(CImg<unsigned char> *mask) {
    QImage binary_mask(mask->width(),mask->height(),QImage::Format_Mono);
    binary_mask.fill(0);
    cimg_forXY(*mask,x,y) {
        if (mask->atXY(x,y) != 0) {
            binary_mask.setPixel(x,y,1);
        }
    }
    return binary_mask;
}
/*******************************************************/
