#ifndef PULSEGENERATORCLASS_H
#define PULSEGENERATORCLASS_H

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef USE_NIDAQ
#include <NIDAQmx.h>
#endif

class PulseGenerator
{
public:
    PulseGenerator();
#ifdef USE_NIDAQ
    int init(double freq, double duty_cycle, double delay, int num_pulses, double high_val, double low_val, int num_reps, char *chan_name);
    int start();
    int stop();
    int clear();
    int is_done();
    int get_num_pulses_generated(uInt64 *num_pulses);
#endif

private:
#ifdef USE_NIDAQ
    TaskHandle  taskHandle;
    char        chan_name[256];
    int         num_pulses;
    int         num_reps;
    double      freq;
    double      duty_cycle;
    double      delay;
    double      high_val;
    double      low_val;
#endif
};

#endif // PULSEGENERATORCLASS_H


