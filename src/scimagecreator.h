#ifndef SCIMAGECREATOR_H
#define SCIMAGECREATOR_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QImage>
#include <QPixmap>
#include "CImg.h"
using namespace cimg_library;

class SCImageCreator : public QObject
{
    Q_OBJECT
public:
    explicit SCImageCreator(QObject *parent = nullptr);
     QPixmap get_sc_qp(void) { return sc_qp; }

signals:
    void scImageReady(QPixmap *, int fps);
    void histogramReady(CImg<float> *histogram);

public slots:
    void checkForSCImage(void);
    void startWatchAcquisition(void);
    void stopWatchAcquisition(void);
    void updateSCImage(void);

private:
    QTimer *timer;
    int refresh_interval;
    QElapsedTimer fps_timer;
    int sc_display_fps;
    QImage sc_qi;
    QPixmap sc_qp;
    int last_sc_displayed;
    int images_shown;
    CImg<unsigned char> colormap; // 256x3 element colormap
    CImg<unsigned char> colormap_image; // image of colormap that's added to displayed image
    CImg<float> histogram;

    void create_sc(void);
    void setColormap(CImg<unsigned char> cmap);
};

#endif // SCIMAGECREATOR_H
