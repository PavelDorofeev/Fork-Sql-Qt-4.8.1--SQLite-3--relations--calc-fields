/****************************************************************************
** Meta object code from reading C++ file 'qp_pretty_evt_loop.h'
**
** Created: Tue 15. Jul 17:01:34 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../evt/qp_pretty_evt_loop.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qp_pretty_evt_loop.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QpPrettyEvtLoop[] = {

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
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QpPrettyEvtLoop[] = {
    "QpPrettyEvtLoop\0\0sig_evt()\0slot_quit()\0"
};

void QpPrettyEvtLoop::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QpPrettyEvtLoop *_t = static_cast<QpPrettyEvtLoop *>(_o);
        switch (_id) {
        case 0: _t->sig_evt(); break;
        case 1: _t->slot_quit(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QpPrettyEvtLoop::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QpPrettyEvtLoop::staticMetaObject = {
    { &QEventLoop::staticMetaObject, qt_meta_stringdata_QpPrettyEvtLoop,
      qt_meta_data_QpPrettyEvtLoop, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QpPrettyEvtLoop::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QpPrettyEvtLoop::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QpPrettyEvtLoop::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QpPrettyEvtLoop))
        return static_cast<void*>(const_cast< QpPrettyEvtLoop*>(this));
    return QEventLoop::qt_metacast(_clname);
}

int QpPrettyEvtLoop::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QEventLoop::qt_metacall(_c, _id, _a);
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
void QpPrettyEvtLoop::sig_evt()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
