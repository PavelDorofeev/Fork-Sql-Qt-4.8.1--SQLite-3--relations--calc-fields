/****************************************************************************
** Meta object code from reading C++ file 'dialog_test.h'
**
** Created: Tue 1. Jul 11:57:01 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialog_test.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogTest[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   11,   11,   11, 0x08,
      68,   11,   11,   11, 0x08,
      90,   11,   11,   11, 0x08,
     113,   11,   11,   11, 0x08,
     137,   11,   11,   11, 0x08,
     167,  162,   11,   11, 0x08,
     212,   11,   11,   11, 0x08,
     238,   11,   11,   11, 0x08,
     260,   11,   11,   11, 0x08,
     282,   11,   11,   11, 0x08,
     323,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogTest[] = {
    "DialogTest\0\0name\0sig_changeLanguage(QString)\0"
    "on_btn_Close_clicked()\0on_btn_save_clicked()\0"
    "on_btn_goods_clicked()\0on_btn_checks_clicked()\0"
    "on_btn_logView_clicked()\0arg1\0"
    "on_cmb_Language_currentIndexChanged(QString)\0"
    "slot_recalculate_tbl(int)\0"
    "on_btn_font_clicked()\0on_btn_test_clicked()\0"
    "on_btn_resizeColumnsToContents_clicked()\0"
    "on_btn_resizeRowsToContents_clicked()\0"
};

void DialogTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DialogTest *_t = static_cast<DialogTest *>(_o);
        switch (_id) {
        case 0: _t->sig_changeLanguage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_btn_Close_clicked(); break;
        case 2: _t->on_btn_save_clicked(); break;
        case 3: _t->on_btn_goods_clicked(); break;
        case 4: _t->on_btn_checks_clicked(); break;
        case 5: _t->on_btn_logView_clicked(); break;
        case 6: _t->on_cmb_Language_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->slot_recalculate_tbl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_btn_font_clicked(); break;
        case 9: _t->on_btn_test_clicked(); break;
        case 10: _t->on_btn_resizeColumnsToContents_clicked(); break;
        case 11: _t->on_btn_resizeRowsToContents_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DialogTest::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DialogTest::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogTest,
      qt_meta_data_DialogTest, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogTest::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogTest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogTest))
        return static_cast<void*>(const_cast< DialogTest*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void DialogTest::sig_changeLanguage(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
