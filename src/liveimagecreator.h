#ifndef LIVEIMAGECREATOR_H
#define LIVEIMAGECREATOR_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QImage>
#include <QPixmap>
#include "CImg.h"
using namespace cimg_library;

class LiveImageCreator : public QObject
{
    Q_OBJECT

public:
    LiveImageCreator();
    QPixmap get_raw_qp(void) { return raw_qp; }

signals:
    void liveImageReady(QPixmap *, int fps);
    void histogramReady(CImg<float> *histogram);

public slots:
    void checkForLiveImage(void);
    void startWatchAcquisition(void);
    void stopWatchAcquisition(void);
    void updateLiveImage(void);

private:
    QTimer *timer;
    int refresh_interval;
    QElapsedTimer fps_timer;
    int raw_display_fps;
    QImage raw_qi;
    QPixmap raw_qp;
    int last_live_displayed;
    int images_shown;
    CImg<unsigned char> colormap; // 256x3 element colormap
    CImg<unsigned char> colormap_image; // image of colormap that's added to displayed image
    CImg<float> histogram;

    void create_live(void);
    void setColormap(CImg<unsigned char> cmap);
};

#endif // LIVEIMAGECREATOR_H
