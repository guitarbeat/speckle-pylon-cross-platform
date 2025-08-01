#include "acquisitionclass.h"
#include <QtDebug>
/***************************************************/
AcquisitionClass::AcquisitionClass()
{
    acquire_fps = 0;
}
/***************************************************/
void AcquisitionClass::setStopCondition(int idx)
{
    switch(idx)
    {
        case 0:
            stop_condition = STOP_NUMBER;
            break;
        case 1:
            stop_condition = STOP_TIME;
            break;
        case 2:
            stop_condition = ACQUIRE_FOREVER;
            break;
    }
}
/***************************************************/
void AcquisitionClass::setDuration(int N)
{
    if (stop_condition == STOP_NUMBER)
        img_to_acquire = N;
    else if (stop_condition == STOP_TIME)
        max_acq_time = N;
}
/***************************************************/
void AcquisitionClass::startTimer(void)
{
    t_last = 0;
    acquire_fps = 0;
    timer.start();
}
/***************************************************/
void AcquisitionClass::updateFPS(void)
{
    // Calculate FPS every 50 frames
    if (img_acquired % 50 == 0)
    {
        qint64 t = timer.elapsed();
        acquire_fps = static_cast<int>(50 * 1000.0 / (t - t_last));
        t_last = t;
        emit postAcquisitionStatus();
    }
}
/***************************************************/
bool AcquisitionClass::isFinished(void)
{
    if (stop_condition == STOP_NUMBER && img_acquired >= img_to_acquire)
        return true;
    else if (stop_condition == STOP_TIME && timer.elapsed() >= max_acq_time)
        return true;
    else
        return false;
}
/***************************************************/
