#ifndef MESI_H
#define MESI_H

#include <QtCore>
#include <math.h>
#include "NIDAQmx.h"

class MESI : public QObject {

    Q_OBJECT

signals:

public slots:

public:
    explicit MESI(QObject *parent = 0);
    bool setExposures(QString input);
    QStringList getExposureList(void);
    bool Calibrate(void);

    // AOM control
    bool setAOMVoltage(double volts);
    int stopAOM(void);
    void deactivateAOM(void);

private:
    bool calibrated, exposures_are_valid;
    QVector<float> exposures;

    TaskHandle AOMTaskHandle;
    bool successAOMOutput;
};

#endif // MESI_H
