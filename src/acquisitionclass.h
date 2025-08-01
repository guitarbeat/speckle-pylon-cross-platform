#ifndef ACQUISITIONCLASS_H
#define ACQUISITIONCLASS_H

#include <QtWidgets>
#include <QElapsedTimer>

class AcquisitionClass : public QObject {
    Q_OBJECT

signals:
    void postAcquisitionStatus(void);

public:
    AcquisitionClass();

    enum {STOP_NUMBER, STOP_TIME, ACQUIRE_FOREVER};

    void setStopCondition(int index);
    void setDuration(int N);
    void startTimer(void);
    qint64 getTimeElapsed(void) { return timer.elapsed(); }
    void updateFPS(void);
    int getFPS(void) { return acquire_fps; }
    bool isFinished(void);

    int stop_condition;
    int img_to_acquire;
    int img_acquired;
    int max_acq_time;

private:
    int acquire_fps;
    QElapsedTimer timer;
    qint64 t_last;
};

#endif // ACQUISITIONCLASS_H
