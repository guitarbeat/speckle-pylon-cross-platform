#include "imagegenerator.h"
#include <QDebug>
#include <cstdlib>

/**************************************************************/
ImageGenerator::ImageGenerator(AcquisitionClass *acquisition)
{
    this->acquisition = acquisition;
}
/**************************************************************/
void ImageGenerator::initialize(int w, int h, unsigned char **buf,
                                QVector<float> *acq_t, int *Nacquired)
{
    width = w;
    height = h;
    buffers = buf;
    acq_times = acq_t;
    img_acquired = Nacquired;
    *img_acquired=0;
}

/**************************************************************/
void ImageGenerator::run()
{
    acquisition->startTimer();
    keep_going=true;
    while(keep_going)
    {
        createRandomImage();
        acq_times->append(acquisition->getTimeElapsed());

        (*img_acquired)++;
        acquisition->img_acquired = *img_acquired;
        acquisition->updateFPS();

        if(acquisition->isFinished())
            keep_going = false;
    }
}
/**************************************************************/
void ImageGenerator::createRandomImage()
{
    const unsigned char white[3]={ 255, 255, 255 };
    int buffer_idx = (*img_acquired)%((int)MAX_NUMBER_IMG_BUFFERS);

    CImg<unsigned char> tmp_img;
    tmp_img.resize(width, height);
    // Fill with uniform random noise
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            tmp_img(x,y) = static_cast<unsigned char>(std::rand() % 256);
        }
    }
    // Draw a simple circle by thresholding distance to center
    int cx = width / 2;
    int cy = height / 2;
    int radius = std::max(1, buffer_idx/10);
    int r2 = radius * radius;
    for (int y = std::max(0, cy - radius); y < std::min(height, cy + radius); ++y) {
        for (int x = std::max(0, cx - radius); x < std::min(width, cx + radius); ++x) {
            int dx = x - cx;
            int dy = y - cy;
            if (dx*dx + dy*dy <= r2) tmp_img(x,y) = 255;
        }
    }
    memcpy((void *)(buffers[buffer_idx]), tmp_img.data(), width*height);
}
/**************************************************************/
void ImageGenerator::stopAcquisition()
{
    keep_going=false;
}
/**************************************************************/
