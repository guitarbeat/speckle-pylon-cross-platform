#ifndef DMDCLASS_H
#define DMDCLASS_H

#include <QObject>
#include <QDir>
#include "SpeckleROIClass.h"
#include "CImg.h"
using namespace cimg_library;

#include "common.h"

// LightCrafter
#include "error.h"
#include "lcr_cmd.h"

// DMD Pattern Limits
#define DMD_MAX_PATTERN 96

// DMD Status
#define DMD_IDLE 0
#define DMD_DISPLAYING_SINGLE_PATTERN 1
#define DMD_DISPLAYING_SEQUENCE 2

class DMD : public QObject {

signals:    
	void postSpeckleMessage(QString);
    void transformUpdated(void);
    void maskUploaded(int);
    void finished(void);

public:	
    DMD();
    int status() const {return _status;}
    bool statusChecker(void);
    bool ready() const {return _ready;}
    int width() const {return dmd_width;}
    int height() const {return dmd_height;}

    long getExposureTime() const {return exposure_time;}
    void setExposureTime(long t) {exposure_time = t;}

    float getTotalSequenceTime(void) const {return total_sequence_time;}
    void setTotalSequenceTime(float t) {total_sequence_time = t + 0.025;} // +25ms overhead

    CImg<float> getTransform(void) const {return tform;}
    void setTransform(CImg<float> t);
    bool setTransformFromFile(QString fname);
    void setDefaultTransform(void);
    bool getTransformStatus(void) const {return use_transform;}
    void enableTransform(void);
    void disableTransform(void);

    CImg<int> getCCDCalibration(void) const {return ccd_calibration;}
    CImg<int> getDMDCalibration(void) const {return dmd_calibration;}
    CImg<int> getNextDMDCalibrationPoint(void);
    void addCCDCalibrationPoint(CImg<int> point);
    void addDMDCalibrationPoint(CImg<int> point);
    void clearCalibration(void);

    void initialize(void);
    void show_dmd_info(void);
    void show_single_pattern(CImg<unsigned char> *p);
    void prepare_pattern_sequence(QList<SpeckleROIClass *> ROI_list);
    void start(void);
    void stop(void);
	void cleanup(void);

    CImg<int> getTileRegion(void) const {return tile_region;}
    void setTileRegion(CImg<int> t) {tile_region = t;}

private:
    Q_OBJECT
    bool _ready; // Flag indicating LightCrafter connectivity
    int _status; // Track LightCrafter operation mode
    bool use_transform; // Toggle use of DMD transform

    int dmd_width, dmd_height;
    long exposure_time;
    float total_sequence_time;

    QString transform_file;
    CImg<float> tform;
    CImg<int> ccd_calibration, dmd_calibration;

    CImg<int> tile_region; // Boundary coordinates for tile generation

    QString DM365_Rev;
    QString FPGA_Rev;
    QString MSP430_Rev;
    LCR_PatternSeqSetting_t patSeqSet;
    LCR_CamTriggerSetting_t camTrigSet;
};

class DMDworker : public QObject {
    Q_OBJECT

signals:
    void maskUploaded(int);
    void finished(void);

public slots:
    void upload(void);

public:
    DMDworker(QList<SpeckleROIClass *> _ROI, bool _use_transform,
              CImg<float> _tfrom, int _dmd_width, int _dmd_height);

private:

    QList<SpeckleROIClass *> ROI;
    bool use_transform;
    CImg<float> tform;
    int dmd_width, dmd_height;

};

QImage transform_image_to_dmd(CImg<unsigned char> *ccd_mask, bool use_transform,
                              CImg<float> tform, int dmd_width, int dmd_height);

#endif // DMDCLASS_H
