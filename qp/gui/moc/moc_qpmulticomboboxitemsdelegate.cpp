/****************************************************************************
** Meta object code from reading C++ file 'qpmulticomboboxitemsdelegate.h'
**
** Created: Mon 14. Jul 18:10:58 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qpmulticomboboxitemsdelegate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qpmulticomboboxitemsdelegate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QpMultiComboBoxItemsDelegate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   29,   29,   29, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QpMultiComboBoxItemsDelegate[] = {
    "QpMultiComboBoxItemsDelegate\0\0"
    "sig_something_changed()\0"
};

void QpMultiComboBoxItemsDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QpMultiComboBoxItemsDelegate *_t = static_cast<QpMultiComboBoxItemsDelegate *>(_o);
        switch (_id) {
        case 0: _t->sig_something_changed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QpMultiComboBoxItemsDelegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QpMultiComboBoxItemsDelegate::staticMetaObject = {
    { &QStyledItemDelegate::staticMetaObject, qt_meta_stringdata_QpMultiComboBoxItemsDelegate,
      qt_meta_data_QpMultiComboBoxItemsDelegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QpMultiComboBoxItemsDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QpMultiComboBoxItemsDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QpMultiComboBoxItemsDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QpMultiComboBoxItemsDelegate))
        return static_cast<void*>(const_cast< QpMultiComboBoxItemsDelegate*>(this));
    return QStyledItemDelegate::qt_metacast(_clname);
}

int QpMultiComboBoxItemsDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStyledItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void QpMultiComboBoxItemsDelegate::sig_something_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
