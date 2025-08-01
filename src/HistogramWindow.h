#ifndef HISTOGRAMWINDOW_H
#define HISTOGRAMWINDOW_H

#include <QDialog>
#include <QtCharts>
#include "CImg.h"
using namespace cimg_library;

class HistogramWindow : public QDialog
{
    Q_OBJECT

signals:
    void histogramClosed(void);

public:
    explicit HistogramWindow(QWidget *parent = nullptr);
    void updateRawHistogram(CImg<float> *histogram);
    void updateSCHistogram(CImg<float> *histogram);
    void updateRawRange(int Imin, int Imax);
    void updateSCRange(float SCmin, float SCmax);
    void showOverlay(bool show_overlay);
    void updateOverlay(float kmin, float kmax, bool use_alpha, float kmid);

private:
    void closeEvent(QCloseEvent *event);

    QBarSeries *rawSeries, *scSeries;
    QChart *rawChart, *scChart;
    QValueAxis *rawAxis, *scAxis;
    QChartView *rawView, *scView;
    QLabel *rawTitle, *scTitle;
    QLineSeries *rawMinSeries, *rawMaxSeries, *scMinSeries,
                *scMaxSeries, *overlaySeries;
};

#endif // HISTOGRAMWINDOW_H
