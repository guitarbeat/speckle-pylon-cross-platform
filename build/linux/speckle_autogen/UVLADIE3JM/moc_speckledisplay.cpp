/****************************************************************************
** Meta object code from reading C++ file 'speckledisplay.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/speckledisplay.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'speckledisplay.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14SpeckleDisplayE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN14SpeckleDisplayE = QtMocHelpers::stringData(
    "SpeckleDisplay",
    "scCtrlPointsChanged",
    "",
    "polygon",
    "videoCtrlPointsChanged",
    "roiAdded",
    "color",
    "allROIVisibilityToggled",
    "show",
    "cameraAOISelected",
    "rect",
    "toggleHideOverlay",
    "incrementSCmin",
    "incrementSCmax",
    "incrementExposure",
    "updateRaw",
    "QPixmap*",
    "fps",
    "updateSC",
    "updateOverlay",
    "updateVideoIn",
    "srcImgChanged",
    "QAction*",
    "action",
    "toggleFitMode",
    "checked",
    "isLive",
    "status",
    "toggleFPSOverlay",
    "updateInfo",
    "type",
    "text",
    "exportImage",
    "popoutWindow",
    "addROI",
    "removeROI",
    "idx",
    "updateROIColor",
    "setROIVisibility",
    "is_visible",
    "toggleShowROICheck",
    "setSCCtrlPoints",
    "setVideoCtrlPoints"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN14SpeckleDisplayE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  176,    2, 0x06,    1 /* Public */,
       4,    1,  179,    2, 0x06,    3 /* Public */,
       5,    2,  182,    2, 0x06,    5 /* Public */,
       7,    1,  187,    2, 0x06,    8 /* Public */,
       9,    1,  190,    2, 0x06,   10 /* Public */,
      11,    0,  193,    2, 0x06,   12 /* Public */,
      12,    1,  194,    2, 0x06,   13 /* Public */,
      13,    1,  197,    2, 0x06,   15 /* Public */,
      14,    1,  200,    2, 0x06,   17 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      15,    2,  203,    2, 0x0a,   19 /* Public */,
      18,    2,  208,    2, 0x0a,   22 /* Public */,
      19,    2,  213,    2, 0x0a,   25 /* Public */,
      20,    2,  218,    2, 0x0a,   28 /* Public */,
      21,    1,  223,    2, 0x0a,   31 /* Public */,
      24,    1,  226,    2, 0x0a,   33 /* Public */,
      26,    1,  229,    2, 0x0a,   35 /* Public */,
      28,    1,  232,    2, 0x0a,   37 /* Public */,
      29,    2,  235,    2, 0x0a,   39 /* Public */,
      32,    0,  240,    2, 0x0a,   42 /* Public */,
      33,    0,  241,    2, 0x0a,   43 /* Public */,
      34,    0,  242,    2, 0x0a,   44 /* Public */,
      35,    1,  243,    2, 0x0a,   45 /* Public */,
      37,    2,  246,    2, 0x0a,   47 /* Public */,
      38,    2,  251,    2, 0x0a,   50 /* Public */,
      40,    1,  256,    2, 0x0a,   53 /* Public */,
      41,    1,  259,    2, 0x0a,   55 /* Public */,
      42,    1,  262,    2, 0x0a,   57 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPolygonF,    3,
    QMetaType::Void, QMetaType::QPolygonF,    3,
    QMetaType::Void, QMetaType::QPolygonF, QMetaType::QColor,    3,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::QRectF,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Float,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,    2,   17,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,    2,   17,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,    2,   17,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,    2,   17,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, QMetaType::Bool,   25,
    QMetaType::Void, QMetaType::Bool,   27,
    QMetaType::Void, QMetaType::Bool,   27,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   30,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   36,
    QMetaType::Void, QMetaType::Int, QMetaType::QColor,   36,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   36,   39,
    QMetaType::Void, QMetaType::Bool,   25,
    QMetaType::Void, QMetaType::QPolygonF,    3,
    QMetaType::Void, QMetaType::QPolygonF,    3,

       0        // eod
};

