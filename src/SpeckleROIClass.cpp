#include "SpeckleROIClass.h"
#include <QImage>
/*******************************************************/
SpeckleROIClass::SpeckleROIClass(void) {
    show = true;
    opacity = 0.5f;
    white[0] = 255; white[1] = 255; white[2] = 255;
    black[0] = 0; black[1] = 0; black[2] = 0;
}
/*******************************************************/
void SpeckleROIClass::set_color(QColor c) {
    int r, g, b;

    ROI_color = c;
    c.getRgb(&r,&g,&b);
}
/*******************************************************/
void SpeckleROIClass::set_mask(CImg<unsigned char> img) {
    mask.resize(img.width(),img.height());
    mask.fill(0);

    // Minimal mask support: fill rectangle for RECT_ROI, or fill polygon bbox for POLY_ROI
    if(type == RECT_ROI) {
        int x1 = static_cast<int>(points(0));
        int y1 = static_cast<int>(points(1));
        int x2 = static_cast<int>(points(3));
        int y2 = static_cast<int>(points(4));
        for (int y = std::max(0,y1); y <= std::min(y2, img.height()-1); ++y)
            for (int x = std::max(0,x1); x <= std::min(x2, img.width()-1); ++x)
                mask(x,y) = 255;
    } else if (type == POLY_ROI) {
        // Simple polygon: mark points only (fallback without rasterization)
        for (int i = 0; i < points.height(); ++i) {
            int x = static_cast<int>(points(i,0));
            int y = static_cast<int>(points(i,1));
            if (x>=0 && x<img.width() && y>=0 && y<img.height()) mask(x,y) = 255;
        }
    }

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
        CImg<float> tmp = sc->get_crop(points(0),points(1),0,points(3),points(4),0);
        double sum = 0.0;
        cimg_forXY(tmp, x, y) { sum += tmp(x,y); }
        this_sc_mean = (tmp.width()*tmp.height() > 0) ? (sum / (tmp.width()*tmp.height())) : 0.0;
    } else if(type == POLY_ROI) {
        double m = 0.0;
        int cnt = 0;
        cimg_forXY(mask,x,y)
            if(mask(x,y) > 0) { m += (*sc)(x,y); ++cnt; }
        this_sc_mean = (cnt>0) ? (m/static_cast<double>(cnt)) : 0.0;
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
    double sum = 0.0; for (double v : vector) sum += v;
    sc_baseline = vector.isEmpty() ? 0.0 : sum/static_cast<double>(vector.size());
}
/*******************************************************/
void SpeckleROIClass::recalcRelative(void) {
    // Recalculates the relative flow vector using new baseline
    for (int i = 0; i < sc_mean.size(); i++) {
        double sc_baseline_squared = sc_baseline*sc_baseline;
        double this_sc_squared = sc_mean.at(i)*sc_mean.at(i);
        sc_mean_norm.replace(i, this_sc_squared == 0.0 ? 0.0 : (sc_baseline_squared/this_sc_squared));
    }
}
/*******************************************************/
void SpeckleROIClass::updateSC(void) {
    // Appends current SC mean to vector and calculates
    // relative flow vector using baseline
    sc_mean.append(this_sc_mean);
    double denom = this_sc_mean*this_sc_mean;
    sc_mean_norm.append(denom == 0.0 ? 0.0 : (sc_baseline*sc_baseline)/denom);
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
        if ((*mask)(x,y) != 0) {
            binary_mask.setPixel(x,y,1);
        }
    }
    return binary_mask;
}
/*******************************************************/
