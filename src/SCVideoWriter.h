#ifndef SCVIDEOWRITER_H
#define SCVIDEOWRITER_H

#include <QtCore>
#include "CImg.h"
using namespace cimg_library;
#include "opencv2/opencv.hpp"
using namespace cv;

class SCVideoWriter :  public QObject
{
    Q_OBJECT

public:
    SCVideoWriter();
    ~SCVideoWriter(void);
    void OpenCaptureDevice(void);
    void SetOutputFile(QString base_fname);
    void CloseOutputFile(void);

public slots:
    //void WriteOneFrame(CImg<unsigned char> img);
    void WriteOneFrame(int);

private:
    QString fname;
    VideoWriter video;

};

#endif
