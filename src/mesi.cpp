#include "mesi.h"

/******************************************************************************************/
MESI::MESI(QObject *parent) : QObject(parent) {
    calibrated = false;
    exposures_are_valid = false;
    successAOMOutput = false;
    stopAOM();
}
/******************************************************************************************/
bool MESI::setExposures(QString input) {
    QStringList split = input.split(",",QString::SkipEmptyParts);

    exposures.clear(); // Clear previous values
    exposures_are_valid = true;

    foreach(QString this_string, split) {
        float this_exp = this_string.toFloat();
        if(this_exp != 0.0)
            exposures << this_exp;
        else
            exposures_are_valid = false;
    }

    return exposures_are_valid;
}
/******************************************************************************************/
QStringList MESI::getExposureList(void) {
    QStringList list;
    foreach(float this_exp, exposures)
        list << QString::number(this_exp);
    return list;
}
/******************************************************************************************/
bool MESI::Calibrate(void) {


    return calibrated;
}
/******************************************************************************************/
#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else
/******************************************************************************************/
bool MESI::setAOMVoltage(double volts) {

    int32 error = 0;
    AOMTaskHandle = 0;
    float64 data[1000];
    char errBuff[2048] = {'\0'};

    for(int i = 0; i < 1000; i++)
        data[i] = volts;

    successAOMOutput = true;
    qDebug() << "DAQ State AA: " << successAOMOutput << " at beginnin of AO";

    // DAQmx Configure Code
    DAQmxErrChk(DAQmxCreateTask("",&AOMTaskHandle));
    DAQmxErrChk(DAQmxCreateAOVoltageChan(AOMTaskHandle,"Dev1/ao0","",-2,2,DAQmx_Val_Volts,NULL));
    DAQmxErrChk(DAQmxCfgSampClkTiming(AOMTaskHandle,"",1000.0,DAQmx_Val_Rising,DAQmx_Val_ContSamps,1000));

    // DAQmx Write Code
    DAQmxErrChk(DAQmxWriteAnalogF64(AOMTaskHandle,1000,0,10.0,DAQmx_Val_GroupByChannel,data,NULL,NULL));

    // DAQmx Start Code
    DAQmxErrChk(DAQmxStartTask(AOMTaskHandle));

    Error:
        successAOMOutput = false;
        if(DAQmxFailed(error))
            DAQmxGetExtendedErrorInfo(errBuff,2048);
        stopAOM();
        if(DAQmxFailed(error))
            printf("DAQmx Error: %s\n",errBuff);
        return successAOMOutput;

    return successAOMOutput;
}
/******************************************************************************************/
int MESI::stopAOM(void) {
    if(AOMTaskHandle != 0) {
        qDebug() << "Parent stopping AOM task ";
        DAQmxStopTask(AOMTaskHandle);
        DAQmxClearTask(AOMTaskHandle);
    }

    return 1;
}
/******************************************************************************************/
void MESI::deactivateAOM(void) {
    stopAOM();
    setAOMVoltage(0.0);
    stopAOM();
}
/******************************************************************************************/
