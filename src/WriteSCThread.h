#ifndef WRITESCTHREAD_H
#define WRITESCTHREAD_H

#include <QThread>
#include <QElapsedTimer>
#include <QFile>
#include <QDataStream>
#include <QTextStream>

class WriteSCThread : public QThread
{
    Q_OBJECT

signals:    
	void postSpeckleMessage(QString);

public:	
    WriteSCThread(QObject *parent = 0);

    int sc_write_fps;

public slots:
    void stopWriting(void);

protected:
    void run();

private:
    QFile sc_timing_file;
    QDataStream sc_timing_file_output;
    QElapsedTimer sc_write_timer;
    bool force_stop;
};

#endif
