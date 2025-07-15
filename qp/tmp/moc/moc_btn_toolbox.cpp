/****************************************************************************
** Meta object code from reading C++ file 'btn_toolbox.h'
**
** Created: Tue 11. Mar 14:31:17 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../db/view/btn_toolbox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'btn_toolbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Btn_ToolBox[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      44,   12,   12,   12, 0x08,
      77,   12,   12,   12, 0x08,
     112,  104,   12,   12, 0x08,
     147,  104,   12,   12, 0x08,
     180,   12,   12,   12, 0x08,
     202,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Btn_ToolBox[] = {
    "Btn_ToolBox\0\0on_ledt_filter_returnPressed()\0"
    "on_btn_search_settings_clicked()\0"
    "on_btn_submitAll_clicked()\0checked\0"
    "on_btn_selectByValue_clicked(bool)\0"
    "on_btn_sortEnabled_clicked(bool)\0"
    "on_btn_view_clicked()\0"
    "on_btn_clear_seached_text_clicked()\0"
};

void Btn_ToolBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Btn_ToolBox *_t = static_cast<Btn_ToolBox *>(_o);
        switch (_id) {
        case 0: _t->on_ledt_filter_returnPressed(); break;
        case 1: _t->on_btn_search_settings_clicked(); break;
        case 2: _t->on_btn_submitAll_clicked(); break;
        case 3: _t->on_btn_selectByValue_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_btn_sortEnabled_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_btn_view_clicked(); break;
        case 6: _t->on_btn_clear_seached_text_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Btn_ToolBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Btn_ToolBox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Btn_ToolBox,
      qt_meta_data_Btn_ToolBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Btn_ToolBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Btn_ToolBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Btn_ToolBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Btn_ToolBox))
        return static_cast<void*>(const_cast< Btn_ToolBox*>(this));
    return QWidget::qt_metacast(_clname);
}

int Btn_ToolBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
