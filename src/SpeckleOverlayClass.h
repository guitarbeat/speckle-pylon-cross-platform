#ifndef SPECKLEOVERLAYCLASS_H
#define SPECKLEOVERLAYCLASS_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <string.h>
#include "cameradescription.h"
#include "CImg.h"
using namespace cimg_library;

enum {SRC_RAW, SRC_SC, SRC_TC, SRC_VIDEO, SRC_NONE};
enum {THRESH_BETWEEN, THRESH_SAT_ABOVE, THRESH_SAT_BELOW};

class SpeckleOverlayClass : public QObject {

signals:
    void postSpeckleMessage(QString);

public:
    SpeckleOverlayClass(void);

    CImg<unsigned char> bg_cmap, over_cmap, output_img;
    int left, top, width, height;

    void CreateOverlayImage(CImg<unsigned char> raw_img,
                            CImg<float> sc_img,
                            CImg<float> tc_img);

    void setBackgroundSource(int src);
    void setBackgroundVideoSource(cameraDescription src);
    void setBackgroundMin(float x) {bg_min = x;}
    void setBackgroundMax(float x) {bg_max = x;}

    void setOverlaySource(int src);
    void setOverlayMin(float x) {over_min = x;}
    void setOverlayMax(float x) {over_max = x;}

    void setThresholdType(int idx);
    void setBlur(int x); // {blur_width = x;}
    void setUseAlpha(bool);
    void setKmid(float x);
    void setAlphaMin(float);
    void setAlphaMax(float);
    float GetKmid(void) {return Kmid;}
    float GetOverMax(void) {return over_max;}
    float GetOverMin(void) {return over_min;}
    float GetAlphaMax(void) {return alpha_max;}
    float GetAlphaMin(void) {return alpha_min;}
    bool useAlpha(void) {return use_alpha;}

    void ComputeTransform(CImgList<float> pts1, CImgList<float> pts2, CImg<float> *tform);
    void GeneratePixelMapping(CImg<unsigned char> img1, CImg<unsigned char> img2,
                                                   CImg<float> tform,  CImg<int> *pixel_mapping);
    void RegisterImages(CImg<float> old_img, CImg<float> *new_img,
                                                   CImg<int> pixel_mapping);
    bool setTransformFromFile(QString fname);
    void setOverlayColormap(QString cmap_string);


    int bg_src, over_src;
    cameraDescription bg_video_src;

private:

    Q_OBJECT

    CImg<float> bg_img;
    CImg<float> over_img;
    int threshold_type;
    int blur_width;
    float bg_min, bg_max;
    float over_min, over_max;
    bool use_alpha;
    float alpha_min, alpha_max;
    float Kmid;

    QElapsedTimer img_gen_timer;
    qint64 img_gen_time;
};

#endif
