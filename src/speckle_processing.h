#include <QString>
#include "flsci.h"
#ifdef _WIN32
#include "windows.h"
#else
#include <cstdint>
struct SYSTEMTIME { uint16_t wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds; };
#endif
#include "CImg.h"
using namespace cimg_library;
#ifdef SPECKLE_USE_OPENCV
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
using namespace cv;
#endif
#include <QImage>

void Save_Raw(QString fname);
int ReadSCFile(QString fname, float *sc);
double SystemTime_to_Seconds(SYSTEMTIME st);
void rescale_roi(CImg<int>, double);
int read_raw_image_file(QString fname, CImgList<unsigned char> *img_list, unsigned short *width, unsigned short *height,
						unsigned short *Nframes, unsigned short *exp_time);
int read_raw_image_file_header(QString fname, unsigned short *width, unsigned short *height, 
						unsigned short *Nframes, unsigned short *exp_time);

void compute_sc16(CImgList<unsigned short> input, int window, int Nframes, float *sc);
void compute_sc8(CImgList<unsigned char> input, int window, int Nframes, float *sc);
void compute_sc_temporal(CImgList<unsigned char> input, int Nframes, float *sc);
void compute_sc_color(void);
void ExtractRedChannel(CImgList<unsigned char> input, CImg<unsigned char> *red, unsigned char **output);
void CalculateSpeckleContrast(void);
void ExtractRedPixelsFromBayer(CImgList<unsigned char> input, CImg<unsigned char> *red, unsigned char **output);

#ifdef USE_FLSCI
void compute_sc16_approx(CImgList<unsigned short> input, int window, int Nframes, float *sc,
                         flsci_sc sc_calc, int Imax, int Imin);
void set_baseline(float *sc_image, float *baseline_image, float *table);
#endif
#ifdef SPECKLE_USE_OPENCV
void OpenCVMat_to_CImg(Mat *cv_in, CImg<unsigned char> *cimg_out);
void CImg_to_OpenCVMat(CImg<unsigned char> *cimg_in, Mat *cv_out);
#endif

void CImg_to_QImage(CImg<unsigned char> *cimg_in, QImage *qi_out);
void ScaleToMinMax(float *buf, CImg<unsigned char> *img, float min, float max);
void AddColorbarToImage(CImg<unsigned char> *rgb_img, CImg<unsigned char> colormap,
                                         float min, float max);
void createColormapImage(CImg<unsigned char> *cmap_img, CImg<unsigned char> colormap,
                                        int w, int h,  float min, float max);
