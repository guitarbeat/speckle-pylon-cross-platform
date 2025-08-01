#include "imagegenerator.h"
#include <QDebug>

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
    tmp_img.rand(0,255);
    tmp_img.draw_circle(width/2, height/2, buffer_idx/10, white);
    memcpy((void *)(buffers[buffer_idx]), tmp_img.data(), width*height);
}
/**************************************************************/
void ImageGenerator::stopAcquisition()
{
    keep_going=false;
}
/**************************************************************/
