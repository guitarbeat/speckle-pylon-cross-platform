/********************************************************************************
** Form generated from reading UI file 'SpeckleSettings.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPECKLESETTINGS_H
#define UI_SPECKLESETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpeckleSettings
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QWidget *Acquisition_page;
    QWidget *gridLayoutWidget_5;
    QGridLayout *AcquisitionSettingsBox;
    QComboBox *camerasAvailableComboBox;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *duration_TypeComboBox;
    QLineEdit *acquireLength_lineEdit;
    QLabel *frames_seq_spin_label;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *outputfile_edit;
    QToolButton *outputfile_browse_button;
    QLabel *label_13;
    QGroupBox *MESIBox;
    QCheckBox *mesi_EnableCheckbox;
    QPushButton *mesi_CalibrationButton;
    QLabel *mesi_ExposureTextboxLabel;
    QComboBox *mesi_DisplayExposureCombo;
    QLabel *mesi_DisplayExposureComboxLabel;
    QPushButton *mesi_StartButton;
    QLineEdit *mesi_ExposureInput;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *SaveSettingsBox;
    QCheckBox *save_sc_check;
    QCheckBox *save_raw_check;
    QSpacerItem *verticalSpacer;
    QCheckBox *save_sc_videocheckBox;
    QCheckBox *save_overlay_videocheckBox;
    QCheckBox *save_input_videocheckBox;
    QGroupBox *CameraSettingsBox;
    QWidget *layoutWidget_3;
    QGridLayout *CameraSettingsGrid;
    QLabel *trigger_combo_label;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_6;
    QSpinBox *left_spin;
    QSpinBox *top_spin;
    QLabel *GainSpinLabel;
    QDoubleSpinBox *exposure_time_spin;
    QLabel *exposure_time_spin_label;
    QSpinBox *GainSpin;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_7;
    QSpinBox *width_spin;
    QSpinBox *height_spin;
    QComboBox *trigger_combo;
    QWidget *Processing_page;
    QGroupBox *DarkLevelMaskGroup;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *Dark_level_label;
    QSpinBox *Dark_level_spinBox;
    QLabel *blur_width_label;
    QSpinBox *blur_width_spinBox;
    QGroupBox *SpeckleContrasGroup;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSpinBox *num_sc_to_avg_spinBox;
    QLabel *Nthreads_label;
    QCheckBox *compute_SC_check;
    QSpinBox *moving_average_spinBox;
    QLabel *process_mode_label;
    QSpinBox *NxN_spin;
    QLabel *NxN_label;
    QLabel *moving_average_label;
    QSpinBox *Nthreads_spinBox;
    QLabel *num_sc_to_avg_label;
    QComboBox *process_mode_comboBox;
    QSpacerItem *horizontalSpacer;
    QWidget *Display_page;
    QGroupBox *ImageOverlayGroup;
    QWidget *layoutWidget;
    QGridLayout *ImageOverlayGrid;
    QLabel *overlaySourceLabel;
    QComboBox *thresh_type_comboBox;
    QComboBox *over_src_comboBox;
    QDoubleSpinBox *bg_min_spin;
    QLabel *overlayBlurLabel;
    QDoubleSpinBox *over_alpha_min_SpinBox;
    QSpinBox *over_blur_spin;
    QLabel *overlayColormapLabel;
    QLabel *overlayBackgroundLabel;
    QDoubleSpinBox *over_min_spin;
    QDoubleSpinBox *bg_max_spin;
    QCheckBox *enable_overlay_checkBox;
    QDoubleSpinBox *over_Kmid_SpinBox;
    QLabel *overlayThreshLabel;
    QCheckBox *alpha_enable_checkBox;
    QLabel *overlayMinLabel;
    QComboBox *bg_cmap_comboBox;
    QDoubleSpinBox *over_alpha_max_SpinBox;
    QLabel *overlayMaxLabel;
    QLabel *overlayOverlayLabel;
    QComboBox *over_cmap_comboBox;
    QLabel *overlayAlphaThresholdLabel;
    QComboBox *bg_src_comboBox;
    QDoubleSpinBox *over_max_spin;
    QLabel *overlayAlphaRangeLabel;
    QDoubleSpinBox *colorCameraExposure_SpinBox;
    QLabel *colorCameraExposureLabel;
    QGroupBox *DisplayRangeGroup;
    QWidget *layoutWidget_2;
    QGridLayout *DisplayRangeGrid;
    QComboBox *raw_colormap_combo;
    QSpinBox *raw_max_spin;
    QLabel *minDisplayLabel;
    QSpinBox *raw_min_spin;
    QLabel *label_15;
    QCheckBox *show_SC_check;
    QCheckBox *show_raw_check;
    QComboBox *sc_colormap_combo;
    QDoubleSpinBox *scmax_spin;
    QDoubleSpinBox *scmin_spin;
    QLabel *colormapLabel;
    QLabel *rawDisplayLabel;
    QLabel *label_14;
    QCheckBox *rawColorbar_checkBox;
    QLabel *maxDisplayLabel;
    QCheckBox *scColorbar_checkBox;
    QLabel *scDisplayLabel;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *DisplayRangeExtra;
    QLabel *satPixelColorLabel;
    QComboBox *SatPixelColor_comboBox;
    QGroupBox *RatioImageGroup;
    QWidget *gridLayoutWidget_6;
    QGridLayout *RatioImageGrid;
    QComboBox *ratio_colormap_combo;
    QDoubleSpinBox *ratio_max_spin;
    QDoubleSpinBox *ratio_min_spin;
    QLabel *ratioMinLabel;
    QLabel *ratioMaxLabel;
    QLabel *ratioColormapLabel;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *RatioImageExtra;
    QCheckBox *enable_ratio_image_checkbox;
    QCheckBox *autoset_baseline_check;
    QGroupBox *groupBox_8;
    QWidget *layoutWidget_5;
    QGridLayout *_2;
    QComboBox *baseline_list_combo;
    QComboBox *sc_list_combo;
    QToolButton *clear_baseline_list_button;
    QToolButton *clear_image_list_button;
    QLabel *baselineListLabel;
    QLabel *scListLabel;
    QLabel *rawListLabel;
    QComboBox *raw_list_combo;
    QToolButton *clear_raw_list_button;
    QWidget *ROI_editor_page;
    QGroupBox *ROIEditorGroup;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *ROIEditorTools;
    QToolButton *add_ROI_button;
    QToolButton *remove_ROI_button;
    QToolButton *ROI_color_button;
    QListWidget *ROI_list_widget;
    QCheckBox *ROI_show_check;
    QGroupBox *roiPlotGroup;
    QWidget *layoutWidget_4;
    QGridLayout *roiPlotDisplay;
    QLabel *roiPlotMaxLabel;
    QLabel *roiPlotMinLabel;
    QDoubleSpinBox *roiplot_ymax_spin;
    QCheckBox *roiplot_autoscale_check;
    QDoubleSpinBox *roiplot_rel_ymax_spin;
    QCheckBox *roiplot_rel_autoscale_check;
    QDoubleSpinBox *roiplot_rel_ymin_spin;
    QLabel *roiPlotRelativeLabel;
    QDoubleSpinBox *roiplot_ymin_spin;
    QLabel *roiPlotSCLabel;
    QLabel *roiPlotAutoLabel;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout;
    QCheckBox *roiPlotCheckbox;
    QCheckBox *roiPlotSaveCheckbox;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *roiPlotEnable;
    QCheckBox *roiPlotHistoryCheckbox;
    QLabel *roiPlotLimitLabel;
    QSpinBox *roiPlotLimitSpin;
    QHBoxLayout *roiPlotBaseline;
    QLabel *roiPlotBaselineLabel;
    QSpinBox *roiPlotBaselineStart;
    QSpinBox *roiPlotBaselineEnd;
    QWidget *DMD_page;
    QGroupBox *dmdBoxSystem;
    QWidget *verticalLayoutWidget_7;
    QVBoxLayout *verticalLayout_10;
    QPushButton *dmdInitializeButton;
    QPushButton *dmdInfoButton;
    QPushButton *dmdRegistrationButton;
    QGroupBox *dmdBoxROI;
    QWidget *verticalLayoutWidget_8;
    QVBoxLayout *verticalLayout_8;
    QPushButton *loadROIButton;
    QPushButton *saveROIButton;
    QPushButton *clearROIButton;
    QGroupBox *dmdBoxSequence;
    QWidget *verticalLayoutWidget_9;
    QVBoxLayout *verticalLayout_11;
    QFormLayout *formLayout_4;
    QLabel *dmdExposureLabel;
    QDoubleSpinBox *dmdExposureSpin;
    QLabel *dmdTotalTimeLabel;
    QDoubleSpinBox *dmdTotalTimeSpin;
    QLabel *dmdCycleLabel;
    QDoubleSpinBox *dmdCycleSpin;
    QSpinBox *dmdROICounter;
    QLabel *dmdROICounterLabel;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *startPatternSequenceButton;
    QProgressBar *dmdProgressBar;
    QGroupBox *dmdBoxTransform;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *loadTransformButton;
    QPushButton *saveTransformButton;
    QVBoxLayout *verticalLayout_12;
    QCheckBox *useTransformCheckbox;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *formLayout_5;
    QLabel *sxLabel;
    QTextBrowser *sxText;
    QLabel *ryLabel;
    QTextBrowser *ryText;
    QLabel *txLabel;
    QTextBrowser *txText;
    QFormLayout *formLayout_6;
    QLabel *rxLabel;
    QTextBrowser *rxText;
    QLabel *syLabel;
    QTextBrowser *syText;
    QLabel *tyLabel;
    QTextBrowser *tyText;
    QGroupBox *dmdBoxTile;
    QPushButton *dmdTileButton;
    QSpinBox *dmdTileXSpin;
    QSpinBox *dmdTileYSpin;
    QLabel *dmdTileYLabel;
    QLabel *dmdTileXLabel;
    QSpinBox *dmdTileXGapSpin;
    QSpinBox *dmdTileYGapSpin;
    QLabel *dmdTileXGapSpinLabel;
    QLabel *dmdTileYGapSpinLabel;
    QPushButton *showSinglePatternButton;
    QCheckBox *dmdMergeCheckbox;

    void setupUi(QDialog *SpeckleSettings)
    {
        if (SpeckleSettings->objectName().isEmpty())
            SpeckleSettings->setObjectName("SpeckleSettings");
        SpeckleSettings->resize(650, 534);
        horizontalLayoutWidget = new QWidget(SpeckleSettings);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 641, 531));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(horizontalLayoutWidget);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Acquire"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setIcon(icon);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Processing"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setIcon(icon1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Display"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget);
        __qlistwidgetitem2->setIcon(icon2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ROI"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidget);
        __qlistwidgetitem3->setIcon(icon3);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/DMD"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(listWidget);
        __qlistwidgetitem4->setIcon(icon4);
        listWidget->setObjectName("listWidget");
        listWidget->setMaximumSize(QSize(150, 16777215));
        listWidget->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(listWidget);

        stackedWidget = new QStackedWidget(horizontalLayoutWidget);
        stackedWidget->setObjectName("stackedWidget");
        Acquisition_page = new QWidget();
        Acquisition_page->setObjectName("Acquisition_page");
        gridLayoutWidget_5 = new QWidget(Acquisition_page);
        gridLayoutWidget_5->setObjectName("gridLayoutWidget_5");
        gridLayoutWidget_5->setGeometry(QRect(20, 30, 226, 91));
        AcquisitionSettingsBox = new QGridLayout(gridLayoutWidget_5);
        AcquisitionSettingsBox->setObjectName("AcquisitionSettingsBox");
        AcquisitionSettingsBox->setContentsMargins(0, 0, 0, 0);
        camerasAvailableComboBox = new QComboBox(gridLayoutWidget_5);
        camerasAvailableComboBox->setObjectName("camerasAvailableComboBox");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(camerasAvailableComboBox->sizePolicy().hasHeightForWidth());
        camerasAvailableComboBox->setSizePolicy(sizePolicy);

        AcquisitionSettingsBox->addWidget(camerasAvailableComboBox, 1, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget_5);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        AcquisitionSettingsBox->addWidget(label_2, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        duration_TypeComboBox = new QComboBox(gridLayoutWidget_5);
        duration_TypeComboBox->addItem(QString());
        duration_TypeComboBox->addItem(QString());
        duration_TypeComboBox->addItem(QString());
        duration_TypeComboBox->setObjectName("duration_TypeComboBox");
        sizePolicy.setHeightForWidth(duration_TypeComboBox->sizePolicy().hasHeightForWidth());
        duration_TypeComboBox->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(duration_TypeComboBox);

        acquireLength_lineEdit = new QLineEdit(gridLayoutWidget_5);
        acquireLength_lineEdit->setObjectName("acquireLength_lineEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(acquireLength_lineEdit->sizePolicy().hasHeightForWidth());
        acquireLength_lineEdit->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(acquireLength_lineEdit);


        AcquisitionSettingsBox->addLayout(horizontalLayout_3, 2, 1, 1, 1);

        frames_seq_spin_label = new QLabel(gridLayoutWidget_5);
        frames_seq_spin_label->setObjectName("frames_seq_spin_label");
        frames_seq_spin_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        AcquisitionSettingsBox->addWidget(frames_seq_spin_label, 2, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        outputfile_edit = new QLineEdit(gridLayoutWidget_5);
        outputfile_edit->setObjectName("outputfile_edit");
        sizePolicy.setHeightForWidth(outputfile_edit->sizePolicy().hasHeightForWidth());
        outputfile_edit->setSizePolicy(sizePolicy);

        horizontalLayout_10->addWidget(outputfile_edit);

        outputfile_browse_button = new QToolButton(gridLayoutWidget_5);
        outputfile_browse_button->setObjectName("outputfile_browse_button");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(outputfile_browse_button->sizePolicy().hasHeightForWidth());
        outputfile_browse_button->setSizePolicy(sizePolicy2);
        outputfile_browse_button->setMinimumSize(QSize(0, 0));

        horizontalLayout_10->addWidget(outputfile_browse_button);


        AcquisitionSettingsBox->addLayout(horizontalLayout_10, 3, 1, 1, 1);

        label_13 = new QLabel(gridLayoutWidget_5);
        label_13->setObjectName("label_13");
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        AcquisitionSettingsBox->addWidget(label_13, 1, 0, 1, 1);

        MESIBox = new QGroupBox(Acquisition_page);
        MESIBox->setObjectName("MESIBox");
        MESIBox->setGeometry(QRect(10, 330, 281, 161));
        mesi_EnableCheckbox = new QCheckBox(MESIBox);
        mesi_EnableCheckbox->setObjectName("mesi_EnableCheckbox");
        mesi_EnableCheckbox->setGeometry(QRect(20, 20, 111, 17));
        mesi_CalibrationButton = new QPushButton(MESIBox);
        mesi_CalibrationButton->setObjectName("mesi_CalibrationButton");
        mesi_CalibrationButton->setEnabled(false);
        mesi_CalibrationButton->setGeometry(QRect(20, 50, 81, 31));
        mesi_ExposureTextboxLabel = new QLabel(MESIBox);
        mesi_ExposureTextboxLabel->setObjectName("mesi_ExposureTextboxLabel");
        mesi_ExposureTextboxLabel->setGeometry(QRect(120, 40, 111, 16));
        mesi_DisplayExposureCombo = new QComboBox(MESIBox);
        mesi_DisplayExposureCombo->setObjectName("mesi_DisplayExposureCombo");
        mesi_DisplayExposureCombo->setEnabled(false);
        mesi_DisplayExposureCombo->setGeometry(QRect(120, 110, 61, 22));
        mesi_DisplayExposureComboxLabel = new QLabel(MESIBox);
        mesi_DisplayExposureComboxLabel->setObjectName("mesi_DisplayExposureComboxLabel");
        mesi_DisplayExposureComboxLabel->setGeometry(QRect(120, 90, 101, 21));
        mesi_StartButton = new QPushButton(MESIBox);
        mesi_StartButton->setObjectName("mesi_StartButton");
        mesi_StartButton->setEnabled(false);
        mesi_StartButton->setGeometry(QRect(20, 90, 81, 31));
        mesi_ExposureInput = new QLineEdit(MESIBox);
        mesi_ExposureInput->setObjectName("mesi_ExposureInput");
        mesi_ExposureInput->setEnabled(false);
        mesi_ExposureInput->setGeometry(QRect(120, 60, 151, 20));
        verticalLayoutWidget_3 = new QWidget(Acquisition_page);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(280, 20, 140, 137));
        SaveSettingsBox = new QVBoxLayout(verticalLayoutWidget_3);
        SaveSettingsBox->setObjectName("SaveSettingsBox");
        SaveSettingsBox->setContentsMargins(0, 0, 0, 0);
        save_sc_check = new QCheckBox(verticalLayoutWidget_3);
        save_sc_check->setObjectName("save_sc_check");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(save_sc_check->sizePolicy().hasHeightForWidth());
        save_sc_check->setSizePolicy(sizePolicy3);
        save_sc_check->setChecked(false);

        SaveSettingsBox->addWidget(save_sc_check);

        save_raw_check = new QCheckBox(verticalLayoutWidget_3);
        save_raw_check->setObjectName("save_raw_check");
        sizePolicy3.setHeightForWidth(save_raw_check->sizePolicy().hasHeightForWidth());
        save_raw_check->setSizePolicy(sizePolicy3);
        save_raw_check->setChecked(true);

        SaveSettingsBox->addWidget(save_raw_check);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        SaveSettingsBox->addItem(verticalSpacer);

        save_sc_videocheckBox = new QCheckBox(verticalLayoutWidget_3);
        save_sc_videocheckBox->setObjectName("save_sc_videocheckBox");
        save_sc_videocheckBox->setChecked(false);

        SaveSettingsBox->addWidget(save_sc_videocheckBox);

        save_overlay_videocheckBox = new QCheckBox(verticalLayoutWidget_3);
        save_overlay_videocheckBox->setObjectName("save_overlay_videocheckBox");
        save_overlay_videocheckBox->setChecked(false);

        SaveSettingsBox->addWidget(save_overlay_videocheckBox);

        save_input_videocheckBox = new QCheckBox(verticalLayoutWidget_3);
        save_input_videocheckBox->setObjectName("save_input_videocheckBox");
        save_input_videocheckBox->setChecked(false);

        SaveSettingsBox->addWidget(save_input_videocheckBox);

        CameraSettingsBox = new QGroupBox(Acquisition_page);
        CameraSettingsBox->setObjectName("CameraSettingsBox");
        CameraSettingsBox->setGeometry(QRect(10, 150, 251, 171));
        layoutWidget_3 = new QWidget(CameraSettingsBox);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(10, 20, 231, 144));
        CameraSettingsGrid = new QGridLayout(layoutWidget_3);
        CameraSettingsGrid->setObjectName("CameraSettingsGrid");
        CameraSettingsGrid->setContentsMargins(0, 0, 0, 0);
        trigger_combo_label = new QLabel(layoutWidget_3);
        trigger_combo_label->setObjectName("trigger_combo_label");
        trigger_combo_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        CameraSettingsGrid->addWidget(trigger_combo_label, 1, 0, 1, 1);

        label_7 = new QLabel(layoutWidget_3);
        label_7->setObjectName("label_7");
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        CameraSettingsGrid->addWidget(label_7, 3, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        left_spin = new QSpinBox(layoutWidget_3);
        left_spin->setObjectName("left_spin");
        sizePolicy2.setHeightForWidth(left_spin->sizePolicy().hasHeightForWidth());
        left_spin->setSizePolicy(sizePolicy2);
        left_spin->setMinimumSize(QSize(65, 0));
        left_spin->setMaximum(9999);

        horizontalLayout_6->addWidget(left_spin);

        top_spin = new QSpinBox(layoutWidget_3);
        top_spin->setObjectName("top_spin");
        sizePolicy2.setHeightForWidth(top_spin->sizePolicy().hasHeightForWidth());
        top_spin->setSizePolicy(sizePolicy2);
        top_spin->setMinimumSize(QSize(65, 0));
        top_spin->setMaximum(9999);

        horizontalLayout_6->addWidget(top_spin);


        CameraSettingsGrid->addLayout(horizontalLayout_6, 2, 1, 1, 1);

        GainSpinLabel = new QLabel(layoutWidget_3);
        GainSpinLabel->setObjectName("GainSpinLabel");
        GainSpinLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        CameraSettingsGrid->addWidget(GainSpinLabel, 4, 0, 1, 1);

        exposure_time_spin = new QDoubleSpinBox(layoutWidget_3);
        exposure_time_spin->setObjectName("exposure_time_spin");
        sizePolicy2.setHeightForWidth(exposure_time_spin->sizePolicy().hasHeightForWidth());
        exposure_time_spin->setSizePolicy(sizePolicy2);
        exposure_time_spin->setMinimumSize(QSize(65, 0));
        exposure_time_spin->setDecimals(2);
        exposure_time_spin->setMaximum(100.000000000000000);
        exposure_time_spin->setValue(5.000000000000000);

        CameraSettingsGrid->addWidget(exposure_time_spin, 0, 1, 1, 1);

        exposure_time_spin_label = new QLabel(layoutWidget_3);
        exposure_time_spin_label->setObjectName("exposure_time_spin_label");
        exposure_time_spin_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        CameraSettingsGrid->addWidget(exposure_time_spin_label, 0, 0, 1, 1);

        GainSpin = new QSpinBox(layoutWidget_3);
        GainSpin->setObjectName("GainSpin");
        sizePolicy2.setHeightForWidth(GainSpin->sizePolicy().hasHeightForWidth());
        GainSpin->setSizePolicy(sizePolicy2);
        GainSpin->setMinimumSize(QSize(65, 0));

        CameraSettingsGrid->addWidget(GainSpin, 4, 1, 1, 1);

        label_6 = new QLabel(layoutWidget_3);
        label_6->setObjectName("label_6");
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        CameraSettingsGrid->addWidget(label_6, 2, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        width_spin = new QSpinBox(layoutWidget_3);
        width_spin->setObjectName("width_spin");
        sizePolicy2.setHeightForWidth(width_spin->sizePolicy().hasHeightForWidth());
        width_spin->setSizePolicy(sizePolicy2);
        width_spin->setMinimumSize(QSize(65, 0));
        width_spin->setMaximum(9999);

        horizontalLayout_7->addWidget(width_spin);

        height_spin = new QSpinBox(layoutWidget_3);
        height_spin->setObjectName("height_spin");
        sizePolicy2.setHeightForWidth(height_spin->sizePolicy().hasHeightForWidth());
        height_spin->setSizePolicy(sizePolicy2);
        height_spin->setMinimumSize(QSize(65, 0));
        height_spin->setMaximum(9999);

        horizontalLayout_7->addWidget(height_spin);


        CameraSettingsGrid->addLayout(horizontalLayout_7, 3, 1, 1, 1);

        trigger_combo = new QComboBox(layoutWidget_3);
        trigger_combo->setObjectName("trigger_combo");
        sizePolicy.setHeightForWidth(trigger_combo->sizePolicy().hasHeightForWidth());
        trigger_combo->setSizePolicy(sizePolicy);
        trigger_combo->setMinimumSize(QSize(0, 0));
        trigger_combo->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        CameraSettingsGrid->addWidget(trigger_combo, 1, 1, 1, 1);

        stackedWidget->addWidget(Acquisition_page);
        Processing_page = new QWidget();
        Processing_page->setObjectName("Processing_page");
        DarkLevelMaskGroup = new QGroupBox(Processing_page);
        DarkLevelMaskGroup->setObjectName("DarkLevelMaskGroup");
        DarkLevelMaskGroup->setGeometry(QRect(10, 160, 131, 81));
        gridLayoutWidget_2 = new QWidget(DarkLevelMaskGroup);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(10, 20, 111, 54));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        Dark_level_label = new QLabel(gridLayoutWidget_2);
        Dark_level_label->setObjectName("Dark_level_label");
        Dark_level_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(Dark_level_label, 0, 0, 1, 1);

        Dark_level_spinBox = new QSpinBox(gridLayoutWidget_2);
        Dark_level_spinBox->setObjectName("Dark_level_spinBox");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(Dark_level_spinBox->sizePolicy().hasHeightForWidth());
        Dark_level_spinBox->setSizePolicy(sizePolicy4);
        Dark_level_spinBox->setMinimumSize(QSize(50, 0));
        Dark_level_spinBox->setMaximum(255);

        gridLayout_2->addWidget(Dark_level_spinBox, 0, 1, 1, 1);

        blur_width_label = new QLabel(gridLayoutWidget_2);
        blur_width_label->setObjectName("blur_width_label");
        blur_width_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(blur_width_label, 1, 0, 1, 1);

        blur_width_spinBox = new QSpinBox(gridLayoutWidget_2);
        blur_width_spinBox->setObjectName("blur_width_spinBox");
        sizePolicy4.setHeightForWidth(blur_width_spinBox->sizePolicy().hasHeightForWidth());
        blur_width_spinBox->setSizePolicy(sizePolicy4);
        blur_width_spinBox->setMinimumSize(QSize(50, 0));
        blur_width_spinBox->setMinimum(1);
        blur_width_spinBox->setMaximum(512);
        blur_width_spinBox->setValue(5);

        gridLayout_2->addWidget(blur_width_spinBox, 1, 1, 1, 1);

        SpeckleContrasGroup = new QGroupBox(Processing_page);
        SpeckleContrasGroup->setObjectName("SpeckleContrasGroup");
        SpeckleContrasGroup->setGeometry(QRect(10, 20, 391, 121));
        gridLayoutWidget = new QWidget(SpeckleContrasGroup);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 20, 371, 91));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        num_sc_to_avg_spinBox = new QSpinBox(gridLayoutWidget);
        num_sc_to_avg_spinBox->setObjectName("num_sc_to_avg_spinBox");
        sizePolicy4.setHeightForWidth(num_sc_to_avg_spinBox->sizePolicy().hasHeightForWidth());
        num_sc_to_avg_spinBox->setSizePolicy(sizePolicy4);
        num_sc_to_avg_spinBox->setMinimumSize(QSize(50, 0));
        num_sc_to_avg_spinBox->setMinimum(1);
        num_sc_to_avg_spinBox->setMaximum(999);
        num_sc_to_avg_spinBox->setValue(5);

        gridLayout->addWidget(num_sc_to_avg_spinBox, 1, 4, 1, 1);

        Nthreads_label = new QLabel(gridLayoutWidget);
        Nthreads_label->setObjectName("Nthreads_label");
        Nthreads_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Nthreads_label, 2, 0, 1, 1);

        compute_SC_check = new QCheckBox(gridLayoutWidget);
        compute_SC_check->setObjectName("compute_SC_check");
        sizePolicy4.setHeightForWidth(compute_SC_check->sizePolicy().hasHeightForWidth());
        compute_SC_check->setSizePolicy(sizePolicy4);
        compute_SC_check->setLayoutDirection(Qt::LeftToRight);
        compute_SC_check->setChecked(true);

        gridLayout->addWidget(compute_SC_check, 0, 0, 1, 1);

        moving_average_spinBox = new QSpinBox(gridLayoutWidget);
        moving_average_spinBox->setObjectName("moving_average_spinBox");
        sizePolicy4.setHeightForWidth(moving_average_spinBox->sizePolicy().hasHeightForWidth());
        moving_average_spinBox->setSizePolicy(sizePolicy4);
        moving_average_spinBox->setMinimumSize(QSize(50, 0));
        moving_average_spinBox->setMinimum(1);
        moving_average_spinBox->setMaximum(999);

        gridLayout->addWidget(moving_average_spinBox, 2, 4, 1, 1);

        process_mode_label = new QLabel(gridLayoutWidget);
        process_mode_label->setObjectName("process_mode_label");
        process_mode_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(process_mode_label, 1, 0, 1, 1);

        NxN_spin = new QSpinBox(gridLayoutWidget);
        NxN_spin->setObjectName("NxN_spin");
        sizePolicy4.setHeightForWidth(NxN_spin->sizePolicy().hasHeightForWidth());
        NxN_spin->setSizePolicy(sizePolicy4);
        NxN_spin->setMinimumSize(QSize(50, 0));
        NxN_spin->setLayoutDirection(Qt::LeftToRight);
        NxN_spin->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        NxN_spin->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        NxN_spin->setMinimum(1);
        NxN_spin->setMaximum(99);
        NxN_spin->setValue(7);

        gridLayout->addWidget(NxN_spin, 0, 4, 1, 1);

        NxN_label = new QLabel(gridLayoutWidget);
        NxN_label->setObjectName("NxN_label");
        NxN_label->setFrameShape(QFrame::NoFrame);
        NxN_label->setFrameShadow(QFrame::Plain);
        NxN_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(NxN_label, 0, 3, 1, 1);

        moving_average_label = new QLabel(gridLayoutWidget);
        moving_average_label->setObjectName("moving_average_label");
        moving_average_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(moving_average_label, 2, 3, 1, 1);

        Nthreads_spinBox = new QSpinBox(gridLayoutWidget);
        Nthreads_spinBox->setObjectName("Nthreads_spinBox");
        sizePolicy4.setHeightForWidth(Nthreads_spinBox->sizePolicy().hasHeightForWidth());
        Nthreads_spinBox->setSizePolicy(sizePolicy4);
        Nthreads_spinBox->setMinimumSize(QSize(50, 0));
        Nthreads_spinBox->setMinimum(1);
        Nthreads_spinBox->setMaximum(32);
        Nthreads_spinBox->setValue(8);

        gridLayout->addWidget(Nthreads_spinBox, 2, 1, 1, 1);

        num_sc_to_avg_label = new QLabel(gridLayoutWidget);
        num_sc_to_avg_label->setObjectName("num_sc_to_avg_label");
        num_sc_to_avg_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(num_sc_to_avg_label, 1, 3, 1, 1);

        process_mode_comboBox = new QComboBox(gridLayoutWidget);
        process_mode_comboBox->addItem(QString());
        process_mode_comboBox->addItem(QString());
        process_mode_comboBox->setObjectName("process_mode_comboBox");
        sizePolicy4.setHeightForWidth(process_mode_comboBox->sizePolicy().hasHeightForWidth());
        process_mode_comboBox->setSizePolicy(sizePolicy4);
        process_mode_comboBox->setMinimumSize(QSize(90, 0));
        process_mode_comboBox->setMaximumSize(QSize(90, 16777215));

        gridLayout->addWidget(process_mode_comboBox, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        stackedWidget->addWidget(Processing_page);
        Display_page = new QWidget();
        Display_page->setObjectName("Display_page");
        ImageOverlayGroup = new QGroupBox(Display_page);
        ImageOverlayGroup->setObjectName("ImageOverlayGroup");
        ImageOverlayGroup->setGeometry(QRect(0, 130, 461, 171));
        layoutWidget = new QWidget(ImageOverlayGroup);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 20, 441, 149));
        ImageOverlayGrid = new QGridLayout(layoutWidget);
        ImageOverlayGrid->setObjectName("ImageOverlayGrid");
        ImageOverlayGrid->setContentsMargins(0, 0, 0, 0);
        overlaySourceLabel = new QLabel(layoutWidget);
        overlaySourceLabel->setObjectName("overlaySourceLabel");
        overlaySourceLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(overlaySourceLabel->sizePolicy().hasHeightForWidth());
        overlaySourceLabel->setSizePolicy(sizePolicy4);
        overlaySourceLabel->setMinimumSize(QSize(75, 18));
        overlaySourceLabel->setMaximumSize(QSize(75, 18));
        overlaySourceLabel->setAlignment(Qt::AlignCenter);

        ImageOverlayGrid->addWidget(overlaySourceLabel, 0, 1, 1, 1);

        thresh_type_comboBox = new QComboBox(layoutWidget);
        thresh_type_comboBox->addItem(QString());
        thresh_type_comboBox->addItem(QString());
        thresh_type_comboBox->addItem(QString());
        thresh_type_comboBox->setObjectName("thresh_type_comboBox");
        thresh_type_comboBox->setEnabled(false);
        sizePolicy4.setHeightForWidth(thresh_type_comboBox->sizePolicy().hasHeightForWidth());
        thresh_type_comboBox->setSizePolicy(sizePolicy4);
        thresh_type_comboBox->setMinimumSize(QSize(75, 18));
        thresh_type_comboBox->setMaximumSize(QSize(75, 18));

        ImageOverlayGrid->addWidget(thresh_type_comboBox, 3, 2, 1, 1);

        over_src_comboBox = new QComboBox(layoutWidget);
        over_src_comboBox->addItem(QString());
        over_src_comboBox->addItem(QString());
        over_src_comboBox->addItem(QString());
        over_src_comboBox->addItem(QString());
        over_src_comboBox->addItem(QString());
        over_src_comboBox->setObjectName("over_src_comboBox");
        over_src_comboBox->setEnabled(false);
        sizePolicy4.setHeightForWidth(over_src_comboBox->sizePolicy().hasHeightForWidth());
        over_src_comboBox->setSizePolicy(sizePolicy4);
        over_src_comboBox->setMinimumSize(QSize(75, 18));
        over_src_comboBox->setMaximumSize(QSize(75, 18));

        ImageOverlayGrid->addWidget(over_src_comboBox, 2, 1, 1, 1);

        bg_min_spin = new QDoubleSpinBox(layoutWidget);
        bg_min_spin->setObjectName("bg_min_spin");
        bg_min_spin->setEnabled(false);
        sizePolicy4.setHeightForWidth(bg_min_spin->sizePolicy().hasHeightForWidth());
        bg_min_spin->setSizePolicy(sizePolicy4);
        bg_min_spin->setMinimumSize(QSize(75, 18));
        bg_min_spin->setMaximumSize(QSize(75, 18));
        bg_min_spin->setDecimals(0);
        bg_min_spin->setMinimum(0.000000000000000);
        bg_min_spin->setMaximum(255.000000000000000);

        ImageOverlayGrid->addWidget(bg_min_spin, 1, 3, 1, 1);

        overlayBlurLabel = new QLabel(layoutWidget);
        overlayBlurLabel->setObjectName("overlayBlurLabel");
        overlayBlurLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(overlayBlurLabel->sizePolicy().hasHeightForWidth());
        overlayBlurLabel->setSizePolicy(sizePolicy4);
        overlayBlurLabel->setMinimumSize(QSize(75, 13));
        overlayBlurLabel->setMaximumSize(QSize(75, 13));
        overlayBlurLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        ImageOverlayGrid->addWidget(overlayBlurLabel, 3, 3, 1, 1);

        over_alpha_min_SpinBox = new QDoubleSpinBox(layoutWidget);
        over_alpha_min_SpinBox->setObjectName("over_alpha_min_SpinBox");
        over_alpha_min_SpinBox->setEnabled(false);
        sizePolicy4.setHeightForWidth(over_alpha_min_SpinBox->sizePolicy().hasHeightForWidth());
        over_alpha_min_SpinBox->setSizePolicy(sizePolicy4);
        over_alpha_min_SpinBox->setMinimumSize(QSize(75, 18));
        over_alpha_min_SpinBox->setMaximumSize(QSize(75, 18));
        over_alpha_min_SpinBox->setDecimals(3);
        over_alpha_min_SpinBox->setMaximum(1.000000000000000);
        over_alpha_min_SpinBox->setSingleStep(0.050000000000000);

        ImageOverlayGrid->addWidget(over_alpha_min_SpinBox, 5, 2, 1, 1);

        over_blur_spin = new QSpinBox(layoutWidget);
        over_blur_spin->setObjectName("over_blur_spin");
        over_blur_spin->setEnabled(false);
        sizePolicy4.setHeightForWidth(over_blur_spin->sizePolicy().hasHeightForWidth());
        over_blur_spin->setSizePolicy(sizePolicy4);
        over_blur_spin->setMinimumSize(QSize(75, 18));
        over_blur_spin->setMaximumSize(QSize(75, 18));

        ImageOverlayGrid->addWidget(over_blur_spin, 3, 4, 1, 1);

        overlayColormapLabel = new QLabel(layoutWidget);
        overlayColormapLabel->setObjectName("overlayColormapLabel");
        overlayColormapLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(overlayColormapLabel->sizePolicy().hasHeightForWidth());
        overlayColormapLabel->setSizePolicy(sizePolicy4);
        overlayColormapLabel->setMinimumSize(QSize(75, 18));
        overlayColormapLabel->setMaximumSize(QSize(75, 18));
        overlayColormapLabel->setAlignment(Qt::AlignCenter);

        ImageOverlayGrid->addWidget(overlayColormapLabel, 0, 2, 1, 1);

        overlayBackgroundLabel = new QLabel(layoutWidget);
        overlayBackgroundLabel->setObjectName("overlayBackgroundLabel");
        overlayBackgroundLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(overlayBackgroundLabel->sizePolicy().hasHeightForWidth());
        overlayBackgroundLabel->setSizePolicy(sizePolicy4);
        overlayBackgroundLabel->setMinimumSize(QSize(60, 16));
        overlayBackgroundLabel->setMaximumSize(QSize(60, 16));
        overlayBackgroundLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        ImageOverlayGrid->addWidget(overlayBackgroundLabel, 1, 0, 1, 1);

        over_min_spin = new QDoubleSpinBox(layoutWidget);
        over_min_spin->setObjectName("over_min_spin");
        over_min_spin->setEnabled(false);
        sizePolicy4.setHeightForWidth(over_min_spin->sizePolicy().hasHeightForWidth());
        over_min_spin->setSizePolicy(sizePolicy4);
        over_min_spin->setMinimumSize(QSize(75, 18));
        over_min_spin->setMaximumSize(QSize(75, 18));
        over_min_spin->setDecimals(3);
        over_min_spin->setMinimum(0.000000000000000);
        over_min_spin->setMaximum(0.200000000000000);
        over_min_spin->setSingleStep(0.010000000000000);

        ImageOverlayGrid->addWidget(over_min_spin, 2, 3, 1, 1);

        bg_max_spin = new QDoubleSpinBox(layoutWidget);
        bg_max_spin->setObjectName("bg_max_spin");
        bg_max_spin->setEnabled(false);
        sizePolicy4.setHeightForWidth(bg_max_spin->sizePolicy().hasHeightForWidth());
        bg_max_spin->setSizePolicy(sizePolicy4);
        bg_max_spin->setMinimumSize(QSize(75, 18));
        bg_max_spin->setMaximumSize(QSize(75, 18));
        bg_max_spin->setDecimals(0);
        bg_max_spin->setMinimum(0.000000000000000);
        bg_max_spin->setMaximum(255.000000000000000);
        bg_max_spin->setValue(255.000000000000000);

        ImageOverlayGrid->addWidget(bg_max_spin, 1, 4, 1, 1);

        enable_overlay_checkBox = new QCheckBox(layoutWidget);
        enable_overlay_checkBox->setObjectName("enable_overlay_checkBox");
        sizePolicy4.setHeightForWidth(enable_overlay_checkBox->sizePolicy().hasHeightForWidth());
        enable_overlay_checkBox->setSizePolicy(sizePolicy4);
        enable_overlay_checkBox->setMinimumSize(QSize(60, 18));
        enable_overlay_checkBox->setMaximumSize(QSize(60, 18));

        ImageOverlayGrid->addWidget(enable_overlay_checkBox, 0, 0, 1, 1);

        over_Kmid_SpinBox = new QDoubleSpinBox(layoutWidget);
        over_Kmid_SpinBox->setObjectName("over_Kmid_SpinBox");
        over_Kmid_SpinBox->setEnabled(false);
        sizePolicy4.setHeightForWidth(over_Kmid_SpinBox->sizePolicy().hasHeightForWidth());
        over_Kmid_SpinBox->setSizePolicy(sizePolicy4);
        over_Kmid_SpinBox->setMinimumSize(QSize(75, 18));
        over_Kmid_SpinBox->setMaximumSize(QSize(75, 18));
        over_Kmid_SpinBox->setDecimals(3);
        over_Kmid_SpinBox->setMaximum(1.000000000000000);
        over_Kmid_SpinBox->setSingleStep(0.010000000000000);
        over_Kmid_SpinBox->setValue(0.000000000000000);

        ImageOverlayGrid->addWidget(over_Kmid_SpinBox, 4, 2, 1, 1);

        overlayThreshLabel = new QLabel(layoutWidget);
        overlayThreshLabel->setObjectName("overlayThreshLabel");
        overlayThreshLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(overlayThreshLabel->sizePolicy().hasHeightForWidth());
        overlayThreshLabel->setSizePolicy(sizePolicy4);
        overlayThreshLabel->setMinimumSize(QSize(75, 13));
        overlayThreshLabel->setMaximumSize(QSize(75, 13));
        overlayThreshLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        ImageOverlayGrid->addWidget(overlayThreshLabel, 3, 1, 1, 1);

        alpha_enable_checkBox = new QCheckBox(layoutWidget);
        alpha_enable_checkBox->setObjectName("alpha_enable_checkBox");
        alpha_enable_checkBox->setEnabled(false);
        sizePolicy4.setHeightForWidth(alpha_enable_checkBox->sizePolicy().hasHeightForWidth());
        alpha_enable_checkBox->setSizePolicy(sizePolicy4);
        alpha_enable_checkBox->setMinimumSize(QSize(60, 18));
        alpha_enable_checkBox->setMaximumSize(QSize(60, 18));
        alpha_enable_checkBox->setChecked(false);

        ImageOverlayGrid->addWidget(alpha_enable_checkBox, 4, 0, 1, 1, Qt::AlignRight);

        overlayMinLabel = new QLabel(layoutWidget);
        overlayMinLabel->setObjectName("overlayMinLabel");
        overlayMinLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(overlayMinLabel->sizePolicy().hasHeightForWidth());
        overlayMinLabel->setSizePolicy(sizePolicy4);
        overlayMinLabel->setMinimumSize(QSize(75, 18));
        overlayMinLabel->setMaximumSize(QSize(75, 18));
        overlayMinLabel->setAlignment(Qt::AlignCenter);

        ImageOverlayGrid->addWidget(overlayMinLabel, 0, 3, 1, 1);

        bg_cmap_comboBox = new QComboBox(layoutWidget);
        bg_cmap_comboBox->addItem(QString());
        bg_cmap_comboBox->addItem(QString());
        bg_cmap_comboBox->addItem(QString());
        bg_cmap_comboBox->addItem(QString());
        bg_cmap_comboBox->addItem(QString());
        bg_cmap_comboBox->addItem(QString());
        bg_cmap_comboBox->addItem(QString());
        bg_cmap_comboBox->addItem(QString());
        bg_cmap_comboBox->addItem(QString());
        bg_cmap_comboBox->setObjectName("bg_cmap_comboBox");
        bg_cmap_comboBox->setEnabled(false);
        sizePolicy4.setHeightForWidth(bg_cmap_comboBox->sizePolicy().hasHeightForWidth());
        bg_cmap_comboBox->setSizePolicy(sizePolicy4);
        bg_cmap_comboBox->setMinimumSize(QSize(75, 18));
        bg_cmap_comboBox->setMaximumSize(QSize(75, 18));

        ImageOverlayGrid->addWidget(bg_cmap_comboBox, 1, 2, 1, 1);

        over_alpha_max_SpinBox = new QDoubleSpinBox(layoutWidget);
        over_alpha_max_SpinBox->setObjectName("over_alpha_max_SpinBox");
        over_alpha_max_SpinBox->setEnabled(false);
        sizePolicy4.setHeightForWidth(over_alpha_max_SpinBox->sizePolicy().hasHeightForWidth());
        over_alpha_max_SpinBox->setSizePolicy(sizePolicy4);
        over_alpha_max_SpinBox->setMinimumSize(QSize(75, 18));
        over_alpha_max_SpinBox->setMaximumSize(QSize(75, 18));
        over_alpha_max_SpinBox->setDecimals(3);
        over_alpha_max_SpinBox->setMaximum(1.000000000000000);
        over_alpha_max_SpinBox->setSingleStep(0.050000000000000);
        over_alpha_max_SpinBox->setValue(1.000000000000000);

        ImageOverlayGrid->addWidget(over_alpha_max_SpinBox, 5, 3, 1, 1);

        overlayMaxLabel = new QLabel(layoutWidget);
        overlayMaxLabel->setObjectName("overlayMaxLabel");
        overlayMaxLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(overlayMaxLabel->sizePolicy().hasHeightForWidth());
        overlayMaxLabel->setSizePolicy(sizePolicy4);
        overlayMaxLabel->setMinimumSize(QSize(75, 18));
        overlayMaxLabel->setMaximumSize(QSize(75, 18));
        overlayMaxLabel->setAlignment(Qt::AlignCenter);

        ImageOverlayGrid->addWidget(overlayMaxLabel, 0, 4, 1, 1);

        overlayOverlayLabel = new QLabel(layoutWidget);
        overlayOverlayLabel->setObjectName("overlayOverlayLabel");
        overlayOverlayLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(overlayOverlayLabel->sizePolicy().hasHeightForWidth());
        overlayOverlayLabel->setSizePolicy(sizePolicy4);
        overlayOverlayLabel->setMinimumSize(QSize(60, 16));
        overlayOverlayLabel->setMaximumSize(QSize(60, 16));
        overlayOverlayLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        ImageOverlayGrid->addWidget(overlayOverlayLabel, 2, 0, 1, 1);

        over_cmap_comboBox = new QComboBox(layoutWidget);
        over_cmap_comboBox->addItem(QString());
        over_cmap_comboBox->addItem(QString());
        over_cmap_comboBox->addItem(QString());
        over_cmap_comboBox->addItem(QString());
        over_cmap_comboBox->addItem(QString());
        over_cmap_comboBox->addItem(QString());
        over_cmap_comboBox->addItem(QString());
        over_cmap_comboBox->addItem(QString());
        over_cmap_comboBox->addItem(QString());
        over_cmap_comboBox->addItem(QString());
        over_cmap_comboBox->setObjectName("over_cmap_comboBox");
        over_cmap_comboBox->setEnabled(false);
        sizePolicy4.setHeightForWidth(over_cmap_comboBox->sizePolicy().hasHeightForWidth());
        over_cmap_comboBox->setSizePolicy(sizePolicy4);
        over_cmap_comboBox->setMinimumSize(QSize(75, 18));
        over_cmap_comboBox->setMaximumSize(QSize(75, 18));

        ImageOverlayGrid->addWidget(over_cmap_comboBox, 2, 2, 1, 1);

        overlayAlphaThresholdLabel = new QLabel(layoutWidget);
        overlayAlphaThresholdLabel->setObjectName("overlayAlphaThresholdLabel");
        overlayAlphaThresholdLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(overlayAlphaThresholdLabel->sizePolicy().hasHeightForWidth());
        overlayAlphaThresholdLabel->setSizePolicy(sizePolicy4);
        overlayAlphaThresholdLabel->setMinimumSize(QSize(80, 13));
        overlayAlphaThresholdLabel->setMaximumSize(QSize(80, 13));
        overlayAlphaThresholdLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        ImageOverlayGrid->addWidget(overlayAlphaThresholdLabel, 4, 1, 1, 1);

        bg_src_comboBox = new QComboBox(layoutWidget);
        bg_src_comboBox->addItem(QString());
        bg_src_comboBox->addItem(QString());
        bg_src_comboBox->addItem(QString());
        bg_src_comboBox->addItem(QString());
        bg_src_comboBox->addItem(QString());
        bg_src_comboBox->setObjectName("bg_src_comboBox");
        bg_src_comboBox->setEnabled(false);
        sizePolicy4.setHeightForWidth(bg_src_comboBox->sizePolicy().hasHeightForWidth());
        bg_src_comboBox->setSizePolicy(sizePolicy4);
        bg_src_comboBox->setMinimumSize(QSize(75, 18));
        bg_src_comboBox->setMaximumSize(QSize(75, 18));

        ImageOverlayGrid->addWidget(bg_src_comboBox, 1, 1, 1, 1);

        over_max_spin = new QDoubleSpinBox(layoutWidget);
        over_max_spin->setObjectName("over_max_spin");
        over_max_spin->setEnabled(false);
        sizePolicy4.setHeightForWidth(over_max_spin->sizePolicy().hasHeightForWidth());
        over_max_spin->setSizePolicy(sizePolicy4);
        over_max_spin->setMinimumSize(QSize(75, 18));
        over_max_spin->setMaximumSize(QSize(75, 18));
        over_max_spin->setDecimals(3);
        over_max_spin->setMinimum(0.000000000000000);
        over_max_spin->setMaximum(1.000000000000000);
        over_max_spin->setSingleStep(0.020000000000000);
        over_max_spin->setValue(0.200000000000000);

        ImageOverlayGrid->addWidget(over_max_spin, 2, 4, 1, 1);

        overlayAlphaRangeLabel = new QLabel(layoutWidget);
        overlayAlphaRangeLabel->setObjectName("overlayAlphaRangeLabel");
        overlayAlphaRangeLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(overlayAlphaRangeLabel->sizePolicy().hasHeightForWidth());
        overlayAlphaRangeLabel->setSizePolicy(sizePolicy4);
        overlayAlphaRangeLabel->setMinimumSize(QSize(75, 13));
        overlayAlphaRangeLabel->setMaximumSize(QSize(75, 13));
        overlayAlphaRangeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        ImageOverlayGrid->addWidget(overlayAlphaRangeLabel, 5, 1, 1, 1);

        colorCameraExposure_SpinBox = new QDoubleSpinBox(layoutWidget);
        colorCameraExposure_SpinBox->setObjectName("colorCameraExposure_SpinBox");
        colorCameraExposure_SpinBox->setEnabled(false);
        colorCameraExposure_SpinBox->setDecimals(1);
        colorCameraExposure_SpinBox->setMaximum(1000.000000000000000);
        colorCameraExposure_SpinBox->setValue(50.000000000000000);

        ImageOverlayGrid->addWidget(colorCameraExposure_SpinBox, 4, 4, 1, 1);

        colorCameraExposureLabel = new QLabel(layoutWidget);
        colorCameraExposureLabel->setObjectName("colorCameraExposureLabel");
        colorCameraExposureLabel->setEnabled(false);

        ImageOverlayGrid->addWidget(colorCameraExposureLabel, 4, 3, 1, 1);

        DisplayRangeGroup = new QGroupBox(Display_page);
        DisplayRangeGroup->setObjectName("DisplayRangeGroup");
        DisplayRangeGroup->setGeometry(QRect(0, 0, 411, 131));
        layoutWidget_2 = new QWidget(DisplayRangeGroup);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(10, 20, 349, 81));
        DisplayRangeGrid = new QGridLayout(layoutWidget_2);
        DisplayRangeGrid->setObjectName("DisplayRangeGrid");
        DisplayRangeGrid->setContentsMargins(0, 0, 0, 0);
        raw_colormap_combo = new QComboBox(layoutWidget_2);
        raw_colormap_combo->addItem(QString());
        raw_colormap_combo->addItem(QString());
        raw_colormap_combo->addItem(QString());
        raw_colormap_combo->addItem(QString());
        raw_colormap_combo->addItem(QString());
        raw_colormap_combo->addItem(QString());
        raw_colormap_combo->addItem(QString());
        raw_colormap_combo->addItem(QString());
        raw_colormap_combo->setObjectName("raw_colormap_combo");
        sizePolicy4.setHeightForWidth(raw_colormap_combo->sizePolicy().hasHeightForWidth());
        raw_colormap_combo->setSizePolicy(sizePolicy4);
        raw_colormap_combo->setMinimumSize(QSize(75, 18));
        raw_colormap_combo->setMaximumSize(QSize(75, 18));

        DisplayRangeGrid->addWidget(raw_colormap_combo, 2, 4, 1, 1);

        raw_max_spin = new QSpinBox(layoutWidget_2);
        raw_max_spin->setObjectName("raw_max_spin");
        raw_max_spin->setMinimumSize(QSize(60, 18));
        raw_max_spin->setMaximumSize(QSize(60, 18));
        raw_max_spin->setMaximum(255);

        DisplayRangeGrid->addWidget(raw_max_spin, 2, 3, 1, 1);

        minDisplayLabel = new QLabel(layoutWidget_2);
        minDisplayLabel->setObjectName("minDisplayLabel");
        sizePolicy4.setHeightForWidth(minDisplayLabel->sizePolicy().hasHeightForWidth());
        minDisplayLabel->setSizePolicy(sizePolicy4);
        minDisplayLabel->setMinimumSize(QSize(60, 13));
        minDisplayLabel->setMaximumSize(QSize(60, 13));
        minDisplayLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        DisplayRangeGrid->addWidget(minDisplayLabel, 0, 2, 1, 1);

        raw_min_spin = new QSpinBox(layoutWidget_2);
        raw_min_spin->setObjectName("raw_min_spin");
        sizePolicy4.setHeightForWidth(raw_min_spin->sizePolicy().hasHeightForWidth());
        raw_min_spin->setSizePolicy(sizePolicy4);
        raw_min_spin->setMinimumSize(QSize(60, 18));
        raw_min_spin->setMaximumSize(QSize(60, 18));
        raw_min_spin->setMaximum(255);

        DisplayRangeGrid->addWidget(raw_min_spin, 2, 2, 1, 1);

        label_15 = new QLabel(layoutWidget_2);
        label_15->setObjectName("label_15");

        DisplayRangeGrid->addWidget(label_15, 0, 1, 1, 1, Qt::AlignHCenter);

        show_SC_check = new QCheckBox(layoutWidget_2);
        show_SC_check->setObjectName("show_SC_check");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(show_SC_check->sizePolicy().hasHeightForWidth());
        show_SC_check->setSizePolicy(sizePolicy5);
        show_SC_check->setChecked(true);

        DisplayRangeGrid->addWidget(show_SC_check, 1, 1, 1, 1, Qt::AlignHCenter);

        show_raw_check = new QCheckBox(layoutWidget_2);
        show_raw_check->setObjectName("show_raw_check");
        sizePolicy5.setHeightForWidth(show_raw_check->sizePolicy().hasHeightForWidth());
        show_raw_check->setSizePolicy(sizePolicy5);
        show_raw_check->setChecked(true);

        DisplayRangeGrid->addWidget(show_raw_check, 2, 1, 1, 1, Qt::AlignHCenter);

        sc_colormap_combo = new QComboBox(layoutWidget_2);
        sc_colormap_combo->addItem(QString());
        sc_colormap_combo->addItem(QString());
        sc_colormap_combo->addItem(QString());
        sc_colormap_combo->addItem(QString());
        sc_colormap_combo->addItem(QString());
        sc_colormap_combo->addItem(QString());
        sc_colormap_combo->addItem(QString());
        sc_colormap_combo->addItem(QString());
        sc_colormap_combo->addItem(QString());
        sc_colormap_combo->setObjectName("sc_colormap_combo");
        sizePolicy4.setHeightForWidth(sc_colormap_combo->sizePolicy().hasHeightForWidth());
        sc_colormap_combo->setSizePolicy(sizePolicy4);
        sc_colormap_combo->setMinimumSize(QSize(75, 18));
        sc_colormap_combo->setMaximumSize(QSize(75, 18));

        DisplayRangeGrid->addWidget(sc_colormap_combo, 1, 4, 1, 1);

        scmax_spin = new QDoubleSpinBox(layoutWidget_2);
        scmax_spin->setObjectName("scmax_spin");
        sizePolicy4.setHeightForWidth(scmax_spin->sizePolicy().hasHeightForWidth());
        scmax_spin->setSizePolicy(sizePolicy4);
        scmax_spin->setMinimumSize(QSize(60, 18));
        scmax_spin->setMaximumSize(QSize(60, 18));
        scmax_spin->setDecimals(3);
        scmax_spin->setMaximum(1.000000000000000);
        scmax_spin->setSingleStep(0.050000000000000);
        scmax_spin->setValue(1.000000000000000);

        DisplayRangeGrid->addWidget(scmax_spin, 1, 3, 1, 1);

        scmin_spin = new QDoubleSpinBox(layoutWidget_2);
        scmin_spin->setObjectName("scmin_spin");
        sizePolicy4.setHeightForWidth(scmin_spin->sizePolicy().hasHeightForWidth());
        scmin_spin->setSizePolicy(sizePolicy4);
        scmin_spin->setMinimumSize(QSize(60, 18));
        scmin_spin->setMaximumSize(QSize(60, 18));
        scmin_spin->setDecimals(3);
        scmin_spin->setMaximum(1.000000000000000);
        scmin_spin->setSingleStep(0.050000000000000);

        DisplayRangeGrid->addWidget(scmin_spin, 1, 2, 1, 1);

        colormapLabel = new QLabel(layoutWidget_2);
        colormapLabel->setObjectName("colormapLabel");
        sizePolicy4.setHeightForWidth(colormapLabel->sizePolicy().hasHeightForWidth());
        colormapLabel->setSizePolicy(sizePolicy4);
        colormapLabel->setMinimumSize(QSize(75, 13));
        colormapLabel->setMaximumSize(QSize(75, 13));
        colormapLabel->setAlignment(Qt::AlignCenter);

        DisplayRangeGrid->addWidget(colormapLabel, 0, 4, 1, 1);

        rawDisplayLabel = new QLabel(layoutWidget_2);
        rawDisplayLabel->setObjectName("rawDisplayLabel");
        sizePolicy4.setHeightForWidth(rawDisplayLabel->sizePolicy().hasHeightForWidth());
        rawDisplayLabel->setSizePolicy(sizePolicy4);
        rawDisplayLabel->setMinimumSize(QSize(30, 18));
        rawDisplayLabel->setMaximumSize(QSize(30, 18));
        rawDisplayLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        DisplayRangeGrid->addWidget(rawDisplayLabel, 2, 0, 1, 1);

        label_14 = new QLabel(layoutWidget_2);
        label_14->setObjectName("label_14");

        DisplayRangeGrid->addWidget(label_14, 0, 5, 1, 1);

        rawColorbar_checkBox = new QCheckBox(layoutWidget_2);
        rawColorbar_checkBox->setObjectName("rawColorbar_checkBox");

        DisplayRangeGrid->addWidget(rawColorbar_checkBox, 2, 5, 1, 1);

        maxDisplayLabel = new QLabel(layoutWidget_2);
        maxDisplayLabel->setObjectName("maxDisplayLabel");
        sizePolicy4.setHeightForWidth(maxDisplayLabel->sizePolicy().hasHeightForWidth());
        maxDisplayLabel->setSizePolicy(sizePolicy4);
        maxDisplayLabel->setMinimumSize(QSize(60, 13));
        maxDisplayLabel->setMaximumSize(QSize(60, 13));
        maxDisplayLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        DisplayRangeGrid->addWidget(maxDisplayLabel, 0, 3, 1, 1);

        scColorbar_checkBox = new QCheckBox(layoutWidget_2);
        scColorbar_checkBox->setObjectName("scColorbar_checkBox");

        DisplayRangeGrid->addWidget(scColorbar_checkBox, 1, 5, 1, 1);

        scDisplayLabel = new QLabel(layoutWidget_2);
        scDisplayLabel->setObjectName("scDisplayLabel");
        sizePolicy4.setHeightForWidth(scDisplayLabel->sizePolicy().hasHeightForWidth());
        scDisplayLabel->setSizePolicy(sizePolicy4);
        scDisplayLabel->setMinimumSize(QSize(30, 18));
        scDisplayLabel->setMaximumSize(QSize(30, 18));
        scDisplayLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        DisplayRangeGrid->addWidget(scDisplayLabel, 1, 0, 1, 1);

        minDisplayLabel->raise();
        scmin_spin->raise();
        scmax_spin->raise();
        maxDisplayLabel->raise();
        raw_min_spin->raise();
        raw_max_spin->raise();
        colormapLabel->raise();
        sc_colormap_combo->raise();
        raw_colormap_combo->raise();
        show_SC_check->raise();
        show_raw_check->raise();
        label_14->raise();
        scColorbar_checkBox->raise();
        rawColorbar_checkBox->raise();
        scDisplayLabel->raise();
        rawDisplayLabel->raise();
        label_15->raise();
        horizontalLayoutWidget_2 = new QWidget(DisplayRangeGroup);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(10, 100, 301, 25));
        DisplayRangeExtra = new QHBoxLayout(horizontalLayoutWidget_2);
        DisplayRangeExtra->setObjectName("DisplayRangeExtra");
        DisplayRangeExtra->setContentsMargins(0, 0, 3, 0);
        satPixelColorLabel = new QLabel(horizontalLayoutWidget_2);
        satPixelColorLabel->setObjectName("satPixelColorLabel");
        satPixelColorLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        DisplayRangeExtra->addWidget(satPixelColorLabel);

        SatPixelColor_comboBox = new QComboBox(horizontalLayoutWidget_2);
        SatPixelColor_comboBox->addItem(QString());
        SatPixelColor_comboBox->addItem(QString());
        SatPixelColor_comboBox->addItem(QString());
        SatPixelColor_comboBox->addItem(QString());
        SatPixelColor_comboBox->setObjectName("SatPixelColor_comboBox");
        sizePolicy4.setHeightForWidth(SatPixelColor_comboBox->sizePolicy().hasHeightForWidth());
        SatPixelColor_comboBox->setSizePolicy(sizePolicy4);
        SatPixelColor_comboBox->setMinimumSize(QSize(75, 18));
        SatPixelColor_comboBox->setMaximumSize(QSize(75, 18));

        DisplayRangeExtra->addWidget(SatPixelColor_comboBox);

        RatioImageGroup = new QGroupBox(Display_page);
        RatioImageGroup->setObjectName("RatioImageGroup");
        RatioImageGroup->setGeometry(QRect(10, 310, 271, 101));
        gridLayoutWidget_6 = new QWidget(RatioImageGroup);
        gridLayoutWidget_6->setObjectName("gridLayoutWidget_6");
        gridLayoutWidget_6->setGeometry(QRect(10, 50, 251, 41));
        RatioImageGrid = new QGridLayout(gridLayoutWidget_6);
        RatioImageGrid->setObjectName("RatioImageGrid");
        RatioImageGrid->setContentsMargins(0, 0, 0, 0);
        ratio_colormap_combo = new QComboBox(gridLayoutWidget_6);
        ratio_colormap_combo->addItem(QString());
        ratio_colormap_combo->addItem(QString());
        ratio_colormap_combo->addItem(QString());
        ratio_colormap_combo->addItem(QString());
        ratio_colormap_combo->addItem(QString());
        ratio_colormap_combo->setObjectName("ratio_colormap_combo");
        ratio_colormap_combo->setEnabled(false);
        ratio_colormap_combo->setMinimumSize(QSize(75, 18));
        ratio_colormap_combo->setMaximumSize(QSize(75, 18));

        RatioImageGrid->addWidget(ratio_colormap_combo, 1, 2, 1, 1);

        ratio_max_spin = new QDoubleSpinBox(gridLayoutWidget_6);
        ratio_max_spin->setObjectName("ratio_max_spin");
        ratio_max_spin->setEnabled(false);
        sizePolicy4.setHeightForWidth(ratio_max_spin->sizePolicy().hasHeightForWidth());
        ratio_max_spin->setSizePolicy(sizePolicy4);
        ratio_max_spin->setMinimumSize(QSize(60, 18));
        ratio_max_spin->setMaximumSize(QSize(60, 18));
        ratio_max_spin->setDecimals(3);
        ratio_max_spin->setMaximum(100000.000000000000000);
        ratio_max_spin->setValue(1.500000000000000);

        RatioImageGrid->addWidget(ratio_max_spin, 1, 1, 1, 1);

        ratio_min_spin = new QDoubleSpinBox(gridLayoutWidget_6);
        ratio_min_spin->setObjectName("ratio_min_spin");
        ratio_min_spin->setEnabled(false);
        sizePolicy4.setHeightForWidth(ratio_min_spin->sizePolicy().hasHeightForWidth());
        ratio_min_spin->setSizePolicy(sizePolicy4);
        ratio_min_spin->setMinimumSize(QSize(60, 18));
        ratio_min_spin->setMaximumSize(QSize(60, 18));
        ratio_min_spin->setDecimals(3);
        ratio_min_spin->setMaximum(100000.000000000000000);
        ratio_min_spin->setValue(0.500000000000000);

        RatioImageGrid->addWidget(ratio_min_spin, 1, 0, 1, 1);

        ratioMinLabel = new QLabel(gridLayoutWidget_6);
        ratioMinLabel->setObjectName("ratioMinLabel");
        ratioMinLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(ratioMinLabel->sizePolicy().hasHeightForWidth());
        ratioMinLabel->setSizePolicy(sizePolicy4);
        ratioMinLabel->setMinimumSize(QSize(60, 13));
        ratioMinLabel->setMaximumSize(QSize(60, 13));
        ratioMinLabel->setAlignment(Qt::AlignCenter);

        RatioImageGrid->addWidget(ratioMinLabel, 0, 0, 1, 1);

        ratioMaxLabel = new QLabel(gridLayoutWidget_6);
        ratioMaxLabel->setObjectName("ratioMaxLabel");
        ratioMaxLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(ratioMaxLabel->sizePolicy().hasHeightForWidth());
        ratioMaxLabel->setSizePolicy(sizePolicy4);
        ratioMaxLabel->setMinimumSize(QSize(60, 13));
        ratioMaxLabel->setMaximumSize(QSize(60, 13));
        ratioMaxLabel->setAlignment(Qt::AlignCenter);

        RatioImageGrid->addWidget(ratioMaxLabel, 0, 1, 1, 1);

        ratioColormapLabel = new QLabel(gridLayoutWidget_6);
        ratioColormapLabel->setObjectName("ratioColormapLabel");
        ratioColormapLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(ratioColormapLabel->sizePolicy().hasHeightForWidth());
        ratioColormapLabel->setSizePolicy(sizePolicy4);
        ratioColormapLabel->setMinimumSize(QSize(75, 13));
        ratioColormapLabel->setMaximumSize(QSize(75, 13));
        ratioColormapLabel->setAlignment(Qt::AlignCenter);

        RatioImageGrid->addWidget(ratioColormapLabel, 0, 2, 1, 1);

        horizontalLayoutWidget_5 = new QWidget(RatioImageGroup);
        horizontalLayoutWidget_5->setObjectName("horizontalLayoutWidget_5");
        horizontalLayoutWidget_5->setGeometry(QRect(10, 20, 251, 21));
        RatioImageExtra = new QHBoxLayout(horizontalLayoutWidget_5);
        RatioImageExtra->setObjectName("RatioImageExtra");
        RatioImageExtra->setContentsMargins(0, 0, 0, 0);
        enable_ratio_image_checkbox = new QCheckBox(horizontalLayoutWidget_5);
        enable_ratio_image_checkbox->setObjectName("enable_ratio_image_checkbox");
        enable_ratio_image_checkbox->setEnabled(false);
        sizePolicy4.setHeightForWidth(enable_ratio_image_checkbox->sizePolicy().hasHeightForWidth());
        enable_ratio_image_checkbox->setSizePolicy(sizePolicy4);
        enable_ratio_image_checkbox->setMinimumSize(QSize(75, 18));
        enable_ratio_image_checkbox->setMaximumSize(QSize(75, 18));

        RatioImageExtra->addWidget(enable_ratio_image_checkbox);

        autoset_baseline_check = new QCheckBox(horizontalLayoutWidget_5);
        autoset_baseline_check->setObjectName("autoset_baseline_check");
        autoset_baseline_check->setEnabled(false);
        autoset_baseline_check->setMinimumSize(QSize(0, 18));
        autoset_baseline_check->setMaximumSize(QSize(16777215, 18));
        autoset_baseline_check->setChecked(true);

        RatioImageExtra->addWidget(autoset_baseline_check);

        groupBox_8 = new QGroupBox(Display_page);
        groupBox_8->setObjectName("groupBox_8");
        groupBox_8->setGeometry(QRect(10, 410, 271, 111));
        layoutWidget_5 = new QWidget(groupBox_8);
        layoutWidget_5->setObjectName("layoutWidget_5");
        layoutWidget_5->setGeometry(QRect(10, 20, 251, 81));
        _2 = new QGridLayout(layoutWidget_5);
        _2->setObjectName("_2");
        _2->setContentsMargins(0, 0, 0, 0);
        baseline_list_combo = new QComboBox(layoutWidget_5);
        baseline_list_combo->setObjectName("baseline_list_combo");
        baseline_list_combo->setEnabled(false);
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(baseline_list_combo->sizePolicy().hasHeightForWidth());
        baseline_list_combo->setSizePolicy(sizePolicy6);
        baseline_list_combo->setMinimumSize(QSize(0, 18));
        baseline_list_combo->setMaximumSize(QSize(16777215, 18));
        baseline_list_combo->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        _2->addWidget(baseline_list_combo, 1, 1, 1, 2);

        sc_list_combo = new QComboBox(layoutWidget_5);
        sc_list_combo->setObjectName("sc_list_combo");
        sc_list_combo->setEnabled(false);
        sizePolicy6.setHeightForWidth(sc_list_combo->sizePolicy().hasHeightForWidth());
        sc_list_combo->setSizePolicy(sizePolicy6);
        sc_list_combo->setMinimumSize(QSize(0, 18));
        sc_list_combo->setMaximumSize(QSize(16777215, 18));

        _2->addWidget(sc_list_combo, 2, 1, 1, 2);

        clear_baseline_list_button = new QToolButton(layoutWidget_5);
        clear_baseline_list_button->setObjectName("clear_baseline_list_button");
        clear_baseline_list_button->setEnabled(false);
        clear_baseline_list_button->setMinimumSize(QSize(40, 18));
        clear_baseline_list_button->setMaximumSize(QSize(40, 18));

        _2->addWidget(clear_baseline_list_button, 1, 3, 1, 1);

        clear_image_list_button = new QToolButton(layoutWidget_5);
        clear_image_list_button->setObjectName("clear_image_list_button");
        clear_image_list_button->setEnabled(false);
        clear_image_list_button->setMinimumSize(QSize(40, 18));
        clear_image_list_button->setMaximumSize(QSize(40, 18));

        _2->addWidget(clear_image_list_button, 2, 3, 1, 1);

        baselineListLabel = new QLabel(layoutWidget_5);
        baselineListLabel->setObjectName("baselineListLabel");
        baselineListLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(baselineListLabel->sizePolicy().hasHeightForWidth());
        baselineListLabel->setSizePolicy(sizePolicy4);
        baselineListLabel->setMinimumSize(QSize(40, 15));
        baselineListLabel->setMaximumSize(QSize(40, 15));
        baselineListLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        _2->addWidget(baselineListLabel, 1, 0, 1, 1);

        scListLabel = new QLabel(layoutWidget_5);
        scListLabel->setObjectName("scListLabel");
        scListLabel->setEnabled(false);
        sizePolicy4.setHeightForWidth(scListLabel->sizePolicy().hasHeightForWidth());
        scListLabel->setSizePolicy(sizePolicy4);
        scListLabel->setMinimumSize(QSize(40, 15));
        scListLabel->setMaximumSize(QSize(40, 15));
        scListLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        _2->addWidget(scListLabel, 2, 0, 1, 1);

        rawListLabel = new QLabel(layoutWidget_5);
        rawListLabel->setObjectName("rawListLabel");
        sizePolicy4.setHeightForWidth(rawListLabel->sizePolicy().hasHeightForWidth());
        rawListLabel->setSizePolicy(sizePolicy4);
        rawListLabel->setMinimumSize(QSize(40, 15));
        rawListLabel->setMaximumSize(QSize(40, 15));
        rawListLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        _2->addWidget(rawListLabel, 0, 0, 1, 1);

        raw_list_combo = new QComboBox(layoutWidget_5);
        raw_list_combo->setObjectName("raw_list_combo");
        raw_list_combo->setMinimumSize(QSize(0, 18));
        raw_list_combo->setMaximumSize(QSize(16777215, 18));

        _2->addWidget(raw_list_combo, 0, 1, 1, 2);

        clear_raw_list_button = new QToolButton(layoutWidget_5);
        clear_raw_list_button->setObjectName("clear_raw_list_button");
        clear_raw_list_button->setMinimumSize(QSize(40, 18));
        clear_raw_list_button->setMaximumSize(QSize(40, 18));

        _2->addWidget(clear_raw_list_button, 0, 3, 1, 1);

        stackedWidget->addWidget(Display_page);
        ROI_editor_page = new QWidget();
        ROI_editor_page->setObjectName("ROI_editor_page");
        ROIEditorGroup = new QGroupBox(ROI_editor_page);
        ROIEditorGroup->setObjectName("ROIEditorGroup");
        ROIEditorGroup->setGeometry(QRect(0, 10, 141, 171));
        verticalLayoutWidget = new QWidget(ROIEditorGroup);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(100, 20, 31, 111));
        ROIEditorTools = new QVBoxLayout(verticalLayoutWidget);
        ROIEditorTools->setObjectName("ROIEditorTools");
        ROIEditorTools->setContentsMargins(0, 0, 0, 0);
        add_ROI_button = new QToolButton(verticalLayoutWidget);
        add_ROI_button->setObjectName("add_ROI_button");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Add"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        add_ROI_button->setIcon(icon5);

        ROIEditorTools->addWidget(add_ROI_button);

        remove_ROI_button = new QToolButton(verticalLayoutWidget);
        remove_ROI_button->setObjectName("remove_ROI_button");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Remove"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        remove_ROI_button->setIcon(icon6);

        ROIEditorTools->addWidget(remove_ROI_button);

        ROI_color_button = new QToolButton(verticalLayoutWidget);
        ROI_color_button->setObjectName("ROI_color_button");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Color Picker"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ROI_color_button->setIcon(icon7);

        ROIEditorTools->addWidget(ROI_color_button);

        ROI_list_widget = new QListWidget(ROIEditorGroup);
        ROI_list_widget->setObjectName("ROI_list_widget");
        ROI_list_widget->setGeometry(QRect(10, 20, 78, 111));
        ROI_show_check = new QCheckBox(ROIEditorGroup);
        ROI_show_check->setObjectName("ROI_show_check");
        ROI_show_check->setGeometry(QRect(10, 140, 101, 19));
        ROI_show_check->setChecked(true);
        roiPlotGroup = new QGroupBox(ROI_editor_page);
        roiPlotGroup->setObjectName("roiPlotGroup");
        roiPlotGroup->setGeometry(QRect(170, 10, 251, 171));
        layoutWidget_4 = new QWidget(roiPlotGroup);
        layoutWidget_4->setObjectName("layoutWidget_4");
        layoutWidget_4->setGeometry(QRect(10, 80, 249, 81));
        roiPlotDisplay = new QGridLayout(layoutWidget_4);
        roiPlotDisplay->setObjectName("roiPlotDisplay");
        roiPlotDisplay->setContentsMargins(0, 0, 0, 0);
        roiPlotMaxLabel = new QLabel(layoutWidget_4);
        roiPlotMaxLabel->setObjectName("roiPlotMaxLabel");
        roiPlotMaxLabel->setEnabled(false);
        sizePolicy3.setHeightForWidth(roiPlotMaxLabel->sizePolicy().hasHeightForWidth());
        roiPlotMaxLabel->setSizePolicy(sizePolicy3);
        roiPlotMaxLabel->setMinimumSize(QSize(0, 13));
        roiPlotMaxLabel->setMaximumSize(QSize(16777215, 13));
        roiPlotMaxLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        roiPlotDisplay->addWidget(roiPlotMaxLabel, 0, 3, 1, 1);

        roiPlotMinLabel = new QLabel(layoutWidget_4);
        roiPlotMinLabel->setObjectName("roiPlotMinLabel");
        roiPlotMinLabel->setEnabled(false);
        sizePolicy3.setHeightForWidth(roiPlotMinLabel->sizePolicy().hasHeightForWidth());
        roiPlotMinLabel->setSizePolicy(sizePolicy3);
        roiPlotMinLabel->setMinimumSize(QSize(0, 13));
        roiPlotMinLabel->setMaximumSize(QSize(16777215, 13));
        roiPlotMinLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        roiPlotDisplay->addWidget(roiPlotMinLabel, 0, 2, 1, 1);

        roiplot_ymax_spin = new QDoubleSpinBox(layoutWidget_4);
        roiplot_ymax_spin->setObjectName("roiplot_ymax_spin");
        roiplot_ymax_spin->setEnabled(false);
        sizePolicy4.setHeightForWidth(roiplot_ymax_spin->sizePolicy().hasHeightForWidth());
        roiplot_ymax_spin->setSizePolicy(sizePolicy4);
        roiplot_ymax_spin->setMinimumSize(QSize(65, 20));
        roiplot_ymax_spin->setMaximumSize(QSize(65, 20));
        roiplot_ymax_spin->setDecimals(3);
        roiplot_ymax_spin->setMaximum(1.000000000000000);
        roiplot_ymax_spin->setSingleStep(0.010000000000000);
        roiplot_ymax_spin->setValue(1.000000000000000);

        roiPlotDisplay->addWidget(roiplot_ymax_spin, 1, 3, 1, 1);

        roiplot_autoscale_check = new QCheckBox(layoutWidget_4);
        roiplot_autoscale_check->setObjectName("roiplot_autoscale_check");
        roiplot_autoscale_check->setEnabled(false);
        sizePolicy4.setHeightForWidth(roiplot_autoscale_check->sizePolicy().hasHeightForWidth());
        roiplot_autoscale_check->setSizePolicy(sizePolicy4);
        roiplot_autoscale_check->setChecked(true);

        roiPlotDisplay->addWidget(roiplot_autoscale_check, 1, 1, 1, 1);

        roiplot_rel_ymax_spin = new QDoubleSpinBox(layoutWidget_4);
        roiplot_rel_ymax_spin->setObjectName("roiplot_rel_ymax_spin");
        roiplot_rel_ymax_spin->setEnabled(false);
        QSizePolicy sizePolicy7(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(roiplot_rel_ymax_spin->sizePolicy().hasHeightForWidth());
        roiplot_rel_ymax_spin->setSizePolicy(sizePolicy7);
        roiplot_rel_ymax_spin->setMinimumSize(QSize(65, 20));
        roiplot_rel_ymax_spin->setMaximumSize(QSize(65, 20));
        roiplot_rel_ymax_spin->setDecimals(3);
        roiplot_rel_ymax_spin->setMaximum(1000000000.000000000000000);
        roiplot_rel_ymax_spin->setSingleStep(0.010000000000000);
        roiplot_rel_ymax_spin->setValue(2.000000000000000);

        roiPlotDisplay->addWidget(roiplot_rel_ymax_spin, 2, 3, 1, 1);

        roiplot_rel_autoscale_check = new QCheckBox(layoutWidget_4);
        roiplot_rel_autoscale_check->setObjectName("roiplot_rel_autoscale_check");
        roiplot_rel_autoscale_check->setEnabled(false);
        sizePolicy4.setHeightForWidth(roiplot_rel_autoscale_check->sizePolicy().hasHeightForWidth());
        roiplot_rel_autoscale_check->setSizePolicy(sizePolicy4);
        roiplot_rel_autoscale_check->setChecked(true);

        roiPlotDisplay->addWidget(roiplot_rel_autoscale_check, 2, 1, 1, 1);

        roiplot_rel_ymin_spin = new QDoubleSpinBox(layoutWidget_4);
        roiplot_rel_ymin_spin->setObjectName("roiplot_rel_ymin_spin");
        roiplot_rel_ymin_spin->setEnabled(false);
        sizePolicy4.setHeightForWidth(roiplot_rel_ymin_spin->sizePolicy().hasHeightForWidth());
        roiplot_rel_ymin_spin->setSizePolicy(sizePolicy4);
        roiplot_rel_ymin_spin->setMinimumSize(QSize(65, 20));
        roiplot_rel_ymin_spin->setMaximumSize(QSize(65, 20));
        roiplot_rel_ymin_spin->setDecimals(3);
        roiplot_rel_ymin_spin->setMaximum(10.000000000000000);
        roiplot_rel_ymin_spin->setSingleStep(0.010000000000000);

        roiPlotDisplay->addWidget(roiplot_rel_ymin_spin, 2, 2, 1, 1);

        roiPlotRelativeLabel = new QLabel(layoutWidget_4);
        roiPlotRelativeLabel->setObjectName("roiPlotRelativeLabel");
        roiPlotRelativeLabel->setEnabled(false);
        roiPlotRelativeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        roiPlotDisplay->addWidget(roiPlotRelativeLabel, 2, 0, 1, 1);

        roiplot_ymin_spin = new QDoubleSpinBox(layoutWidget_4);
        roiplot_ymin_spin->setObjectName("roiplot_ymin_spin");
        roiplot_ymin_spin->setEnabled(false);
        sizePolicy4.setHeightForWidth(roiplot_ymin_spin->sizePolicy().hasHeightForWidth());
        roiplot_ymin_spin->setSizePolicy(sizePolicy4);
        roiplot_ymin_spin->setMinimumSize(QSize(65, 20));
        roiplot_ymin_spin->setMaximumSize(QSize(65, 20));
        roiplot_ymin_spin->setDecimals(3);
        roiplot_ymin_spin->setMaximum(10.000000000000000);
        roiplot_ymin_spin->setSingleStep(0.010000000000000);

        roiPlotDisplay->addWidget(roiplot_ymin_spin, 1, 2, 1, 1);

        roiPlotSCLabel = new QLabel(layoutWidget_4);
        roiPlotSCLabel->setObjectName("roiPlotSCLabel");
        roiPlotSCLabel->setEnabled(false);
        sizePolicy3.setHeightForWidth(roiPlotSCLabel->sizePolicy().hasHeightForWidth());
        roiPlotSCLabel->setSizePolicy(sizePolicy3);
        roiPlotSCLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        roiPlotDisplay->addWidget(roiPlotSCLabel, 1, 0, 1, 1);

        roiPlotAutoLabel = new QLabel(layoutWidget_4);
        roiPlotAutoLabel->setObjectName("roiPlotAutoLabel");
        roiPlotAutoLabel->setEnabled(false);
        sizePolicy3.setHeightForWidth(roiPlotAutoLabel->sizePolicy().hasHeightForWidth());
        roiPlotAutoLabel->setSizePolicy(sizePolicy3);
        roiPlotAutoLabel->setMinimumSize(QSize(0, 13));
        roiPlotAutoLabel->setMaximumSize(QSize(16777215, 13));
        roiPlotAutoLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        roiPlotDisplay->addWidget(roiPlotAutoLabel, 0, 1, 1, 1);

        verticalLayoutWidget_2 = new QWidget(roiPlotGroup);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(10, 20, 67, 61));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        roiPlotCheckbox = new QCheckBox(verticalLayoutWidget_2);
        roiPlotCheckbox->setObjectName("roiPlotCheckbox");

        verticalLayout->addWidget(roiPlotCheckbox);

        roiPlotSaveCheckbox = new QCheckBox(verticalLayoutWidget_2);
        roiPlotSaveCheckbox->setObjectName("roiPlotSaveCheckbox");
        roiPlotSaveCheckbox->setEnabled(false);
        roiPlotSaveCheckbox->setCheckable(true);
        roiPlotSaveCheckbox->setChecked(false);

        verticalLayout->addWidget(roiPlotSaveCheckbox);

        verticalLayoutWidget_5 = new QWidget(roiPlotGroup);
        verticalLayoutWidget_5->setObjectName("verticalLayoutWidget_5");
        verticalLayoutWidget_5->setGeometry(QRect(70, 20, 171, 61));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        roiPlotEnable = new QHBoxLayout();
        roiPlotEnable->setSpacing(4);
        roiPlotEnable->setObjectName("roiPlotEnable");
        roiPlotEnable->setSizeConstraint(QLayout::SetDefaultConstraint);
        roiPlotHistoryCheckbox = new QCheckBox(verticalLayoutWidget_5);
        roiPlotHistoryCheckbox->setObjectName("roiPlotHistoryCheckbox");
        roiPlotHistoryCheckbox->setEnabled(false);
        QSizePolicy sizePolicy8(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(roiPlotHistoryCheckbox->sizePolicy().hasHeightForWidth());
        roiPlotHistoryCheckbox->setSizePolicy(sizePolicy8);
        roiPlotHistoryCheckbox->setMinimumSize(QSize(0, 0));
        roiPlotHistoryCheckbox->setMaximumSize(QSize(88, 16777215));
        roiPlotHistoryCheckbox->setChecked(true);

        roiPlotEnable->addWidget(roiPlotHistoryCheckbox);

        roiPlotLimitLabel = new QLabel(verticalLayoutWidget_5);
        roiPlotLimitLabel->setObjectName("roiPlotLimitLabel");
        roiPlotLimitLabel->setEnabled(false);
        QSizePolicy sizePolicy9(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(roiPlotLimitLabel->sizePolicy().hasHeightForWidth());
        roiPlotLimitLabel->setSizePolicy(sizePolicy9);
        roiPlotLimitLabel->setMaximumSize(QSize(20, 16777215));
        QFont font;
        font.setPointSize(8);
        roiPlotLimitLabel->setFont(font);
        roiPlotLimitLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        roiPlotLimitLabel->setIndent(0);

        roiPlotEnable->addWidget(roiPlotLimitLabel);

        roiPlotLimitSpin = new QSpinBox(verticalLayoutWidget_5);
        roiPlotLimitSpin->setObjectName("roiPlotLimitSpin");
        roiPlotLimitSpin->setEnabled(false);
        sizePolicy4.setHeightForWidth(roiPlotLimitSpin->sizePolicy().hasHeightForWidth());
        roiPlotLimitSpin->setSizePolicy(sizePolicy4);
        roiPlotLimitSpin->setMinimumSize(QSize(50, 20));
        roiPlotLimitSpin->setMaximumSize(QSize(40, 20));
        roiPlotLimitSpin->setMinimum(1);
        roiPlotLimitSpin->setMaximum(9999);
        roiPlotLimitSpin->setValue(100);

        roiPlotEnable->addWidget(roiPlotLimitSpin);


        verticalLayout_3->addLayout(roiPlotEnable);

        roiPlotBaseline = new QHBoxLayout();
        roiPlotBaseline->setSpacing(4);
        roiPlotBaseline->setObjectName("roiPlotBaseline");
        roiPlotBaselineLabel = new QLabel(verticalLayoutWidget_5);
        roiPlotBaselineLabel->setObjectName("roiPlotBaselineLabel");
        roiPlotBaselineLabel->setEnabled(false);
        roiPlotBaselineLabel->setMaximumSize(QSize(56, 16777215));
        roiPlotBaselineLabel->setFont(font);
        roiPlotBaselineLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        roiPlotBaseline->addWidget(roiPlotBaselineLabel);

        roiPlotBaselineStart = new QSpinBox(verticalLayoutWidget_5);
        roiPlotBaselineStart->setObjectName("roiPlotBaselineStart");
        roiPlotBaselineStart->setEnabled(false);
        roiPlotBaselineStart->setMaximumSize(QSize(50, 16777215));
        roiPlotBaselineStart->setMaximum(10000);

        roiPlotBaseline->addWidget(roiPlotBaselineStart);

        roiPlotBaselineEnd = new QSpinBox(verticalLayoutWidget_5);
        roiPlotBaselineEnd->setObjectName("roiPlotBaselineEnd");
        roiPlotBaselineEnd->setEnabled(false);
        roiPlotBaselineEnd->setMaximumSize(QSize(50, 16777215));
        roiPlotBaselineEnd->setMinimum(1);
        roiPlotBaselineEnd->setMaximum(10000);
        roiPlotBaselineEnd->setValue(1);

        roiPlotBaseline->addWidget(roiPlotBaselineEnd);


        verticalLayout_3->addLayout(roiPlotBaseline);

        stackedWidget->addWidget(ROI_editor_page);
        DMD_page = new QWidget();
        DMD_page->setObjectName("DMD_page");
        dmdBoxSystem = new QGroupBox(DMD_page);
        dmdBoxSystem->setObjectName("dmdBoxSystem");
        dmdBoxSystem->setGeometry(QRect(0, 20, 111, 121));
        verticalLayoutWidget_7 = new QWidget(dmdBoxSystem);
        verticalLayoutWidget_7->setObjectName("verticalLayoutWidget_7");
        verticalLayoutWidget_7->setGeometry(QRect(10, 20, 95, 100));
        verticalLayout_10 = new QVBoxLayout(verticalLayoutWidget_7);
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        dmdInitializeButton = new QPushButton(verticalLayoutWidget_7);
        dmdInitializeButton->setObjectName("dmdInitializeButton");

        verticalLayout_10->addWidget(dmdInitializeButton);

        dmdInfoButton = new QPushButton(verticalLayoutWidget_7);
        dmdInfoButton->setObjectName("dmdInfoButton");

        verticalLayout_10->addWidget(dmdInfoButton);

        dmdRegistrationButton = new QPushButton(verticalLayoutWidget_7);
        dmdRegistrationButton->setObjectName("dmdRegistrationButton");

        verticalLayout_10->addWidget(dmdRegistrationButton);

        dmdBoxROI = new QGroupBox(DMD_page);
        dmdBoxROI->setObjectName("dmdBoxROI");
        dmdBoxROI->setGeometry(QRect(130, 20, 111, 121));
        verticalLayoutWidget_8 = new QWidget(dmdBoxROI);
        verticalLayoutWidget_8->setObjectName("verticalLayoutWidget_8");
        verticalLayoutWidget_8->setGeometry(QRect(10, 20, 95, 100));
        verticalLayout_8 = new QVBoxLayout(verticalLayoutWidget_8);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        loadROIButton = new QPushButton(verticalLayoutWidget_8);
        loadROIButton->setObjectName("loadROIButton");

        verticalLayout_8->addWidget(loadROIButton);

        saveROIButton = new QPushButton(verticalLayoutWidget_8);
        saveROIButton->setObjectName("saveROIButton");

        verticalLayout_8->addWidget(saveROIButton);

        clearROIButton = new QPushButton(verticalLayoutWidget_8);
        clearROIButton->setObjectName("clearROIButton");

        verticalLayout_8->addWidget(clearROIButton);

        dmdBoxSequence = new QGroupBox(DMD_page);
        dmdBoxSequence->setObjectName("dmdBoxSequence");
        dmdBoxSequence->setGeometry(QRect(250, 20, 201, 201));
        verticalLayoutWidget_9 = new QWidget(dmdBoxSequence);
        verticalLayoutWidget_9->setObjectName("verticalLayoutWidget_9");
        verticalLayoutWidget_9->setGeometry(QRect(10, 20, 207, 181));
        verticalLayout_11 = new QVBoxLayout(verticalLayoutWidget_9);
        verticalLayout_11->setObjectName("verticalLayout_11");
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName("formLayout_4");
        formLayout_4->setSizeConstraint(QLayout::SetFixedSize);
        formLayout_4->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_4->setLabelAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        formLayout_4->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        dmdExposureLabel = new QLabel(verticalLayoutWidget_9);
        dmdExposureLabel->setObjectName("dmdExposureLabel");

        formLayout_4->setWidget(0, QFormLayout::LabelRole, dmdExposureLabel);

        dmdExposureSpin = new QDoubleSpinBox(verticalLayoutWidget_9);
        dmdExposureSpin->setObjectName("dmdExposureSpin");
        dmdExposureSpin->setEnabled(true);
        dmdExposureSpin->setDecimals(4);
        dmdExposureSpin->setMaximum(2.000000000000000);
        dmdExposureSpin->setSingleStep(0.000000000000000);
        dmdExposureSpin->setValue(0.100000000000000);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, dmdExposureSpin);

        dmdTotalTimeLabel = new QLabel(verticalLayoutWidget_9);
        dmdTotalTimeLabel->setObjectName("dmdTotalTimeLabel");

        formLayout_4->setWidget(1, QFormLayout::LabelRole, dmdTotalTimeLabel);

        dmdTotalTimeSpin = new QDoubleSpinBox(verticalLayoutWidget_9);
        dmdTotalTimeSpin->setObjectName("dmdTotalTimeSpin");
        dmdTotalTimeSpin->setEnabled(true);
        dmdTotalTimeSpin->setMaximum(1000000000.000000000000000);
        dmdTotalTimeSpin->setValue(10.000000000000000);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, dmdTotalTimeSpin);

        dmdCycleLabel = new QLabel(verticalLayoutWidget_9);
        dmdCycleLabel->setObjectName("dmdCycleLabel");

        formLayout_4->setWidget(2, QFormLayout::LabelRole, dmdCycleLabel);

        dmdCycleSpin = new QDoubleSpinBox(verticalLayoutWidget_9);
        dmdCycleSpin->setObjectName("dmdCycleSpin");
        dmdCycleSpin->setMaximum(1000000.000000000000000);
        dmdCycleSpin->setSingleStep(0.010000000000000);
        dmdCycleSpin->setValue(100.000000000000000);

        formLayout_4->setWidget(2, QFormLayout::FieldRole, dmdCycleSpin);

        dmdROICounter = new QSpinBox(verticalLayoutWidget_9);
        dmdROICounter->setObjectName("dmdROICounter");
        dmdROICounter->setEnabled(true);
        sizePolicy4.setHeightForWidth(dmdROICounter->sizePolicy().hasHeightForWidth());
        dmdROICounter->setSizePolicy(sizePolicy4);
        dmdROICounter->setReadOnly(true);
        dmdROICounter->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dmdROICounter->setMaximum(96);

        formLayout_4->setWidget(3, QFormLayout::FieldRole, dmdROICounter);

        dmdROICounterLabel = new QLabel(verticalLayoutWidget_9);
        dmdROICounterLabel->setObjectName("dmdROICounterLabel");

        formLayout_4->setWidget(3, QFormLayout::LabelRole, dmdROICounterLabel);


        verticalLayout_11->addLayout(formLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        startPatternSequenceButton = new QPushButton(verticalLayoutWidget_9);
        startPatternSequenceButton->setObjectName("startPatternSequenceButton");
        sizePolicy4.setHeightForWidth(startPatternSequenceButton->sizePolicy().hasHeightForWidth());
        startPatternSequenceButton->setSizePolicy(sizePolicy4);

        horizontalLayout_5->addWidget(startPatternSequenceButton);


        verticalLayout_11->addLayout(horizontalLayout_5);

        dmdProgressBar = new QProgressBar(verticalLayoutWidget_9);
        dmdProgressBar->setObjectName("dmdProgressBar");
        dmdProgressBar->setValue(0);
        dmdProgressBar->setTextVisible(false);

        verticalLayout_11->addWidget(dmdProgressBar);

        dmdBoxTransform = new QGroupBox(DMD_page);
        dmdBoxTransform->setObjectName("dmdBoxTransform");
        dmdBoxTransform->setGeometry(QRect(0, 150, 241, 171));
        verticalLayoutWidget_6 = new QWidget(dmdBoxTransform);
        verticalLayoutWidget_6->setObjectName("verticalLayoutWidget_6");
        verticalLayoutWidget_6->setGeometry(QRect(10, 20, 221, 142));
        verticalLayout_9 = new QVBoxLayout(verticalLayoutWidget_6);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        loadTransformButton = new QPushButton(verticalLayoutWidget_6);
        loadTransformButton->setObjectName("loadTransformButton");

        horizontalLayout_4->addWidget(loadTransformButton);

        saveTransformButton = new QPushButton(verticalLayoutWidget_6);
        saveTransformButton->setObjectName("saveTransformButton");

        horizontalLayout_4->addWidget(saveTransformButton);


        verticalLayout_9->addLayout(horizontalLayout_4);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName("verticalLayout_12");
        verticalLayout_12->setContentsMargins(60, -1, -1, -1);
        useTransformCheckbox = new QCheckBox(verticalLayoutWidget_6);
        useTransformCheckbox->setObjectName("useTransformCheckbox");
        useTransformCheckbox->setLayoutDirection(Qt::LeftToRight);
        useTransformCheckbox->setChecked(true);

        verticalLayout_12->addWidget(useTransformCheckbox);


        verticalLayout_9->addLayout(verticalLayout_12);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(10, -1, 10, -1);
        formLayout_5 = new QFormLayout();
        formLayout_5->setObjectName("formLayout_5");
        formLayout_5->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_5->setLabelAlignment(Qt::AlignCenter);
        formLayout_5->setFormAlignment(Qt::AlignHCenter|Qt::AlignTop);
        formLayout_5->setHorizontalSpacing(5);
        formLayout_5->setVerticalSpacing(5);
        sxLabel = new QLabel(verticalLayoutWidget_6);
        sxLabel->setObjectName("sxLabel");

        formLayout_5->setWidget(0, QFormLayout::LabelRole, sxLabel);

        sxText = new QTextBrowser(verticalLayoutWidget_6);
        sxText->setObjectName("sxText");
        sizePolicy4.setHeightForWidth(sxText->sizePolicy().hasHeightForWidth());
        sxText->setSizePolicy(sizePolicy4);
        sxText->setMaximumSize(QSize(60, 20));
        QFont font1;
        font1.setPointSize(7);
        sxText->setFont(font1);
        sxText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        sxText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        sxText->setLineWrapMode(QTextEdit::NoWrap);

        formLayout_5->setWidget(0, QFormLayout::FieldRole, sxText);

        ryLabel = new QLabel(verticalLayoutWidget_6);
        ryLabel->setObjectName("ryLabel");

        formLayout_5->setWidget(1, QFormLayout::LabelRole, ryLabel);

        ryText = new QTextBrowser(verticalLayoutWidget_6);
        ryText->setObjectName("ryText");
        sizePolicy4.setHeightForWidth(ryText->sizePolicy().hasHeightForWidth());
        ryText->setSizePolicy(sizePolicy4);
        ryText->setMaximumSize(QSize(60, 20));
        ryText->setFont(font1);
        ryText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ryText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ryText->setLineWrapMode(QTextEdit::NoWrap);

        formLayout_5->setWidget(1, QFormLayout::FieldRole, ryText);

        txLabel = new QLabel(verticalLayoutWidget_6);
        txLabel->setObjectName("txLabel");

        formLayout_5->setWidget(2, QFormLayout::LabelRole, txLabel);

        txText = new QTextBrowser(verticalLayoutWidget_6);
        txText->setObjectName("txText");
        sizePolicy4.setHeightForWidth(txText->sizePolicy().hasHeightForWidth());
        txText->setSizePolicy(sizePolicy4);
        txText->setMaximumSize(QSize(60, 20));
        txText->setFont(font1);
        txText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        txText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        txText->setLineWrapMode(QTextEdit::NoWrap);

        formLayout_5->setWidget(2, QFormLayout::FieldRole, txText);


        horizontalLayout_2->addLayout(formLayout_5);

        formLayout_6 = new QFormLayout();
        formLayout_6->setObjectName("formLayout_6");
        formLayout_6->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_6->setLabelAlignment(Qt::AlignCenter);
        formLayout_6->setFormAlignment(Qt::AlignHCenter|Qt::AlignTop);
        formLayout_6->setHorizontalSpacing(5);
        formLayout_6->setVerticalSpacing(5);
        rxLabel = new QLabel(verticalLayoutWidget_6);
        rxLabel->setObjectName("rxLabel");

        formLayout_6->setWidget(0, QFormLayout::LabelRole, rxLabel);

        rxText = new QTextBrowser(verticalLayoutWidget_6);
        rxText->setObjectName("rxText");
        sizePolicy4.setHeightForWidth(rxText->sizePolicy().hasHeightForWidth());
        rxText->setSizePolicy(sizePolicy4);
        rxText->setMaximumSize(QSize(60, 20));
        rxText->setFont(font1);
        rxText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        rxText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        rxText->setLineWrapMode(QTextEdit::NoWrap);

        formLayout_6->setWidget(0, QFormLayout::FieldRole, rxText);

        syLabel = new QLabel(verticalLayoutWidget_6);
        syLabel->setObjectName("syLabel");

        formLayout_6->setWidget(1, QFormLayout::LabelRole, syLabel);

        syText = new QTextBrowser(verticalLayoutWidget_6);
        syText->setObjectName("syText");
        sizePolicy4.setHeightForWidth(syText->sizePolicy().hasHeightForWidth());
        syText->setSizePolicy(sizePolicy4);
        syText->setMaximumSize(QSize(60, 20));
        syText->setFont(font1);
        syText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        syText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        syText->setLineWrapMode(QTextEdit::NoWrap);

        formLayout_6->setWidget(1, QFormLayout::FieldRole, syText);

        tyLabel = new QLabel(verticalLayoutWidget_6);
        tyLabel->setObjectName("tyLabel");

        formLayout_6->setWidget(2, QFormLayout::LabelRole, tyLabel);

        tyText = new QTextBrowser(verticalLayoutWidget_6);
        tyText->setObjectName("tyText");
        sizePolicy4.setHeightForWidth(tyText->sizePolicy().hasHeightForWidth());
        tyText->setSizePolicy(sizePolicy4);
        tyText->setMaximumSize(QSize(60, 20));
        tyText->setFont(font1);
        tyText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tyText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tyText->setLineWrapMode(QTextEdit::NoWrap);

        formLayout_6->setWidget(2, QFormLayout::FieldRole, tyText);


        horizontalLayout_2->addLayout(formLayout_6);


        verticalLayout_9->addLayout(horizontalLayout_2);

        dmdBoxTile = new QGroupBox(DMD_page);
        dmdBoxTile->setObjectName("dmdBoxTile");
        dmdBoxTile->setGeometry(QRect(250, 240, 181, 111));
        dmdTileButton = new QPushButton(dmdBoxTile);
        dmdTileButton->setObjectName("dmdTileButton");
        dmdTileButton->setEnabled(true);
        dmdTileButton->setGeometry(QRect(40, 80, 91, 23));
        dmdTileXSpin = new QSpinBox(dmdBoxTile);
        dmdTileXSpin->setObjectName("dmdTileXSpin");
        dmdTileXSpin->setGeometry(QRect(40, 20, 42, 22));
        dmdTileXSpin->setMinimum(1);
        dmdTileXSpin->setMaximum(96);
        dmdTileXSpin->setValue(12);
        dmdTileYSpin = new QSpinBox(dmdBoxTile);
        dmdTileYSpin->setObjectName("dmdTileYSpin");
        dmdTileYSpin->setGeometry(QRect(40, 50, 42, 22));
        dmdTileYSpin->setMinimum(1);
        dmdTileYSpin->setMaximum(96);
        dmdTileYSpin->setValue(8);
        dmdTileYLabel = new QLabel(dmdBoxTile);
        dmdTileYLabel->setObjectName("dmdTileYLabel");
        dmdTileYLabel->setGeometry(QRect(10, 50, 21, 20));
        dmdTileYLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dmdTileXLabel = new QLabel(dmdBoxTile);
        dmdTileXLabel->setObjectName("dmdTileXLabel");
        dmdTileXLabel->setGeometry(QRect(10, 20, 21, 21));
        dmdTileXLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dmdTileXGapSpin = new QSpinBox(dmdBoxTile);
        dmdTileXGapSpin->setObjectName("dmdTileXGapSpin");
        dmdTileXGapSpin->setGeometry(QRect(120, 20, 41, 22));
        dmdTileXGapSpin->setMaximum(999);
        dmdTileYGapSpin = new QSpinBox(dmdBoxTile);
        dmdTileYGapSpin->setObjectName("dmdTileYGapSpin");
        dmdTileYGapSpin->setGeometry(QRect(120, 50, 42, 22));
        dmdTileYGapSpin->setMaximum(999);
        dmdTileXGapSpinLabel = new QLabel(dmdBoxTile);
        dmdTileXGapSpinLabel->setObjectName("dmdTileXGapSpinLabel");
        dmdTileXGapSpinLabel->setGeometry(QRect(100, 20, 21, 21));
        dmdTileYGapSpinLabel = new QLabel(dmdBoxTile);
        dmdTileYGapSpinLabel->setObjectName("dmdTileYGapSpinLabel");
        dmdTileYGapSpinLabel->setGeometry(QRect(100, 50, 21, 21));
        showSinglePatternButton = new QPushButton(DMD_page);
        showSinglePatternButton->setObjectName("showSinglePatternButton");
        showSinglePatternButton->setGeometry(QRect(20, 340, 141, 31));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(false);
        showSinglePatternButton->setFont(font2);
        dmdMergeCheckbox = new QCheckBox(DMD_page);
        dmdMergeCheckbox->setObjectName("dmdMergeCheckbox");
        dmdMergeCheckbox->setGeometry(QRect(170, 340, 70, 31));
        stackedWidget->addWidget(DMD_page);

        horizontalLayout->addWidget(stackedWidget);

        QWidget::setTabOrder(camerasAvailableComboBox, duration_TypeComboBox);
        QWidget::setTabOrder(duration_TypeComboBox, acquireLength_lineEdit);
        QWidget::setTabOrder(acquireLength_lineEdit, outputfile_edit);
        QWidget::setTabOrder(outputfile_edit, outputfile_browse_button);
        QWidget::setTabOrder(outputfile_browse_button, save_sc_check);
        QWidget::setTabOrder(save_sc_check, save_raw_check);
        QWidget::setTabOrder(save_raw_check, save_sc_videocheckBox);
        QWidget::setTabOrder(save_sc_videocheckBox, save_overlay_videocheckBox);
        QWidget::setTabOrder(save_overlay_videocheckBox, save_input_videocheckBox);
        QWidget::setTabOrder(save_input_videocheckBox, exposure_time_spin);
        QWidget::setTabOrder(exposure_time_spin, trigger_combo);
        QWidget::setTabOrder(trigger_combo, left_spin);
        QWidget::setTabOrder(left_spin, top_spin);
        QWidget::setTabOrder(top_spin, width_spin);
        QWidget::setTabOrder(width_spin, height_spin);
        QWidget::setTabOrder(height_spin, GainSpin);
        QWidget::setTabOrder(GainSpin, mesi_EnableCheckbox);
        QWidget::setTabOrder(mesi_EnableCheckbox, mesi_CalibrationButton);
        QWidget::setTabOrder(mesi_CalibrationButton, mesi_StartButton);
        QWidget::setTabOrder(mesi_StartButton, mesi_ExposureInput);
        QWidget::setTabOrder(mesi_ExposureInput, mesi_DisplayExposureCombo);
        QWidget::setTabOrder(mesi_DisplayExposureCombo, show_SC_check);
        QWidget::setTabOrder(show_SC_check, scmin_spin);
        QWidget::setTabOrder(scmin_spin, scmax_spin);
        QWidget::setTabOrder(scmax_spin, sc_colormap_combo);
        QWidget::setTabOrder(sc_colormap_combo, scColorbar_checkBox);
        QWidget::setTabOrder(scColorbar_checkBox, show_raw_check);
        QWidget::setTabOrder(show_raw_check, raw_min_spin);
        QWidget::setTabOrder(raw_min_spin, raw_max_spin);
        QWidget::setTabOrder(raw_max_spin, raw_colormap_combo);
        QWidget::setTabOrder(raw_colormap_combo, rawColorbar_checkBox);
        QWidget::setTabOrder(rawColorbar_checkBox, SatPixelColor_comboBox);
        QWidget::setTabOrder(SatPixelColor_comboBox, enable_overlay_checkBox);
        QWidget::setTabOrder(enable_overlay_checkBox, bg_src_comboBox);
        QWidget::setTabOrder(bg_src_comboBox, bg_cmap_comboBox);
        QWidget::setTabOrder(bg_cmap_comboBox, bg_min_spin);
        QWidget::setTabOrder(bg_min_spin, bg_max_spin);
        QWidget::setTabOrder(bg_max_spin, over_src_comboBox);
        QWidget::setTabOrder(over_src_comboBox, over_cmap_comboBox);
        QWidget::setTabOrder(over_cmap_comboBox, over_min_spin);
        QWidget::setTabOrder(over_min_spin, over_max_spin);
        QWidget::setTabOrder(over_max_spin, thresh_type_comboBox);
        QWidget::setTabOrder(thresh_type_comboBox, over_blur_spin);
        QWidget::setTabOrder(over_blur_spin, alpha_enable_checkBox);
        QWidget::setTabOrder(alpha_enable_checkBox, over_Kmid_SpinBox);
        QWidget::setTabOrder(over_Kmid_SpinBox, over_alpha_min_SpinBox);
        QWidget::setTabOrder(over_alpha_min_SpinBox, over_alpha_max_SpinBox);
        QWidget::setTabOrder(over_alpha_max_SpinBox, enable_ratio_image_checkbox);
        QWidget::setTabOrder(enable_ratio_image_checkbox, autoset_baseline_check);
        QWidget::setTabOrder(autoset_baseline_check, ratio_min_spin);
        QWidget::setTabOrder(ratio_min_spin, ratio_max_spin);
        QWidget::setTabOrder(ratio_max_spin, ratio_colormap_combo);
        QWidget::setTabOrder(ratio_colormap_combo, raw_list_combo);
        QWidget::setTabOrder(raw_list_combo, clear_raw_list_button);
        QWidget::setTabOrder(clear_raw_list_button, baseline_list_combo);
        QWidget::setTabOrder(baseline_list_combo, clear_baseline_list_button);
        QWidget::setTabOrder(clear_baseline_list_button, sc_list_combo);
        QWidget::setTabOrder(sc_list_combo, clear_image_list_button);
        QWidget::setTabOrder(clear_image_list_button, add_ROI_button);
        QWidget::setTabOrder(add_ROI_button, remove_ROI_button);
        QWidget::setTabOrder(remove_ROI_button, ROI_color_button);
        QWidget::setTabOrder(ROI_color_button, roiPlotCheckbox);
        QWidget::setTabOrder(roiPlotCheckbox, roiPlotHistoryCheckbox);
        QWidget::setTabOrder(roiPlotHistoryCheckbox, roiPlotLimitSpin);
        QWidget::setTabOrder(roiPlotLimitSpin, roiPlotSaveCheckbox);
        QWidget::setTabOrder(roiPlotSaveCheckbox, roiPlotBaselineStart);
        QWidget::setTabOrder(roiPlotBaselineStart, roiPlotBaselineEnd);
        QWidget::setTabOrder(roiPlotBaselineEnd, roiplot_autoscale_check);
        QWidget::setTabOrder(roiplot_autoscale_check, roiplot_ymin_spin);
        QWidget::setTabOrder(roiplot_ymin_spin, roiplot_ymax_spin);
        QWidget::setTabOrder(roiplot_ymax_spin, roiplot_rel_autoscale_check);
        QWidget::setTabOrder(roiplot_rel_autoscale_check, roiplot_rel_ymin_spin);
        QWidget::setTabOrder(roiplot_rel_ymin_spin, roiplot_rel_ymax_spin);
        QWidget::setTabOrder(roiplot_rel_ymax_spin, dmdInitializeButton);
        QWidget::setTabOrder(dmdInitializeButton, dmdInfoButton);
        QWidget::setTabOrder(dmdInfoButton, dmdRegistrationButton);
        QWidget::setTabOrder(dmdRegistrationButton, loadROIButton);
        QWidget::setTabOrder(loadROIButton, saveROIButton);
        QWidget::setTabOrder(saveROIButton, clearROIButton);
        QWidget::setTabOrder(clearROIButton, loadTransformButton);
        QWidget::setTabOrder(loadTransformButton, saveTransformButton);
        QWidget::setTabOrder(saveTransformButton, useTransformCheckbox);
        QWidget::setTabOrder(useTransformCheckbox, sxText);
        QWidget::setTabOrder(sxText, rxText);
        QWidget::setTabOrder(rxText, ryText);
        QWidget::setTabOrder(ryText, syText);
        QWidget::setTabOrder(syText, txText);
        QWidget::setTabOrder(txText, tyText);
        QWidget::setTabOrder(tyText, showSinglePatternButton);
        QWidget::setTabOrder(showSinglePatternButton, dmdMergeCheckbox);
        QWidget::setTabOrder(dmdMergeCheckbox, dmdExposureSpin);
        QWidget::setTabOrder(dmdExposureSpin, dmdTotalTimeSpin);
        QWidget::setTabOrder(dmdTotalTimeSpin, dmdCycleSpin);
        QWidget::setTabOrder(dmdCycleSpin, dmdROICounter);
        QWidget::setTabOrder(dmdROICounter, startPatternSequenceButton);
        QWidget::setTabOrder(startPatternSequenceButton, dmdTileXSpin);
        QWidget::setTabOrder(dmdTileXSpin, dmdTileXGapSpin);
        QWidget::setTabOrder(dmdTileXGapSpin, dmdTileYSpin);
        QWidget::setTabOrder(dmdTileYSpin, dmdTileYGapSpin);
        QWidget::setTabOrder(dmdTileYGapSpin, dmdTileButton);
        QWidget::setTabOrder(dmdTileButton, listWidget);
        QWidget::setTabOrder(listWidget, compute_SC_check);
        QWidget::setTabOrder(compute_SC_check, process_mode_comboBox);
        QWidget::setTabOrder(process_mode_comboBox, Nthreads_spinBox);
        QWidget::setTabOrder(Nthreads_spinBox, NxN_spin);
        QWidget::setTabOrder(NxN_spin, num_sc_to_avg_spinBox);
        QWidget::setTabOrder(num_sc_to_avg_spinBox, moving_average_spinBox);
        QWidget::setTabOrder(moving_average_spinBox, Dark_level_spinBox);
        QWidget::setTabOrder(Dark_level_spinBox, blur_width_spinBox);
        QWidget::setTabOrder(blur_width_spinBox, colorCameraExposure_SpinBox);
        QWidget::setTabOrder(colorCameraExposure_SpinBox, ROI_list_widget);
        QWidget::setTabOrder(ROI_list_widget, ROI_show_check);

        retranslateUi(SpeckleSettings);

        listWidget->setCurrentRow(0);
        stackedWidget->setCurrentIndex(0);
        process_mode_comboBox->setCurrentIndex(0);
        thresh_type_comboBox->setCurrentIndex(0);
        over_src_comboBox->setCurrentIndex(1);
        over_cmap_comboBox->setCurrentIndex(0);
        sc_colormap_combo->setCurrentIndex(0);
        ratio_colormap_combo->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SpeckleSettings);
    } // setupUi

    void retranslateUi(QDialog *SpeckleSettings)
    {
        SpeckleSettings->setWindowTitle(QCoreApplication::translate("SpeckleSettings", "Settings", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("SpeckleSettings", "Acquisition", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("SpeckleSettings", "Processing", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("SpeckleSettings", "Display", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("SpeckleSettings", "ROI Editor", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("SpeckleSettings", "DMD", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

#if QT_CONFIG(tooltip)
        camerasAvailableComboBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Select primary camera", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("SpeckleSettings", "Output", nullptr));
        duration_TypeComboBox->setItemText(0, QCoreApplication::translate("SpeckleSettings", "Frames", nullptr));
        duration_TypeComboBox->setItemText(1, QCoreApplication::translate("SpeckleSettings", "Time", nullptr));
        duration_TypeComboBox->setItemText(2, QCoreApplication::translate("SpeckleSettings", "Continuous", nullptr));

#if QT_CONFIG(tooltip)
        duration_TypeComboBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Select type of duration", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        acquireLength_lineEdit->setToolTip(QCoreApplication::translate("SpeckleSettings", "Number of frames to acquire", nullptr));
#endif // QT_CONFIG(tooltip)
        acquireLength_lineEdit->setText(QCoreApplication::translate("SpeckleSettings", "100", nullptr));
        frames_seq_spin_label->setText(QCoreApplication::translate("SpeckleSettings", "Duration", nullptr));
#if QT_CONFIG(tooltip)
        outputfile_edit->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set output file", nullptr));
#endif // QT_CONFIG(tooltip)
        outputfile_edit->setText(QCoreApplication::translate("SpeckleSettings", "test", nullptr));
#if QT_CONFIG(tooltip)
        outputfile_browse_button->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set working directory", nullptr));
#endif // QT_CONFIG(tooltip)
        outputfile_browse_button->setText(QCoreApplication::translate("SpeckleSettings", "...", nullptr));
        label_13->setText(QCoreApplication::translate("SpeckleSettings", "Camera", nullptr));
        MESIBox->setTitle(QCoreApplication::translate("SpeckleSettings", "MESI Settings", nullptr));
        mesi_EnableCheckbox->setText(QCoreApplication::translate("SpeckleSettings", "Enable MESI", nullptr));
        mesi_CalibrationButton->setText(QCoreApplication::translate("SpeckleSettings", "Calibration", nullptr));
        mesi_ExposureTextboxLabel->setText(QCoreApplication::translate("SpeckleSettings", "Exposure Times (ms)", nullptr));
        mesi_DisplayExposureComboxLabel->setText(QCoreApplication::translate("SpeckleSettings", "Exposure to Display", nullptr));
        mesi_StartButton->setText(QCoreApplication::translate("SpeckleSettings", "Start", nullptr));
        mesi_ExposureInput->setInputMask(QString());
        mesi_ExposureInput->setText(QCoreApplication::translate("SpeckleSettings", "0.05,0.075,0.1,0.25,0.5,0.75,1,2.5,5,7.5,10,25,40,50,80", nullptr));
#if QT_CONFIG(tooltip)
        save_sc_check->setToolTip(QCoreApplication::translate("SpeckleSettings", "Save speckle contrast data", nullptr));
#endif // QT_CONFIG(tooltip)
        save_sc_check->setText(QCoreApplication::translate("SpeckleSettings", "Save SC", nullptr));
#if QT_CONFIG(tooltip)
        save_raw_check->setToolTip(QCoreApplication::translate("SpeckleSettings", "Save raw data", nullptr));
#endif // QT_CONFIG(tooltip)
        save_raw_check->setText(QCoreApplication::translate("SpeckleSettings", "Save Raw", nullptr));
#if QT_CONFIG(tooltip)
        save_sc_videocheckBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Save speckle contrast display as MP4 video", nullptr));
#endif // QT_CONFIG(tooltip)
        save_sc_videocheckBox->setText(QCoreApplication::translate("SpeckleSettings", "Save SC Video", nullptr));
#if QT_CONFIG(tooltip)
        save_overlay_videocheckBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Save overlay display as MP4 video", nullptr));
#endif // QT_CONFIG(tooltip)
        save_overlay_videocheckBox->setText(QCoreApplication::translate("SpeckleSettings", "Save Overlay Video", nullptr));
#if QT_CONFIG(tooltip)
        save_input_videocheckBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Save input as MP4 video", nullptr));
#endif // QT_CONFIG(tooltip)
        save_input_videocheckBox->setText(QCoreApplication::translate("SpeckleSettings", "Save Input Video", nullptr));
        CameraSettingsBox->setTitle(QCoreApplication::translate("SpeckleSettings", "Camera Settings", nullptr));
        trigger_combo_label->setText(QCoreApplication::translate("SpeckleSettings", "Trigger", nullptr));
        label_7->setText(QCoreApplication::translate("SpeckleSettings", "Width / Height", nullptr));
#if QT_CONFIG(tooltip)
        left_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set left coordinate of camera crop", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        top_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set top coordinate of camera crop", nullptr));
#endif // QT_CONFIG(tooltip)
        GainSpinLabel->setText(QCoreApplication::translate("SpeckleSettings", "Gain", nullptr));
#if QT_CONFIG(tooltip)
        exposure_time_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set camera exposure time", nullptr));
#endif // QT_CONFIG(tooltip)
        exposure_time_spin_label->setText(QCoreApplication::translate("SpeckleSettings", "Exposure (ms)", nullptr));
#if QT_CONFIG(tooltip)
        GainSpin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set camera gain", nullptr));
#endif // QT_CONFIG(tooltip)
        label_6->setText(QCoreApplication::translate("SpeckleSettings", "Left / Top", nullptr));
#if QT_CONFIG(tooltip)
        width_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set width of camera crop", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        height_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set height of camera crop", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        trigger_combo->setToolTip(QCoreApplication::translate("SpeckleSettings", "Select camera triggering mode", nullptr));
#endif // QT_CONFIG(tooltip)
        DarkLevelMaskGroup->setTitle(QCoreApplication::translate("SpeckleSettings", "Dark Level Mask", nullptr));
        Dark_level_label->setText(QCoreApplication::translate("SpeckleSettings", "Threshold", nullptr));
#if QT_CONFIG(tooltip)
        Dark_level_spinBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Mask pixels with raw intensity level below this threshold", nullptr));
#endif // QT_CONFIG(tooltip)
        blur_width_label->setText(QCoreApplication::translate("SpeckleSettings", "Blur", nullptr));
#if QT_CONFIG(tooltip)
        blur_width_spinBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Blur width along edge of dark level mask", nullptr));
#endif // QT_CONFIG(tooltip)
        SpeckleContrasGroup->setTitle(QCoreApplication::translate("SpeckleSettings", "Speckle Contrast", nullptr));
#if QT_CONFIG(tooltip)
        num_sc_to_avg_spinBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Number of speckle contrast frames to average during processing", nullptr));
#endif // QT_CONFIG(tooltip)
        Nthreads_label->setText(QCoreApplication::translate("SpeckleSettings", "Threads", nullptr));
#if QT_CONFIG(tooltip)
        compute_SC_check->setToolTip(QCoreApplication::translate("SpeckleSettings", "Toggle speckle contrast processing", nullptr));
#endif // QT_CONFIG(tooltip)
        compute_SC_check->setText(QCoreApplication::translate("SpeckleSettings", "Compute SC", nullptr));
#if QT_CONFIG(tooltip)
        moving_average_spinBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Number of speckle contrast frames to include in moving average", nullptr));
#endif // QT_CONFIG(tooltip)
        process_mode_label->setText(QCoreApplication::translate("SpeckleSettings", "Processing Mode", nullptr));
#if QT_CONFIG(tooltip)
        NxN_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Sliding window size (NxN)", nullptr));
#endif // QT_CONFIG(tooltip)
        NxN_label->setText(QCoreApplication::translate("SpeckleSettings", "Window Size", nullptr));
        moving_average_label->setText(QCoreApplication::translate("SpeckleSettings", "Moving Average Width", nullptr));
#if QT_CONFIG(tooltip)
        Nthreads_spinBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Number of threads to use when calculating speckle contrast", nullptr));
#endif // QT_CONFIG(tooltip)
        num_sc_to_avg_label->setText(QCoreApplication::translate("SpeckleSettings", "Frames to Average", nullptr));
        process_mode_comboBox->setItemText(0, QCoreApplication::translate("SpeckleSettings", "Most Recent", nullptr));
        process_mode_comboBox->setItemText(1, QCoreApplication::translate("SpeckleSettings", "All Frames", nullptr));

#if QT_CONFIG(tooltip)
        process_mode_comboBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Speckle contrast processing mode", nullptr));
#endif // QT_CONFIG(tooltip)
        ImageOverlayGroup->setTitle(QCoreApplication::translate("SpeckleSettings", "Image Overlay", nullptr));
        overlaySourceLabel->setText(QCoreApplication::translate("SpeckleSettings", "Source", nullptr));
        thresh_type_comboBox->setItemText(0, QCoreApplication::translate("SpeckleSettings", "Between", nullptr));
        thresh_type_comboBox->setItemText(1, QCoreApplication::translate("SpeckleSettings", "Above", nullptr));
        thresh_type_comboBox->setItemText(2, QCoreApplication::translate("SpeckleSettings", "Below", nullptr));

#if QT_CONFIG(tooltip)
        thresh_type_comboBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set overlay rendering mode", nullptr));
#endif // QT_CONFIG(tooltip)
        over_src_comboBox->setItemText(0, QCoreApplication::translate("SpeckleSettings", "Raw", nullptr));
        over_src_comboBox->setItemText(1, QCoreApplication::translate("SpeckleSettings", "SC", nullptr));
        over_src_comboBox->setItemText(2, QCoreApplication::translate("SpeckleSettings", "TC", nullptr));
        over_src_comboBox->setItemText(3, QCoreApplication::translate("SpeckleSettings", "Video In", nullptr));
        over_src_comboBox->setItemText(4, QCoreApplication::translate("SpeckleSettings", "None", nullptr));

#if QT_CONFIG(tooltip)
        over_src_comboBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Select data source for overlay", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        bg_min_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set minimum display value for overlay background", nullptr));
#endif // QT_CONFIG(tooltip)
        overlayBlurLabel->setText(QCoreApplication::translate("SpeckleSettings", "Blur Width", nullptr));
#if QT_CONFIG(tooltip)
        over_alpha_min_SpinBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set minimum alpha level for overlay transparency", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        over_blur_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set overlay blur width", nullptr));
#endif // QT_CONFIG(tooltip)
        overlayColormapLabel->setText(QCoreApplication::translate("SpeckleSettings", "Colormap", nullptr));
        overlayBackgroundLabel->setText(QCoreApplication::translate("SpeckleSettings", "Background", nullptr));
#if QT_CONFIG(tooltip)
        over_min_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set minimum display value for overlay", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        bg_max_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set maximum display value for overlay background", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        enable_overlay_checkBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Toggle display of the image overlay view", nullptr));
#endif // QT_CONFIG(tooltip)
        enable_overlay_checkBox->setText(QCoreApplication::translate("SpeckleSettings", "Enable", nullptr));
#if QT_CONFIG(tooltip)
        over_Kmid_SpinBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set overlay threshold for determining transparency. All overlay pixels less than this value will be opaque.", nullptr));
#endif // QT_CONFIG(tooltip)
        overlayThreshLabel->setText(QCoreApplication::translate("SpeckleSettings", "Overlay Mode", nullptr));
#if QT_CONFIG(tooltip)
        alpha_enable_checkBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Toggle overlay transparency", nullptr));
#endif // QT_CONFIG(tooltip)
        alpha_enable_checkBox->setText(QCoreApplication::translate("SpeckleSettings", "Alpha", nullptr));
        overlayMinLabel->setText(QCoreApplication::translate("SpeckleSettings", "Min", nullptr));
        bg_cmap_comboBox->setItemText(0, QCoreApplication::translate("SpeckleSettings", "Gray", nullptr));
        bg_cmap_comboBox->setItemText(1, QCoreApplication::translate("SpeckleSettings", "Jet", nullptr));
        bg_cmap_comboBox->setItemText(2, QCoreApplication::translate("SpeckleSettings", "Reverse Jet", nullptr));
        bg_cmap_comboBox->setItemText(3, QCoreApplication::translate("SpeckleSettings", "Hot", nullptr));
        bg_cmap_comboBox->setItemText(4, QCoreApplication::translate("SpeckleSettings", "Cool", nullptr));
        bg_cmap_comboBox->setItemText(5, QCoreApplication::translate("SpeckleSettings", "Autumn", nullptr));
        bg_cmap_comboBox->setItemText(6, QCoreApplication::translate("SpeckleSettings", "pmkmp", nullptr));
        bg_cmap_comboBox->setItemText(7, QCoreApplication::translate("SpeckleSettings", "Greens", nullptr));
        bg_cmap_comboBox->setItemText(8, QCoreApplication::translate("SpeckleSettings", "Reverse Gray", nullptr));

#if QT_CONFIG(tooltip)
        bg_cmap_comboBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Select colormap for overlay background", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        over_alpha_max_SpinBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set maximum alpha level for overlay transparency", nullptr));
#endif // QT_CONFIG(tooltip)
        overlayMaxLabel->setText(QCoreApplication::translate("SpeckleSettings", "Max", nullptr));
        overlayOverlayLabel->setText(QCoreApplication::translate("SpeckleSettings", "Overlay", nullptr));
        over_cmap_comboBox->setItemText(0, QCoreApplication::translate("SpeckleSettings", "Gray", nullptr));
        over_cmap_comboBox->setItemText(1, QCoreApplication::translate("SpeckleSettings", "Jet", nullptr));
        over_cmap_comboBox->setItemText(2, QCoreApplication::translate("SpeckleSettings", "Reverse Jet", nullptr));
        over_cmap_comboBox->setItemText(3, QCoreApplication::translate("SpeckleSettings", "Hot", nullptr));
        over_cmap_comboBox->setItemText(4, QCoreApplication::translate("SpeckleSettings", "Cool", nullptr));
        over_cmap_comboBox->setItemText(5, QCoreApplication::translate("SpeckleSettings", "Autumn", nullptr));
        over_cmap_comboBox->setItemText(6, QCoreApplication::translate("SpeckleSettings", "pmkmp", nullptr));
        over_cmap_comboBox->setItemText(7, QCoreApplication::translate("SpeckleSettings", "Greens", nullptr));
        over_cmap_comboBox->setItemText(8, QCoreApplication::translate("SpeckleSettings", "Neon", nullptr));
        over_cmap_comboBox->setItemText(9, QCoreApplication::translate("SpeckleSettings", "Reverse Gray", nullptr));

#if QT_CONFIG(tooltip)
        over_cmap_comboBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Select colormap for overlay", nullptr));
#endif // QT_CONFIG(tooltip)
        overlayAlphaThresholdLabel->setText(QCoreApplication::translate("SpeckleSettings", "Alpha Threshold", nullptr));
        bg_src_comboBox->setItemText(0, QCoreApplication::translate("SpeckleSettings", "Raw", nullptr));
        bg_src_comboBox->setItemText(1, QCoreApplication::translate("SpeckleSettings", "SC", nullptr));
        bg_src_comboBox->setItemText(2, QCoreApplication::translate("SpeckleSettings", "TC", nullptr));
        bg_src_comboBox->setItemText(3, QCoreApplication::translate("SpeckleSettings", "Video In", nullptr));
        bg_src_comboBox->setItemText(4, QCoreApplication::translate("SpeckleSettings", "None", nullptr));

#if QT_CONFIG(tooltip)
        bg_src_comboBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Select data source for overlay background", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        over_max_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set maximum display value for overlay", nullptr));
#endif // QT_CONFIG(tooltip)
        overlayAlphaRangeLabel->setText(QCoreApplication::translate("SpeckleSettings", "Alpha Min/Max", nullptr));
#if QT_CONFIG(tooltip)
        colorCameraExposure_SpinBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Exposure of color camera (ms)", nullptr));
#endif // QT_CONFIG(tooltip)
        colorCameraExposureLabel->setText(QCoreApplication::translate("SpeckleSettings", "Color Exp (ms)", nullptr));
        DisplayRangeGroup->setTitle(QCoreApplication::translate("SpeckleSettings", "Display Range", nullptr));
        raw_colormap_combo->setItemText(0, QCoreApplication::translate("SpeckleSettings", "Gray", nullptr));
        raw_colormap_combo->setItemText(1, QCoreApplication::translate("SpeckleSettings", "Jet", nullptr));
        raw_colormap_combo->setItemText(2, QCoreApplication::translate("SpeckleSettings", "Reverse Jet", nullptr));
        raw_colormap_combo->setItemText(3, QCoreApplication::translate("SpeckleSettings", "Hot", nullptr));
        raw_colormap_combo->setItemText(4, QCoreApplication::translate("SpeckleSettings", "Cool", nullptr));
        raw_colormap_combo->setItemText(5, QCoreApplication::translate("SpeckleSettings", "Autumn", nullptr));
        raw_colormap_combo->setItemText(6, QCoreApplication::translate("SpeckleSettings", "pmkmp", nullptr));
        raw_colormap_combo->setItemText(7, QCoreApplication::translate("SpeckleSettings", "Greens", nullptr));

        minDisplayLabel->setText(QCoreApplication::translate("SpeckleSettings", "Min", nullptr));
        label_15->setText(QCoreApplication::translate("SpeckleSettings", "Enable", nullptr));
        show_SC_check->setText(QString());
        show_raw_check->setText(QString());
        sc_colormap_combo->setItemText(0, QCoreApplication::translate("SpeckleSettings", "Gray", nullptr));
        sc_colormap_combo->setItemText(1, QCoreApplication::translate("SpeckleSettings", "Jet", nullptr));
        sc_colormap_combo->setItemText(2, QCoreApplication::translate("SpeckleSettings", "Reverse Jet", nullptr));
        sc_colormap_combo->setItemText(3, QCoreApplication::translate("SpeckleSettings", "Hot", nullptr));
        sc_colormap_combo->setItemText(4, QCoreApplication::translate("SpeckleSettings", "Cool", nullptr));
        sc_colormap_combo->setItemText(5, QCoreApplication::translate("SpeckleSettings", "Autumn", nullptr));
        sc_colormap_combo->setItemText(6, QCoreApplication::translate("SpeckleSettings", "pmkmp", nullptr));
        sc_colormap_combo->setItemText(7, QCoreApplication::translate("SpeckleSettings", "Greens", nullptr));
        sc_colormap_combo->setItemText(8, QCoreApplication::translate("SpeckleSettings", "Reverse Gray", nullptr));

        colormapLabel->setText(QCoreApplication::translate("SpeckleSettings", "Colormap", nullptr));
        rawDisplayLabel->setText(QCoreApplication::translate("SpeckleSettings", "Raw", nullptr));
        label_14->setText(QCoreApplication::translate("SpeckleSettings", "Colorbar", nullptr));
#if QT_CONFIG(tooltip)
        rawColorbar_checkBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "show colorbar", nullptr));
#endif // QT_CONFIG(tooltip)
        rawColorbar_checkBox->setText(QString());
        maxDisplayLabel->setText(QCoreApplication::translate("SpeckleSettings", "Max", nullptr));
#if QT_CONFIG(tooltip)
        scColorbar_checkBox->setToolTip(QCoreApplication::translate("SpeckleSettings", "show colorbar", nullptr));
#endif // QT_CONFIG(tooltip)
        scColorbar_checkBox->setText(QString());
        scDisplayLabel->setText(QCoreApplication::translate("SpeckleSettings", "SC", nullptr));
        satPixelColorLabel->setText(QCoreApplication::translate("SpeckleSettings", "Saturated Pixel Color", nullptr));
        SatPixelColor_comboBox->setItemText(0, QCoreApplication::translate("SpeckleSettings", "Red", nullptr));
        SatPixelColor_comboBox->setItemText(1, QCoreApplication::translate("SpeckleSettings", "Green", nullptr));
        SatPixelColor_comboBox->setItemText(2, QCoreApplication::translate("SpeckleSettings", "Blue", nullptr));
        SatPixelColor_comboBox->setItemText(3, QCoreApplication::translate("SpeckleSettings", "Yellow", nullptr));

        RatioImageGroup->setTitle(QCoreApplication::translate("SpeckleSettings", "Ratio Image", nullptr));
        ratio_colormap_combo->setItemText(0, QCoreApplication::translate("SpeckleSettings", "Grayscale", nullptr));
        ratio_colormap_combo->setItemText(1, QCoreApplication::translate("SpeckleSettings", "Jet", nullptr));
        ratio_colormap_combo->setItemText(2, QCoreApplication::translate("SpeckleSettings", "Hot", nullptr));
        ratio_colormap_combo->setItemText(3, QCoreApplication::translate("SpeckleSettings", "Cool", nullptr));
        ratio_colormap_combo->setItemText(4, QCoreApplication::translate("SpeckleSettings", "Autumn", nullptr));

#if QT_CONFIG(tooltip)
        ratio_colormap_combo->setToolTip(QCoreApplication::translate("SpeckleSettings", "Select the colormap for the ratio image", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        ratio_max_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set the maximum display value for the ratio image", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        ratio_min_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Set the minimum display value for the ratio image", nullptr));
#endif // QT_CONFIG(tooltip)
        ratioMinLabel->setText(QCoreApplication::translate("SpeckleSettings", "Min", nullptr));
        ratioMaxLabel->setText(QCoreApplication::translate("SpeckleSettings", "Max", nullptr));
        ratioColormapLabel->setText(QCoreApplication::translate("SpeckleSettings", "Colormap", nullptr));
#if QT_CONFIG(tooltip)
        enable_ratio_image_checkbox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Toggle display of the ratio image (relative inverse correlation time) during data acquisition", nullptr));
#endif // QT_CONFIG(tooltip)
        enable_ratio_image_checkbox->setText(QCoreApplication::translate("SpeckleSettings", "Enable", nullptr));
#if QT_CONFIG(tooltip)
        autoset_baseline_check->setToolTip(QCoreApplication::translate("SpeckleSettings", "Automatically set baseline for ratio image calculations using first sequence of acquired data", nullptr));
#endif // QT_CONFIG(tooltip)
        autoset_baseline_check->setText(QCoreApplication::translate("SpeckleSettings", "Autoset Baseline", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("SpeckleSettings", "Image Sequence", nullptr));
        clear_baseline_list_button->setText(QCoreApplication::translate("SpeckleSettings", "Clear", nullptr));
        clear_image_list_button->setText(QCoreApplication::translate("SpeckleSettings", "Clear", nullptr));
        baselineListLabel->setText(QCoreApplication::translate("SpeckleSettings", "Baseline", nullptr));
        scListLabel->setText(QCoreApplication::translate("SpeckleSettings", "SC", nullptr));
        rawListLabel->setText(QCoreApplication::translate("SpeckleSettings", "Raw", nullptr));
        clear_raw_list_button->setText(QCoreApplication::translate("SpeckleSettings", "Clear", nullptr));
        ROIEditorGroup->setTitle(QCoreApplication::translate("SpeckleSettings", "ROI Editor", nullptr));
#if QT_CONFIG(tooltip)
        add_ROI_button->setToolTip(QCoreApplication::translate("SpeckleSettings", "Add new ROI", nullptr));
#endif // QT_CONFIG(tooltip)
        add_ROI_button->setText(QString());
#if QT_CONFIG(tooltip)
        remove_ROI_button->setToolTip(QCoreApplication::translate("SpeckleSettings", "Remove selected ROI", nullptr));
#endif // QT_CONFIG(tooltip)
        remove_ROI_button->setText(QString());
#if QT_CONFIG(tooltip)
        ROI_color_button->setToolTip(QCoreApplication::translate("SpeckleSettings", "Change color of selected ROI", nullptr));
#endif // QT_CONFIG(tooltip)
        ROI_color_button->setText(QString());
        ROI_show_check->setText(QCoreApplication::translate("SpeckleSettings", "Show All ROIs", nullptr));
        roiPlotGroup->setTitle(QCoreApplication::translate("SpeckleSettings", "ROI Plot", nullptr));
        roiPlotMaxLabel->setText(QCoreApplication::translate("SpeckleSettings", "Max", nullptr));
        roiPlotMinLabel->setText(QCoreApplication::translate("SpeckleSettings", "Min", nullptr));
#if QT_CONFIG(tooltip)
        roiplot_ymax_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Maximum display value for SC plot", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        roiplot_autoscale_check->setToolTip(QCoreApplication::translate("SpeckleSettings", "Automatically scale SC plot to fit data", nullptr));
#endif // QT_CONFIG(tooltip)
        roiplot_autoscale_check->setText(QString());
#if QT_CONFIG(tooltip)
        roiplot_rel_ymax_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Maximum display value for relative flow plot", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        roiplot_rel_autoscale_check->setToolTip(QCoreApplication::translate("SpeckleSettings", "Automatically scale relative flow plot to fit data", nullptr));
#endif // QT_CONFIG(tooltip)
        roiplot_rel_autoscale_check->setText(QString());
#if QT_CONFIG(tooltip)
        roiplot_rel_ymin_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Minimum display value for relative flow plot", nullptr));
#endif // QT_CONFIG(tooltip)
        roiPlotRelativeLabel->setText(QCoreApplication::translate("SpeckleSettings", "Relative Plot", nullptr));
#if QT_CONFIG(tooltip)
        roiplot_ymin_spin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Minimum display value for SC plot", nullptr));
#endif // QT_CONFIG(tooltip)
        roiPlotSCLabel->setText(QCoreApplication::translate("SpeckleSettings", "SC Plot", nullptr));
        roiPlotAutoLabel->setText(QCoreApplication::translate("SpeckleSettings", "Auto", nullptr));
#if QT_CONFIG(tooltip)
        roiPlotCheckbox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Enable display of ROI timecourse plot", nullptr));
#endif // QT_CONFIG(tooltip)
        roiPlotCheckbox->setText(QCoreApplication::translate("SpeckleSettings", "Enable", nullptr));
#if QT_CONFIG(tooltip)
        roiPlotSaveCheckbox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Toggle saving of ROI data during acquisition", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        roiPlotSaveCheckbox->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        roiPlotSaveCheckbox->setText(QCoreApplication::translate("SpeckleSettings", "Save", nullptr));
#if QT_CONFIG(tooltip)
        roiPlotHistoryCheckbox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Show entire acquisition on plot", nullptr));
#endif // QT_CONFIG(tooltip)
        roiPlotHistoryCheckbox->setText(QCoreApplication::translate("SpeckleSettings", "All Sequences", nullptr));
        roiPlotLimitLabel->setText(QCoreApplication::translate("SpeckleSettings", "Last", nullptr));
#if QT_CONFIG(tooltip)
        roiPlotLimitSpin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Show last n sequences on plot", nullptr));
#endif // QT_CONFIG(tooltip)
        roiPlotLimitSpin->setSuffix(QString());
        roiPlotLimitSpin->setPrefix(QString());
#if QT_CONFIG(tooltip)
        roiPlotBaselineLabel->setToolTip(QCoreApplication::translate("SpeckleSettings", "Baseline for relative plot. Defaults to first second.", nullptr));
#endif // QT_CONFIG(tooltip)
        roiPlotBaselineLabel->setText(QCoreApplication::translate("SpeckleSettings", "Baseline (s)", nullptr));
#if QT_CONFIG(tooltip)
        roiPlotBaselineStart->setToolTip(QCoreApplication::translate("SpeckleSettings", "Start time (s) for baseline", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        roiPlotBaselineEnd->setToolTip(QCoreApplication::translate("SpeckleSettings", "End time (s) for baseline", nullptr));
#endif // QT_CONFIG(tooltip)
        dmdBoxSystem->setTitle(QCoreApplication::translate("SpeckleSettings", "System", nullptr));
        dmdInitializeButton->setText(QCoreApplication::translate("SpeckleSettings", "Initialize", nullptr));
        dmdInfoButton->setText(QCoreApplication::translate("SpeckleSettings", "DMD Info", nullptr));
        dmdRegistrationButton->setText(QCoreApplication::translate("SpeckleSettings", "Registration", nullptr));
        dmdBoxROI->setTitle(QCoreApplication::translate("SpeckleSettings", "ROI Editor", nullptr));
        loadROIButton->setText(QCoreApplication::translate("SpeckleSettings", "Load ROIs", nullptr));
        saveROIButton->setText(QCoreApplication::translate("SpeckleSettings", "Save ROIs", nullptr));
        clearROIButton->setText(QCoreApplication::translate("SpeckleSettings", "Clear ROIs", nullptr));
        dmdBoxSequence->setTitle(QCoreApplication::translate("SpeckleSettings", "Sequence", nullptr));
#if QT_CONFIG(tooltip)
        dmdExposureLabel->setToolTip(QCoreApplication::translate("SpeckleSettings", "Display time for each pattern", nullptr));
#endif // QT_CONFIG(tooltip)
        dmdExposureLabel->setText(QCoreApplication::translate("SpeckleSettings", "Exposure (s)", nullptr));
#if QT_CONFIG(tooltip)
        dmdExposureSpin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Display time for each pattern", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        dmdTotalTimeLabel->setToolTip(QCoreApplication::translate("SpeckleSettings", "Total running time for DMD", nullptr));
#endif // QT_CONFIG(tooltip)
        dmdTotalTimeLabel->setText(QCoreApplication::translate("SpeckleSettings", "Total Time (s)", nullptr));
#if QT_CONFIG(tooltip)
        dmdTotalTimeSpin->setToolTip(QCoreApplication::translate("SpeckleSettings", "Total running time for DMD", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        dmdCycleLabel->setToolTip(QCoreApplication::translate("SpeckleSettings", "Total running time for DMD", nullptr));
#endif // QT_CONFIG(tooltip)
        dmdCycleLabel->setText(QCoreApplication::translate("SpeckleSettings", "Cycles", nullptr));
        dmdROICounterLabel->setText(QCoreApplication::translate("SpeckleSettings", "# ROIs", nullptr));
        startPatternSequenceButton->setText(QCoreApplication::translate("SpeckleSettings", "Start DMD Sequence", nullptr));
        dmdBoxTransform->setTitle(QCoreApplication::translate("SpeckleSettings", "Transform", nullptr));
        loadTransformButton->setText(QCoreApplication::translate("SpeckleSettings", "Load Transform", nullptr));
        saveTransformButton->setText(QCoreApplication::translate("SpeckleSettings", "Save Transform", nullptr));
        useTransformCheckbox->setText(QCoreApplication::translate("SpeckleSettings", "Use Transform", nullptr));
        sxLabel->setText(QCoreApplication::translate("SpeckleSettings", "sx", nullptr));
        ryLabel->setText(QCoreApplication::translate("SpeckleSettings", "ry", nullptr));
        txLabel->setText(QCoreApplication::translate("SpeckleSettings", "tx", nullptr));
        rxLabel->setText(QCoreApplication::translate("SpeckleSettings", "rx", nullptr));
        syLabel->setText(QCoreApplication::translate("SpeckleSettings", "sy", nullptr));
        tyLabel->setText(QCoreApplication::translate("SpeckleSettings", "ty", nullptr));
        dmdBoxTile->setTitle(QCoreApplication::translate("SpeckleSettings", "Tile Generation", nullptr));
        dmdTileButton->setText(QCoreApplication::translate("SpeckleSettings", "Go", nullptr));
        dmdTileYLabel->setText(QCoreApplication::translate("SpeckleSettings", "Ny", nullptr));
        dmdTileXLabel->setText(QCoreApplication::translate("SpeckleSettings", "Nx", nullptr));
        dmdTileXGapSpinLabel->setText(QCoreApplication::translate("SpeckleSettings", "\342\210\206x", nullptr));
        dmdTileYGapSpinLabel->setText(QCoreApplication::translate("SpeckleSettings", "\342\210\206y", nullptr));
        showSinglePatternButton->setText(QCoreApplication::translate("SpeckleSettings", "Show ROI on DMD", nullptr));
#if QT_CONFIG(tooltip)
        dmdMergeCheckbox->setToolTip(QCoreApplication::translate("SpeckleSettings", "Merge all ROIs together for projection", nullptr));
#endif // QT_CONFIG(tooltip)
        dmdMergeCheckbox->setText(QCoreApplication::translate("SpeckleSettings", "Merge", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpeckleSettings: public Ui_SpeckleSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPECKLESETTINGS_H
