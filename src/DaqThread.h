#ifndef DAQTHREAD_H
#define DAQTHREAD_H

#include <QThread>
#include <QElapsedTimer>

#ifdef USE_NIDAQ
#include <NIDAQmx.h>
#include "DOPulseGenerator.h"
#endif

#include "speckle.h"

class DaqThread : public QThread
{
    Q_OBJECT
public:
    explicit DaqThread(QObject *parent = 0);
    void run();
    void stop();
    void set_speckle_obj(SpeckleClass *s);

    bool daq_running;
    bool daq_stop;
    int daq_mode;
    int daq_status;
    int daq_samples_per_trigger;
    int daq_camera_delay;
    int seq_delay;

    SpeckleClass *speckle;

#ifdef USE_NIDAQ
    TaskHandle  taskHandle;
    TaskHandle  ao_taskHandle;
    int32       error;
    char        errBuff[2048];
    int         num_daq_chan_in_use;
    QVector<double> daq_data;
    QVector<short> daq_data16;
    int         ai_input_config;
    double      daq_samp_rate;
    float       daq_duration;
    double      daq_AOM_pulse_rate;
    double      daq_AOM_voltage;
    double      daq_AOM_pulse_width;
    int         daq_AOM_mode;
    QVector<double> ao_vec;
    QVector<double> ao_freq_list;
    double      daq_AOM_offset;
    bool        daq_write_continuously;
    QString     daq_task_name1;
    QString     daq_task_name2;

    PulseGenerator pulse_gen;
#endif

signals:
    void daq_data_ready(void);
    void daq_status_changed(int status);
    void daq_message(QString msg);

public slots:

};

#endif // DAQTHREAD_H


