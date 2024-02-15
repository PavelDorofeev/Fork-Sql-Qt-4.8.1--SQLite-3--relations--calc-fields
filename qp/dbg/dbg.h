#ifndef DBG_H
#define DBG_H

#include <QString>
#include <QWidget>
#include <QAbstractItemView>


namespace qp
{
    static const QString error2 = QString::fromUtf8("59860980948695");

    namespace dbg
    {


    static const QString toStr_StateFlag(QStyle::StateFlag StateFlag);

    static QString toStr_ColorGroup(QPalette::ColorGroup colorGroup);


    static QString toStr_ColorRole(QPalette::ColorRole colorRole);

    static QString toStr_Event_Type(int event);

    static QString toStr_ItemFlag(int ItemFlag);

    static const QString toStr_InputMethodQuery(Qt::InputMethodQuery mtd);

    static const QString toStr_SelectedPosition(QStyleOptionHeader::SelectedPosition SelectedPosition);

    static const QString toStr_SectionPosition(QStyleOptionHeader::SectionPosition SectionPosition);

    static QString  toStr_modelRole(int role);


    static const QString error_ = QString::fromUtf8("error");
    static const QString warning = QString::fromUtf8("warning");
    static const QString submitAllFalse = QString::fromUtf8("submitAll returns false,\n table :  '%1',\n error: %2");;
    static const QString submitFalse = QString::fromUtf8("submit returns false,\n table : '%1',\n error: %2");

;


    }
}

#endif // DBG_H
