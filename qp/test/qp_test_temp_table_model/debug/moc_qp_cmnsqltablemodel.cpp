/****************************************************************************
** Meta object code from reading C++ file 'qp_cmnsqltablemodel.h'
**
** Created: Tue 1. Jul 11:06:29 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../db/model/qp_cmnsqltablemodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qp_cmnsqltablemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QpCmnSqlTableModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      78,   74,   19,   19, 0x05,
      98,   19,   19,   19, 0x05,
     120,   19,   19,   19, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QpCmnSqlTableModel[] = {
    "QpCmnSqlTableModel\0\0"
    "sig_editStrategyChanged(QSqlTableModel::EditStrategy)\0"
    "row\0sig_rowIsDirty(int)\0sig_afterSelect(bool)\0"
    "sig_select_exec()\0"
};

void QpCmnSqlTableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QpCmnSqlTableModel *_t = static_cast<QpCmnSqlTableModel *>(_o);
        switch (_id) {
        case 0: _t->sig_editStrategyChanged((*reinterpret_cast< QSqlTableModel::EditStrategy(*)>(_a[1]))); break;
        case 1: _t->sig_rowIsDirty((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sig_afterSelect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->sig_select_exec(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QpCmnSqlTableModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QpCmnSqlTableModel::staticMetaObject = {
    { &QSqlTableModel::staticMetaObject, qt_meta_stringdata_QpCmnSqlTableModel,
      qt_meta_data_QpCmnSqlTableModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QpCmnSqlTableModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QpCmnSqlTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QpCmnSqlTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QpCmnSqlTableModel))
        return static_cast<void*>(const_cast< QpCmnSqlTableModel*>(this));
    if (!strcmp(_clname, "QpAbstractTableModel"))
        return static_cast< QpAbstractTableModel*>(const_cast< QpCmnSqlTableModel*>(this));
    return QSqlTableModel::qt_metacast(_clname);
}

int QpCmnSqlTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSqlTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QpCmnSqlTableModel::sig_editStrategyChanged(QSqlTableModel::EditStrategy _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QpCmnSqlTableModel::sig_rowIsDirty(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QpCmnSqlTableModel::sig_afterSelect(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QpCmnSqlTableModel::sig_select_exec()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
