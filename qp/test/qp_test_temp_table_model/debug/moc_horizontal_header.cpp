/****************************************************************************
** Meta object code from reading C++ file 'horizontal_header.h'
**
** Created: Tue 1. Jul 11:06:30 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../db/view/horizontal_header.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'horizontal_header.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Horizontal_Header[] = {

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
      19,   18,   18,   18, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Horizontal_Header[] = {
    "Horizontal_Header\0\0sig_needsReselect(QList<int>)\0"
};

void Horizontal_Header::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Horizontal_Header *_t = static_cast<Horizontal_Header *>(_o);
        switch (_id) {
        case 0: _t->sig_needsReselect((*reinterpret_cast< QList<int>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Horizontal_Header::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Horizontal_Header::staticMetaObject = {
    { &QHeaderView::staticMetaObject, qt_meta_stringdata_Horizontal_Header,
      qt_meta_data_Horizontal_Header, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Horizontal_Header::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Horizontal_Header::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Horizontal_Header::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Horizontal_Header))
        return static_cast<void*>(const_cast< Horizontal_Header*>(this));
    return QHeaderView::qt_metacast(_clname);
}

int Horizontal_Header::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHeaderView::qt_metacall(_c, _id, _a);
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
void Horizontal_Header::sig_needsReselect(QList<int> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
