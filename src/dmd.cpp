#include "dmd.h"
/***************************************************************************/
DMD::DMD(void) {
    _ready = false; // Assume DMD is unavailable until one is found
    _status = DMD_IDLE;
    tform.resize(3,3).fill(0);
}
/***************************************************************************/
bool DMD::statusChecker(void) {
    if(!_ready) {
        initialize();
        if(!_ready) {
            return false;
        }
    }
    return true;
}
/***************************************************************************/
void DMD::setTransform(CImg<float> t) {
    tform = t;
    emit transformUpdated();
}
/***************************************************************************/
bool DMD::setTransformFromFile(QString fname) {
    // Loads transformation matrix from file
    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    float sx, sy, rx, ry, tx, ty;
    QTextStream in(&file);
    in >> sx >> rx >> ry >> sy >> tx >> ty;

    tform(0,0) = sx;
    tform(1,0) = rx;
    tform(0,1) = ry;
    tform(1,1) = sy;
    tform(0,2) = tx;
    tform(1,2) = ty;
    tform(2,2) = 1;

    emit transformUpdated();
    emit postSpeckleMessage(QString("%1: sx=%2, rx=%3, ry=%4, sy=%5, tx=%6, ty=%7").arg(fname).
                            arg(sx).arg(rx).arg(ry).arg(sy).arg(tx).arg(ty));
    return true;
}
/***************************************************************************/
void DMD::setDefaultTransform(void) {
    // Set default transform with no scaling, rotation, or translation
    tform(0,0) = 1;  //sx
    tform(1,0) = 0;  //rx
    tform(0,1) = 0;  //ry
    tform(1,1) = 1;  //sy
    tform(0,2) = 0;  //tx
    tform(1,2) = 0;  //ty
    tform(2,2) = 1;
    emit transformUpdated();
}
/***************************************************************************/
void DMD::enableTransform(void) {
    use_transform = true;
    emit transformUpdated();
}
/***************************************************************************/
void DMD::disableTransform(void) {
    use_transform = false;
    emit transformUpdated();
}
/***************************************************************************/
CImg<int> DMD::getNextDMDCalibrationPoint(void) {
    int row = dmd_calibration.height() - 1;
    return CImg<int>::vector(dmd_calibration(0,row),dmd_calibration(1,row));
}
/***************************************************************************/
void DMD::addCCDCalibrationPoint(CImg<int> point) {
    ccd_calibration.append(point.transpose(),'y');
}
/***************************************************************************/
void DMD::addDMDCalibrationPoint(CImg<int> point) {
    dmd_calibration.append(point.transpose(),'y');
}
/***************************************************************************/
void DMD::clearCalibration(void) {
    ccd_calibration.clear();
    dmd_calibration.clear();
    enableTransform();
}
/***************************************************************************/
void DMD::initialize(void) {

    qDebug() << "Opening connection to LightCrafter 3000";
    if(LCR_CMD_Open()) {
        qDebug() << "Unable to connect to the LightCrafter 3000";
        _ready = false;
    } else {
        char verName[LCR_CMD_VERSION_STR_LEN];

        LCR_CMD_GetRevision(REV_DM365,&verName[0]);
        DM365_Rev = QString::fromUtf8(verName);
        qDebug() << "DM365 Revision: " << DM365_Rev;

        LCR_CMD_GetRevision(REV_FPGA,&verName[0]);
        FPGA_Rev = QString::fromUtf8(verName);
        qDebug() << "FPGA Revision: " << FPGA_Rev;

        LCR_CMD_GetRevision(REV_MSP430,&verName[0]);
        MSP430_Rev = QString::fromUtf8(verName);
        qDebug() << "MSP430 Revision: " << MSP430_Rev;

        _ready = true;
        dmd_width = 608;
        dmd_height = 684;
        use_transform = true;

        if(!setTransformFromFile(QString("tform.txt"))) {
            setDefaultTransform();
        }
    }
}
/***************************************************************************/
void DMD::show_dmd_info(void) {
    if(_ready) {
        emit postSpeckleMessage(QString("Using LightCrafter 3000, dmd_width=%1, dmd_height=%2").
                                arg(dmd_width).arg(dmd_height));
        emit postSpeckleMessage(QString("FPGA Rev: %1, DM365 Rev: %2, MSP430 Rev: %3").
                                arg(FPGA_Rev).arg(DM365_Rev).arg(MSP430_Rev));
    } else {
        initialize();
        if(!_ready)
            emit postSpeckleMessage(QString("DMD not connected"));
    }
}
/***************************************************************************/
void DMD::show_single_pattern(CImg<unsigned char> *p) {

    if(!statusChecker())
        return;

    QImage mask = transform_image_to_dmd(p,use_transform,tform,dmd_width,dmd_height);
    QString tmp_save_path = QDir::tempPath() + "/tmp_roi.bmp";
    mask.save(tmp_save_path);

    LCR_CMD_SetDisplayMode((LCR_DisplayMode_t)(0x00));
    LCR_CMD_DisplayStaticImage(tmp_save_path.toLatin1().constData());

    qDebug() << "Displaying single pattern";
    _status = DMD_DISPLAYING_SINGLE_PATTERN;
}
/***************************************************************************/
void DMD::prepare_pattern_sequence(QList<SpeckleROIClass *> ROI_list) {

    stop();
    if(!statusChecker())
        return;

    int Nimg = ROI_list.size();
    if(Nimg < 1)
        return;

    // Set pattern sequence settings
    LCR_CMD_SetDisplayMode((LCR_DisplayMode_t)(0x04)); // Set pattern sequence display mode
    patSeqSet.BitDepth = 1;
    patSeqSet.NumPatterns = Nimg;
    patSeqSet.InvertPatterns = 0;
    patSeqSet.InputTriggerType = 1;
    patSeqSet.InputTriggerDelay = 0;
    patSeqSet.AutoTriggerPeriod = exposure_time;
    patSeqSet.ExposureTime = 0;
    patSeqSet.LEDSelect = 0;
    LCR_CMD_SetPatternSeqSetting(&patSeqSet);

    // Set triggering settings
    camTrigSet.Enable = 1;
    camTrigSet.Source = 1;
    camTrigSet.Polarity = 0;
    camTrigSet.Delay = 0;
    camTrigSet.PulseWidth = 1000;
    LCR_CMD_SetCamTriggerSetting(&camTrigSet);

    // Upload patterns using worker in separate thread
    QThread* thread = new QThread;
    DMDworker* worker = new DMDworker(ROI_list,use_transform,tform,dmd_width,dmd_height);
    worker->moveToThread(thread);

    // Propagate signals back to main thread
    connect(worker, SIGNAL(maskUploaded(int)), this, SIGNAL(maskUploaded(int)));
    connect(worker, SIGNAL(finished()), this, SIGNAL(finished()));

    // Connect worker and thread together
    connect(thread, SIGNAL(started()), worker, SLOT(upload()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

}
/***************************************************************************/
void DMD::start(void) {
    qDebug() << "Starting pattern sequence";
    if(_ready)
        LCR_CMD_StartPatternSeq(1);
    _status = DMD_DISPLAYING_SEQUENCE;
}
/***************************************************************************/
void DMD::stop(void) {
    if(_ready) {
        if(_status == DMD_DISPLAYING_SEQUENCE)
            LCR_CMD_StartPatternSeq(0); //Stop pattern sequence
        LCR_CMD_SetDisplayMode((LCR_DisplayMode_t)(0x00));
        LCR_CMD_DisplayStaticColor(0);
        _status = DMD_IDLE;
        qDebug() << "Stopping DMD";
    }
}
/***************************************************************************/
void DMD::cleanup(void) {
    if(_ready) {
        stop();
        if(LCR_CMD_Close()) {
            qDebug() << "Unable to disconnect from LightCrafter 3000";
        } else {
            qDebug() << "Disconnected from LightCrafter 3000";
            _ready = false;
        }
    }
}
/***************************************************************************/
DMDworker::DMDworker(QList<SpeckleROIClass *> _ROI, bool _use_transform,
                     CImg<float> _tform, int _dmd_width, int _dmd_height) {
    ROI = _ROI;
    use_transform = _use_transform;
    tform = _tform;
    dmd_width = _dmd_width;
    dmd_height = _dmd_height;
}
/***************************************************************************/
void DMDworker::upload(void) {
    QImage mask;
    QString tmp_save_path = QDir::tempPath() + "/tmp_roi.bmp";
    for(int i = 0; i < ROI.size(); i++) {
        mask = transform_image_to_dmd(&ROI[i]->mask,use_transform,tform,dmd_width,dmd_height);
        mask.save(tmp_save_path);
        LCR_CMD_DefinePatternBMP(i,tmp_save_path.toLatin1().constData());
        emit maskUploaded(i);
    }
    emit finished();
}
/***************************************************************************/
QImage transform_image_to_dmd(CImg<unsigned char> *ccd_mask, bool use_transform,
                              CImg<float> tform, int dmd_width, int dmd_height) {

    CImg<unsigned char> dmd_mask(dmd_width,dmd_height,1,1,0);

    if(use_transform) {
        float sx, sy, rx, ry, tx, ty, i_ccd, j_ccd;

        int ccd_width = ccd_mask->width();
        int ccd_height = ccd_mask->height();

        sx = tform(0,0);
        rx = tform(1,0);
        ry = tform(0,1);
        sy = tform(1,1);
        tx = tform(0,2);
        ty = tform(1,2);

        for(int j_dmd = 0; j_dmd < dmd_height; j_dmd++) {
            for(int i_dmd = 0; i_dmd < dmd_width; i_dmd++) {
                i_ccd = sx*((float)(i_dmd)) + ry*((float)(j_dmd)) + tx;
                j_ccd = rx*((float)(i_dmd)) + sy*((float)(j_dmd)) + ty;
                if(i_ccd >= 0 && j_ccd >= 0 && i_ccd < ccd_width && j_ccd < ccd_height) {
                    if (ccd_mask->linear_atXY(i_ccd,j_ccd) != 0) {
                        dmd_mask(i_dmd,j_dmd) = 1;
                    }
                }
            }
        }

    } else {
        dmd_mask = ccd_mask->resize(dmd_width,dmd_height,1,1);
    }

    return convert_mask_to_1bit(&dmd_mask);

}
/***************************************************************************/
