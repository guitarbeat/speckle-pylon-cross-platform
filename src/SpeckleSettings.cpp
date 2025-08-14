#include <QComboBox>
#include "SpeckleSettings.h"
#include "ui_SpeckleSettings.h"

#include "speckle.h"
#include <cstdlib>
#include "speckle_processing.h"

extern SpeckleClass *speckle;

SpeckleSettings::SpeckleSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpeckleSettings)
{
    ui->setupUi(this);

    // Disable question mark in settings dialog window
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Initialize settings
    listAvailableCameras();
    hideDisabledFeatures();
    FillInCurrentValues();
    setup_trigger_gui();
    setupCameraComboboxLists();

    // Update currently selected QStackedWidget page when new item in sidebar is selected
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->listWidget, &QListWidget::currentRowChanged,
            ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    // Change cameras when new item in list is selected
    connect(ui->camerasAvailableComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SpeckleSettings::updateSpeckleCamera);
}
/*******************************************************************/
void SpeckleSettings::hideDisabledFeatures(void) {

#ifndef SPECKLE_USE_OPENCV
    ui->save_sc_videocheckBox->hide();
    ui->save_overlay_videocheckBox->hide();
    ui->save_input_videocheckBox->hide();

#endif

#ifndef USE_MESI
    ui->MESIBox->hide();
#endif

#ifndef USE_LIGHTCRAFTER
    ui->listWidget->takeItem(4);
    ui->stackedWidget->removeWidget(ui->DMD_page);
#endif

}
/*******************************************************************/
void SpeckleSettings::setup_trigger_gui(void)
{
    if(speckle->theCamera->camera_type == CAMERA_PYLON)
    {
        ui->trigger_combo->clear();
        ui->trigger_combo->addItem(tr("No Trigger"));
        ui->trigger_combo->addItem(tr("Frame Trigger"));
        ui->trigger_combo->addItem(tr("Exposure Width"));        
        ui->trigger_combo->setCurrentIndex(0);
    }
}
/*******************************************************************/
void SpeckleSettings::listAvailableCameras(void) {

    qDebug() << "listing cameras" ;

    const QSignalBlocker blocker(ui->camerasAvailableComboBox); // Temporarily prevent checkbox signal from firing
    const QSignalBlocker blocker2(ui->bg_src_comboBox); // Temporarily prevent checkbox signal from firing

    ui->camerasAvailableComboBox->clear();
    qDebug() <<  speckle->cameras_available.size() << " available";

    for(int i=0;i<speckle->cameras_available.size();i++)
        ui->camerasAvailableComboBox->addItem(speckle->cameras_available[i].description);
    qDebug() << "listing cameras 2";

    // populate list in background source of overlays
    if(speckle->cameras_available.size()>1)
    {
        for(int i=0; i<speckle->cameras_available.size()-1;i++)
            ui->bg_src_comboBox->addItem(speckle->cameras_available[i].description);
    }
    qDebug() << "listing cameras 3";

    updateSpeckleCamera(0);
}
/*******************************************************************/
int SpeckleSettings::getCameraIdx(void) {
    return ui->camerasAvailableComboBox->currentIndex();
}
/*******************************************************************/
void SpeckleSettings::updateSpeckleCamera(int idx) {

    // check camera type and update theCamera pointer
    speckle->setCamera(speckle->cameras_available[idx]);

    // make sure same camera is not selected as bg overlay source
    if(speckle->theCamera->isOpened() && ui->bg_src_comboBox->currentIndex()==(idx+5))
    {
        const QSignalBlocker blocker(ui->bg_src_comboBox);
        //qobject_cast< QStandardItemModel * >( ui->bg_src_comboBox->model() )->item( idx+5 )->setEnabled( false );
        // select different camera for background src in overlays
        if(idx == ui->bg_src_comboBox->count()-5) // last in list is currently selected
            ui->bg_src_comboBox->setCurrentIndex(ui->bg_src_comboBox->currentIndex()-1); // select previous index
        else
            ui->bg_src_comboBox->setCurrentIndex(ui->bg_src_comboBox->currentIndex()+1);

    }

    // if camera was not opened, set to simulated camera
    if(!speckle->theCamera->isOpened())
    {
        int Ncameras = speckle->cameras_available.size();
        speckle->setCamera(speckle->cameras_available[Ncameras-1]); // sets to simulated camera
        const QSignalBlocker blocker(ui->camerasAvailableComboBox);
        ui->camerasAvailableComboBox->setCurrentIndex(Ncameras-1); // update combo to simulated camera
        // disable camera listing that couldn't be opened
        qobject_cast< QStandardItemModel * >( ui->camerasAvailableComboBox->model() )->item( idx )->setEnabled( false );
    }

    SetLimits();

    // Toggle fields based on camera functionality
    bool enabled;
    enabled = speckle->theCamera->camera_type == CAMERA_PYLON ||
              speckle->theCamera->camera_type == CAMERA_FRAMEGRABBER ||
              speckle->theCamera->camera_type == CAMERA_NONE;
    ui->GainSpin->setEnabled(!enabled);
    ui->GainSpinLabel->setEnabled(!enabled);

    enabled = speckle->theCamera->camera_type == CAMERA_FRAMEGRABBER ||
              speckle->theCamera->camera_type == CAMERA_NONE;
    ui->exposure_time_spin->setEnabled(!enabled);
    ui->exposure_time_spin_label->setEnabled(!enabled);
    ui->trigger_combo->setEnabled(!enabled);
}
/*******************************************************************/
void SpeckleSettings::setupCameraComboboxLists(void) {

    qDebug() << "enabling all background overlay sources. Be careful";
    return;

    // temporarily disable overlay background sources that cause crashes
    const QSignalBlocker blocker(ui->bg_src_comboBox);
    for(int i=1; i<5; i++)
        qobject_cast< QStandardItemModel * >( ui->bg_src_comboBox->model() )->item(i)->setEnabled( false );
    // completely disable overlays for now unless 2 cameras are available
    if(ui->bg_src_comboBox->count()<6)
    {
        //ui->enable_overlay_checkBox->setEnabled(false);
        qDebug() << "not disabling overlays";
    }

    // select last camera in list as default
    ui->bg_src_comboBox->setCurrentIndex(ui->bg_src_comboBox->count()-1);
}
/*******************************************************************/
void SpeckleSettings::SetLimits()
{
    // set default limits based on camera
    ui->width_spin->setMaximum(speckle->theCamera->max_width);
    ui->width_spin->setValue(speckle->theCamera->im_w);
    ui->width_spin->setToolTip(QString("camera AOI width (max=%1)").arg(speckle->theCamera->max_width));
    ui->height_spin->setMaximum(speckle->theCamera->max_height);
    ui->height_spin->setValue(speckle->theCamera->im_h);
    ui->height_spin->setToolTip(QString("camera AOI height (max=%1)").arg(speckle->theCamera->max_height));
    ui->GainSpin->setMaximum(100);
    ui->GainSpin->setValue(0);

    ui->raw_min_spin->setMaximum((1 << speckle->theCamera->bit_depth) - 1);
    ui->raw_max_spin->setMaximum((1 << speckle->theCamera->bit_depth) - 1);
    ui->raw_max_spin->setValue((1 << speckle->theCamera->bit_depth) - 1);

    ui->SatPixelColor_comboBox->setCurrentIndex(0);
}
/*******************************************************************/
void SpeckleSettings::FillInCurrentValues()
{
    // pull all gui settings into speckle
    //speckle->Nframes = ui->frames_seq_spin->value();
    //speckle->Nreps = ui->Nseq_spin->value();
    speckle->theCamera->top = ui->top_spin->value();
    speckle->theCamera->left = ui->left_spin->value();
    speckle->theCamera->im_w = ui->width_spin->value();
    speckle->theCamera->im_h = ui->height_spin->value();
    speckle->Set_sc_width_height();
    speckle->theCamera->exp_time = ui->exposure_time_spin->value();
    speckle->filename = ui->outputfile_edit->text();

    speckle->acquisition->setStopCondition(ui->duration_TypeComboBox->currentIndex());
    speckle->acquisition->setDuration(verified_duration);

    speckle->save_raw = ui->save_raw_check->isChecked();
    speckle->save_SC = ui->save_sc_check->isChecked();
    speckle->save_sc_video = ui->save_sc_videocheckBox->isChecked();
    speckle->save_overlay_video = ui->save_overlay_videocheckBox->isChecked();
    speckle->save_input_video = ui->save_input_videocheckBox->isChecked();

    // processing settings
    speckle->compute_SC = ui->compute_SC_check->isChecked();
    speckle->NxN = ui->NxN_spin->value();
    speckle->num_processing_threads = ui->Nthreads_spinBox->value();
    speckle->mask_dark_areas_threshold = ui->Dark_level_spinBox->value();
    speckle->moving_avg_width = ui->moving_average_spinBox->value();
    speckle->num_sc_to_avg = ui->num_sc_to_avg_spinBox->value();
    speckle->mask_blur_width = ui->blur_width_spinBox->value();
    speckle->process_mode = ui->process_mode_comboBox->currentIndex();

    // display settings
    speckle->SC_min = ui->scmin_spin->value();
    speckle->SC_max = ui->scmax_spin->value();
    speckle->Imin = ui->raw_min_spin->value();
    speckle->Imax = ui->raw_max_spin->value();
    speckle->setRawColormap(ui->raw_colormap_combo->currentText());
    speckle->setSCColormap(ui->sc_colormap_combo->currentText());
    speckle->show_raw = ui->show_raw_check->isChecked();
    speckle->show_SC = ui->show_SC_check->isChecked();
    speckle->ratio_min = ui->ratio_min_spin->value();
    speckle->ratio_max = ui->ratio_max_spin->value();
    speckle->autoset_baseline = ui->autoset_baseline_check->isChecked();
    speckle->show_sc_colorbar = ui->scColorbar_checkBox->isChecked();
    speckle->show_raw_colorbar = ui->rawColorbar_checkBox->isChecked();

    // speckle->show_rTC = ????

    // overlay settings
    speckle->show_overlay = ui->enable_overlay_checkBox->isChecked();
    // the next few lines should be cleaned up
    speckle->overlays.setBackgroundSource(ui->bg_src_comboBox->currentIndex());
    if(ui->bg_src_comboBox->currentIndex()>4)
    {
        speckle->overlays.setBackgroundSource(SRC_VIDEO);
        int idx = ui->bg_src_comboBox->currentIndex();
        speckle->overlays.setBackgroundVideoSource(speckle->cameras_available[idx-5]);
    }
    speckle->overlays.setOverlayColormap(ui->over_cmap_comboBox->currentText());
    speckle->overlays.setBackgroundMin(ui->bg_min_spin->value());
    speckle->overlays.setBackgroundMax(ui->bg_max_spin->value());
    speckle->overlays.setOverlaySource(ui->over_src_comboBox->currentIndex());
    speckle->overlays.setOverlayMin(ui->over_min_spin->value());
    speckle->overlays.setOverlayMax(ui->over_max_spin->value());
    speckle->overlays.setOverlayColormap(ui->over_cmap_comboBox->currentText());
    speckle->overlays.setThresholdType(ui->thresh_type_comboBox->currentIndex());
    speckle->overlays.setBlur(ui->over_blur_spin->value());

    // roi plot
    speckle->roi_min = ui->roiplot_ymin_spin->value();
    speckle->roi_max = ui->roiplot_ymax_spin->value();
    speckle->roi_rel_min = ui->roiplot_rel_ymin_spin->value();
    speckle->roi_rel_max = ui->roiplot_rel_ymax_spin->value();
    speckle->roi_plot_limit = ui->roiPlotLimitSpin->value();
    speckle->roi_plot_baseline_start = ui->roiPlotBaselineStart->value();
    speckle->roi_plot_baseline_end = ui->roiPlotBaselineEnd->value();

}
/***************************************************************************/
void SpeckleSettings::on_enable_overlay_checkBox_toggled(bool checked) {
    int bg_src, over_src;
    bool enable_bg_controls, enable_over_controls, enable_alpha_controls;

    speckle->show_overlay = checked;

    bg_src = speckle->overlays.bg_src;
    enable_bg_controls = checked && bg_src != SRC_VIDEO && bg_src != SRC_NONE;
    ui->overlaySourceLabel->setEnabled(checked);
    ui->overlayColormapLabel->setEnabled(checked);
    ui->overlayMinLabel->setEnabled(checked);
    ui->overlayMaxLabel->setEnabled(checked);
    ui->overlayBackgroundLabel->setEnabled(checked);
    ui->bg_src_comboBox->setEnabled(checked);
    ui->bg_cmap_comboBox->setEnabled(enable_bg_controls);
    ui->bg_min_spin->setEnabled(enable_bg_controls);
    ui->bg_max_spin->setEnabled(enable_bg_controls);

    over_src = speckle->overlays.over_src;
    enable_over_controls = checked && over_src != SRC_VIDEO && over_src != SRC_NONE;
    ui->overlayOverlayLabel->setEnabled(checked);
    ui->over_src_comboBox->setEnabled(checked);
    ui->over_cmap_comboBox->setEnabled(enable_over_controls);
    ui->over_min_spin->setEnabled(enable_over_controls);
    ui->over_max_spin->setEnabled(enable_over_controls);

    ui->overlayThreshLabel->setEnabled(enable_over_controls);
    ui->thresh_type_comboBox->setEnabled(enable_over_controls);
    ui->overlayBlurLabel->setEnabled(enable_over_controls);
    ui->over_blur_spin->setEnabled(enable_over_controls);

    ui->alpha_enable_checkBox->setEnabled(enable_over_controls);
    enable_alpha_controls = enable_over_controls && ui->alpha_enable_checkBox->isChecked();
    ui->overlayAlphaThresholdLabel->setEnabled(enable_alpha_controls);
    ui->over_Kmid_SpinBox->setEnabled(enable_alpha_controls);
    ui->overlayAlphaRangeLabel->setEnabled(enable_alpha_controls);
    ui->over_alpha_max_SpinBox->setEnabled(enable_alpha_controls);
    ui->over_alpha_min_SpinBox->setEnabled(enable_alpha_controls);

    ui->colorCameraExposureLabel->setEnabled(checked);
    ui->colorCameraExposure_SpinBox->setEnabled(checked);

    FillInCurrentValues(); // this is needed in case enable is checked before an acquisition is started
  //  emit overlaySettingsChanged();
    emit overlayToggled(speckle->show_overlay);
}
/***************************************************************************/
void SpeckleSettings::on_alpha_enable_checkBox_toggled(bool checked) {
    speckle->overlays.setUseAlpha(checked);
    ui->overlayAlphaThresholdLabel->setEnabled(checked);
    ui->over_Kmid_SpinBox->setEnabled(checked);
    ui->overlayAlphaRangeLabel->setEnabled(checked);
    ui->over_alpha_max_SpinBox->setEnabled(checked);
    ui->over_alpha_min_SpinBox->setEnabled(checked);
    emit overlaySettingsChanged();
    emit overlayChanged(speckle->overlays.GetOverMin(), speckle->overlays.GetOverMax(),
                        speckle->overlays.useAlpha(), speckle->overlays.GetKmid());

}
/***************************************************************************/
void SpeckleSettings::on_exposure_time_spin_valueChanged(double value) {
//  speckle->theCamera->exp_time = value;
  speckle->theCamera->SetCameraExposureTime(value);

  emit cameraSettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_outputfile_browse_button_clicked(void) {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Set Output File"));

    if(fileName.isEmpty()) {
        qDebug() << "No file selected";
    } else {
        qDebug() << "Output file set to" << fileName;
        ui->outputfile_edit->setText(fileName);
    }
}
/****************************************************************************/
void SpeckleSettings::on_trigger_combo_currentIndexChanged(int idx) {

    // Changing trigger mode while camera is active is unstable
    speckle->acquire_flag = IDLE_MODE;

    switch(idx) {
        case 0:
            ui->exposure_time_spin->setEnabled(true);
            ui->exposure_time_spin_label->setEnabled(true);
            break;
        case 1:
            ui->exposure_time_spin->setEnabled(true);
            ui->exposure_time_spin_label->setEnabled(true);
            break;
        case 3:
            ui->exposure_time_spin->setEnabled(false);
            ui->exposure_time_spin_label->setEnabled(false);
            break;
    }

    speckle->theCamera->SetCameraTrigger(ui->trigger_combo->currentText());
}
/***************************************************************************/
void SpeckleSettings::on_GainSpin_valueChanged(int value) {
    speckle->theCamera->SetCameraGain();
}
/***************************************************************************/
void SpeckleSettings::on_save_raw_check_toggled(bool checked) {
    speckle->save_raw = checked;
}
/***************************************************************************/
void SpeckleSettings::on_compute_SC_check_toggled(bool checked) {
    speckle->compute_SC = checked;

    ui->save_sc_check->setEnabled(checked);
    if(ui->save_sc_check->isChecked())
        ui->save_sc_check->setChecked(false);

    ui->process_mode_comboBox->setEnabled(checked);
    ui->process_mode_label->setEnabled(checked);
    ui->Nthreads_spinBox->setEnabled(checked);
    ui->Nthreads_label->setEnabled(checked);
    ui->NxN_spin->setEnabled(checked);
    ui->NxN_label->setEnabled(checked);
    ui->num_sc_to_avg_spinBox->setEnabled(checked);
    ui->num_sc_to_avg_label->setEnabled(checked);
    ui->moving_average_spinBox->setEnabled(checked);
    ui->moving_average_label->setEnabled(checked);
    ui->DarkLevelMaskGroup->setEnabled(checked);
}
/****************************************************************************/
void SpeckleSettings::on_duration_TypeComboBox_currentIndexChanged(int idx)
{
    ui->acquireLength_lineEdit->clear();
    switch(idx)
    {
        case 0: // STOP_NUMBER
            ui->acquireLength_lineEdit->setEnabled(true);
            ui->acquireLength_lineEdit->setText("100");
            ui->acquireLength_lineEdit->setToolTip(tr("Number of frames to acquire"));
            verified_duration = 100; // 100 frames
            break;
        case 1: // STOP_TIME
            ui->acquireLength_lineEdit->setEnabled(true);
            ui->acquireLength_lineEdit->setText("10:00");
            ui->acquireLength_lineEdit->setToolTip(tr("Duration in m:s, m:s.z, s, or s.z"));
            verified_duration = 600000; // 10:00
            break;
        case 2: // ACQUIRE_FOREVER
            ui->acquireLength_lineEdit->setEnabled(false);
            ui->acquireLength_lineEdit->setToolTip("");
            break;
    }
}
/****************************************************************************/
void SpeckleSettings::on_acquireLength_lineEdit_editingFinished(void)
{
    QString text = ui->acquireLength_lineEdit->text();

    // Validate input based on currently selected duration type
    int idx = ui->duration_TypeComboBox->currentIndex();
    if (idx == AcquisitionClass::STOP_NUMBER)
    {
        if (text.toUInt()) // Must be positive integer
            verified_duration = text.toInt();
        else
        {
            QMessageBox::warning(this, tr("Invalid Acquisition Length"),
                                 tr("Please enter a valid number of frames to acquire."),
                                 QMessageBox::Ok);
            ui->acquireLength_lineEdit->setText("100");
            verified_duration = 100; // 100 frames
        }
    }
    else if (idx == AcquisitionClass::STOP_TIME)
    {
        QTime t = QTime();
        if (text.contains(":") && text.contains(".")) // m:s.z format - DOESN'T WORK FOR m>=60
            t = QTime::fromString(text, "m:s.z");
        else if (text.contains(":") && !text.contains(".")) // m:s format - DOESN'T WORK FOR m>=60
            t = QTime::fromString(text, "m:s");
        else if (!text.contains(":") && text.toFloat() > 0) // s or s.z format
        {
            t = QTime(0, 0);
            t = t.addMSecs(static_cast<int>(text.toFloat() * 1000));
        }

        if (t.isValid() && t != QTime(0, 0))
        {
            QTime t0 = QTime(0, 0);
            verified_duration = t0.msecsTo(t);
        }
        else
        {
            QMessageBox::warning(this, tr("Invalid Acquisition Duration"),
                                 tr("Please enter a valid time duration for the acquisition.<br/>"
                                    "Valid formats include m:s, m:s.z, s, and s.z"),
                                 QMessageBox::Ok);
            ui->acquireLength_lineEdit->setText("10:00");
            verified_duration = 600000; // 10:00
        }
    }
}
/****************************************************************************/
void SpeckleSettings::on_ROI_list_widget_itemChanged(QListWidgetItem *item)
{
    int row = ui->ROI_list_widget->row(item);
    speckle->ROI_list[row]->show = item->checkState();
    emit roiVisibilityToggled(row, item->checkState());
}
/****************************************************************************/
void SpeckleSettings::toggleAllROIVisibility(bool show)
{
    const QSignalBlocker blocker(ui->ROI_show_check); // Temporarily prevent checkbox signal from firing
    ui->ROI_show_check->setChecked(show);
    ui->ROI_list_widget->setCurrentRow(show ? (ui->ROI_list_widget->count() - 1) : -1);
    ui->ROI_list_widget->setEnabled(show);
    ui->add_ROI_button->setEnabled(show);
    ui->remove_ROI_button->setEnabled(show);
    ui->ROI_color_button->setEnabled(show);

    for(int i = 0; i < speckle->ROI_list.size(); i++)
        emit roiVisibilityToggled(i, show && speckle->ROI_list[i]->show);
}
/****************************************************************************/
void SpeckleSettings::toggleOverlaySource()
{
    // switch overlay source from SC to None or vice versa
    if(ui->over_src_comboBox->currentText()==QString("None"))
        ui->over_src_comboBox->setCurrentText("SC");
    else
        ui->over_src_comboBox->setCurrentText("None");
}
/****************************************************************************/
void SpeckleSettings::changeSCmin(float dK)
{
    // increment SC min by dK for both SC display and overlay
    ui->scmin_spin->setValue(ui->scmin_spin->value()+dK);
    ui->over_min_spin->setValue(ui->over_min_spin->value()+dK);
    emit hotkeyStatusUpdate();
    emit infoUpdate(SC_IMG, QString("K=[%1,%2]").arg(speckle->SC_min).arg(speckle->SC_max));
    emit infoUpdate(OVERLAY_IMG, QString("K=[%1,%2]").arg(speckle->overlays.GetOverMin()).arg(speckle->overlays.GetOverMax()));
}
/****************************************************************************/
void SpeckleSettings::changeSCmax(float dK)
{
    // increment SC max by dK for both SC display and overlay
    ui->scmax_spin->setValue(ui->scmax_spin->value()+dK);
    ui->over_max_spin->setValue(ui->over_max_spin->value()+dK);
    emit hotkeyStatusUpdate();
    emit infoUpdate(SC_IMG, QString("K=[%1,%2]").arg(speckle->SC_min).arg(speckle->SC_max));
    emit infoUpdate(OVERLAY_IMG, QString("K=[%1,%2]").arg(speckle->overlays.GetOverMin()).arg(speckle->overlays.GetOverMax()));
}
/****************************************************************************/
void SpeckleSettings::changeExposure(float dT)
{
    // increment camera exposure time by dT
    ui->exposure_time_spin->setValue(ui->exposure_time_spin->value()+dT);
    emit hotkeyStatusUpdate();
    emit infoUpdate(RAW_IMG, QString("T=%1ms").arg(speckle->theCamera->exp_time));
}
/****************************************************************************/
void SpeckleSettings::RefreshROIList(void) {
    QListWidgetItem *p;
    QString roi_name;

    // Temporarily prevent QListWidget item change signal from firing
    const QSignalBlocker blocker(ui->ROI_list_widget);

    int N = speckle->ROI_list.count();
    ui->dmdROICounter->setValue(N);
    ui->ROI_list_widget->clear();
    if(N < 1)
        return;

    for(int i=0;i<N;i++) {
        roi_name = QString("ROI %1").arg(i);
        ui->ROI_list_widget->insertItem(i, roi_name);
        p = ui->ROI_list_widget->item(i);
        p->setBackground(QBrush(speckle->ROI_list[i]->ROI_color));
        p->setCheckState(speckle->ROI_list[i]->show ? Qt::Checked : Qt::Unchecked);
        p->setToolTip("Check/Uncheck to toggle visibility of " + roi_name);
        ui->ROI_show_check->setChecked(speckle->ROI_list[i]->show);
    }

    // The last ROI in the list will be selected by default.
    ui->ROI_list_widget->setCurrentRow(ui->ROI_list_widget->count() - 1);

    if(speckle->acquire_flag != ACQUISITION_MODE) {
        speckle->sc_ready_for_display=1;
        speckle->update_live=1;
        speckle->update_roi_plot=true;
    }
}
/****************************************************************************/
void SpeckleSettings::on_add_ROI_button_clicked(void) {
    emit roiAdded();
}
/****************************************************************************/
void SpeckleSettings::on_ROI_color_button_clicked(void)
{
    int row = ui->ROI_list_widget->currentRow();
    if(row<0)
        return;

    QColor color = QColorDialog::getColor(speckle->ROI_list[row]->ROI_color, this);
    if (color.isValid()) {
        speckle->ROI_list[row]->set_color(color);
        RefreshROIList();
        emit roiColorChanged(row, color);
    }
}
/****************************************************************************/
void SpeckleSettings::on_remove_ROI_button_clicked(void)
{
    int row = ui->ROI_list_widget->currentRow();
    if(row<0)
        return;

    // No acq_times vector on ROI; clear SC data vectors instead
    speckle->ROI_list[row]->ROI_data.clear();
    speckle->ROI_list[row]->ROI_rel_data.clear();
//	speckle->ROI_list[row]->raw_mean.clear();
//	speckle->ROI_list[row]->tc_mean.clear();
//  speckle->ROI_list[row]->curve->detach();
    delete speckle->ROI_list.takeAt(row);

    RefreshROIList();
    emit roiRemoved(row);
}
/****************************************************************************/
void SpeckleSettings::on_ROI_show_check_toggled(bool checked) {
    toggleAllROIVisibility(checked);
    emit showROICheckToggled(checked);
}
/****************************************************************************/
void SpeckleSettings::on_roiPlotCheckbox_toggled(bool checked) {
    speckle->enable_ROI_plot = checked;
    ui->roiPlotSaveCheckbox->setEnabled(checked);
    ui->roiPlotHistoryCheckbox->setEnabled(checked);
    ui->roiPlotBaselineLabel->setEnabled(checked);
    ui->roiPlotBaselineStart->setEnabled(checked);
    ui->roiPlotBaselineEnd->setEnabled(checked);
    ui->roiPlotAutoLabel->setEnabled(checked);
    ui->roiPlotMinLabel->setEnabled(checked);
    ui->roiPlotMaxLabel->setEnabled(checked);
    ui->roiPlotSCLabel->setEnabled(checked);
    ui->roiPlotRelativeLabel->setEnabled(checked);
    ui->roiplot_autoscale_check->setEnabled(checked);
    ui->roiplot_rel_autoscale_check->setEnabled(checked);

    if(!speckle->show_full_ROI_plot) {
        ui->roiPlotLimitSpin->setEnabled(checked);
        ui->roiPlotLimitLabel->setEnabled(checked);
    }

    if(!speckle->autoscale_roi_plot) {
        ui->roiplot_ymin_spin->setEnabled(checked);
        ui->roiplot_ymax_spin->setEnabled(checked);
    }

    if(!speckle->autoscale_roi_rel_plot) {
        ui->roiplot_rel_ymin_spin->setEnabled(checked);
        ui->roiplot_rel_ymax_spin->setEnabled(checked);
    }
}
/****************************************************************************/
void SpeckleSettings::on_roiPlotSaveCheckbox_toggled(bool checked) {
    speckle->enable_ROI_plot_save = checked;
}
/****************************************************************************/
void SpeckleSettings::on_roiPlotHistoryCheckbox_toggled(bool checked) {
    speckle->show_full_ROI_plot = checked;
    ui->roiPlotLimitSpin->setEnabled(!checked);
    ui->roiPlotLimitLabel->setEnabled(!checked);
}
/****************************************************************************/
void SpeckleSettings::on_roiPlotLimitSpin_editingFinished(void) {
    speckle->roi_plot_limit = ui->roiPlotLimitSpin->value();
}
/****************************************************************************/
void SpeckleSettings::on_roiplot_autoscale_check_toggled(bool checked) {
    speckle->autoscale_roi_plot = checked;
    ui->roiplot_ymin_spin->setEnabled(!checked);
    ui->roiplot_ymax_spin->setEnabled(!checked);
}
/****************************************************************************/
void SpeckleSettings::on_roiplot_rel_autoscale_check_toggled(bool checked) {
    speckle->autoscale_roi_rel_plot = checked;
    ui->roiplot_rel_ymin_spin->setEnabled(!checked);
    ui->roiplot_rel_ymax_spin->setEnabled(!checked);
}
/****************************************************************************/
void SpeckleSettings::on_roiplot_ymin_spin_editingFinished(void) {
    if(ui->roiplot_ymin_spin->value() >= ui->roiplot_ymax_spin->value())
        ui->roiplot_ymax_spin->setValue(ui->roiplot_ymin_spin->value() + 0.001);
    speckle->roi_min = ui->roiplot_ymin_spin->value();
}
/****************************************************************************/
void SpeckleSettings::on_roiplot_ymax_spin_editingFinished(void) {
    if(ui->roiplot_ymax_spin->value() <= ui->roiplot_ymin_spin->value())
        ui->roiplot_ymin_spin->setValue(ui->roiplot_ymax_spin->value() - 0.001);
    speckle->roi_max = ui->roiplot_ymax_spin->value();
}
/****************************************************************************/
void SpeckleSettings::on_roiplot_rel_ymin_spin_editingFinished(void) {
    if(ui->roiplot_rel_ymin_spin->value() >= ui->roiplot_rel_ymax_spin->value())
        ui->roiplot_rel_ymax_spin->setValue(ui->roiplot_rel_ymin_spin->value() + 0.001);
    speckle->roi_rel_min = ui->roiplot_rel_ymin_spin->value();
}
/****************************************************************************/
void SpeckleSettings::on_roiplot_rel_ymax_spin_editingFinished(void) {
    if(ui->roiplot_rel_ymax_spin->value() <= ui->roiplot_rel_ymin_spin->value())
        ui->roiplot_rel_ymin_spin->setValue(ui->roiplot_rel_ymax_spin->value() - 0.001);
    speckle->roi_rel_max = ui->roiplot_rel_ymax_spin->value();
}
/****************************************************************************/
void SpeckleSettings::on_roiPlotBaselineStart_editingFinished(void) {
    int value = ui->roiPlotBaselineStart->value();
    if (value != speckle->roi_plot_baseline_start) {
        speckle->roi_plot_baseline_start = value;
        if (value >= ui->roiPlotBaselineEnd->value()) {
            ui->roiPlotBaselineEnd->setValue(value + 1);
            speckle->roi_plot_baseline_end = ui->roiPlotBaselineEnd->value();
        }
        speckle->roi_plot_baseline = true;
    }
}
/****************************************************************************/
void SpeckleSettings::on_roiPlotBaselineEnd_editingFinished(void) {
    int value = ui->roiPlotBaselineEnd->value();
    if (value != speckle->roi_plot_baseline_end) {
        speckle->roi_plot_baseline_end = value;
        if (value <= ui->roiPlotBaselineStart->value()) {
            ui->roiPlotBaselineStart->setValue(value - 1);
            speckle->roi_plot_baseline_start = ui->roiPlotBaselineStart->value();
        }
        speckle->roi_plot_baseline = true;
    }
}
/***************************************************************************/
void SpeckleSettings::on_autoset_baseline_check_toggled(bool checked) {
    speckle->autoset_baseline = checked;
}
/***************************************************************************/
void SpeckleSettings::on_scmin_spin_valueChanged(double value) {
    speckle->SC_min = value;
    emit scSettingsChanged();
    emit scDisplayRangeChanged(speckle->SC_min, speckle->SC_max);
}
/***************************************************************************/
void SpeckleSettings::on_scmin_spin_editingFinished(void) {
    ui->scmax_spin->setMinimum(speckle->SC_min);
}
/***************************************************************************/
void SpeckleSettings::on_scmax_spin_valueChanged(double value) {
    speckle->SC_max = value;
    emit scSettingsChanged();
    emit scDisplayRangeChanged(speckle->SC_min, speckle->SC_max);
}
/***************************************************************************/
void SpeckleSettings::on_scmax_spin_editingFinished(void) {
    ui->scmin_spin->setMaximum(speckle->SC_max);
}
/***************************************************************************/
void SpeckleSettings::on_raw_min_spin_valueChanged(int value) {
    speckle->Imin = value;
    emit rawSettingsChanged();
    emit rawDisplayRangeChanged(speckle->Imin, speckle->Imax);
}
/***************************************************************************/
void SpeckleSettings::on_raw_min_spin_editingFinished(void) {
    ui->raw_max_spin->setMinimum(speckle->Imin);
}
/***************************************************************************/
void SpeckleSettings::on_raw_max_spin_valueChanged(int value) {
    speckle->Imax = value;
    emit rawSettingsChanged();
    emit rawDisplayRangeChanged(speckle->Imin, speckle->Imax);
}
/***************************************************************************/
void SpeckleSettings::on_raw_max_spin_editingFinished(void) {
    ui->raw_min_spin->setMaximum(speckle->Imax);
}
/***************************************************************************/
void SpeckleSettings::on_ratio_min_spin_valueChanged(double value) {
    speckle->ratio_min = value;
    if(speckle->acquire_flag == IDLE_MODE)
        speckle->rTC_ready_for_display = true;
}
/***************************************************************************/
void SpeckleSettings::on_ratio_max_spin_valueChanged(double value) {
    speckle->ratio_max = value;
    if(speckle->acquire_flag == IDLE_MODE)
        speckle->rTC_ready_for_display = true;
}
/***************************************************************************/
void SpeckleSettings::on_bg_min_spin_valueChanged(double value) {
    speckle->overlays.setBackgroundMin(value);
    emit overlaySettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_bg_min_spin_editingFinished(void) {
    ui->bg_max_spin->setMinimum(ui->bg_min_spin->value());
}
/***************************************************************************/
void SpeckleSettings::on_bg_max_spin_valueChanged(double value) {
    speckle->overlays.setBackgroundMax(value);
    emit overlaySettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_bg_max_spin_editingFinished(void) {
    ui->bg_min_spin->setMaximum(ui->bg_max_spin->value());
}
/***************************************************************************/
void SpeckleSettings::on_over_min_spin_valueChanged(double value) {
    speckle->overlays.setOverlayMin(value);
    emit overlaySettingsChanged();
    emit overlayChanged(speckle->overlays.GetOverMin(), speckle->overlays.GetOverMax(),
                        speckle->overlays.useAlpha(), speckle->overlays.GetKmid());
}
/***************************************************************************/
void SpeckleSettings::on_over_min_spin_editingFinished(void) {
    ui->over_max_spin->setMinimum(ui->over_min_spin->value());
    ui->over_Kmid_SpinBox->setRange(ui->over_min_spin->value(),  ui->over_max_spin->value());
    emit overlaySettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_over_max_spin_valueChanged(double value) {
    speckle->overlays.setOverlayMax(value);
    emit overlaySettingsChanged();
    emit overlayChanged(speckle->overlays.GetOverMin(), speckle->overlays.GetOverMax(),
                        speckle->overlays.useAlpha(), speckle->overlays.GetKmid());
}
/***************************************************************************/
void SpeckleSettings::on_over_max_spin_editingFinished(void) {
    ui->over_min_spin->setMaximum(ui->over_max_spin->value());
    ui->over_Kmid_SpinBox->setRange(ui->over_min_spin->value(),  ui->over_max_spin->value());
    emit overlaySettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_over_blur_spin_valueChanged(int value) {
    speckle->overlays.setBlur(value);
    emit overlaySettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_over_Kmid_SpinBox_valueChanged(double value) {
    speckle->overlays.setKmid(value);
    emit overlaySettingsChanged();
    emit overlayChanged(speckle->overlays.GetOverMin(), speckle->overlays.GetOverMax(),
                        speckle->overlays.useAlpha(), speckle->overlays.GetKmid());
}
/***************************************************************************/
void SpeckleSettings::on_over_alpha_min_SpinBox_valueChanged(double value) {
    speckle->overlays.setAlphaMin(value);
    emit overlaySettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_over_alpha_max_SpinBox_valueChanged(double value) {
    speckle->overlays.setAlphaMax(value);
    emit overlaySettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_colorCameraExposure_SpinBox_valueChanged(double value) {
    emit colorCameraExpChanged((float)(value));
}
/***************************************************************************/
void SpeckleSettings::on_raw_colormap_combo_activated(int idx) {
    switch(idx) {
    case 0:
        speckle->live_palette = speckle->gray_palette;
        break;
    case 1:
        speckle->live_palette = speckle->jet_palette;
        break;
    case 2:
        speckle->live_palette = speckle->reverse_jet_palette;
        break;
    case 3:
        speckle->live_palette = speckle->hot_palette;
        break;
    case 4:
        speckle->live_palette = speckle->cool_palette;
        break;
    case 5:
        speckle->live_palette = speckle->autumn_palette;
        break;
    case 6:
        speckle->live_palette = speckle->pmkmp_palette;
        break;
    case 7:
        speckle->live_palette = speckle->greens_palette;
        break;
    }


    emit rawSettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_sc_colormap_combo_activated(int idx) {
    // need to clean this up and use string matching
    switch(idx) {
    case 0:
        speckle->sc_palette = speckle->gray_palette;
        break;
    case 1:
        speckle->sc_palette = speckle->jet_palette;
        break;
    case 2:
        speckle->sc_palette = speckle->reverse_jet_palette;
        break;
    case 3:
        speckle->sc_palette = speckle->hot_palette;
        break;
    case 4:
        speckle->sc_palette = speckle->cool_palette;
        break;
    case 5:
        speckle->sc_palette = speckle->autumn_palette;
        break;
    case 6:
        speckle->sc_palette = speckle->pmkmp_palette;
        break;
    case 7:
        speckle->sc_palette = speckle->greens_palette;
        break;
    case 8:
        speckle->sc_palette = speckle->reverse_gray_palette;
        break;
    }

    emit scSettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_ratio_colormap_combo_activated(int idx) {
    switch(idx) {
        case 0:
            speckle->tc_palette = speckle->gray_palette;
            break;
        case 1:
            speckle->tc_palette = speckle->jet_palette;
            break;
        case 2:
            speckle->tc_palette = speckle->hot_palette;
            break;
        case 3:
            speckle->tc_palette = speckle->cool_palette;
            break;
        case 4:
            speckle->tc_palette = speckle->autumn_palette;
            break;
    }
    if(speckle->acquire_flag == IDLE_MODE)
        speckle->overlay_ready_for_display = true;
}
/***************************************************************************/
void SpeckleSettings::on_scColorbar_checkBox_toggled(bool checked)
{
    speckle->show_sc_colorbar=checked;
    emit scSettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_rawColorbar_checkBox_toggled(bool checked)
{
    speckle->show_raw_colorbar=checked;
    emit rawSettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_bg_cmap_comboBox_activated(int idx) {
    switch(idx) {
    case 0:
        speckle->overlays.bg_cmap = speckle->gray_palette;
        break;
    case 1:
        speckle->overlays.bg_cmap = speckle->jet_palette;
        break;
    case 2:
        speckle->overlays.bg_cmap = speckle->reverse_jet_palette;
        break;
    case 3:
        speckle->overlays.bg_cmap = speckle->hot_palette;
        break;
    case 4:
        speckle->overlays.bg_cmap = speckle->cool_palette;
        break;
    case 5:
        speckle->overlays.bg_cmap = speckle->autumn_palette;
        break;
    case 6:
        speckle->overlays.bg_cmap = speckle->pmkmp_palette;
        break;
    case 7:
        speckle->overlays.bg_cmap = speckle->greens_palette;
        break;
    case 8:
        speckle->overlays.bg_cmap = speckle->reverse_gray_palette;
        break;
    }
    emit overlaySettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_SatPixelColor_comboBox_activated(int idx) {
    switch(idx) {
        case 0: // Red
            speckle->red_chan = 255;
            speckle->green_chan = 0;
            speckle->blue_chan = 0;
            break;
        case 1: // Green
            speckle->red_chan = 0;
            speckle->green_chan = 255;
            speckle->blue_chan = 0;
            break;
        case 2: // Blue
            speckle->red_chan = 0;
            speckle->green_chan = 0;
            speckle->blue_chan = 255;
            break;
        case 3: // Yellow
            speckle->red_chan = 255;
            speckle->green_chan = 255;
            speckle->blue_chan = 0;
            break;
    }

    if(&(speckle->live_palette) == &(speckle->gray_sat_palette)) {
        speckle->gray_sat_palette.resize(256,1,1,3);
        speckle->gray_sat_palette = speckle->gray_palette;
        speckle->gray_sat_palette(255,0) = speckle->red_chan;
        speckle->gray_sat_palette(255,1) = speckle->green_chan;
        speckle->gray_sat_palette(255,2) = speckle->blue_chan;
        speckle->live_palette = speckle->gray_sat_palette;
    }
}
/***************************************************************************/
void SpeckleSettings::on_thresh_type_comboBox_activated(int idx) {
    switch(idx) {
        case 0:
            ui->over_min_spin->setEnabled(true);
            ui->over_max_spin->setEnabled(true);
            break;
        case 1:
            ui->over_min_spin->setEnabled(true);
            ui->over_max_spin->setEnabled(false);
            break;
        case 2:
            ui->over_min_spin->setEnabled(false);
            ui->over_max_spin->setEnabled(true);
            break;
    }

    speckle->overlays.setThresholdType(idx);
    emit overlaySettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_bg_src_comboBox_currentIndexChanged(QString text) {
    int src;

    if (text == QString("Raw")) {
        src = SRC_RAW;
        ui->bg_min_spin->setRange(0, ui->raw_max_spin->value());
        ui->bg_min_spin->setDecimals(0);
        ui->bg_min_spin->setSingleStep(1);
        ui->bg_min_spin->setValue(ui->raw_min_spin->value());
        ui->bg_max_spin->setRange(ui->raw_min_spin->value(), 255);
        ui->bg_max_spin->setDecimals(0);
        ui->bg_max_spin->setSingleStep(1);
        ui->bg_max_spin->setValue(ui->raw_max_spin->value());
    } else if (text == QString("SC")) {
        src = SRC_SC;
        ui->bg_min_spin->setRange(0, ui->scmax_spin->value());
        ui->bg_min_spin->setDecimals(3);
        ui->bg_min_spin->setSingleStep(0.01);
        ui->bg_min_spin->setValue(ui->scmin_spin->value());
        ui->bg_max_spin->setRange(ui->scmin_spin->value(), 1);
        ui->bg_max_spin->setDecimals(3);
        ui->bg_max_spin->setSingleStep(0.01);
        ui->bg_max_spin->setValue(ui->scmax_spin->value());
    } else if (text == QString("TC")) {
        src = SRC_TC;
        ui->bg_min_spin->setRange(0, 1);
        ui->bg_min_spin->setDecimals(2);
        ui->bg_min_spin->setSingleStep(0.1);
        ui->bg_min_spin->setValue(0);
        ui->bg_max_spin->setRange(1, 10);
        ui->bg_max_spin->setDecimals(2);
        ui->bg_max_spin->setSingleStep(0.1);
        ui->bg_max_spin->setValue(1);
    } else if (text == QString("Video In") || ui->bg_src_comboBox->currentIndex()>4) {
        src = SRC_VIDEO;
        int idx = ui->bg_src_comboBox->currentIndex();
        speckle->overlays.setBackgroundVideoSource(speckle->cameras_available[idx-5]);
    } else {
        src = SRC_NONE;
        ui->bg_cmap_comboBox->setCurrentText(QString("Gray"));
        ui->bg_min_spin->setValue(0);
        ui->bg_max_spin->setValue(0);
    }

    speckle->overlays.setBackgroundSource(src);

    bool enable_controls = src != SRC_VIDEO && src != SRC_NONE;
    ui->bg_cmap_comboBox->setEnabled(enable_controls);
    ui->bg_min_spin->setEnabled(enable_controls);
    ui->bg_max_spin->setEnabled(enable_controls);

    emit overlaySettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_over_src_comboBox_currentIndexChanged(QString text) {

    int src;

    if (text == QString("Raw")) {
        src = SRC_RAW;
        ui->over_min_spin->setRange(0, ui->raw_max_spin->value());
        ui->over_min_spin->setDecimals(0);
        ui->over_min_spin->setSingleStep(1);
        ui->over_min_spin->setValue(ui->raw_min_spin->value());
        ui->over_max_spin->setRange(ui->raw_min_spin->value(), 255);
        ui->over_max_spin->setDecimals(0);
        ui->over_max_spin->setSingleStep(1);
        ui->over_max_spin->setValue(ui->raw_max_spin->value());
    } else if (text == QString("SC")) {
        src = SRC_SC;
        ui->over_min_spin->setRange(0, ui->scmax_spin->value());
        ui->over_min_spin->setDecimals(3);
        ui->over_min_spin->setSingleStep(0.01);
        //ui->over_min_spin->setValue(ui->scmin_spin->value());
        ui->over_max_spin->setRange(ui->scmin_spin->value(), 1);
        ui->over_max_spin->setDecimals(3);
        ui->over_max_spin->setSingleStep(0.01);
        //ui->over_max_spin->setValue(ui->scmax_spin->value());
    } else if (text == QString("TC")) {
        src = SRC_TC;
        ui->over_min_spin->setRange(0, 1);
        ui->over_min_spin->setDecimals(2);
        ui->over_min_spin->setSingleStep(0.1);
        ui->over_min_spin->setValue(0);
        ui->over_max_spin->setRange(1, 10);
        ui->over_max_spin->setDecimals(2);
        ui->over_max_spin->setSingleStep(0.1);
        ui->over_max_spin->setValue(1);
    } else if (text == QString("Video In")) {
        src = SRC_VIDEO;
    } else {
        src = SRC_NONE;
        //ui->over_cmap_comboBox->setCurrentText(QString("Gray"));
        //ui->over_min_spin->setValue(0);
        //ui->over_max_spin->setValue(0);
    }

    speckle->overlays.setOverlaySource(src);

    bool enable_controls = src != SRC_VIDEO && src != SRC_NONE;
    ui->over_cmap_comboBox->setEnabled(enable_controls);
    ui->over_min_spin->setEnabled(enable_controls);
    ui->over_max_spin->setEnabled(enable_controls);
    ui->thresh_type_comboBox->setEnabled(enable_controls);
    ui->overlayThreshLabel->setEnabled(enable_controls);
    ui->over_blur_spin->setEnabled(enable_controls);
    ui->overlayBlurLabel->setEnabled(enable_controls);

    ui->alpha_enable_checkBox->setEnabled(enable_controls);
    enable_controls = enable_controls && ui->alpha_enable_checkBox->isChecked();
    ui->overlayAlphaThresholdLabel->setEnabled(enable_controls);
    ui->over_Kmid_SpinBox->setEnabled(enable_controls);
    ui->overlayAlphaRangeLabel->setEnabled(enable_controls);
    ui->over_alpha_max_SpinBox->setEnabled(enable_controls);
    ui->over_alpha_min_SpinBox->setEnabled(enable_controls);

    emit overlaySettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_over_cmap_comboBox_activated(int idx) {
    switch(idx) {
    case 0:
        speckle->overlays.over_cmap = speckle->gray_palette;
        break;
    case 1:
        speckle->overlays.over_cmap = speckle->jet_palette;
        break;
    case 2:
        speckle->overlays.over_cmap = speckle->reverse_jet_palette;
        break;
    case 3:
        speckle->overlays.over_cmap = speckle->hot_palette;
        break;
    case 4:
        speckle->overlays.over_cmap = speckle->cool_palette;
        break;
    case 5:
        speckle->overlays.over_cmap = speckle->autumn_palette;
        break;
    case 6:
        speckle->overlays.over_cmap = speckle->pmkmp_palette;
        break;
    case 7:
        speckle->overlays.over_cmap = speckle->greens_palette;
        break;
    case 8:
        speckle->overlays.over_cmap = speckle->neon_palette;
        break;
    case 9:
        speckle->overlays.over_cmap = speckle->reverse_gray_palette;
        break;
    }
    emit overlaySettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_enable_ratio_image_checkbox_toggled(bool checked) {
    speckle->show_rTC = checked;
    ui->ratio_min_spin->setEnabled(checked);
    ui->ratio_max_spin->setEnabled(checked);
    ui->ratio_colormap_combo->setEnabled(checked);
    ui->ratioMinLabel->setEnabled(checked);
    ui->ratioMaxLabel->setEnabled(checked);
    ui->ratioColormapLabel->setEnabled(checked);
}
/***************************************************************************/
void SpeckleSettings::on_show_raw_check_toggled(bool checked) {
    speckle->show_raw = checked;
    emit rawSettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_show_SC_check_toggled(bool checked) {
    speckle->show_SC = checked;
    emit scSettingsChanged();
}
/***************************************************************************/
void SpeckleSettings::on_save_sc_check_toggled(bool checked) {
    speckle->save_SC = checked;

    ui->baselineListLabel->setEnabled(checked);
    ui->baseline_list_combo->setEnabled(checked);
    ui->clear_baseline_list_button->setEnabled(checked);
    ui->scListLabel->setEnabled(checked);
    ui->sc_list_combo->setEnabled(checked);
    ui->clear_image_list_button->setEnabled(checked);
}
/****************************************************************************/
void SpeckleSettings::on_sc_list_combo_currentIndexChanged(QString fname) {
    QFile file(fname);
    int retval=0;

    if(speckle->acquire_flag == ACQUISITION_MODE)
        return;

    if(file.exists())
        retval = ReadSCFile(fname, speckle->SC);
    if(retval == 1) {
        memcpy((void *)(speckle->sc_imgf.data()), (void *)(speckle->SC), speckle->sc_w*speckle->sc_h*sizeof(float));
        emit scSettingsChanged();
    } else
        return;

#ifdef USE_FLSCI
    if(speckle->rct_calc == NULL) {
        flsci_rct_end(&(speckle->rct_calc));
        speckle->rct_calc=flsci_rct_init(speckle->rct_table, TC_TABLE_SIZE, speckle->theCamera->im_w, speckle->theCamera->im_h, 2);
    }

    if(speckle->show_rTC || speckle->show_overlay) {
        flsci_rct_process(speckle->rct_calc, speckle->SC, speckle->rTC_base, speckle->rTC);
        speckle->rTC_ready_for_display = true;
    }
#endif

}
/****************************************************************************/
void SpeckleSettings::on_raw_list_combo_currentIndexChanged(QString fname)
{
        QFile file(fname);
        int retval,ii;
        unsigned short Nframes = 0, exp_time = 0;

        if(speckle->acquire_flag == ACQUISITION_MODE)
                return;

        if(file.exists())
        {
            // Read header and data; functions return 1 on success
            if(!read_raw_image_file_header(fname, (unsigned short *)&(speckle->theCamera->im_w), (unsigned short *)&(speckle->theCamera->im_h),
                                          &Nframes, &exp_time)) {
                qDebug() << "reading header failed";
                return;
            }
            if(!read_raw_image_file(fname, &(speckle->raw_list), (unsigned short *)&(speckle->theCamera->im_w), (unsigned short *)&(speckle->theCamera->im_h),
                                    &Nframes, &exp_time)) {
                qDebug() << "reading failed";
                return;
            }
            // set up pointers
            for(ii=0;ii<Nframes;ii++)
                speckle->raw_images[ii]= speckle->raw_list[ii].data();
        }

        emit rawSettingsChanged();
}
/****************************************************************************/
void SpeckleSettings::on_baseline_list_combo_currentIndexChanged(QString fname) {
    QFile file(fname);
    float *sc_tmp;
    int retval=0;

    #ifdef _WIN32
    sc_tmp = (float *)_aligned_malloc(MAX_IMG_SIZE*MAX_IMG_SIZE*sizeof(float), 16); // force 16-byte aligned
    #else
    sc_tmp = (float *)aligned_alloc(16, MAX_IMG_SIZE*MAX_IMG_SIZE*sizeof(float));
    #endif

    if(file.exists())
        retval = ReadSCFile(fname, sc_tmp);
    if(retval != 1)
        return;

#ifdef USE_FLSCI
    if(speckle->rct_calc == NULL) {
        flsci_rct_end(&(speckle->rct_calc));
        speckle->rct_calc = flsci_rct_init(speckle->rct_table, TC_TABLE_SIZE, speckle->theCamera->im_w, speckle->theCamera->im_h, 2);
    }

    set_baseline(sc_tmp, speckle->rTC_base, speckle->rct_table);
    if(speckle->show_rTC || speckle->show_overlay) {
        flsci_rct_process(speckle->rct_calc, speckle->SC, speckle->rTC_base, speckle->rTC);
        speckle->rTC_ready_for_display = true;
    }
#endif

    #ifdef _WIN32
    _aligned_free(sc_tmp);
    #else
    free(sc_tmp);
    #endif
}
/****************************************************************************/
void SpeckleSettings::on_clear_raw_list_button_clicked(void)
{
    ui->raw_list_combo->clear();
}
/****************************************************************************/
void SpeckleSettings::on_clear_image_list_button_clicked(void)
{
    ui->sc_list_combo->clear();
}
/****************************************************************************/
void SpeckleSettings::on_clear_baseline_list_button_clicked(void)
{
    ui->baseline_list_combo->clear();
}
/*******************************************************************/
void SpeckleSettings::setWorkingDirectory(void)
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Working Directory"),
                    nullptr, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty())
    {
        if(QDir::setCurrent(dir))
            qDebug() << "Working directory set to" << dir;
        else
            qDebug() << "Failed to set the working directory to" << dir;
    }
}
/*******************************************************************/
void SpeckleSettings::setCameraAOIValues(void)
{
    ui->top_spin->setValue(speckle->theCamera->top);
    ui->left_spin->setValue(speckle->theCamera->left);
    ui->width_spin->setValue(speckle->theCamera->im_w);
    ui->height_spin->setValue(speckle->theCamera->im_h);
}
/*******************************************************************/
void SpeckleSettings::saveSettings(QSettings *settings)
{
    // Acquisition
    settings->setValue("working_dir", QDir::currentPath());
    settings->setValue("current camera", ui->camerasAvailableComboBox->currentIndex());
    settings->setValue("acquisition duration type", ui->duration_TypeComboBox->currentIndex());
    settings->setValue("acquire length edit", ui->acquireLength_lineEdit->text());
    settings->setValue("output file", ui->outputfile_edit->text());
    settings->setValue("save raw", ui->save_raw_check->isChecked());
    settings->setValue("save sc", ui->save_sc_check->isChecked());
    settings->setValue("save sc video", ui->save_sc_videocheckBox->isChecked());
    settings->setValue("save overlay video", ui->save_overlay_videocheckBox->isChecked());
    settings->setValue("save input video", ui->save_input_videocheckBox->isChecked());
    settings->setValue("exposure time", ui->exposure_time_spin->value());
    settings->setValue("left", ui->left_spin->value());
    settings->setValue("top", ui->top_spin->value());
    settings->setValue("width", ui->width_spin->value());
    settings->setValue("height", ui->height_spin->value());
    settings->setValue("gain", ui->GainSpin->value());
    settings->setValue("MESI enable", ui->mesi_EnableCheckbox->isChecked());
    settings->setValue("MESI exposure list", ui->mesi_ExposureInput->text());
    settings->setValue("MESI display exposure", ui->mesi_DisplayExposureCombo->currentIndex());

    // Processing
    settings->setValue("NxN", ui->NxN_spin->value());
    settings->setValue("Nthreads", ui->Nthreads_spinBox->value() );
    settings->setValue("Dark level threshold", ui->Dark_level_spinBox->value());
    settings->setValue("Dark blur width", ui->blur_width_spinBox->value());
    settings->setValue("Processing mode", ui->process_mode_comboBox->currentIndex());
    settings->setValue("Frames to average", ui->num_sc_to_avg_spinBox->value());
    settings->setValue("Moving average", ui->moving_average_spinBox->value());

    // Display
    settings->setValue("Show SC", ui->show_SC_check->isChecked());
    settings->setValue("Show raw", ui->show_raw_check->isChecked());
    settings->setValue("SC min", ui->scmin_spin->value());
    settings->setValue("SC max", ui->scmax_spin->value());
    settings->setValue("raw min", ui->raw_min_spin->value());
    settings->setValue("raw max", ui->raw_max_spin->value());
    settings->setValue("sc colormap", ui->sc_colormap_combo->currentIndex());
    settings->setValue("raw colormap", ui->raw_colormap_combo->currentIndex());
    settings->setValue("show sc colorbar", ui->scColorbar_checkBox->isChecked());
    settings->setValue("show raw colorbar", ui->rawColorbar_checkBox->isChecked());
    settings->setValue("sat pixel color", ui->SatPixelColor_comboBox->currentIndex());
    settings->setValue("enable overlay", ui->enable_overlay_checkBox->isChecked());
    settings->setValue("bg src", ui->bg_src_comboBox->currentIndex());
    settings->setValue("bg cmap", ui->bg_cmap_comboBox->currentIndex());
    settings->setValue("bg min", ui->bg_min_spin->value());
    settings->setValue("bg max", ui->bg_max_spin->value());
    settings->setValue("over src", ui->over_src_comboBox->currentIndex() );
    settings->setValue("over cmap", ui->over_cmap_comboBox->currentIndex() );
    settings->setValue("over min", ui->over_min_spin->value());
    settings->setValue("over max", ui->over_max_spin->value());
    settings->setValue("over mode", ui->thresh_type_comboBox->currentIndex());
    settings->setValue("over blur width", ui->over_blur_spin->value());
    settings->setValue("over alpha enable", ui->alpha_enable_checkBox->isChecked());
    settings->setValue("over kmid", ui->over_Kmid_SpinBox->value());
    settings->setValue("color camera exposure", ui->colorCameraExposure_SpinBox->value());
    settings->setValue("over alpha min", ui->over_alpha_min_SpinBox->value());
    settings->setValue("over alpha max", ui->over_alpha_max_SpinBox->value());
}
/*******************************************************************/
void SpeckleSettings::loadSettings(QSettings *settings)
{
    // Acquisition
    QDir::setCurrent(settings->value("working_dir").toString());
    ui->camerasAvailableComboBox->setCurrentIndex(settings->value("current camera",0).toInt());
    ui->duration_TypeComboBox->setCurrentIndex(settings->value("acquisition duration type",0).toInt());
    ui->acquireLength_lineEdit->setText(settings->value("acquire length edit","100").toString());
    ui->outputfile_edit->setText(settings->value("output file","test").toString());
    ui->save_raw_check->setChecked(settings->value("save raw",true).toBool());
    ui->save_sc_check->setChecked(settings->value("save sc",true).toBool());
    ui->save_sc_videocheckBox->setChecked(settings->value("save sc video",false).toBool());
    ui->save_overlay_videocheckBox->setChecked(settings->value("save overlay video",false).toBool());
    ui->save_input_videocheckBox->setChecked(settings->value("save input video",false).toBool());
    ui->exposure_time_spin->setValue(settings->value("exposure time",5).toDouble());
    ui->left_spin->setValue(settings->value("left",0).toInt());
    ui->top_spin->setValue(settings->value("top",0).toInt());
    ui->width_spin->setValue(settings->value("width",1024).toInt());
    ui->height_spin->setValue(settings->value("height",768).toInt());
    ui->GainSpin->setValue(settings->value("gain",0).toInt());
    ui->mesi_EnableCheckbox->setChecked(settings->value("MESI enable",false).toBool());
    ui->mesi_ExposureInput->setText(settings->value("MESI exposure list","1 2 3").toString());
    ui->mesi_DisplayExposureCombo->setCurrentIndex(settings->value("MESI display exposure",0).toInt());

    // Processing
    ui->NxN_spin->setValue(settings->value("NxN",5).toInt());
    ui->Nthreads_spinBox->setValue(settings->value("Nthreads",8).toInt());
    ui->Dark_level_spinBox->setValue(settings->value("Dark level threshold",0).toInt());
    ui->blur_width_spinBox->setValue(settings->value("Dark blur width",5).toInt());
    ui->process_mode_comboBox->setCurrentIndex(settings->value("Processing mode",0).toInt());
    ui->num_sc_to_avg_spinBox->setValue(settings->value("Frames to average",5).toInt());
    ui->moving_average_spinBox->setValue(settings->value("Moving average",1).toInt());

    // Display
    ui->show_SC_check->setChecked(settings->value("Show SC", true).toBool());
    ui->show_raw_check->setChecked(settings->value("Show raw", true).toBool());
    ui->scmin_spin->setValue(settings->value("SC min", 0).toDouble());
    ui->scmax_spin->setValue(settings->value("SC max", 1.0).toDouble());
    ui->raw_min_spin->setValue(settings->value("raw min", 0).toInt());
    ui->raw_max_spin->setValue(settings->value("raw max", 255).toInt());
    ui->sc_colormap_combo->setCurrentIndex(settings->value("sc colormap", 0).toInt());
    ui->raw_colormap_combo->setCurrentIndex(settings->value("raw colormap", 0).toInt());
    ui->scColorbar_checkBox->setChecked(settings->value("show sc colorbar", false).toBool());
    ui->rawColorbar_checkBox->setChecked(settings->value("show raw colorbar", false).toBool());
    ui->SatPixelColor_comboBox->setCurrentIndex(settings->value("sat pixel color",0).toInt());
    ui->enable_overlay_checkBox->setChecked(settings->value("enable overlay",false).toBool());
    ui->bg_src_comboBox->setCurrentIndex(settings->value("bg src",0).toInt());
    ui->bg_cmap_comboBox->setCurrentIndex(settings->value("bg cmap",0).toInt());
    ui->bg_min_spin->setValue(settings->value("bg min",0).toInt());
    ui->bg_max_spin->setValue(settings->value("bg max",255).toInt());
    ui->over_src_comboBox->setCurrentIndex(settings->value("over src",0).toInt());
    ui->over_cmap_comboBox->setCurrentIndex(settings->value("over cmap",0).toInt());
    ui->over_min_spin->setValue(settings->value("over min",0).toDouble());
    ui->over_max_spin->setValue(settings->value("over max",0.2).toDouble());
    ui->thresh_type_comboBox->setCurrentIndex(settings->value("over mode",0).toInt());
    ui->over_blur_spin->setValue(settings->value("over blur width",5).toInt());
    ui->alpha_enable_checkBox->setChecked(settings->value("over alpha enable",false).toBool());
    ui->over_Kmid_SpinBox->setValue(settings->value("over kmid",0.5).toDouble());
    ui->colorCameraExposure_SpinBox->setValue(settings->value("color camera exposure",50).toDouble());
    ui->over_alpha_min_SpinBox->setValue(settings->value("over alpha min",0).toDouble());
    ui->over_alpha_max_SpinBox->setValue(settings->value("over alpha max",1).toDouble());
}
/***************************************************************************/
SpeckleSettings::~SpeckleSettings()
{
    delete ui;
}
