/****************************************************************************
** Meta object code from reading C++ file 'qp_combobox.h'
**
** Created: Tue 1. Jul 11:48:30 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/qp_combobox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qp_combobox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QpComboBox[] = {

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
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   37,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QpComboBox[] = {
    "QpComboBox\0\0sig_commitData(QVariant)\0"
    "newVal\0slot_dataChanged_2(QVariant)\0"
};

void QpComboBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QpComboBox *_t = static_cast<QpComboBox *>(_o);
        switch (_id) {
        case 0: _t->sig_commitData((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 1: _t->slot_dataChanged_2((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QpComboBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QpComboBox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_QpComboBox,
      qt_meta_data_QpComboBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QpComboBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QpComboBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QpComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QpComboBox))
        return static_cast<void*>(const_cast< QpComboBox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int QpComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
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
void QpComboBox::sig_commitData(const QVariant & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
