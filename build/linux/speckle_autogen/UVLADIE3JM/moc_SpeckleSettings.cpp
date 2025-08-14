/****************************************************************************
** Meta object code from reading C++ file 'SpeckleSettings.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/SpeckleSettings.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SpeckleSettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15SpeckleSettingsE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN15SpeckleSettingsE = QtMocHelpers::stringData(
    "SpeckleSettings",
    "processModeChanged",
    "",
    "displayLayoutChanged",
    "QStringList*",
    "rawSettingsChanged",
    "scSettingsChanged",
    "overlaySettingsChanged",
    "cameraSettingsChanged",
    "rawDisplayRangeChanged",
    "Imin",
    "Imax",
    "scDisplayRangeChanged",
    "SCmin",
    "SCmax",
    "overlayToggled",
    "show_overlay",
    "overlayChanged",
    "kmin",
    "kmax",
    "use_alpha",
    "kmid",
    "roiAdded",
    "roiRemoved",
    "idx",
    "roiColorChanged",
    "color",
    "roiVisibilityToggled",
    "is_visible",
    "showROICheckToggled",
    "checked",
    "colorCameraExpChanged",
    "exp_time",
    "hotkeyStatusUpdate",
    "infoUpdate",
    "type",
    "text",
    "setWorkingDirectory",
    "on_outputfile_browse_button_clicked",
    "toggleAllROIVisibility",
    "show",
    "setCameraAOIValues",
    "toggleOverlaySource",
    "changeSCmin",
    "changeSCmax",
    "changeExposure",
    "on_scmin_spin_valueChanged",
    "value",
    "on_scmin_spin_editingFinished",
    "on_scmax_spin_valueChanged",
    "on_scmax_spin_editingFinished",
    "on_raw_min_spin_valueChanged",
    "on_raw_min_spin_editingFinished",
    "on_raw_max_spin_valueChanged",
    "on_raw_max_spin_editingFinished",
    "on_ratio_min_spin_valueChanged",
    "on_ratio_max_spin_valueChanged",
    "on_scColorbar_checkBox_toggled",
    "on_rawColorbar_checkBox_toggled",
    "on_raw_list_combo_currentIndexChanged",
    "on_clear_raw_list_button_clicked",
    "on_baseline_list_combo_currentIndexChanged",
    "on_clear_baseline_list_button_clicked",
    "on_sc_list_combo_currentIndexChanged",
    "on_clear_image_list_button_clicked",
    "on_autoset_baseline_check_toggled",
    "on_enable_ratio_image_checkbox_toggled",
    "on_show_raw_check_toggled",
    "on_show_SC_check_toggled",
    "on_sc_colormap_combo_activated",
    "on_ratio_colormap_combo_activated",
    "on_raw_colormap_combo_activated",
    "on_SatPixelColor_comboBox_activated",
    "on_ROI_list_widget_itemChanged",
    "QListWidgetItem*",
    "item",
    "on_add_ROI_button_clicked",
    "on_remove_ROI_button_clicked",
    "on_ROI_color_button_clicked",
    "on_ROI_show_check_toggled",
    "on_roiPlotCheckbox_toggled",
    "on_roiPlotSaveCheckbox_toggled",
    "on_roiPlotHistoryCheckbox_toggled",
    "on_roiPlotLimitSpin_editingFinished",
    "on_roiplot_autoscale_check_toggled",
    "on_roiplot_ymin_spin_editingFinished",
    "on_roiplot_ymax_spin_editingFinished",
    "on_roiplot_rel_autoscale_check_toggled",
    "on_roiplot_rel_ymax_spin_editingFinished",
    "on_roiplot_rel_ymin_spin_editingFinished",
    "on_roiPlotBaselineStart_editingFinished",
    "on_roiPlotBaselineEnd_editingFinished",
    "on_enable_overlay_checkBox_toggled",
    "on_bg_src_comboBox_currentIndexChanged",
    "on_bg_cmap_comboBox_activated",
    "on_bg_min_spin_valueChanged",
    "on_bg_min_spin_editingFinished",
    "on_bg_max_spin_valueChanged",
    "on_bg_max_spin_editingFinished",
    "on_over_src_comboBox_currentIndexChanged",
    "on_over_cmap_comboBox_activated",
    "on_over_min_spin_valueChanged",
    "on_over_min_spin_editingFinished",
    "on_over_max_spin_valueChanged",
    "on_over_max_spin_editingFinished",
    "on_thresh_type_comboBox_activated",
    "on_over_blur_spin_valueChanged",
    "on_alpha_enable_checkBox_toggled",
    "on_over_Kmid_SpinBox_valueChanged",
    "on_over_alpha_min_SpinBox_valueChanged",
    "on_over_alpha_max_SpinBox_valueChanged",
    "on_colorCameraExposure_SpinBox_valueChanged",
    "on_compute_SC_check_toggled",
    "on_save_raw_check_toggled",
    "on_save_sc_check_toggled",
    "on_exposure_time_spin_valueChanged",
    "on_trigger_combo_currentIndexChanged",
    "on_GainSpin_valueChanged",
    "updateSpeckleCamera",
    "on_duration_TypeComboBox_currentIndexChanged",
    "on_acquireLength_lineEdit_editingFinished"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN15SpeckleSettingsE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      98,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  602,    2, 0x06,    1 /* Public */,
       3,    1,  603,    2, 0x06,    2 /* Public */,
       5,    0,  606,    2, 0x06,    4 /* Public */,
       6,    0,  607,    2, 0x06,    5 /* Public */,
       7,    0,  608,    2, 0x06,    6 /* Public */,
       8,    0,  609,    2, 0x06,    7 /* Public */,
       9,    2,  610,    2, 0x06,    8 /* Public */,
      12,    2,  615,    2, 0x06,   11 /* Public */,
      15,    1,  620,    2, 0x06,   14 /* Public */,
      17,    4,  623,    2, 0x06,   16 /* Public */,
      22,    0,  632,    2, 0x06,   21 /* Public */,
      23,    1,  633,    2, 0x06,   22 /* Public */,
      25,    2,  636,    2, 0x06,   24 /* Public */,
      27,    2,  641,    2, 0x06,   27 /* Public */,
      29,    1,  646,    2, 0x06,   30 /* Public */,
      31,    1,  649,    2, 0x06,   32 /* Public */,
      33,    0,  652,    2, 0x06,   34 /* Public */,
      34,    2,  653,    2, 0x06,   35 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      37,    0,  658,    2, 0x0a,   38 /* Public */,
      38,    0,  659,    2, 0x0a,   39 /* Public */,
      39,    1,  660,    2, 0x0a,   40 /* Public */,
      41,    0,  663,    2, 0x0a,   42 /* Public */,
      42,    0,  664,    2, 0x0a,   43 /* Public */,
      43,    1,  665,    2, 0x0a,   44 /* Public */,
      44,    1,  668,    2, 0x0a,   46 /* Public */,
      45,    1,  671,    2, 0x0a,   48 /* Public */,
      46,    1,  674,    2, 0x08,   50 /* Private */,
      48,    0,  677,    2, 0x08,   52 /* Private */,
      49,    1,  678,    2, 0x08,   53 /* Private */,
      50,    0,  681,    2, 0x08,   55 /* Private */,
      51,    1,  682,    2, 0x08,   56 /* Private */,
      52,    0,  685,    2, 0x08,   58 /* Private */,
      53,    1,  686,    2, 0x08,   59 /* Private */,
      54,    0,  689,    2, 0x08,   61 /* Private */,
      55,    1,  690,    2, 0x08,   62 /* Private */,
      56,    1,  693,    2, 0x08,   64 /* Private */,
      57,    1,  696,    2, 0x08,   66 /* Private */,
      58,    1,  699,    2, 0x08,   68 /* Private */,
      59,    1,  702,    2, 0x08,   70 /* Private */,
      60,    0,  705,    2, 0x08,   72 /* Private */,
      61,    1,  706,    2, 0x08,   73 /* Private */,
      62,    0,  709,    2, 0x08,   75 /* Private */,
      63,    1,  710,    2, 0x08,   76 /* Private */,
      64,    0,  713,    2, 0x08,   78 /* Private */,
      65,    1,  714,    2, 0x08,   79 /* Private */,
      66,    1,  717,    2, 0x08,   81 /* Private */,
      67,    1,  720,    2, 0x08,   83 /* Private */,
      68,    1,  723,    2, 0x08,   85 /* Private */,
      69,    1,  726,    2, 0x08,   87 /* Private */,
      70,    1,  729,    2, 0x08,   89 /* Private */,
      71,    1,  732,    2, 0x08,   91 /* Private */,
      72,    1,  735,    2, 0x08,   93 /* Private */,
      73,    1,  738,    2, 0x08,   95 /* Private */,
      76,    0,  741,    2, 0x08,   97 /* Private */,
      77,    0,  742,    2, 0x08,   98 /* Private */,
      78,    0,  743,    2, 0x08,   99 /* Private */,
      79,    1,  744,    2, 0x08,  100 /* Private */,
      80,    1,  747,    2, 0x08,  102 /* Private */,
      81,    1,  750,    2, 0x08,  104 /* Private */,
      82,    1,  753,    2, 0x08,  106 /* Private */,
      83,    0,  756,    2, 0x08,  108 /* Private */,
      84,    1,  757,    2, 0x08,  109 /* Private */,
      85,    0,  760,    2, 0x08,  111 /* Private */,
      86,    0,  761,    2, 0x08,  112 /* Private */,
      87,    1,  762,    2, 0x08,  113 /* Private */,
      88,    0,  765,    2, 0x08,  115 /* Private */,
      89,    0,  766,    2, 0x08,  116 /* Private */,
      90,    0,  767,    2, 0x08,  117 /* Private */,
      91,    0,  768,    2, 0x08,  118 /* Private */,
      92,    1,  769,    2, 0x08,  119 /* Private */,
      93,    1,  772,    2, 0x08,  121 /* Private */,
      94,    1,  775,    2, 0x08,  123 /* Private */,
      95,    1,  778,    2, 0x08,  125 /* Private */,
      96,    0,  781,    2, 0x08,  127 /* Private */,
      97,    1,  782,    2, 0x08,  128 /* Private */,
      98,    0,  785,    2, 0x08,  130 /* Private */,
      99,    1,  786,    2, 0x08,  131 /* Private */,
     100,    1,  789,    2, 0x08,  133 /* Private */,
     101,    1,  792,    2, 0x08,  135 /* Private */,
     102,    0,  795,    2, 0x08,  137 /* Private */,
     103,    1,  796,    2, 0x08,  138 /* Private */,
     104,    0,  799,    2, 0x08,  140 /* Private */,
     105,    1,  800,    2, 0x08,  141 /* Private */,
     106,    1,  803,    2, 0x08,  143 /* Private */,
     107,    1,  806,    2, 0x08,  145 /* Private */,
     108,    1,  809,    2, 0x08,  147 /* Private */,
     109,    1,  812,    2, 0x08,  149 /* Private */,
     110,    1,  815,    2, 0x08,  151 /* Private */,
     111,    1,  818,    2, 0x08,  153 /* Private */,
     112,    1,  821,    2, 0x08,  155 /* Private */,
     113,    1,  824,    2, 0x08,  157 /* Private */,
     114,    1,  827,    2, 0x08,  159 /* Private */,
     115,    1,  830,    2, 0x08,  161 /* Private */,
     116,    1,  833,    2, 0x08,  163 /* Private */,
     117,    1,  836,    2, 0x08,  165 /* Private */,
     118,    1,  839,    2, 0x08,  167 /* Private */,
     119,    1,  842,    2, 0x08,  169 /* Private */,
     120,    0,  845,    2, 0x08,  171 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   13,   14,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Bool, QMetaType::Float,   18,   19,   20,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int, QMetaType::QColor,   24,   26,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   24,   28,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Float,   32,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   35,   36,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   47,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   47,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, 0x80000000 | 74,   75,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   47,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   47,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SpeckleSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_ZN15SpeckleSettingsE.offsetsAndSizes,
    qt_meta_data_ZN15SpeckleSettingsE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN15SpeckleSettingsE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SpeckleSettings, std::true_type>,
        // method 'processModeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'displayLayoutChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QStringList *, std::false_type>,
        // method 'rawSettingsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'scSettingsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'overlaySettingsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cameraSettingsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rawDisplayRangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'scDisplayRangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'overlayToggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'overlayChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'roiAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'roiRemoved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'roiColorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'roiVisibilityToggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'showROICheckToggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'colorCameraExpChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'hotkeyStatusUpdate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'infoUpdate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'setWorkingDirectory'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_outputfile_browse_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleAllROIVisibility'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setCameraAOIValues'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleOverlaySource'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeSCmin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'changeSCmax'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'changeExposure'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'on_scmin_spin_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_scmin_spin_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_scmax_spin_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_scmax_spin_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_raw_min_spin_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_raw_min_spin_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_raw_max_spin_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_raw_max_spin_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ratio_min_spin_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_ratio_max_spin_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_scColorbar_checkBox_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_rawColorbar_checkBox_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_raw_list_combo_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_clear_raw_list_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_baseline_list_combo_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_clear_baseline_list_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_sc_list_combo_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_clear_image_list_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_autoset_baseline_check_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_enable_ratio_image_checkbox_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_show_raw_check_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_show_SC_check_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_sc_colormap_combo_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_ratio_colormap_combo_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_raw_colormap_combo_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_SatPixelColor_comboBox_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_ROI_list_widget_itemChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'on_add_ROI_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_remove_ROI_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ROI_color_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ROI_show_check_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_roiPlotCheckbox_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_roiPlotSaveCheckbox_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_roiPlotHistoryCheckbox_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_roiPlotLimitSpin_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_roiplot_autoscale_check_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_roiplot_ymin_spin_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_roiplot_ymax_spin_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_roiplot_rel_autoscale_check_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_roiplot_rel_ymax_spin_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_roiplot_rel_ymin_spin_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_roiPlotBaselineStart_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_roiPlotBaselineEnd_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_enable_overlay_checkBox_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_bg_src_comboBox_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_bg_cmap_comboBox_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_bg_min_spin_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_bg_min_spin_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_bg_max_spin_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_bg_max_spin_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_over_src_comboBox_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_over_cmap_comboBox_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_over_min_spin_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_over_min_spin_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_over_max_spin_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_over_max_spin_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_thresh_type_comboBox_activated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_over_blur_spin_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_alpha_enable_checkBox_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_over_Kmid_SpinBox_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_over_alpha_min_SpinBox_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_over_alpha_max_SpinBox_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_colorCameraExposure_SpinBox_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_compute_SC_check_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_save_raw_check_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_save_sc_check_toggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_exposure_time_spin_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_trigger_combo_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_GainSpin_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateSpeckleCamera'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_duration_TypeComboBox_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_acquireLength_lineEdit_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SpeckleSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SpeckleSettings *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->processModeChanged(); break;
        case 1: _t->displayLayoutChanged((*reinterpret_cast< std::add_pointer_t<QStringList*>>(_a[1]))); break;
        case 2: _t->rawSettingsChanged(); break;
        case 3: _t->scSettingsChanged(); break;
        case 4: _t->overlaySettingsChanged(); break;
        case 5: _t->cameraSettingsChanged(); break;
        case 6: _t->rawDisplayRangeChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 7: _t->scDisplayRangeChanged((*reinterpret_cast< std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2]))); break;
        case 8: _t->overlayToggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->overlayChanged((*reinterpret_cast< std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[4]))); break;
        case 10: _t->roiAdded(); break;
        case 11: _t->roiRemoved((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->roiColorChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[2]))); break;
        case 13: _t->roiVisibilityToggled((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 14: _t->showROICheckToggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 15: _t->colorCameraExpChanged((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 16: _t->hotkeyStatusUpdate(); break;
        case 17: _t->infoUpdate((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 18: _t->setWorkingDirectory(); break;
        case 19: _t->on_outputfile_browse_button_clicked(); break;
        case 20: _t->toggleAllROIVisibility((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 21: _t->setCameraAOIValues(); break;
        case 22: _t->toggleOverlaySource(); break;
        case 23: _t->changeSCmin((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 24: _t->changeSCmax((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 25: _t->changeExposure((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 26: _t->on_scmin_spin_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 27: _t->on_scmin_spin_editingFinished(); break;
        case 28: _t->on_scmax_spin_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 29: _t->on_scmax_spin_editingFinished(); break;
        case 30: _t->on_raw_min_spin_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 31: _t->on_raw_min_spin_editingFinished(); break;
        case 32: _t->on_raw_max_spin_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 33: _t->on_raw_max_spin_editingFinished(); break;
        case 34: _t->on_ratio_min_spin_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 35: _t->on_ratio_max_spin_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 36: _t->on_scColorbar_checkBox_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 37: _t->on_rawColorbar_checkBox_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 38: _t->on_raw_list_combo_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 39: _t->on_clear_raw_list_button_clicked(); break;
        case 40: _t->on_baseline_list_combo_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 41: _t->on_clear_baseline_list_button_clicked(); break;
        case 42: _t->on_sc_list_combo_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 43: _t->on_clear_image_list_button_clicked(); break;
        case 44: _t->on_autoset_baseline_check_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 45: _t->on_enable_ratio_image_checkbox_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 46: _t->on_show_raw_check_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 47: _t->on_show_SC_check_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 48: _t->on_sc_colormap_combo_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 49: _t->on_ratio_colormap_combo_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 50: _t->on_raw_colormap_combo_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 51: _t->on_SatPixelColor_comboBox_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 52: _t->on_ROI_list_widget_itemChanged((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 53: _t->on_add_ROI_button_clicked(); break;
        case 54: _t->on_remove_ROI_button_clicked(); break;
        case 55: _t->on_ROI_color_button_clicked(); break;
        case 56: _t->on_ROI_show_check_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 57: _t->on_roiPlotCheckbox_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 58: _t->on_roiPlotSaveCheckbox_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 59: _t->on_roiPlotHistoryCheckbox_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 60: _t->on_roiPlotLimitSpin_editingFinished(); break;
        case 61: _t->on_roiplot_autoscale_check_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 62: _t->on_roiplot_ymin_spin_editingFinished(); break;
        case 63: _t->on_roiplot_ymax_spin_editingFinished(); break;
        case 64: _t->on_roiplot_rel_autoscale_check_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 65: _t->on_roiplot_rel_ymax_spin_editingFinished(); break;
        case 66: _t->on_roiplot_rel_ymin_spin_editingFinished(); break;
        case 67: _t->on_roiPlotBaselineStart_editingFinished(); break;
        case 68: _t->on_roiPlotBaselineEnd_editingFinished(); break;
        case 69: _t->on_enable_overlay_checkBox_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 70: _t->on_bg_src_comboBox_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 71: _t->on_bg_cmap_comboBox_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 72: _t->on_bg_min_spin_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 73: _t->on_bg_min_spin_editingFinished(); break;
        case 74: _t->on_bg_max_spin_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 75: _t->on_bg_max_spin_editingFinished(); break;
        case 76: _t->on_over_src_comboBox_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 77: _t->on_over_cmap_comboBox_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 78: _t->on_over_min_spin_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 79: _t->on_over_min_spin_editingFinished(); break;
        case 80: _t->on_over_max_spin_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 81: _t->on_over_max_spin_editingFinished(); break;
        case 82: _t->on_thresh_type_comboBox_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 83: _t->on_over_blur_spin_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 84: _t->on_alpha_enable_checkBox_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 85: _t->on_over_Kmid_SpinBox_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 86: _t->on_over_alpha_min_SpinBox_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 87: _t->on_over_alpha_max_SpinBox_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 88: _t->on_colorCameraExposure_SpinBox_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 89: _t->on_compute_SC_check_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 90: _t->on_save_raw_check_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 91: _t->on_save_sc_check_toggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 92: _t->on_exposure_time_spin_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 93: _t->on_trigger_combo_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 94: _t->on_GainSpin_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 95: _t->updateSpeckleCamera((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 96: _t->on_duration_TypeComboBox_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 97: _t->on_acquireLength_lineEdit_editingFinished(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (SpeckleSettings::*)();
            if (_q_method_type _q_method = &SpeckleSettings::processModeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)(QStringList * );
            if (_q_method_type _q_method = &SpeckleSettings::displayLayoutChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)();
            if (_q_method_type _q_method = &SpeckleSettings::rawSettingsChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)();
            if (_q_method_type _q_method = &SpeckleSettings::scSettingsChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)();
            if (_q_method_type _q_method = &SpeckleSettings::overlaySettingsChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)();
            if (_q_method_type _q_method = &SpeckleSettings::cameraSettingsChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)(int , int );
            if (_q_method_type _q_method = &SpeckleSettings::rawDisplayRangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)(float , float );
            if (_q_method_type _q_method = &SpeckleSettings::scDisplayRangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)(bool );
            if (_q_method_type _q_method = &SpeckleSettings::overlayToggled; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)(float , float , bool , float );
            if (_q_method_type _q_method = &SpeckleSettings::overlayChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)();
            if (_q_method_type _q_method = &SpeckleSettings::roiAdded; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)(int );
            if (_q_method_type _q_method = &SpeckleSettings::roiRemoved; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)(int , QColor );
            if (_q_method_type _q_method = &SpeckleSettings::roiColorChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)(int , bool );
            if (_q_method_type _q_method = &SpeckleSettings::roiVisibilityToggled; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 13;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)(bool );
            if (_q_method_type _q_method = &SpeckleSettings::showROICheckToggled; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 14;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)(float );
            if (_q_method_type _q_method = &SpeckleSettings::colorCameraExpChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 15;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)();
            if (_q_method_type _q_method = &SpeckleSettings::hotkeyStatusUpdate; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 16;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleSettings::*)(int , QString );
            if (_q_method_type _q_method = &SpeckleSettings::infoUpdate; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 17;
                return;
            }
        }
    }
}

const QMetaObject *SpeckleSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpeckleSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN15SpeckleSettingsE.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SpeckleSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 98)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 98;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 98)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 98;
    }
    return _id;
}

// SIGNAL 0
void SpeckleSettings::processModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SpeckleSettings::displayLayoutChanged(QStringList * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SpeckleSettings::rawSettingsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SpeckleSettings::scSettingsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SpeckleSettings::overlaySettingsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void SpeckleSettings::cameraSettingsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void SpeckleSettings::rawDisplayRangeChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SpeckleSettings::scDisplayRangeChanged(float _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SpeckleSettings::overlayToggled(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void SpeckleSettings::overlayChanged(float _t1, float _t2, bool _t3, float _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void SpeckleSettings::roiAdded()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void SpeckleSettings::roiRemoved(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void SpeckleSettings::roiColorChanged(int _t1, QColor _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void SpeckleSettings::roiVisibilityToggled(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void SpeckleSettings::showROICheckToggled(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void SpeckleSettings::colorCameraExpChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void SpeckleSettings::hotkeyStatusUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void SpeckleSettings::infoUpdate(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}
QT_WARNING_POP
