#ifndef WRITETHREAD_H
#define WRITETHREAD_H

#include <QThread>
#include <QElapsedTimer>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#ifdef SPECKLE_USE_OPENCV
#include "opencv2/opencv.hpp"
using namespace cv;
#endif

class WriteThread : public QThread
{
    Q_OBJECT

public:	
    WriteThread(QObject *parent = 0);

    int raw_write_fps;

public slots:
    void stopWriting(void);

protected:
    void run();

private:
    QFile timing_file;
    QDataStream timing_file_output;
    QElapsedTimer raw_write_timer;

    bool force_stop;
};

#endif
