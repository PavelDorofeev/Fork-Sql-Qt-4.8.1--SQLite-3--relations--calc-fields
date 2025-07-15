/****************************************************************************
** Meta object code from reading C++ file 'search_settings_dlg.h'
**
** Created: Tue 11. Mar 14:31:16 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../db/view/search_settings_dlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'search_settings_dlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Search_Settings_Dlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      44,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      75,   20,   20,   20, 0x0a,
     111,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Search_Settings_Dlg[] = {
    "Search_Settings_Dlg\0\0sig_setFilter(QString)\0"
    "sig_setSettings(FIND_SETTINGS)\0"
    "cmb_Fields_currentIndexChanged(int)\0"
    "on_buttonBox_accepted()\0"
};

void Search_Settings_Dlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Search_Settings_Dlg *_t = static_cast<Search_Settings_Dlg *>(_o);
        switch (_id) {
        case 0: _t->sig_setFilter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sig_setSettings((*reinterpret_cast< FIND_SETTINGS(*)>(_a[1]))); break;
        case 2: _t->cmb_Fields_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_buttonBox_accepted(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Search_Settings_Dlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Search_Settings_Dlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Search_Settings_Dlg,
      qt_meta_data_Search_Settings_Dlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Search_Settings_Dlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Search_Settings_Dlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Search_Settings_Dlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Search_Settings_Dlg))
        return static_cast<void*>(const_cast< Search_Settings_Dlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int Search_Settings_Dlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void Search_Settings_Dlg::sig_setFilter(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Search_Settings_Dlg::sig_setSettings(FIND_SETTINGS _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
