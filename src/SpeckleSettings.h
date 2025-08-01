#ifndef SPECKLESETTINGS_H
#define SPECKLESETTINGS_H

#include <QDialog>
#include <QAbstractButton>
#include <QGridLayout>
//#include <QCameraInfo>
#include <QTime>
#include <QListWidgetItem>
#include <QSettings>

namespace Ui {
class SpeckleSettings;
}

class SpeckleSettings : public QDialog
{
    Q_OBJECT

public:
    explicit SpeckleSettings(QWidget *parent = nullptr);
    ~SpeckleSettings();

    void FillInCurrentValues(void);    
    void RefreshROIList(void);
    void saveSettings(QSettings *settings);
    void loadSettings(QSettings *settings);
    void listAvailableCameras(void);
    int getCameraIdx(void);

signals:
    void processModeChanged(void);
    void displayLayoutChanged(QStringList *);
    void rawSettingsChanged(void);
    void scSettingsChanged(void);
    void overlaySettingsChanged(void);
    void cameraSettingsChanged(void);
    void rawDisplayRangeChanged(int Imin, int Imax);
    void scDisplayRangeChanged(float SCmin, float SCmax);
    void overlayToggled(bool show_overlay);
    void overlayChanged(float kmin, float kmax, bool use_alpha, float kmid);
    void roiAdded(void);
    void roiRemoved(int idx);
    void roiColorChanged(int idx, QColor color);
    void roiVisibilityToggled(int idx, bool is_visible);
    void showROICheckToggled(bool checked);
    void colorCameraExpChanged(float exp_time);
    void hotkeyStatusUpdate(void);
    void infoUpdate(int type, QString text);

public slots:
    void setWorkingDirectory(void);
    void on_outputfile_browse_button_clicked(void);
    void toggleAllROIVisibility(bool show);
    void setCameraAOIValues(void);
    void toggleOverlaySource(void);
    void changeSCmin(float);
    void changeSCmax(float);
    void changeExposure(float);

private slots:
    // Display Settings Tab
    void on_scmin_spin_valueChanged(double value);
    void on_scmin_spin_editingFinished(void);
    void on_scmax_spin_valueChanged(double value);
    void on_scmax_spin_editingFinished(void);
    void on_raw_min_spin_valueChanged(int value);
    void on_raw_min_spin_editingFinished(void);
    void on_raw_max_spin_valueChanged(int value);
    void on_raw_max_spin_editingFinished(void);
    void on_ratio_min_spin_valueChanged(double value);
    void on_ratio_max_spin_valueChanged(double value);
    void on_scColorbar_checkBox_toggled(bool checked);
    void on_rawColorbar_checkBox_toggled(bool checked);

    void on_raw_list_combo_currentIndexChanged(QString);
    void on_clear_raw_list_button_clicked(void);
    void on_baseline_list_combo_currentIndexChanged(QString);
    void on_clear_baseline_list_button_clicked(void);
    void on_sc_list_combo_currentIndexChanged(QString);
    void on_clear_image_list_button_clicked(void);
    void on_autoset_baseline_check_toggled(bool checked);
    void on_enable_ratio_image_checkbox_toggled(bool checked);
    void on_show_raw_check_toggled(bool checked);
    void on_show_SC_check_toggled(bool checked);
    //void on_bayer_hist_check_toggled(void);
    //void on_hist_without0_check_toggled(bool checked);
    void on_sc_colormap_combo_activated(int idx);
    void on_ratio_colormap_combo_activated(int idx);
    void on_raw_colormap_combo_activated(int idx);
    void on_SatPixelColor_comboBox_activated(int idx);
    void on_ROI_list_widget_itemChanged(QListWidgetItem *item);
    void on_add_ROI_button_clicked(void);
    void on_remove_ROI_button_clicked(void);
    void on_ROI_color_button_clicked(void);
    void on_ROI_show_check_toggled(bool checked);
    void on_roiPlotCheckbox_toggled(bool checked);
    void on_roiPlotSaveCheckbox_toggled(bool checked);
    void on_roiPlotHistoryCheckbox_toggled(bool checked);
    void on_roiPlotLimitSpin_editingFinished(void);
    void on_roiplot_autoscale_check_toggled(bool checked);
    void on_roiplot_ymin_spin_editingFinished(void);
    void on_roiplot_ymax_spin_editingFinished(void);
    void on_roiplot_rel_autoscale_check_toggled(bool checked);
    void on_roiplot_rel_ymax_spin_editingFinished(void);
    void on_roiplot_rel_ymin_spin_editingFinished(void);
    void on_roiPlotBaselineStart_editingFinished(void);
    void on_roiPlotBaselineEnd_editingFinished(void);
    void on_enable_overlay_checkBox_toggled(bool checked);
    void on_bg_src_comboBox_currentIndexChanged(QString text);
    void on_bg_cmap_comboBox_activated(int idx);
    void on_bg_min_spin_valueChanged(double value);
    void on_bg_min_spin_editingFinished(void);
    void on_bg_max_spin_valueChanged(double value);
    void on_bg_max_spin_editingFinished(void);
    void on_over_src_comboBox_currentIndexChanged(QString text);
    void on_over_cmap_comboBox_activated(int idx);
    void on_over_min_spin_valueChanged(double value);
    void on_over_min_spin_editingFinished(void);
    void on_over_max_spin_valueChanged(double value);
    void on_over_max_spin_editingFinished(void);
    void on_thresh_type_comboBox_activated(int idx);
    void on_over_blur_spin_valueChanged(int value);
    void on_alpha_enable_checkBox_toggled(bool checked);
    void on_over_Kmid_SpinBox_valueChanged(double value);
    void on_over_alpha_min_SpinBox_valueChanged(double value);
    void on_over_alpha_max_SpinBox_valueChanged(double value);
    void on_colorCameraExposure_SpinBox_valueChanged(double value);

    // Acquisition Settings Tab
    void on_compute_SC_check_toggled(bool checked);
    void on_save_raw_check_toggled(bool checked);
    void on_save_sc_check_toggled(bool checked);
    //void on_write_mode_combo_currentIndexChanged(int idx);
    void on_exposure_time_spin_valueChanged(double value);
    void on_trigger_combo_currentIndexChanged(int idx);
    void on_GainSpin_valueChanged(int value);
    //void on_bit_depth_combo_activated(int idx);
    void updateSpeckleCamera(int);
    void on_duration_TypeComboBox_currentIndexChanged(int idx);
    void on_acquireLength_lineEdit_editingFinished(void);

private:
    enum {RAW_IMG, SC_IMG, OVERLAY_IMG};
    Ui::SpeckleSettings *ui;
    void SetLimits(void);
    QStringList getVideoDevices(void);
    void hideDisabledFeatures(void);
    void setup_trigger_gui(void);
    void setupCameraComboboxLists(void);
    void readSettingsFile(QString fileName);

    int verified_duration = 100; // 100 frames
};

#endif // SPECKLESETTINGS_H
