#ifndef OVERLAYIMAGECREATOR_H
#define OVERLAYIMAGECREATOR_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QImage>
#include <QPixmap>
#include "CImg.h"
using namespace cimg_library;

class OverlayImageCreator : public QObject
{
    Q_OBJECT
public:
    OverlayImageCreator();
    int overlay_display_fps;
    QPixmap get_overlay_qp(void) { return overlay_qp; }

signals:
    void overlayImageReady(QPixmap *, int fps);

public slots:
    void checkForOverlayImage(void);
    void startWatchAcquisition(void);
    void stopWatchAcquisition(void);
    void updateOverlayImage(void);

private:
    QTimer *timer;
    QElapsedTimer fps_timer;
    QElapsedTimer img_creation_timer;
    qint64 img_creation_time;
    int refresh_interval;
    QImage overlay_qi;
    QPixmap overlay_qp;
    int last_overlay_displayed, last_bg_displayed;
    int images_shown;
    CImg<unsigned char> colormap; // 256x3 element colormap
     CImg<unsigned char> colormap_image; // image of colormap that's added to displayed image

    void create_overlay(void);
    void setColormap(CImg<unsigned char> cmap);
};

#endif // OVERLAYIMAGECREATOR_H
