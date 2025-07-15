/****************************************************************************
** Meta object code from reading C++ file 'qp_horheaderview.h'
**
** Created: Tue 11. Mar 14:31:04 2025
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tableview/qp_horheaderview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qp_horheaderview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QpHorHeaderView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       7,  139, // properties
       1,  160, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: signature, parameters, type, tag, flags
      60,   17,   16,   16, 0x05,
     107,   86,   16,   16, 0x05,
     148,  135,   16,   16, 0x05,
     168,  135,   16,   16, 0x05,
     188,  135,   16,   16, 0x05,
     208,  135,   16,   16, 0x05,
     252,  234,   16,   16, 0x05,
     281,  135,   16,   16, 0x05,
     331,  313,   16,   16, 0x05,
     382,   16,   16,   16, 0x05,
     421,  402,   16,   16, 0x05,
     461,   16,   16,   16, 0x05,
     490,  480,   16,   16, 0x05,
     512,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     538,   16,   16,   16, 0x0a,
     561,  554,   16,   16, 0x0a,
     588,  576,   16,   16, 0x0a,
     620,   16,   16,   16, 0x0a,
     682,  645,   16,   16, 0x0a,
     725,  135,   16,   16, 0x09,
     744,   16,   16,   16, 0x09,
     793,  761,   16,   16, 0x09,
     831,  761,   16,   16, 0x09,
     877,  761,   16,   16, 0x08,
     917,   16,   16,   16, 0x08,

 // properties: name, type, flags
     950,  945, 0x01095003,
     968,  945, 0x01095103,
     986,  945, 0x01095103,
    1005,  945, 0x01095103,
    1033, 1029, 0x02095103,
    1052, 1029, 0x02095103,
    1085, 1071, 0x0009510b,

 // enums: name, flags, count, data
    1102, 0x0,    5,  164,

 // enum data: key, value
    1113, uint(QpHorHeaderView::Interactive),
    1125, uint(QpHorHeaderView::Stretch),
    1133, uint(QpHorHeaderView::Fixed),
    1139, uint(QpHorHeaderView::ResizeToContents),
    1156, uint(QpHorHeaderView::Custom),

       0        // eod
};

static const char qt_meta_stringdata_QpHorHeaderView[] = {
    "QpHorHeaderView\0\0"
    "logicalIndex,oldVisualIndex,newVisualIndex\0"
    "sectionMoved(int,int,int)\0"
    "numX,oldSize,newSize\0sectionResized(int,int,int)\0"
    "logicalIndex\0sectionPressed(int)\0"
    "sectionClicked(int)\0sectionEntered(int)\0"
    "sectionDoubleClicked(int)\0oldCount,newCount\0"
    "sectionCountChanged(int,int)\0"
    "sectionHandleDoubleClicked(int)\0"
    "logicalIndex,mode\0"
    "sectionAutoResize(int,QpHorHeaderView::ResizeMode)\0"
    "geometriesChanged()\0logicalIndex,order\0"
    "sortIndicatorChanged(int,Qt::SortOrder)\0"
    "sectionResized_Y()\0xNum_from\0"
    "sectionResized_X(int)\0sig_sectionsTmplChanged()\0"
    "doItemsLayout()\0offset\0setOffset(int)\0"
    "visualIndex\0setOffsetToSectionPosition(int)\0"
    "setOffsetToLastSection()\0"
    "orientation,logicalFirst,logicalLast\0"
    "headerDataChanged(Qt::Orientation,int,int)\0"
    "updateSection(int)\0resizeSections()\0"
    "parent,logicalFirst,logicalLast\0"
    "sectionsInserted(QModelIndex,int,int)\0"
    "sectionsAboutToBeRemoved(QModelIndex,int,int)\0"
    "_q_sectionsRemoved(QModelIndex,int,int)\0"
    "_q_layoutAboutToBeChanged()\0bool\0"
    "showSortIndicator\0highlightSections\0"
    "stretchLastSection\0cascadingSectionResizes\0"
    "int\0defaultSectionSize\0minimumSectionSize\0"
    "Qt::Alignment\0defaultAlignment\0"
    "ResizeMode\0Interactive\0Stretch\0Fixed\0"
    "ResizeToContents\0Custom\0"
};

void QpHorHeaderView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QpHorHeaderView *_t = static_cast<QpHorHeaderView *>(_o);
        switch (_id) {
        case 0: _t->sectionMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->sectionResized((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->sectionPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sectionClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->sectionEntered((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sectionDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->sectionCountChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->sectionHandleDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->sectionAutoResize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QpHorHeaderView::ResizeMode(*)>(_a[2]))); break;
        case 9: _t->geometriesChanged(); break;
        case 10: _t->sortIndicatorChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Qt::SortOrder(*)>(_a[2]))); break;
        case 11: _t->sectionResized_Y(); break;
        case 12: _t->sectionResized_X((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->sig_sectionsTmplChanged(); break;
        case 14: _t->doItemsLayout(); break;
        case 15: _t->setOffset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->setOffsetToSectionPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->setOffsetToLastSection(); break;
        case 18: _t->headerDataChanged((*reinterpret_cast< Qt::Orientation(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 19: _t->updateSection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->resizeSections(); break;
        case 21: _t->sectionsInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 22: _t->sectionsAboutToBeRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 23: _t->d_func()->_q_sectionsRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 24: _t->d_func()->_q_layoutAboutToBeChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QpHorHeaderView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QpHorHeaderView::staticMetaObject = {
    { &QpAbstractItemView::staticMetaObject, qt_meta_stringdata_QpHorHeaderView,
      qt_meta_data_QpHorHeaderView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QpHorHeaderView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QpHorHeaderView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QpHorHeaderView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QpHorHeaderView))
        return static_cast<void*>(const_cast< QpHorHeaderView*>(this));
    return QpAbstractItemView::qt_metacast(_clname);
}

int QpHorHeaderView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QpAbstractItemView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = isSortIndicatorShown(); break;
        case 1: *reinterpret_cast< bool*>(_v) = highlightSections(); break;
        case 2: *reinterpret_cast< bool*>(_v) = stretchLastSection(); break;
        case 3: *reinterpret_cast< bool*>(_v) = cascadingSectionResizes(); break;
        case 4: *reinterpret_cast< int*>(_v) = defaultSectionSize(); break;
        case 5: *reinterpret_cast< int*>(_v) = minimumSectionSize(); break;
        case 6: *reinterpret_cast< Qt::Alignment*>(_v) = defaultAlignment(); break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setSortIndicatorShown(*reinterpret_cast< bool*>(_v)); break;
        case 1: setHighlightSections(*reinterpret_cast< bool*>(_v)); break;
        case 2: setStretchLastSection(*reinterpret_cast< bool*>(_v)); break;
        case 3: setCascadingSectionResizes(*reinterpret_cast< bool*>(_v)); break;
        case 4: setDefaultSectionSize(*reinterpret_cast< int*>(_v)); break;
        case 5: setMinimumSectionSize(*reinterpret_cast< int*>(_v)); break;
        case 6: setDefaultAlignment(*reinterpret_cast< Qt::Alignment*>(_v)); break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QpHorHeaderView::sectionMoved(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QpHorHeaderView::sectionResized(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QpHorHeaderView::sectionPressed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QpHorHeaderView::sectionClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QpHorHeaderView::sectionEntered(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QpHorHeaderView::sectionDoubleClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QpHorHeaderView::sectionCountChanged(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QpHorHeaderView::sectionHandleDoubleClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QpHorHeaderView::sectionAutoResize(int _t1, QpHorHeaderView::ResizeMode _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QpHorHeaderView::geometriesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void QpHorHeaderView::sortIndicatorChanged(int _t1, Qt::SortOrder _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QpHorHeaderView::sectionResized_Y()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void QpHorHeaderView::sectionResized_X(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void QpHorHeaderView::sig_sectionsTmplChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, 0);
}
QT_END_MOC_NAMESPACE
