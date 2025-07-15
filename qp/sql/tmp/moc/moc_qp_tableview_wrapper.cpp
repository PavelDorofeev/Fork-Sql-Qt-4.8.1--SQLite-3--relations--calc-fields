/****************************************************************************
** Meta object code from reading C++ file 'qp_tableview_wrapper.h'
**
** Created: Tue 15. Jul 17:02:01 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../view/qp_tableview_wrapper.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qp_tableview_wrapper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QpTableViewWrapper[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      56,   46,   41,   19, 0x05,
      82,   19,   41,   19, 0x05,
     103,   99,   41,   19, 0x05,
     120,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     148,  144,   19,   19, 0x0a,
     181,   19,   41,   19, 0x0a,
     204,   19,   41,   19, 0x0a,
     229,   19,   41,   19, 0x0a,
     252,   19,   41,   19, 0x0a,
     275,   19,   41,   19, 0x0a,
     298,   19,   41,   19, 0x0a,
     330,  323,   41,   19, 0x0a,
     358,   19,   19,   19, 0x0a,
     398,  394,   41,   19, 0x0a,
     443,  435,   19,   19, 0x0a,
     483,   19,   19,   19, 0x2a,
     522,  519,   19,   19, 0x0a,
     548,   19,   19,   19, 0x0a,
     586,  580,   19,   19, 0x0a,
     637,  629,   19,   19, 0x0a,
     665,   19,   19,   19, 0x0a,
     686,   19,   19,   19, 0x0a,
     709,   19,   19,   19, 0x08,
     764,   19,   19,   19, 0x08,
     801,   19,   19,   19, 0x08,
     855,  835,   19,   19, 0x08,
     899,  897,   19,   19, 0x08,
     941,  934,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QpTableViewWrapper[] = {
    "QpTableViewWrapper\0\0sig_rowSelected(int)\0"
    "bool\0tableName\0sig_setRelations(QString)\0"
    "sig_editRow(int)\0row\0sig_viewRow(int)\0"
    "sig_showSubmitBtn(bool)\0pos\0"
    "slot_CustomMenuRequested(QPoint)\0"
    "slot_clearFieldClick()\0slot_insertRowBtnClick()\0"
    "slot_editRowBtnClick()\0slot_viewRowBtnClick()\0"
    "slot_copyRowBtnClick()\0slot_removeRowBtnClick()\0"
    "filter\0slot_searchInTable(QString)\0"
    "slot_setVisibleExRelIdColumns(bool)\0"
    "idx\0slot_selectByFieldValue(QModelIndex)\0"
    "checked\0slot_selectByFieldValue_Triggered(bool)\0"
    "slot_selectByFieldValue_Triggered()\0"
    "on\0slot_setEditEnabled(bool)\0"
    "slot_doubleClicked(QModelIndex)\0index\0"
    "slot_cmb_Strategy_currentIndexChanged(int)\0"
    "enabled\0slot_repaintSubmitBtn(bool)\0"
    "slot_rowIsDirty(int)\0slot_afterSelect(bool)\0"
    "slot_editStrategyChanged(QSqlTableModel::EditStrategy)\0"
    "slot_editStrategyChange_clicked(int)\0"
    "slot_editingEnabled_clicked(bool)\0"
    "topLeft,bottomRight\0"
    "slot_dataChanged(QModelIndex,QModelIndex)\0"
    ",\0slot_beforeUpdate(int,QSqlRecord&)\0"
    "record\0slot_beforeInsert(QSqlRecord&)\0"
};

void QpTableViewWrapper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QpTableViewWrapper *_t = static_cast<QpTableViewWrapper *>(_o);
        switch (_id) {
        case 0: _t->sig_rowSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: { bool _r = _t->sig_setRelations((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->sig_editRow((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->sig_viewRow((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: _t->sig_showSubmitBtn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->slot_CustomMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 6: { bool _r = _t->slot_clearFieldClick();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->slot_insertRowBtnClick();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->slot_editRowBtnClick();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->slot_viewRowBtnClick();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->slot_copyRowBtnClick();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->slot_removeRowBtnClick();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->slot_searchInTable((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: _t->slot_setVisibleExRelIdColumns((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: { bool _r = _t->slot_selectByFieldValue((*reinterpret_cast< QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: _t->slot_selectByFieldValue_Triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->slot_selectByFieldValue_Triggered(); break;
        case 17: _t->slot_setEditEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->slot_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 19: _t->slot_cmb_Strategy_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->slot_repaintSubmitBtn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->slot_rowIsDirty((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->slot_afterSelect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->slot_editStrategyChanged((*reinterpret_cast< QSqlTableModel::EditStrategy(*)>(_a[1]))); break;
        case 24: _t->slot_editStrategyChange_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->slot_editingEnabled_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->slot_dataChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 27: _t->slot_beforeUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QSqlRecord(*)>(_a[2]))); break;
        case 28: _t->slot_beforeInsert((*reinterpret_cast< QSqlRecord(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QpTableViewWrapper::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QpTableViewWrapper::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_QpTableViewWrapper,
      qt_meta_data_QpTableViewWrapper, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QpTableViewWrapper::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QpTableViewWrapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QpTableViewWrapper::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QpTableViewWrapper))
        return static_cast<void*>(const_cast< QpTableViewWrapper*>(this));
    return QTableView::qt_metacast(_clname);
}

int QpTableViewWrapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    return _id;
}

// SIGNAL 0
void QpTableViewWrapper::sig_rowSelected(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
bool QpTableViewWrapper::sig_setRelations(QString _t1)
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}

// SIGNAL 2
bool QpTableViewWrapper::sig_editRow(int _t1)
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}

// SIGNAL 3
bool QpTableViewWrapper::sig_viewRow(int _t1)
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
    return _t0;
}

// SIGNAL 4
void QpTableViewWrapper::sig_showSubmitBtn(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
