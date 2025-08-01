#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H

#include <QThread>
#include <QElapsedTimer>

class ProcessingThread : public QThread
{
    Q_OBJECT

signals:    
	void postSpeckleMessage(QString);

public:	
    ProcessingThread(QObject *parent = 0);
    int processing_fps;

protected:
    void run();

private:
    int InitializeProcessing(void);
    void ProcessImages(int);

    unsigned char *images_to_process[10000];
    QElapsedTimer processing_timer;
};

#endif
