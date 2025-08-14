#include "scconfigdialog.h"
#include "ui_scconfigdialog.h"
#include "speckleform.h"

#include <Windows.h>
#include <dshow.h>

#pragma comment(lib, "strmiids")

extern SpeckleClass *speckle;

SCConfigDialog::SCConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SCConfigDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), this, SLOT(ExtractSettings()));
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(ExtractSettings()));
    connect(ui->Dark_level_spinBox, SIGNAL(valueChanged(int)), this, SLOT(SetDarkLevelThreshold(int)));
    connect(ui->num_sc_to_avg_spinBox, SIGNAL(valueChanged(int)), this, SLOT(SetNumSCToAvg(int)));
    connect(ui->blur_width_spinBox, SIGNAL(valueChanged(int)), this, SLOT(SetBlurWidth(int)));
    connect(ui->VideoFileFormat_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(SetVideoFileFormat(int)));
    connect(ui->moving_average_spinBox, SIGNAL(valueChanged(int)), this, SLOT(SetMovingAvgWidth(int)));

}
/*******************************************************************/
void SCConfigDialog::ExtractSettings(void)
{
    speckle->mask_dark_areas_threshold = ui->Dark_level_spinBox->value();
    speckle->mask_blur_width = ui->blur_width_spinBox->value();
    speckle->process_mode = ui->process_mode_comboBox->currentIndex();
    speckle->num_sc_to_avg = ui->num_sc_to_avg_spinBox->value();
    speckle->moving_avg_width = ui->moving_average_spinBox->value();
    emit(processModeChanged());
}

/*******************************************************************/
void SCConfigDialog::FillInCurrentValues(void)
{
    ui->Nthreads_spinBox->setValue(speckle->num_processing_threads);
    ui->Dark_level_spinBox->setValue(speckle->mask_dark_areas_threshold);
    ui->process_mode_comboBox->setCurrentIndex(speckle->process_mode);
    ui->num_sc_to_avg_spinBox->setValue(speckle->num_sc_to_avg);
    ui->blur_width_spinBox->setValue(speckle->mask_blur_width);
    ui->moving_average_spinBox->setValue(speckle->moving_avg_width);

    if(speckle->acquire_flag==FOCUS_MODE || speckle->acquire_flag==ACQUISITION_MODE)
    {
        ui->Nthreads_spinBox->setDisabled(true);
        ui->process_mode_comboBox->setDisabled(true);
    }
    else {
        ui->Nthreads_spinBox->setDisabled(false);
        ui->process_mode_comboBox->setDisabled(false);
    }

    ui->videoDevice_comboBox->clear();
    QStringList devices = getVideoDevices();
    if (!devices.empty()) {
        ui->videoDevice_comboBox->addItems(devices);
        ui->videoDevice_comboBox->setCurrentIndex(speckle->video_in_device_number);
    }
}

