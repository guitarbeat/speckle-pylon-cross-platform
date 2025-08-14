#include "liveimagecreator.h"
#include "speckle.h"
#include "speckle_processing.h"
extern SpeckleClass *speckle;
/********************************************************************/
LiveImageCreator::LiveImageCreator()
{
    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    connect(timer, &QTimer::timeout, this, &LiveImageCreator::checkForLiveImage);
    refresh_interval = 20; // 50 fps refresh rate
}
/********************************************************************/
void LiveImageCreator::startWatchAcquisition(void)
{
    last_live_displayed = 0;
    images_shown = 0;
    raw_display_fps = 0;
    timer->start(refresh_interval);
    fps_timer.restart();
}
/********************************************************************/
void LiveImageCreator::stopWatchAcquisition(void)
{
    timer->stop();
}
/********************************************************************/
void LiveImageCreator::checkForLiveImage(void)
{
    // timer callback - check for new raw image to display
    if (speckle->show_raw)
        create_live();
}
/********************************************************************/
void LiveImageCreator::updateLiveImage(void)
{
    // slot to force update of live image when a display setting is changed
    if (speckle->show_raw && (speckle->theCamera->img_acquired > 0))
    {
        setColormap(speckle->live_palette); // this isn't the best way to force a colormap update
        create_live();
    }
}
/********************************************************************/
void LiveImageCreator::setColormap(CImg<unsigned char> cmap)
{
    colormap = cmap;
    createColormapImage(&colormap_image, colormap, 50, speckle->live_img_rgb.height()/2,
                        speckle->Imin, speckle->Imax);
}
/********************************************************************/
void LiveImageCreator::create_live(void)
{
    last_live_displayed = speckle->theCamera->img_acquired - 1;
    if(last_live_displayed<0)
        last_live_displayed=0;

    // Resize live image to match camera image size
    if((speckle->live_img.width()*speckle->live_img.height() != speckle->theCamera->im_w*speckle->theCamera->im_h) ||
        (speckle->live_img.width() != speckle->live_img_rgb.width()) ||
        (speckle->live_img.height() != speckle->live_img_rgb.height()))
    {
        speckle->live_img.resize(speckle->theCamera->im_w, speckle->theCamera->im_h, 1, speckle->theCamera->color_planes);
        speckle->live_img_rgb.resize(speckle->theCamera->im_w, speckle->theCamera->im_h, 1, 3);
        if(speckle->theCamera->bytes_pixel == 2)
            speckle->live_img16.resize(speckle->theCamera->im_w, speckle->theCamera->im_h, 1, 1);
    }
    if( (raw_qi.width()!=speckle->live_img_rgb.width()) || (raw_qi.height()!=speckle->live_img_rgb.height()) )
        raw_qi = QImage(speckle->live_img_rgb.width(), speckle->live_img_rgb.height(), QImage::Format_RGB888);

    int Imin = speckle->Imin;
    int Imax = speckle->Imax;

    if(speckle->theCamera->bytes_pixel == 2) {
        // re-map 16-bit pixels to an 8-bit pixel image for display and processing
        cimg_forXY(speckle->raw_list16[0],x,y) {
            if(speckle->raw_list16[0](x,y) < Imin)
                speckle->live_img(x,y) = 0;
            else if(speckle->raw_list16[0](x,y) > Imax)
                speckle->live_img(x,y) = 255;
            else
                speckle->live_img(x,y) = (unsigned char)(((float)(speckle->raw_list16[0](x,y)) - Imin)/((float)((Imax - Imin)))*255.0);
        }
        memcpy(speckle->live_img16.data(), speckle->raw_images[last_live_displayed], speckle->theCamera->im_w*speckle->theCamera->im_h*speckle->theCamera->bytes_pixel);
    } else {
        memcpy(speckle->live_img.data(), speckle->raw_images[last_live_displayed], speckle->theCamera->im_w*speckle->theCamera->im_h*speckle->theCamera->color_planes);
    }

    if(speckle->theCamera->color_planes == 1) {
        if(Imin>0 || Imax<255)
        {
            // only scale if needed
            // Create a temporary float buffer view and scale
            std::vector<float> tmp(static_cast<size_t>(speckle->live_img.width()*speckle->live_img.height()), 0.0f);
            // Fill from current 8-bit image as floats
            int idx = 0;
            cimg_forXY(speckle->live_img,x,y) { tmp[idx++] = static_cast<float>(speckle->live_img(x,y)); }
            ScaleToMinMax(tmp.data(), &(speckle->live_img), Imin, Imax);
        }
        speckle->live_img_rgb = speckle->live_img;
        speckle->live_img_rgb.map(speckle->live_palette);
    } else {

        // Update RGB histogram
        speckle->histogram_red = speckle->live_img.get_channel(0).get_histogram(256,0,255);
        speckle->histogram_green = speckle->live_img.get_channel(1).get_histogram(256,0,255);
        speckle->histogram_blue = speckle->live_img.get_channel(2).get_histogram(256,0,255);


        // Create RGB image for display
        //speckle->live_img_rgb.assign(speckle->raw_images[0], speckle->theCamera->im_w, speckle->theCamera->im_h, 1, 3, false);
        speckle->live_img_rgb = speckle->live_img;
        cimg_forXY(speckle->live_img_rgb,x,y) {
            if((speckle->live_img_rgb(x,y,0) == 255) || (speckle->live_img_rgb(x,y,1) == 255) || (speckle->live_img_rgb(x,y,2) == 255)) {
                speckle->live_img_rgb(x,y,0) = speckle->red_chan;
                speckle->live_img_rgb(x,y,1) = speckle->green_chan;
                speckle->live_img_rgb(x,y,2) = speckle->blue_chan;
            }
        }
    }

    // Draw colorbar
    if(speckle->show_raw_colorbar)
    {
        if(colormap_image.height() != speckle->live_img_rgb.height()/2)
            createColormapImage(&colormap_image, colormap, 50, speckle->live_img_rgb.height()/2, Imin, Imax);
        speckle->live_img_rgb.draw_image(speckle->live_img_rgb.width()-50,0,colormap_image);
        //AddColorbarToImage(&(speckle->live_img_rgb), speckle->live_palette, Imax, Imin);
    }

    if(speckle->transpose == 1)
        speckle->live_img_rgb.transpose();
    if(speckle->flip_horizontal == 1)
        speckle->live_img_rgb.mirror('y');
    if(speckle->flip_vertical == 1)
        speckle->live_img_rgb.mirror('x');
    if(speckle->rotate != 0)
        speckle->live_img_rgb.rotate((float)(speckle->rotate));

    CImg_to_QImage(&(speckle->live_img_rgb), &raw_qi);
    raw_qp = QPixmap::fromImage(raw_qi); //QImage::Format_RGB888

    images_shown++;

    // Update fps counter every 50 iterations (1 Hz)
    if(images_shown % 50 == 0)
        raw_display_fps = static_cast<int>(50 * 1000.0 / fps_timer.restart());

    emit liveImageReady(&raw_qp, raw_display_fps); // Send to SpeckleDisplay(s)

    // Update histogram every 25 iterations (2 Hz)
    if(speckle->show_hist && images_shown % 25 == 0)
    {
        if(speckle->theCamera->bytes_pixel == 2)
            histogram = speckle->live_img16.get_histogram(256, 0, (1 << speckle->theCamera->bit_depth) - 1);
        else
            histogram = speckle->live_img.get_histogram(256, 0, 255);
        emit histogramReady(&histogram); // Send to HistogramWindow
    }
}
/********************************************************************/
