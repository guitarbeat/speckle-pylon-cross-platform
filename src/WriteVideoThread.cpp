#include "WriteVideoThread.h"
#include "speckle_defines.h"
#include <QCoreApplication>
#include <QFileInfo>
#include <QElapsedTimer>
#include <QDebug>
/********************************************************************************************/
WriteVideoThread::WriteVideoThread(QString filename, int *acquire_flag, int *frames_shown,
                                   CImgList<uchar> *frames_to_write, QObject *parent)
    : QThread(parent)
{
    this->filename = filename;
    this->acquire_flag = acquire_flag;
    this->frames_shown = frames_shown;
    this->frames_to_write = frames_to_write;

    fps = 25; // Default video frames-per-second (fps)
    fourcc = cv::VideoWriter::fourcc('m','p','4','v'); // Default video format
    save_timing = false;
    force_stop = false;
    fix_vfr = false;
}
/********************************************************************************************/
void WriteVideoThread::run()
{    
    uint idx;
    CImg<uchar> frame;
    cv::Mat frame_mat;
    QElapsedTimer timer;
    float t;
    QFile timing_file;
    QDataStream timing_out;

    write_fps = 0;
    force_stop = false;
    int frames_written = 0;
    bool keep_going = true;

    if(save_timing)
    {
        timing_file.setFileName(QString(filename).replace(".mp4", ".timing"));
        timing_file.open(QIODevice::WriteOnly);
        timing_out.setDevice(&timing_file);
    }

    timer.start();
    while(keep_going)
    {
        // Stop once acquisition is complete and all buffered frames have been written
        if(*acquire_flag == IDLE && *frames_shown == frames_written)
            keep_going = false;

        if(*frames_shown > frames_written)
        {
            if(!video.isOpened())
            {
                int height = (*frames_to_write)(0).height();
                int width = (*frames_to_write)(0).width();
                video.open(filename.toUtf8().constData(), fourcc, fps, cv::Size(width, height));
            }

            idx = frames_written % NUM_VIDEO_FRAME_BUFFERS;
            frame = (*frames_to_write)(idx);

            if(frame.is_empty())
                return;

            frame_mat = frame._cimg2cvmat();
            video.write(frame_mat);

            if(save_timing)
            {
                t = timing->at(frames_written);
                timing_out.writeRawData(reinterpret_cast<const char*>(&t), sizeof(float));
            }

            frames_written++;

            if(frames_written % fps == 0)
                write_fps = qRound(fps * 1000.0 / timer.restart());

//            qDebug().nospace() << filename << ": shown=" << *frames_shown << ", written=" << frames_written << ", fps=" << write_fps;

        }
        if(force_stop)
            keep_going=false;
    }

    if(video.isOpened())
        video.release();
    if(save_timing)
        timing_file.close();
    if(fix_vfr && save_timing)
        writeVFRFile();
}
/********************************************************************************************/
void WriteVideoThread::saveTiming(QVector<float> *timing)
{
    save_timing = true;
    this->timing = timing;
}
/********************************************************************************************/
void WriteVideoThread::stopWriting(void)
{
    // force writing thread to stop when stop button is pressed even if some frames haven't been written
    force_stop=true;
}
/********************************************************************************************/
void WriteVideoThread::fixVFR(bool fix)
{
    // set flag to fix variable frame rate after acquisition
    fix_vfr = fix;
}
/********************************************************************************************/
void WriteVideoThread::writeVFRFile(void)
{
    // create new mp4 with variable frame rate by calling external program, mp4fpsmod

    QString program = QCoreApplication::applicationDirPath() + "/plugins/mp4fpsmod.exe";
    QFileInfo info(program);
    if (!info.exists())
    {
        qDebug() << "mp4fpsmod.exe not found. Skipping variable frame rate correction.";
        return;
    }

    // export timing to timecode text file
    QFile timing_file(QString(filename).replace(".mp4", ".timing.txt"));
    timing_file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream timing_out(&timing_file);
    timing_out << "# timecode format v2\n";
    foreach(const float &t, *timing)
        timing_out << static_cast<int>(t - timing->at(0)) << "\n";
    timing_file.close();

    // run mp4fpsmod to fix variable frame rate like this:
    // mp4fpsmod -t timecode.txt input.mp4 -o vfr.mp4
    QStringList arguments;
    arguments << "-t" << timing_file.fileName()
              << filename
              << "-o" << QString(filename).replace(".mp4", "_vfr.mp4");

//    qDebug() << "running " << program << "with arguments: " << arguments;

    QProcess mp4fpsmod;
    mp4fpsmod.start(program, arguments);
    if (!mp4fpsmod.waitForStarted())
            qDebug() << "could not start " << program << "with arguments: " << arguments;

    if(!mp4fpsmod.waitForFinished(3000))
        qDebug() << "timeout error in mp4fpsmod";
    else
        timing_file.remove(); // Remove timecode file if successful
}
/********************************************************************************************/
