#include "scimagecreator.h"
#include "speckle.h"
#include "speckle_processing.h"
extern SpeckleClass *speckle;
/********************************************************************/
SCImageCreator::SCImageCreator(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    connect(timer, &QTimer::timeout, this, &SCImageCreator::checkForSCImage);
    refresh_interval = 20; // 50 fps refresh rate
}
/********************************************************************/
void SCImageCreator::startWatchAcquisition(void)
{
    last_sc_displayed = 0;
    images_shown = 0;
    sc_display_fps = 0;
    speckle->sc_frames_shown = 0;
    speckle->sc_frames_buffered = 0;
    timer->start(refresh_interval);
    fps_timer.restart();
}
/********************************************************************/
void SCImageCreator::stopWatchAcquisition(void)
{
    timer->stop();
}
/********************************************************************/
void SCImageCreator::checkForSCImage(void)
{
    // timer callback - check for new sc image to display
    if (speckle->compute_SC && speckle->show_SC)
        create_sc();
}
/********************************************************************/
void SCImageCreator::updateSCImage(void)
{
    // slot to force update of sc image when a display setting is changed
    setColormap(speckle->sc_palette); // this isn't the best way to force a colormap update
    create_sc();
}
/********************************************************************/
void SCImageCreator::setColormap(CImg<unsigned char> cmap)
{
    colormap = cmap;
    createColormapImage(&colormap_image, colormap, 50, speckle->sc_img_rgb.height()/2,
                        speckle->SC_min, speckle->SC_max);
}
/********************************************************************/
void SCImageCreator::create_sc(void)
{
    last_sc_displayed = speckle->num_sc_processed;

    if((speckle->sc_img.height() != speckle->sc_h) || (speckle->sc_img.width() != speckle->sc_w) ||
        (speckle->sc_img.height() != speckle->sc_img_rgb.height()) ||
        (speckle->sc_img.width() != speckle->sc_img_rgb.width()))
    {
        speckle->sc_img.resize(speckle->sc_w, speckle->sc_h, 1, 1);
        speckle->sc_imgf.resize(speckle->sc_w, speckle->sc_h, 1, 1);
        speckle->sc_img_rgb.resize(speckle->sc_w, speckle->sc_h, 1, 3);
    }
    if( (sc_qi.width()!=speckle->sc_img_rgb.width()) || (sc_qi.height()!=speckle->sc_img_rgb.height()) )
        sc_qi = QImage(speckle->sc_img_rgb.width(), speckle->sc_img_rgb.height(), QImage::Format_RGB888);

    ScaleToMinMax(speckle->sc_imgf.data(), &(speckle->sc_img), speckle->SC_min, speckle->SC_max);
    speckle->sc_img_rgb = speckle->sc_img;
    speckle->sc_img_rgb.map(speckle->sc_palette);

    // mask out dark areas by thresholding live image
    if(speckle->mask_dark_areas_threshold>0)
    {
        CImg<unsigned char> live_threshold = speckle->live_img;
        live_threshold.crop(speckle->NxN/2, speckle->NxN/2, speckle->NxN/2+speckle->sc_w, speckle->NxN/2+speckle->sc_h);
        live_threshold.resize(speckle->sc_img);
        //live_threshold.blur_median(5);
        live_threshold.blur(speckle->mask_blur_width);
        cimg_forXY(speckle->sc_img,x,y) {
            if(live_threshold(x,y) <= speckle->mask_dark_areas_threshold)
                speckle->sc_img_rgb.fillC(x,y,0,0,0,0);
        }
    }

    // draw colorbar
    if(speckle->show_sc_colorbar)
    {
        if(colormap_image.height() != speckle->sc_img_rgb.height()/2)
            createColormapImage(&colormap_image, colormap, 50, speckle->sc_img_rgb.height()/2,
                                speckle->SC_min, speckle->SC_max);
        speckle->sc_img_rgb.draw_image(speckle->sc_img_rgb.width()-50,0,colormap_image);
        //AddColorbarToImage(&(speckle->sc_img_rgb), speckle->sc_palette,
        //    speckle->SC_min, speckle->SC_max);
    }

    // scale image according to zoom level
    if(speckle->transpose==1)
        speckle->sc_img_rgb.transpose();
    if(speckle->flip_horizontal==1)
        speckle->sc_img_rgb.mirror('y');
    if(speckle->flip_vertical==1)
        speckle->sc_img_rgb.mirror('x');
    if(speckle->rotate != 0)
        speckle->sc_img_rgb.rotate((float)(speckle->rotate));

    CImg_to_QImage(&(speckle->sc_img_rgb), &sc_qi);
    sc_qp = QPixmap::fromImage(sc_qi); //QImage::Format_RGB888

    // Insert every other frame into buffer for writing to video file
    if(speckle->acquire_flag==ACQUISITION_MODE && speckle->save_sc_video && images_shown % 2 == 0)
    {
        uint idx = (images_shown / 2) % NUM_VIDEO_FRAME_BUFFERS;
        speckle->sc_frames_to_write(idx) = speckle->sc_img_rgb;
        speckle->sc_frames_buffered = (images_shown + 1) / 2;
    }

    images_shown++;
    speckle->sc_frames_shown = images_shown;

    // Update fps counter every 50 iterations (1 Hz)
    if(images_shown % 50 == 0)
        sc_display_fps = static_cast<int>(50 * 1000.0 / fps_timer.restart());

    emit scImageReady(&sc_qp, sc_display_fps); // Send to SpeckleDisplay(s)

    // Update histogram every 25 iterations
    if(speckle->show_hist && images_shown % 25 == 0)
    {
        histogram = speckle->sc_imgf.get_histogram(256, 0, 1.0);
        emit(histogramReady(&histogram)); // Send to HistogramWindow
    }
}
/********************************************************************/
