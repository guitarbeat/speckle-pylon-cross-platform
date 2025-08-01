#ifndef IMAGEGENERATOR_H
#define IMAGEGENERATOR_H

#include <QObject>
#include <QThread>
#include "speckle_defines.h"
#include "acquisitionclass.h"
#include "CImg.h"
using namespace cimg_library;

class ImageGenerator : public QThread {
    Q_OBJECT

public:
    ImageGenerator(AcquisitionClass *acquisition);
    void initialize(int w, int h, unsigned char **buf, QVector<float> *acq_t,
                    int *Nacquired);
    void stopAcquisition(void);

private:
    void createRandomImage(void);

protected:
    void run();

    AcquisitionClass *acquisition;
    bool keep_going;
    int width, height, color_planes;
    unsigned char **buffers;
    QVector<float> *acq_times;
    int *img_acquired;
};

#endif // IMAGEGENERATOR_H
