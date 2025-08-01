#include "DOPulseGenerator.h"

#ifdef USE_NIDAQ

/***************************************************************************/
PulseGenerator::PulseGenerator()
{
    taskHandle = 0;
}

/***************************************************************************/
int PulseGenerator::init(double freq, double duty_cycle, double delay, int num_pulses, double high_val, double low_val, int num_reps, char *chan_name)
{
    int32       error = 0;
    char        errBuff[2048] = {'\0'};

    this->freq = freq;
    this->duty_cycle = duty_cycle;
    this->delay = delay;
    this->num_pulses = num_pulses;
    this->num_reps = num_reps;
    this->high_val = high_val;
    this->low_val = low_val;
    strcpy(this->chan_name, chan_name);

    /******************************************************************/
    // DAQmx Configure Code
    /******************************************************************/
    DAQmxErrChk (DAQmxCreateTask("",&taskHandle));
    DAQmxErrChk (DAQmxCreateCOPulseChanFreq(taskHandle,chan_name,"",DAQmx_Val_Hz,DAQmx_Val_Low,0.0,freq,duty_cycle));
    DAQmxErrChk (DAQmxCfgImplicitTiming(taskHandle,DAQmx_Val_FiniteSamps,num_pulses));

    return 0;

Error:
    if( DAQmxFailed(error) )
        DAQmxGetExtendedErrorInfo(errBuff,2048);
    if( taskHandle!=0 )
    {
        /******************************************************************/
        // DAQmx Stop Code
        /******************************************************************/
        DAQmxStopTask(taskHandle);
        DAQmxClearTask(taskHandle);
    }
    printf("DAQmx Error: %s\n",errBuff);
    return 1;
}

/***************************************************************************/
int PulseGenerator::start()
{
    int32       error = 0;
    char        errBuff[2048] = {'\0'};

    /******************************************************************/
    // DAQmx Start Code
    /******************************************************************/
    DAQmxErrChk (DAQmxStartTask(taskHandle));

    return 0;

Error:
    if( DAQmxFailed(error) )
        DAQmxGetExtendedErrorInfo(errBuff,2048);
    if( taskHandle!=0 )
    {
        /******************************************************************/
        // DAQmx Stop Code
        /******************************************************************/
        DAQmxStopTask(taskHandle);
        DAQmxClearTask(taskHandle);
    }
    printf("DAQmx Error: %s\n",errBuff);
    return 1;
}

/***************************************************************************/
int PulseGenerator::stop()
{
    int32       error = 0;
    char        errBuff[2048] = {'\0'};

    /******************************************************************/
    // DAQmx Stop Code
    /******************************************************************/
    DAQmxErrChk (DAQmxStopTask(taskHandle));

    return 0;

Error:
    if( DAQmxFailed(error) )
        DAQmxGetExtendedErrorInfo(errBuff,2048);
    if( taskHandle!=0 )
    {
        /******************************************************************/
        // DAQmx Stop Code
        /******************************************************************/
        DAQmxStopTask(taskHandle);
        DAQmxClearTask(taskHandle);
    }
    printf("DAQmx Error: %s\n",errBuff);
    return 1;
}

/***************************************************************************/
int PulseGenerator::clear()
{
    int32       error = 0;
    char        errBuff[2048] = {'\0'};

    /******************************************************************/
    // DAQmx Clear Code
    /******************************************************************/
    DAQmxErrChk (DAQmxClearTask(taskHandle));

    return 0;

Error:
    if( DAQmxFailed(error) )
        DAQmxGetExtendedErrorInfo(errBuff,2048);
    if( taskHandle!=0 )
    {
        /******************************************************************/
        // DAQmx Stop Code
        /******************************************************************/
        DAQmxStopTask(taskHandle);
        DAQmxClearTask(taskHandle);
    }
    printf("DAQmx Error: %s\n",errBuff);
    return 1;
}

/***************************************************************************/
int PulseGenerator::is_done()
{
    int32       error = 0;
    char        errBuff[2048] = {'\0'};
    bool32      isDone = 0;

    /******************************************************************/
    // DAQmx Is Task Done Code
    /******************************************************************/
    DAQmxErrChk (DAQmxIsTaskDone(taskHandle,&isDone));

    return isDone;

Error:
    if( DAQmxFailed(error) )
        DAQmxGetExtendedErrorInfo(errBuff,2048);
    if( taskHandle!=0 )
    {
        /******************************************************************/
        // DAQmx Stop Code
        /******************************************************************/
        DAQmxStopTask(taskHandle);
        DAQmxClearTask(taskHandle);
    }
    printf("DAQmx Error: %s\n",errBuff);
    return 1;
}

/***************************************************************************/
int PulseGenerator::get_num_pulses_generated(uInt64 *num_pulses)
{
    int32       error = 0;
    char        errBuff[2048] = {'\0'};

    /******************************************************************/
    // DAQmx Get Number of Pulses Generated Code
    /******************************************************************/
    DAQmxErrChk (DAQmxGetCOPulseChanFreq(taskHandle,"",DAQmx_Val_Low,0.0,freq,duty_cycle));

    return 0;

Error:
    if( DAQmxFailed(error) )
        DAQmxGetExtendedErrorInfo(errBuff,2048);
    if( taskHandle!=0 )
    {
        /******************************************************************/
        // DAQmx Stop Code
        /******************************************************************/
        DAQmxStopTask(taskHandle);
        DAQmxClearTask(taskHandle);
    }
    printf("DAQmx Error: %s\n",errBuff);
    return 1;
}

#endif // USE_NIDAQ


