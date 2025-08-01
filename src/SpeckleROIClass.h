#ifndef SPECKLEROICLASS_H
#define SPECKLEROICLASS_H

#include <QObject>
#include <QColor>
#include <QRectF>
#include <QPointF>
#include <QVector>

#ifdef _WIN32
#include <windows.h>
#endif

class SpeckleROIClass : public QObject
{
    Q_OBJECT
public:
    explicit SpeckleROIClass(QObject *parent = 0);
    void set_ROI(QRectF rect);
    void set_color(QColor color);
    void add_data(float data);
    void add_data(float data, float rel_data);
    void clear_data(void);
    void set_name(QString name);
    void set_baseline(float baseline);
    void set_baseline_rel(float baseline);

    QRectF ROI_rect;
    QColor ROI_color;
    QVector<float> ROI_data;
    QVector<float> ROI_rel_data;
    QString ROI_name;
    float ROI_baseline;
    float ROI_baseline_rel;

signals:

public slots:

};

#endif // SPECKLEROICLASS_H


