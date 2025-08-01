#ifndef WRITEVIDEOTHREAD_H
#define WRITEVIDEOTHREAD_H

#include <QThread>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QProcess>
#include "opencv2/opencv.hpp"
#include "CImg.h"
using namespace cimg_library;

class WriteVideoThread : public QThread
{
    Q_OBJECT

public:	
    WriteVideoThread(QString filename, int *acquire_flag, int *frames_shown,
                     CImgList<uchar> *frames_to_write, QObject *parent = nullptr);
    void saveTiming(QVector<float> *timing);
    int get_write_fps(void) const {return write_fps;}
    void fixVFR(bool);

public slots:
    void stopWriting(void);

protected:
    void run();

private:
    int *frames_shown;
    int *acquire_flag;
    CImgList<uchar> *frames_to_write;

    QString filename;
    int fps;
    int fourcc;
    int write_fps;
    cv::VideoWriter video;

    QVector<float> *timing;
    bool save_timing;
    bool force_stop;
    bool fix_vfr;

    void writeVFRFile(void);
};

#endif
