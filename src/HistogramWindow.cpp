#include "HistogramWindow.h"
#include <QDebug>

/****************************************************************************/
HistogramWindow::HistogramWindow(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle("Histograms");
    this->resize(600, 500);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setAttribute(Qt::WA_DeleteOnClose); // Delete widget on close

    // Set widget background to white
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    QFont font; // Chart titles
    font.setPixelSize(12);

    // Set up Raw Histogram
    rawChart = new QChart();
    rawChart->legend()->setVisible(false);
    rawChart->setContentsMargins(-10, -10, -10, -10);
    rawChart->layout()->setContentsMargins(0, 0, 0, 0);    
    rawChart->setBackgroundRoundness(0);

    rawMinSeries = new QLineSeries(); // Minimum display value
    rawMinSeries->append(QPoint(0, 0));
    rawMinSeries->append(QPoint(0, 1));
    rawMinSeries->setPen(QPen(Qt::red, 2));
    rawChart->addSeries(rawMinSeries);

    rawMaxSeries = new QLineSeries(); // Maximum display value
    rawMaxSeries->append(QPoint(255, 0));
    rawMaxSeries->append(QPoint(255, 1));
    rawMaxSeries->setPen(QPen(Qt::red, 2));
    rawChart->addSeries(rawMaxSeries);

    rawSeries = new QBarSeries(); // Histogram
    rawChart->addSeries(rawSeries);

    rawAxis = new QValueAxis(); // Horizontal axis
    rawAxis->setRange(0, 255);
    rawAxis->setTickCount(2);
    rawAxis->setMinorTickCount(3);
    rawAxis->setLabelFormat("%d"); // Integer only
    rawChart->addAxis(rawAxis, Qt::AlignBottom);
    rawSeries->attachAxis(rawAxis);
    rawMinSeries->attachAxis(rawAxis);
    rawMaxSeries->attachAxis(rawAxis);

    rawView = new QChartView(rawChart);
    rawView->setRenderHint(QPainter::Antialiasing);

    rawTitle = new QLabel("Raw"); // Title
    rawTitle->setAlignment(Qt::AlignHCenter);
    rawTitle->setFont(font);

    // Set up Speckle Contrast Histogram
    scChart = new QChart();
    scChart->legend()->setVisible(false);
    scChart->setContentsMargins(-10, -10, -10, -15);
    scChart->layout()->setContentsMargins(0, 0, 0, 0);
    scChart->setBackgroundRoundness(0);

    scMinSeries = new QLineSeries(); // Minimum display value
    scMinSeries->append(QPointF(0.0, 0));
    scMinSeries->append(QPointF(0.0, 1));
    scMinSeries->setPen(QPen(Qt::red, 2));
    scChart->addSeries(scMinSeries);

    scMaxSeries = new QLineSeries(); // Maximum display value
    scMaxSeries->append(QPointF(0.5, 0));
    scMaxSeries->append(QPointF(0.5, 1));
    scMaxSeries->setPen(QPen(Qt::red, 2));
    scChart->addSeries(scMaxSeries);

    overlaySeries = new QLineSeries(); // Overlay display settings
    overlaySeries->append(QPointF(0.0, 0));
    overlaySeries->append(QPointF(0.0, 0)); // OverlayMin
    overlaySeries->append(QPointF(0.0, 1));
    overlaySeries->append(QPointF(0.5, 1)); // Alpha Threshold (Kmid)
    overlaySeries->append(QPointF(0.5, 0)); // OverlayMax
    overlaySeries->append(QPointF(1.0, 0));
    overlaySeries->setPen(QPen(Qt::green, 2));
    overlaySeries->setVisible(false);
    scChart->addSeries(overlaySeries);

    scSeries = new QBarSeries(); // Histogram
    scChart->addSeries(scSeries);

    scAxis = new QValueAxis(); // Horizontal axis
    scAxis->setRange(0, 1);
    scAxis->setTickCount(2);
    scAxis->setMinorTickCount(3);
    scAxis->setLabelFormat("%.2f"); // 2 decimals
    scChart->addAxis(scAxis, Qt::AlignBottom);
    scSeries->attachAxis(scAxis);
    scMinSeries->attachAxis(scAxis);
    scMaxSeries->attachAxis(scAxis);

    scView = new QChartView(scChart);
    scView->setRenderHint(QPainter::Antialiasing);

    scTitle = new QLabel("Speckle Contrast");
    scTitle->setAlignment(Qt::AlignCenter);
    scTitle->setFont(font);

    // Add charts to the window
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(rawTitle);
    verticalLayout->addWidget(rawView);
    verticalLayout->addWidget(scTitle);
    verticalLayout->addWidget(scView);
    verticalLayout->setContentsMargins(0, 5, 0, 0);
    this->setLayout(verticalLayout);
}
/****************************************************************************/
void HistogramWindow::closeEvent(QCloseEvent *event)
{
    emit(histogramClosed());
    QDialog::closeEvent(event);
}
/****************************************************************************/
void HistogramWindow::updateRawHistogram(CImg<float> *histogram)
{
    QBarSet *data = new QBarSet("Raw");
    cimg_for(*histogram, ptr, float)
        *data << *ptr;
    data->setBorderColor(Qt::transparent);

    rawSeries->clear();
    rawSeries->append(data);

    // No idea why this is necessary to get chart to update
    rawChart->removeSeries(rawSeries);
    rawChart->addSeries(rawSeries);

    CImg<double> stats = histogram->get_stats();
    qreal saturated = data->at(data->count() - 1);
    rawTitle->setText(QString("Raw (Peak = %1, Saturated = %2)")
                      .arg(QString::number(stats(8)), QString::number(saturated)));
}
/****************************************************************************/
void HistogramWindow::updateSCHistogram(CImg<float> *histogram)
{
    QBarSet *data = new QBarSet("Raw");
    cimg_for(*histogram, ptr, float)
        *data << *ptr;
    data->setBorderColor(Qt::transparent);

    scSeries->clear();
    scSeries->append(data);

    // No idea why this is necessary to get chart to update
    scChart->removeSeries(scSeries);
    scChart->addSeries(scSeries);

    CImg<double> stats = histogram->get_stats();
    scTitle->setText(QString("Speckle Contrast (Peak = %1)")
                      .arg(stats(8)/255.0, 0, 'f', 2));
}
/****************************************************************************/
void HistogramWindow::updateRawRange(int Imin, int Imax)
{
    rawMinSeries->replace(0, Imin, 0);
    rawMinSeries->replace(1, Imin, 1);
    rawMaxSeries->replace(0, Imax, 0);
    rawMaxSeries->replace(1, Imax, 1);
}
/****************************************************************************/
void HistogramWindow::updateSCRange(float SCmin, float SCmax)
{
    scMinSeries->replace(0, SCmin, 0);
    scMinSeries->replace(1, SCmin, 1);
    scMaxSeries->replace(0, SCmax, 0);
    scMaxSeries->replace(1, SCmax, 1);
}
/****************************************************************************/
void HistogramWindow::showOverlay(bool show_overlay)
{
    overlaySeries->setVisible(show_overlay);
}
/****************************************************************************/
void HistogramWindow::updateOverlay(float kmin, float kmax, bool use_alpha, float kmid)
{
    // OverlayMin
    overlaySeries->replace(1, kmin, 0);
    overlaySeries->replace(2, kmin, 1);

    // Kmid (Alpha Transparency)
    if(use_alpha)
        overlaySeries->replace(3, kmid, 1);
    else
        overlaySeries->replace(3, kmax, 1);

    // OverlayMax
    overlaySeries->replace(4, kmax, 0);
}
/****************************************************************************/
