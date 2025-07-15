/****************************************************************************
** Meta object code from reading C++ file 'qp_temptablemodel.h'
**
** Created: Tue 15. Jul 17:01:59 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../model/qp_temptablemodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qp_temptablemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QpTempSqlTableModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   20,   52,   20, 0x0a,
      66,   20,   52,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QpTempSqlTableModel[] = {
    "QpTempSqlTableModel\0\0"
    "sig_column_values_changed(int)\0bool\0"
    "submit()\0submitAll()\0"
};

void QpTempSqlTableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QpTempSqlTableModel *_t = static_cast<QpTempSqlTableModel *>(_o);
        switch (_id) {
        case 0: _t->sig_column_values_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: { bool _r = _t->submit();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->submitAll();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QpTempSqlTableModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QpTempSqlTableModel::staticMetaObject = {
    { &QpCmnSqlTableModel::staticMetaObject, qt_meta_stringdata_QpTempSqlTableModel,
      qt_meta_data_QpTempSqlTableModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QpTempSqlTableModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QpTempSqlTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QpTempSqlTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QpTempSqlTableModel))
        return static_cast<void*>(const_cast< QpTempSqlTableModel*>(this));
    return QpCmnSqlTableModel::qt_metacast(_clname);
}

int QpTempSqlTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QpCmnSqlTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QpTempSqlTableModel::sig_column_values_changed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
