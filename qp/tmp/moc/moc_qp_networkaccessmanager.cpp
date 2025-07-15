/****************************************************************************
** Meta object code from reading C++ file 'qp_networkaccessmanager.h'
**
** Created: Tue 11. Mar 14:31:18 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ntw/qp_networkaccessmanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qp_networkaccessmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QpNetworkAccessManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      35,   24,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QpNetworkAccessManager[] = {
    "QpNetworkAccessManager\0\0reply,list\0"
    "slot_sslErrors(QNetworkReply*,QList<QSslError>)\0"
};

void QpNetworkAccessManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QpNetworkAccessManager *_t = static_cast<QpNetworkAccessManager *>(_o);
        switch (_id) {
        case 0: _t->slot_sslErrors((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QList<QSslError>(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QpNetworkAccessManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QpNetworkAccessManager::staticMetaObject = {
    { &QNetworkAccessManager::staticMetaObject, qt_meta_stringdata_QpNetworkAccessManager,
      qt_meta_data_QpNetworkAccessManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QpNetworkAccessManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QpNetworkAccessManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QpNetworkAccessManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QpNetworkAccessManager))
        return static_cast<void*>(const_cast< QpNetworkAccessManager*>(this));
    return QNetworkAccessManager::qt_metacast(_clname);
}

int QpNetworkAccessManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QNetworkAccessManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
