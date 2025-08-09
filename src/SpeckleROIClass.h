#ifndef SPECKLEROICLASS_H
#define SPECKLEROICLASS_H

#include <QObject>
#include <QColor>
#include <QRectF>
#include <QPointF>
#include <QVector>
#include <QPolygonF>

#ifdef _WIN32
#include <windows.h>
#endif

#include "CImg.h"
using namespace cimg_library;

enum ROIType { RECT_ROI, POLY_ROI };

class SpeckleROIClass : public QObject
{
    Q_OBJECT
public:
    explicit SpeckleROIClass(QObject *parent = 0);
    // Legacy constructor used by implementation
    SpeckleROIClass(void);

    void set_ROI(QRectF rect);
    void set_color(QColor color);
    void add_data(float data);
    void add_data(float data, float rel_data);
    void clear_data(void);
    void set_name(QString name);
    void set_baseline(float baseline);
    void set_baseline_rel(float baseline);

    // New polygon API used by UI
    void setPolygon(const QPolygonF &poly) { polygon = poly; }

    QRectF ROI_rect;
    QColor ROI_color;
    QVector<float> ROI_data;
    QVector<float> ROI_rel_data;
    QString ROI_name;
    float ROI_baseline;
    float ROI_baseline_rel;
    QPolygonF polygon;

    // Members used by implementation
    bool show;
    float opacity;
    unsigned char white[3];
    unsigned char black[3];
    ROIType type;
    CImg<unsigned char> mask;
    CImg<float> points;
    CImgList<float> points_list;
    int mask_size;
    double this_sc_mean;
    double sc_baseline;
    QVector<double> sc_mean;
    QVector<double> sc_mean_norm;

    void set_mask(CImg<unsigned char> img);
    void set_points(void);
    void calculateMaskSize(void);
    void calculateMean(CImg<float> *sc);
    void setDefaultBaseline(void);
    void calculateBaseline(int idx_start, int idx_end);
    void recalcRelative(void);
    void updateSC(void);
    void lateROIUpdate(int currentSize);

signals:

public slots:

};

#endif // SPECKLEROICLASS_H


