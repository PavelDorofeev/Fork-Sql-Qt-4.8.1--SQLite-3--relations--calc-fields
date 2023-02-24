#include "my_sql.h"
#include <QObject>

#include <QCoreApplication>

const QString mySql::error_ =  QObject::trUtf8("error");

const QString mySql::warning =  QObject::trUtf8("warning");

const QString mySql::submitAllFalse = QObject::trUtf8("submitAll returns false,\n table :  '%1',\n error: %2");

const QString mySql::submitFalse = QObject::trUtf8("submit returns false,\n table : '%1',\n error: %2");


mySql::mySql()
{
}

const char * mySql::roleToStr(int role)
{
    switch (role)
    {
    case Qt::DisplayRole:
        return "Qt::DisplayRole";

    case Qt::DecorationRole:
        return "Qt::DecorationRole";

    case Qt::EditRole:
        return "Qt::EditRole";

    case Qt::ToolTipRole:
        return "Qt::ToolTipRole";

    case Qt::StatusTipRole:
        return "Qt::StatusTipRole";

    case Qt::WhatsThisRole:
        return "Qt::WhatsThisRole";

    case Qt::FontRole:
        return "Qt::FontRole";

    case Qt::TextAlignmentRole:
        return "Qt::TextAlignmentRole";

    case Qt::BackgroundColorRole:
        return "Qt::BackgroundColorRole";

    //case Qt::BackgroundRole:
        //return "Qt::BackgroundRole";

    case Qt::TextColorRole:
        return "Qt::TextColorRole";

    //case Qt::ForegroundRole:
        //return "Qt::ForegroundRole";

    case Qt::CheckStateRole:
        return "Qt::CheckStateRole";

    case Qt::AccessibleTextRole:
        return "Qt::AccessibleTextRole";

    case Qt::AccessibleDescriptionRole:
        return "Qt::AccessibleDescriptionRole";

    case Qt::SizeHintRole:
        return "Qt::SizeHintRole";

    case Qt::InitialSortOrderRole:
        return "Qt::InitialSortOrderRole";

    case Qt::DisplayPropertyRole:
        return "Qt::DisplayPropertyRole";

    case Qt::DecorationPropertyRole:
        return "Qt::DecorationPropertyRole";

    case Qt::ToolTipPropertyRole:
        return "Qt::ToolTipPropertyRole";

    case Qt::StatusTipPropertyRole:
        return "Qt::StatusTipPropertyRole";

    case Qt::WhatsThisPropertyRole:
        return "Qt::WhatsThisPropertyRole";

    case Qt::UserRole:
        return "Qt::UserRole";

    default:
        return "Qt:: unknown role";
    }
};