/****************************************************************************
** Meta object code from reading C++ file 'specklewindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/specklewindow.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qabstractbarseries.h>
#include <QtCharts/qvbarmodelmapper.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCharts/qcandlestickseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'specklewindow.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13SpeckleWindowE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13SpeckleWindowE = QtMocHelpers::stringData(
    "SpeckleWindow",
    "startAcquisition",
    "",
    "stopAcquisition",
    "isLive",
    "status",
    "stopPressed",
    "updateAcquisitionStatus",
    "addNewROI",
    "polygon",
    "color",
    "updateSCControlPoints",
    "updateVideoInControlPoints",
    "on_actionLive",
    "on_actionStop",
    "on_actionRecord",
    "on_actionShowSettings",
    "on_actionShowHistogram",
    "exportRawImage",
    "exportSCImage",
    "exportOverlayImage",
    "showCameraInfo",
    "showAboutDialog",
    "saveSettings",
    "loadSettings",
    "showMissingActionAlert",
    "acquisitionComplete",
    "on_refreshCamerasAction",
    "histogramClosed",
    "on_actionAlignQR",
    "loadVideoTform",
    "saveVideoTform",
    "startStopVideoIn",
    "updateHotkeyStatus"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13SpeckleWindowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  188,    2, 0x06,    1 /* Public */,
       3,    0,  189,    2, 0x06,    2 /* Public */,
       4,    1,  190,    2, 0x06,    3 /* Public */,
       6,    0,  193,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,  194,    2, 0x08,    6 /* Private */,
       8,    2,  195,    2, 0x08,    7 /* Private */,
      11,    1,  200,    2, 0x08,   10 /* Private */,
      12,    1,  203,    2, 0x08,   12 /* Private */,
      13,    0,  206,    2, 0x08,   14 /* Private */,
      14,    0,  207,    2, 0x08,   15 /* Private */,
      15,    0,  208,    2, 0x08,   16 /* Private */,
      16,    0,  209,    2, 0x08,   17 /* Private */,
      17,    0,  210,    2, 0x08,   18 /* Private */,
      18,    0,  211,    2, 0x08,   19 /* Private */,
      19,    0,  212,    2, 0x08,   20 /* Private */,
      20,    0,  213,    2, 0x08,   21 /* Private */,
      21,    0,  214,    2, 0x08,   22 /* Private */,
      22,    0,  215,    2, 0x08,   23 /* Private */,
      23,    0,  216,    2, 0x08,   24 /* Private */,
      24,    0,  217,    2, 0x08,   25 /* Private */,
      25,    0,  218,    2, 0x08,   26 /* Private */,
      26,    0,  219,    2, 0x08,   27 /* Private */,
      27,    0,  220,    2, 0x08,   28 /* Private */,
      28,    0,  221,    2, 0x08,   29 /* Private */,
      29,    0,  222,    2, 0x08,   30 /* Private */,
      30,    0,  223,    2, 0x08,   31 /* Private */,
      31,    0,  224,    2, 0x08,   32 /* Private */,
      32,    0,  225,    2, 0x08,   33 /* Private */,
      33,    0,  226,    2, 0x08,   34 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPolygonF, QMetaType::QColor,    9,   10,
    QMetaType::Void, QMetaType::QPolygonF,    9,
    QMetaType::Void, QMetaType::QPolygonF,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SpeckleWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN13SpeckleWindowE.offsetsAndSizes,
    qt_meta_data_ZN13SpeckleWindowE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13SpeckleWindowE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SpeckleWindow, std::true_type>,
        // method 'startAcquisition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopAcquisition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'isLive'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'stopPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateAcquisitionStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addNewROI'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPolygonF, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'updateSCControlPoints'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPolygonF, std::false_type>,
        // method 'updateVideoInControlPoints'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPolygonF, std::false_type>,
        // method 'on_actionLive'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionStop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionRecord'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionShowSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionShowHistogram'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exportRawImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exportSCImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exportOverlayImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showCameraInfo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showAboutDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showMissingActionAlert'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'acquisitionComplete'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_refreshCamerasAction'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'histogramClosed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionAlignQR'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadVideoTform'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveVideoTform'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startStopVideoIn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateHotkeyStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SpeckleWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SpeckleWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->startAcquisition(); break;
        case 1: _t->stopAcquisition(); break;
        case 2: _t->isLive((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->stopPressed(); break;
        case 4: _t->updateAcquisitionStatus(); break;
        case 5: _t->addNewROI((*reinterpret_cast< std::add_pointer_t<QPolygonF>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[2]))); break;
        case 6: _t->updateSCControlPoints((*reinterpret_cast< std::add_pointer_t<QPolygonF>>(_a[1]))); break;
        case 7: _t->updateVideoInControlPoints((*reinterpret_cast< std::add_pointer_t<QPolygonF>>(_a[1]))); break;
        case 8: _t->on_actionLive(); break;
        case 9: _t->on_actionStop(); break;
        case 10: _t->on_actionRecord(); break;
        case 11: _t->on_actionShowSettings(); break;
        case 12: _t->on_actionShowHistogram(); break;
        case 13: _t->exportRawImage(); break;
        case 14: _t->exportSCImage(); break;
        case 15: _t->exportOverlayImage(); break;
        case 16: _t->showCameraInfo(); break;
        case 17: _t->showAboutDialog(); break;
        case 18: _t->saveSettings(); break;
        case 19: _t->loadSettings(); break;
        case 20: _t->showMissingActionAlert(); break;
        case 21: _t->acquisitionComplete(); break;
        case 22: _t->on_refreshCamerasAction(); break;
        case 23: _t->histogramClosed(); break;
        case 24: _t->on_actionAlignQR(); break;
        case 25: _t->loadVideoTform(); break;
        case 26: _t->saveVideoTform(); break;
        case 27: _t->startStopVideoIn(); break;
        case 28: _t->updateHotkeyStatus(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (SpeckleWindow::*)();
            if (_q_method_type _q_method = &SpeckleWindow::startAcquisition; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleWindow::*)();
            if (_q_method_type _q_method = &SpeckleWindow::stopAcquisition; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleWindow::*)(bool );
            if (_q_method_type _q_method = &SpeckleWindow::isLive; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleWindow::*)();
            if (_q_method_type _q_method = &SpeckleWindow::stopPressed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *SpeckleWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpeckleWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN13SpeckleWindowE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int SpeckleWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 29;
    }
    return _id;
}

// SIGNAL 0
void SpeckleWindow::startAcquisition()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SpeckleWindow::stopAcquisition()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SpeckleWindow::isLive(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SpeckleWindow::stopPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
