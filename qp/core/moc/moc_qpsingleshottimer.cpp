/****************************************************************************
** Meta object code from reading C++ file 'qpsingleshottimer.h'
**
** Created: Mon 14. Jul 18:10:42 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../meta/qpsingleshottimer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qpsingleshottimer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QpSingleShotTimer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      36,   19,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      95,   70,   65,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QpSingleShotTimer[] = {
    "QpSingleShotTimer\0\0resInvokeMethod,\0"
    "sig_retResult(bool,QVariant)\0bool\0"
    "obj,slot_name,map,retVal\0"
    "invokeMethod_slot_byName_withPars(const QObject*,QString,QList<QVarian"
    "t>,QVariant&)\0"
};

void QpSingleShotTimer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QpSingleShotTimer *_t = static_cast<QpSingleShotTimer *>(_o);
        switch (_id) {
        case 0: _t->sig_retResult((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 1: { bool _r = _t->invokeMethod_slot_byName_withPars((*reinterpret_cast< const QObject*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QList<QVariant>(*)>(_a[3])),(*reinterpret_cast< QVariant(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QpSingleShotTimer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QpSingleShotTimer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QpSingleShotTimer,
      qt_meta_data_QpSingleShotTimer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QpSingleShotTimer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QpSingleShotTimer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QpSingleShotTimer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QpSingleShotTimer))
        return static_cast<void*>(const_cast< QpSingleShotTimer*>(this));
    return QObject::qt_metacast(_clname);
}

int QpSingleShotTimer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QpSingleShotTimer::sig_retResult(bool _t1, const QVariant & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