Q_CONSTINIT const QMetaObject SpeckleDisplay::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_ZN14SpeckleDisplayE.offsetsAndSizes,
    qt_meta_data_ZN14SpeckleDisplayE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN14SpeckleDisplayE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SpeckleDisplay, std::true_type>,
        // method 'scCtrlPointsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPolygonF, std::false_type>,
        // method 'videoCtrlPointsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPolygonF, std::false_type>,
        // method 'roiAdded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPolygonF, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'allROIVisibilityToggled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'cameraAOISelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QRectF, std::false_type>,
        // method 'toggleHideOverlay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'incrementSCmin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'incrementSCmax'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'incrementExposure'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'updateRaw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateSC'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateOverlay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateVideoIn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'srcImgChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAction *, std::false_type>,
        // method 'toggleFitMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'isLive'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'toggleFPSOverlay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'updateInfo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'exportImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'popoutWindow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addROI'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeROI'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateROIColor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'setROIVisibility'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'toggleShowROICheck'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setSCCtrlPoints'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPolygonF, std::false_type>,
        // method 'setVideoCtrlPoints'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPolygonF, std::false_type>
    >,
    nullptr
} };

void SpeckleDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SpeckleDisplay *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->scCtrlPointsChanged((*reinterpret_cast< std::add_pointer_t<QPolygonF>>(_a[1]))); break;
        case 1: _t->videoCtrlPointsChanged((*reinterpret_cast< std::add_pointer_t<QPolygonF>>(_a[1]))); break;
        case 2: _t->roiAdded((*reinterpret_cast< std::add_pointer_t<QPolygonF>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[2]))); break;
        case 3: _t->allROIVisibilityToggled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->cameraAOISelected((*reinterpret_cast< std::add_pointer_t<QRectF>>(_a[1]))); break;
        case 5: _t->toggleHideOverlay(); break;
        case 6: _t->incrementSCmin((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 7: _t->incrementSCmax((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 8: _t->incrementExposure((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 9: _t->updateRaw((*reinterpret_cast< std::add_pointer_t<QPixmap*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 10: _t->updateSC((*reinterpret_cast< std::add_pointer_t<QPixmap*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 11: _t->updateOverlay((*reinterpret_cast< std::add_pointer_t<QPixmap*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 12: _t->updateVideoIn((*reinterpret_cast< std::add_pointer_t<QPixmap*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 13: _t->srcImgChanged((*reinterpret_cast< std::add_pointer_t<QAction*>>(_a[1]))); break;
        case 14: _t->toggleFitMode((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 15: _t->isLive((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 16: _t->toggleFPSOverlay((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 17: _t->updateInfo((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 18: _t->exportImage(); break;
        case 19: _t->popoutWindow(); break;
        case 20: _t->addROI(); break;
        case 21: _t->removeROI((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 22: _t->updateROIColor((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[2]))); break;
        case 23: _t->setROIVisibility((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 24: _t->toggleShowROICheck((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 25: _t->setSCCtrlPoints((*reinterpret_cast< std::add_pointer_t<QPolygonF>>(_a[1]))); break;
        case 26: _t->setVideoCtrlPoints((*reinterpret_cast< std::add_pointer_t<QPolygonF>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAction* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (SpeckleDisplay::*)(QPolygonF );
            if (_q_method_type _q_method = &SpeckleDisplay::scCtrlPointsChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleDisplay::*)(QPolygonF );
            if (_q_method_type _q_method = &SpeckleDisplay::videoCtrlPointsChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleDisplay::*)(QPolygonF , QColor );
            if (_q_method_type _q_method = &SpeckleDisplay::roiAdded; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleDisplay::*)(bool );
            if (_q_method_type _q_method = &SpeckleDisplay::allROIVisibilityToggled; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleDisplay::*)(QRectF );
            if (_q_method_type _q_method = &SpeckleDisplay::cameraAOISelected; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleDisplay::*)();
            if (_q_method_type _q_method = &SpeckleDisplay::toggleHideOverlay; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleDisplay::*)(float );
            if (_q_method_type _q_method = &SpeckleDisplay::incrementSCmin; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleDisplay::*)(float );
            if (_q_method_type _q_method = &SpeckleDisplay::incrementSCmax; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (SpeckleDisplay::*)(float );
            if (_q_method_type _q_method = &SpeckleDisplay::incrementExposure; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject *SpeckleDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpeckleDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN14SpeckleDisplayE.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int SpeckleDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void SpeckleDisplay::scCtrlPointsChanged(QPolygonF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SpeckleDisplay::videoCtrlPointsChanged(QPolygonF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SpeckleDisplay::roiAdded(QPolygonF _t1, QColor _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SpeckleDisplay::allROIVisibilityToggled(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SpeckleDisplay::cameraAOISelected(QRectF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SpeckleDisplay::toggleHideOverlay()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void SpeckleDisplay::incrementSCmin(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SpeckleDisplay::incrementSCmax(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SpeckleDisplay::incrementExposure(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