/*******************************************************************/
void SCConfigDialog::SetDarkLevelThreshold(int val)
{
    //qDebug() << "val = " << val;
    speckle->mask_dark_areas_threshold = val;

}
/*******************************************************************/
void SCConfigDialog::SetNumSCToAvg(int val)
{
    //qDebug() << "val = " << val;
    speckle->num_sc_to_avg = val;

}
/*******************************************************************/
void SCConfigDialog::SetMovingAvgWidth(int val)
{
    //qDebug() << "val = " << val;
    speckle->moving_avg_width = val;

}
/*******************************************************************/
void SCConfigDialog::on_videoDevice_comboBox_activated(int idx) {
    if (idx != -1) {
        speckle->video_in_device_number = idx;

#ifdef USE_FRAMEGRABBER
            if(speckle->theCamera.camera_type == CAMERA_FRAMEGRABBER)
                speckle->theCamera.frame_grabber.SetDeviceNumber(idx);
#endif
    }
}
/*******************************************************************/
void SCConfigDialog::SetBlurWidth(int val)
{
    speckle->mask_blur_width = val;
}
/*******************************************************************/
void SCConfigDialog::SetVideoFileFormat(int val)
{
    speckle->VideoFileFormat = val;
    qDebug() << "format= " << val << endl;
}
/****************************************************************************/
void SCConfigDialog::on_calculate_tform_pushButton_clicked(void)
{
    CImg<unsigned char> video_in_zoom, sc_zoom; // resized images with zoom factor taken into consideration

    //if()
    //video_in_zoom =

    speckle->overlays.ComputeTransform(speckle->video_in_ctrl_pts, speckle->sc_ctrl_pts , &(speckle->VideoTform));
    if(!(speckle->VideoTform.is_empty()))
        speckle->overlays.GeneratePixelMapping(speckle->captured_rgb, speckle->sc_imgf,
                                               speckle->VideoTform, &(speckle->VideoPixelMapping));

      //  speckle->overlays.GeneratePixelMapping(speckle->captured_rgb, speckle->sc_img_rgb,
      //                                         speckle->VideoTform, &(speckle->VideoPixelMapping));
}
/****************************************************************************/
void SCConfigDialog::on_saveVideoTform_pushButton_clicked(void)
{
    if(speckle->VideoTform.is_empty())
        return;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),NULL, tr("Text files (*.txt)"));
    if(fileName.isEmpty())
        return;

    float a00 = speckle->VideoTform(0,0);
    float a01 = speckle->VideoTform(1,0);
    float b00 = speckle->VideoTform(2,0);
    float a10 = speckle->VideoTform(0,1);
    float a11 = speckle->VideoTform(1,1);
    float b10 = speckle->VideoTform(2,1);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return;
    QTextStream out(&file);
    out.setRealNumberNotation(QTextStream::SmartNotation);
    out.setFieldWidth(16);
    out.setFieldAlignment(QTextStream::AlignLeft);
    out << a00 << a01 << b00 << a10 << a11 << b10;
    file.close();
}
/****************************************************************************/
void SCConfigDialog::on_loadVideoTform_pushButton_clicked(void)
{
    QString file = QFileDialog::getOpenFileName(
                         this,
                         "Select transform file",
                         NULL, tr("Text files (*.txt)"));
    if(file.isEmpty())
        return;
    if(speckle->overlays.setTransformFromFile(file))
        speckle->overlays.GeneratePixelMapping(speckle->captured_rgb, speckle->sc_imgf,
                                           speckle->VideoTform, &(speckle->VideoPixelMapping));

}
/*******************************************************************/
QStringList SCConfigDialog::getVideoDevices(void) {
    // Based on Microsoft documentation for "Selecting a Capture Device"
    // https://docs.microsoft.com/en-us/windows/win32/directshow/selecting-a-capture-device

    QStringList devices;
    IEnumMoniker *pEnum;
    ICreateDevEnum *pDevEnum;

    HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
        CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));

    if (SUCCEEDED(hr)) {
        // Create an enumerator for the category.
        hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
        if (hr == S_FALSE)
            return devices;
        pDevEnum->Release();
    }

    IMoniker *pMoniker = NULL;
    while (pEnum->Next(1, &pMoniker, NULL) == S_OK) {
        IPropertyBag *pPropBag;
        HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
        if (FAILED(hr)) {
            pMoniker->Release();
            continue;
        }

        VARIANT var;
        VariantInit(&var);

        // Get friendly name.
        hr = pPropBag->Read(L"FriendlyName", &var, 0);
        if (SUCCEEDED(hr)) {
            devices << QString::fromUtf16(reinterpret_cast<ushort*>(var.bstrVal));
            VariantClear(&var);
        }

        pPropBag->Release();
        pMoniker->Release();
    }
    return devices;
}
/*******************************************************************/
SCConfigDialog::~SCConfigDialog()
{
    delete ui;
}
