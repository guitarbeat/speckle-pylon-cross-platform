#include "overlayimagecreator.h"
#include "speckle.h"
#include "speckle_processing.h"
#include "SpeckleOverlayClass.h"
extern SpeckleClass *speckle;
/********************************************************************/
OverlayImageCreator::OverlayImageCreator()
{
    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    connect(timer, &QTimer::timeout, this, &OverlayImageCreator::checkForOverlayImage);
    refresh_interval = 40; // 25 fps refresh rate
}
/********************************************************************/
void OverlayImageCreator::startWatchAcquisition(void)
{
    last_overlay_displayed = 0;
    last_bg_displayed = 0;
    images_shown = 0;
    overlay_display_fps = 0;
    speckle->overlay_frames_shown = 0;
    timer->start(refresh_interval);
    fps_timer.restart();
}
/********************************************************************/
void OverlayImageCreator::stopWatchAcquisition(void)
{
    timer->stop();
}
/********************************************************************/
void OverlayImageCreator::checkForOverlayImage(void)
{
    // timer callback - check for new overlay image to display
    bool update=false;

    if(speckle->show_overlay && speckle->overlays.bg_src==SRC_SC)
        update=true;
    if(speckle->show_overlay && speckle->overlays.over_src==SRC_SC)
        update=true;
    if(speckle->show_overlay && speckle->overlays.bg_src==SRC_VIDEO)
        update=true;
    if(speckle->show_overlay && speckle->overlays.bg_src==SRC_RAW)
        update=true;

    if(update)
        create_overlay();
}
/********************************************************************/
void OverlayImageCreator::updateOverlayImage(void)
{
    // slot to force update of live image when a display setting is changed
    setColormap(speckle->overlays.over_cmap);
    if(speckle->show_overlay)
        create_overlay();
}
/********************************************************************/
void OverlayImageCreator::setColormap(CImg<unsigned char> cmap)
{
    colormap = cmap;
    createColormapImage(&colormap_image, colormap, 50, speckle->overlay_img_rgb.height()/2,
                        speckle->overlays.GetOverMin(), speckle->overlays.GetOverMax());
}
/********************************************************************/
void OverlayImageCreator::create_overlay(void)
{
    if(speckle->overlays.bg_src==SRC_RAW)
        last_bg_displayed=speckle->theCamera->img_acquired;
    if(speckle->overlays.bg_src==SRC_VIDEO)
        last_bg_displayed=speckle->video_in_frames_acquired;
    if(speckle->overlays.over_src==SRC_SC)
        last_overlay_displayed=speckle->num_sc_processed;

    // Resize overlay image to match speckle contrast image size
    if(((speckle->overlay_img.width()*speckle->overlay_img.height() != (speckle->sc_w)*(speckle->sc_h)) ||
            (speckle->overlay_img.height() != speckle->overlay_img_rgb.height()) ||
            (speckle->overlay_img.width() != speckle->overlay_img_rgb.width())) &&
            speckle->overlays.bg_src != SRC_VIDEO) // no need to do this when overlaying video
    {       
        speckle->overlay_img.resize(speckle->sc_w, speckle->sc_h,1,1);
        speckle->overlay_imgf.resize(speckle->sc_w, speckle->sc_h,1,1);
        speckle->overlay_img_rgb.resize(speckle->sc_w, speckle->sc_h,1,3);
    }

    if(((speckle->overlays.bg_src == SRC_RAW || speckle->overlays.over_src == SRC_RAW)) && speckle->theCamera->img_acquired>0)
        memcpy(speckle->live_img.data(), speckle->raw_images[speckle->theCamera->img_acquired], speckle->theCamera->im_w*speckle->theCamera->im_h);

    if(speckle->overlays.bg_src == SRC_TC)
        speckle->overlay_imgf.assign(speckle->rTC, speckle->sc_w, speckle->sc_h);

    //img_creation_timer.restart();
    speckle->overlays.CreateOverlayImage(speckle->live_img, speckle->sc_imgf, speckle->overlay_imgf);
    //img_creation_time=img_creation_timer.elapsed();
    //if(QRandomGenerator::global()->generateDouble() < 0.05)
    //    qDebug() << "overlay speed: " << img_creation_time;

    speckle->overlay_img_rgb = speckle->overlays.output_img;
    // resize Qimage
    if( (overlay_qi.width()!=speckle->overlay_img_rgb.width()) || (overlay_qi.height()!=speckle->overlay_img_rgb.height()) )
        overlay_qi = QImage(speckle->overlay_img_rgb.width(), speckle->overlay_img_rgb.height(), QImage::Format_RGB888);

    if(speckle->show_sc_colorbar)
    {
        if(colormap_image.height() != speckle->overlay_img_rgb.height()/2)
            createColormapImage(&colormap_image, colormap, 50, speckle->overlay_img_rgb.height()/2,
                                speckle->overlays.GetOverMin(), speckle->overlays.GetOverMax());
        speckle->overlay_img_rgb.draw_image(speckle->overlay_img_rgb.width()-50,0,colormap_image);
       // AddColorbarToImage(&(speckle->overlay_img_rgb), speckle->overlays.over_cmap,
       //     speckle->overlays.GetOverMin(), speckle->overlays.GetOverMax());
    }

    // Resize, rotate, and flip image as specified
    if(speckle->transpose == 1)
        speckle->overlay_img_rgb.transpose();
    if(speckle->flip_horizontal == 1)
        speckle->overlay_img_rgb.mirror('y');
    if(speckle->flip_vertical == 1)
        speckle->overlay_img_rgb.mirror('x');
    if(speckle->rotate != 0)
        speckle->overlay_img_rgb.rotate((float)(speckle->rotate));

    CImg_to_QImage(&(speckle->overlay_img_rgb), &overlay_qi);
    overlay_qp = QPixmap::fromImage(overlay_qi); //QImage::Format_RGB888

    // insert current frame into image list buffer for writing to video file
    if(speckle->acquire_flag==ACQUISITION_MODE && speckle->save_overlay_video)
    {
        int idx = images_shown % NUM_VIDEO_FRAME_BUFFERS;
        speckle->overlay_frames_to_write(idx) = speckle->overlay_img_rgb;
    }

    images_shown++;
    speckle->overlay_frames_shown = images_shown;

    // Update fps counter every 25 iterations (1 Hz)
    if(images_shown % 25 == 0)
        overlay_display_fps = static_cast<int>(25 * 1000.0 / fps_timer.restart());

    emit overlayImageReady(&overlay_qp, overlay_display_fps);
}
/********************************************************************/
