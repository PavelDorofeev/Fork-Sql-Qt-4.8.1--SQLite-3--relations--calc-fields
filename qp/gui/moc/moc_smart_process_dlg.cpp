/****************************************************************************
** Meta object code from reading C++ file 'smart_process_dlg.h'
**
** Created: Mon 14. Jul 18:10:58 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../smart_process_dlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'smart_process_dlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Smart_Process_Dlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      37,   19,   18,   18, 0x0a,
      84,   74,   18,   18, 0x0a,
     112,   18,   18,   18, 0x0a,
     142,  140,   18,   18, 0x0a,
     169,   18,   18,   18, 0x08,
     209,  192,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Smart_Process_Dlg[] = {
    "Smart_Process_Dlg\0\0description,style\0"
    "slot_log(QString,qp::gui::LOG_STYLE)\0"
    "str,error\0slot_finished(QString,bool)\0"
    "slot_linkActivated(QString)\0,\0"
    "slot_rangeChanged(int,int)\0"
    "on_btn_Close_clicked()\0resInvokeMethod,\0"
    "slot_retResult(bool,QVariant)\0"
};

void Smart_Process_Dlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Smart_Process_Dlg *_t = static_cast<Smart_Process_Dlg *>(_o);
        switch (_id) {
        case 0: _t->slot_log((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< qp::gui::LOG_STYLE(*)>(_a[2]))); break;
        case 1: _t->slot_finished((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->slot_linkActivated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->slot_rangeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->on_btn_Close_clicked(); break;
        case 5: _t->slot_retResult((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Smart_Process_Dlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Smart_Process_Dlg::staticMetaObject = {
    { &SizeRememberDlg::staticMetaObject, qt_meta_stringdata_Smart_Process_Dlg,
      qt_meta_data_Smart_Process_Dlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Smart_Process_Dlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Smart_Process_Dlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Smart_Process_Dlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Smart_Process_Dlg))
        return static_cast<void*>(const_cast< Smart_Process_Dlg*>(this));
    return SizeRememberDlg::qt_metacast(_clname);
}

int Smart_Process_Dlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SizeRememberDlg::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
