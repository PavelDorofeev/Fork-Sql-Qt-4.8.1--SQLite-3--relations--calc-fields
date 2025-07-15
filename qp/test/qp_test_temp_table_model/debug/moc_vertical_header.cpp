/****************************************************************************
** Meta object code from reading C++ file 'vertical_header.h'
**
** Created: Tue 1. Jul 11:06:31 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../db/view/vertical_header.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vertical_header.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Vertical_Header[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_Vertical_Header[] = {
    "Vertical_Header\0"
};

void Vertical_Header::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Vertical_Header::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Vertical_Header::staticMetaObject = {
    { &QHeaderView::staticMetaObject, qt_meta_stringdata_Vertical_Header,
      qt_meta_data_Vertical_Header, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Vertical_Header::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Vertical_Header::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Vertical_Header::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Vertical_Header))
        return static_cast<void*>(const_cast< Vertical_Header*>(this));
    return QHeaderView::qt_metacast(_clname);
}

int Vertical_Header::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHeaderView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
