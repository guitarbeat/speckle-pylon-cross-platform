/****************************************************************************
** Meta object code from reading C++ file 'liveimagecreator.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/liveimagecreator.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'liveimagecreator.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN16LiveImageCreatorE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN16LiveImageCreatorE = QtMocHelpers::stringData(
    "LiveImageCreator",
    "liveImageReady",
    "",
    "QPixmap*",
    "fps",
    "histogramReady",
    "CImg<float>*",
    "histogram",
    "checkForLiveImage",
    "startWatchAcquisition",
    "stopWatchAcquisition",
    "updateLiveImage"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN16LiveImageCreatorE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   50,    2, 0x06,    1 /* Public */,
       5,    1,   55,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,   58,    2, 0x0a,    6 /* Public */,
       9,    0,   59,    2, 0x0a,    7 /* Public */,
      10,    0,   60,    2, 0x0a,    8 /* Public */,
      11,    0,   61,    2, 0x0a,    9 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject LiveImageCreator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN16LiveImageCreatorE.offsetsAndSizes,
    qt_meta_data_ZN16LiveImageCreatorE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN16LiveImageCreatorE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<LiveImageCreator, std::true_type>,
        // method 'liveImageReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'histogramReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<CImg<float> *, std::false_type>,
        // method 'checkForLiveImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startWatchAcquisition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopWatchAcquisition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateLiveImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void LiveImageCreator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LiveImageCreator *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->liveImageReady((*reinterpret_cast< std::add_pointer_t<QPixmap*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->histogramReady((*reinterpret_cast< std::add_pointer_t<CImg<float>*>>(_a[1]))); break;
        case 2: _t->checkForLiveImage(); break;
        case 3: _t->startWatchAcquisition(); break;
        case 4: _t->stopWatchAcquisition(); break;
        case 5: _t->updateLiveImage(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (LiveImageCreator::*)(QPixmap * , int );
            if (_q_method_type _q_method = &LiveImageCreator::liveImageReady; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (LiveImageCreator::*)(CImg<float> * );
            if (_q_method_type _q_method = &LiveImageCreator::histogramReady; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *LiveImageCreator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LiveImageCreator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN16LiveImageCreatorE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LiveImageCreator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void LiveImageCreator::liveImageReady(QPixmap * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LiveImageCreator::histogramReady(CImg<float> * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
