/****************************************************************************
** Meta object code from reading C++ file 'qp_table_dlg.h'
**
** Created: Tue 1. Jul 11:06:31 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../db/view/qp_table_dlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qp_table_dlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QpTableDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      28,   11,   11,   11, 0x0a,
      59,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QpTableDlg[] = {
    "QpTableDlg\0\0slot_accepted()\0"
    "slot_view_clicked(QModelIndex)\0"
    "on_btn_close_clicked()\0"
};

void QpTableDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QpTableDlg *_t = static_cast<QpTableDlg *>(_o);
        switch (_id) {
        case 0: _t->slot_accepted(); break;
        case 1: _t->slot_view_clicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: _t->on_btn_close_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QpTableDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QpTableDlg::staticMetaObject = {
    { &SizeRememberDlg::staticMetaObject, qt_meta_stringdata_QpTableDlg,
      qt_meta_data_QpTableDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QpTableDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QpTableDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QpTableDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QpTableDlg))
        return static_cast<void*>(const_cast< QpTableDlg*>(this));
    return SizeRememberDlg::qt_metacast(_clname);
}

int QpTableDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SizeRememberDlg::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
