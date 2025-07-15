/****************************************************************************
** Meta object code from reading C++ file 'qp_sqltablemodel.h'
**
** Created: Tue 15. Jul 17:01:59 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../model/qp_sqltablemodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qp_sqltablemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QpSqlTableModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   17,   16,   16, 0x0a,
      80,   72,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QpSqlTableModel[] = {
    "QpSqlTableModel\0\0strategy\0"
    "setEditStrategy(QSqlTableModel::EditStrategy)\0"
    "row,rec\0slot_primeInsert(int,QSqlRecord&)\0"
};

void QpSqlTableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QpSqlTableModel *_t = static_cast<QpSqlTableModel *>(_o);
        switch (_id) {
        case 0: _t->setEditStrategy((*reinterpret_cast< QSqlTableModel::EditStrategy(*)>(_a[1]))); break;
        case 1: _t->slot_primeInsert((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QSqlRecord(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QpSqlTableModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QpSqlTableModel::staticMetaObject = {
    { &QpCmnSqlTableModel::staticMetaObject, qt_meta_stringdata_QpSqlTableModel,
      qt_meta_data_QpSqlTableModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QpSqlTableModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QpSqlTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QpSqlTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QpSqlTableModel))
        return static_cast<void*>(const_cast< QpSqlTableModel*>(this));
    return QpCmnSqlTableModel::qt_metacast(_clname);
}

int QpSqlTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QpCmnSqlTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
