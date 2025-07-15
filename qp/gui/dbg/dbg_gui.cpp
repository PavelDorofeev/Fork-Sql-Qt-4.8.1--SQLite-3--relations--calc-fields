#include "dbg_gui.h"
#include <QMetaMethod>


const QString qp::dbg_gui::toStr_SectionPosition(QStyleOptionHeader::SectionPosition SectionPosition)
{
    QString str="";

    if(SectionPosition & QStyleOptionHeader::Beginning)
        str=str+"Beginning";

    if(SectionPosition & QStyleOptionHeader::Middle)
        str=str+"|Middle";

    if(SectionPosition & QStyleOptionHeader::End)
        str=str+"|End";

    if(SectionPosition & QStyleOptionHeader::OnlyOneSection)
        str=str+"|OnlyOneSection";

    return str;

}
const QString qp::dbg_gui::toStr_SelectedPosition(QStyleOptionHeader::SelectedPosition SelectedPosition)
{
    QString str="";

    if(SelectedPosition & QStyleOptionHeader::NotAdjacent)
        str=str+"|NotAdjacent";

    if(SelectedPosition & QStyleOptionHeader::NextIsSelected)
        str=str+"|NextIsSelected";

    if(SelectedPosition & QStyleOptionHeader::PreviousIsSelected)
        str=str+"|PreviousIsSelected";

    if(SelectedPosition & QStyleOptionHeader::NextAndPreviousAreSelected)
        str=str+"|NextAndPreviousAreSelected";

    return str;

}
const QString qp::dbg_gui::toStr_StateFlag(QStyle::StateFlag StateFlag)
{
    QString str="";

    if(StateFlag & QStyle::State_None)
        str=str+"State_None";

    if(StateFlag & QStyle::State_Enabled)
        str=str+" | State_Enabled";

    if(StateFlag & QStyle::State_Raised)
        str=str+" | State_Raised";

    if(StateFlag & QStyle::State_Sunken)
        str=str+" | State_Sunken";

    if(StateFlag & QStyle::State_Off)
        str=str+" | State_Off";

    if(StateFlag & QStyle::State_NoChange)
        str=str+" | State_NoChange";

    if(StateFlag & QStyle::State_On)
        str=str+" | State_On";

    if(StateFlag & QStyle::State_DownArrow)
        str=str+" | State_DownArrow";

    if(StateFlag & QStyle::State_Horizontal)
        str=str+" | State_Horizontal";

    if(StateFlag & QStyle::State_HasFocus)
        str=str+" | State_HasFocus";

    if(StateFlag & QStyle::State_Top)
        str=str+" | State_Top";

    if(StateFlag & QStyle::State_Bottom)
        str=str+" | State_Bottom";

    if(StateFlag & QStyle::State_FocusAtBorder)
        str=str+" | State_FocusAtBorder";

    if(StateFlag & QStyle::State_AutoRaise)
        str=str+" | State_AutoRaise";

    if(StateFlag & QStyle::State_MouseOver)
        str=str+" | State_MouseOver";

    if(StateFlag & QStyle::State_UpArrow)
        str=str+" | State_UpArrow";

    if(StateFlag & QStyle::State_Selected)
        str=str+" | State_Selected";

    if(StateFlag & QStyle::State_Active)
        str=str+" | State_Active";

    if(StateFlag & QStyle::State_Window)
        str=str+" | State_Window";

    if(StateFlag & QStyle::State_Open)
        str=str+" | State_Open";

    if(StateFlag & QStyle::State_Children)
        str=str+" | State_Children";

    if(StateFlag & QStyle::State_Item)
        str=str+" | State_Item";

    if(StateFlag & QStyle::State_Sibling)
        str=str+" | State_Sibling";

    if(StateFlag & QStyle::State_Editing)
        str=str+" | State_Editing";

    if(StateFlag & QStyle::State_KeyboardFocusChange)
        str=str+" | State_KeyboardFocusChange";

    if(StateFlag & QStyle::State_ReadOnly)
        str=str+" | State_ReadOnly";

    if(StateFlag & QStyle::State_Small)
        str=str+" | State_Small";

    if(StateFlag & QStyle::State_Mini)
        str=str+" | State_Mini";

    return str;

}
//QString toStr_CursorAction(QAbstractItemView::CursorAction cursorAction)
//{
//    switch(cursorAction)
//    {
//    case QAbstractItemView::MoveUp :return "MoveUp";
//    case QAbstractItemView::MoveDown :return "MoveDown";
//    case QAbstractItemView::MoveLeft :return "MoveLeft";
//    case QAbstractItemView::MoveRight :return "MoveRight";
//    case QAbstractItemView::MoveHome :return "MoveHome";
//    case QAbstractItemView::MoveEnd :return "MoveEnd";
//    case QAbstractItemView::MovePageUp :return "MovePageUp";
//    case QAbstractItemView::MovePageDown :return "MovePageDown";
//    case QAbstractItemView::MoveNext :return "MoveNext";
//    case QAbstractItemView::MovePrevious :return "MovePrevious";

//    default:  return "unknown QAbstractItemView::CursorAction ??";
//    }

//}

QString const qp::dbg_gui::toStr_ColorGroup(QPalette::ColorGroup colorGroup)
{
    switch(colorGroup)
    {
    case QPalette::Active :return "Active(Normal)";
    case QPalette::Disabled :return "Disabled";
    case QPalette::Inactive :return "Inactive";
    case QPalette::NColorGroups :return "NColorGroups";
    case QPalette::Current :return "Current";
    case QPalette::All :return "All";

    default:  return "unknown QPalette::ColorGroup ??";
    }

}
const QString qp::dbg_gui::toStr_ColorRole(QPalette::ColorRole colorRole)
{
    switch(colorRole)
    {
    case QPalette::WindowText :return "WindowText(Foreground)";
    case QPalette::Button :return "Button";
    case QPalette::Light :return "Light";
    case QPalette::Midlight :return "Midlight";
    case QPalette::Dark :return "Dark";
    case QPalette::Mid :return "Mid";
    case QPalette::Text :return "Text";
    case QPalette::BrightText :return "BrightText";
    case QPalette::ButtonText :return "ButtonText";
    case QPalette::Base :return "Base";
    case QPalette::Window :return "Window(Background)";
    case QPalette::Shadow :return "Shadow";
    case QPalette::Highlight :return "Highlight";
    case QPalette::HighlightedText :return "HighlightedText";
    case QPalette::Link :return "Link";
    case QPalette::LinkVisited :return "LinkVisited";
    case QPalette::AlternateBase :return "AlternateBase";
    case QPalette::NoRole :return "NoRole";
    case QPalette::ToolTipBase :return "ToolTipBase";
    case QPalette::ToolTipText :return "ToolTipText";
    case QPalette::NColorRoles :return "NColorRoles";
        //case QPalette::Foreground :return "Foreground";
        //case QPalette::Background :return "Background";

    default:  return "unknown QPalette::ColorRole ??";
    }

}


//const QString qp::dbg_core::toStr_ItemFlag(int ItemFlag)
//{
//    QString str="";

//    if(ItemFlag & Qt::NoItemFlags)
//        str=str+"NoItemFlags";

//    if(ItemFlag & Qt::ItemIsSelectable)
//        str=str + " | ItemIsSelectable";

//    if(ItemFlag & Qt::ItemIsEditable)
//        str=str+"| ItemIsEditable";

//    if(ItemFlag & Qt::ItemIsDragEnabled)
//        str=str+" | ItemIsDragEnabled";

//    if(ItemFlag & Qt::ItemIsDropEnabled)
//        str=str+" | ItemIsDropEnabled";

//    if(ItemFlag & Qt::ItemIsUserCheckable)
//        str=str+" | ItemIsUserCheckable";

//    if(ItemFlag & Qt::ItemIsEnabled)
//        str=str+" | ItemIsEnabled";

//    if(ItemFlag & Qt::ItemIsTristate)
//        str=str+" | ItemIsTristate";

//    return str;
//}



//const QString qp::dbg_core::toStr_InputMethodQuery(Qt::InputMethodQuery mtd)
//{
//    switch(mtd)
//    {
//    case Qt::ImMicroFocus       :  return "ImMicroFocus";
//    case Qt::ImFont             :  return "ImFont";
//    case Qt::ImCursorPosition   :  return "ImCursorPosition";
//    case Qt::ImSurroundingText  :  return "ImSurroundingText";
//    case Qt::ImCurrentSelection :  return "ImCurrentSelection";
//    case Qt::ImMaximumTextLength:  return "ImMaximumTextLength";
//    case Qt::ImAnchorPosition   :  return "ImAnchorPosition";

//    default:  return "? unknown ?  InputMethodQuery";
//    }
//}




//const QString qp::dbg_core::toStr_modelRole(int role)
//{
//    switch (role)
//    {
//    case Qt::DisplayRole:
//        return "Qt::DisplayRole";

//    case Qt::DecorationRole:
//        return "Qt::DecorationRole";

//    case Qt::EditRole:
//        return "Qt::EditRole";

//    case Qt::ToolTipRole:
//        return "Qt::ToolTipRole";

//    case Qt::StatusTipRole:
//        return "Qt::StatusTipRole";

//    case Qt::WhatsThisRole:
//        return "Qt::WhatsThisRole";

//    case Qt::FontRole:
//        return "Qt::FontRole";

//    case Qt::TextAlignmentRole:
//        return "Qt::TextAlignmentRole";

//    case Qt::BackgroundColorRole:
//        return "Qt::BackgroundColorRole";

//    //case Qt::BackgroundRole:
//        //return "Qt::BackgroundRole";

//    case Qt::TextColorRole:
//        return "Qt::TextColorRole";

//    //case Qt::ForegroundRole:
//        //return "Qt::ForegroundRole";

//    case Qt::CheckStateRole:
//        return "Qt::CheckStateRole";

//    case Qt::AccessibleTextRole:
//        return "Qt::AccessibleTextRole";

//    case Qt::AccessibleDescriptionRole:
//        return "Qt::AccessibleDescriptionRole";

//    case Qt::SizeHintRole:
//        return "Qt::SizeHintRole";

//    case Qt::InitialSortOrderRole:
//        return "Qt::InitialSortOrderRole";

//    case Qt::DisplayPropertyRole:
//        return "Qt::DisplayPropertyRole";

//    case Qt::DecorationPropertyRole:
//        return "Qt::DecorationPropertyRole";

//    case Qt::ToolTipPropertyRole:
//        return "Qt::ToolTipPropertyRole";

//    case Qt::StatusTipPropertyRole:
//        return "Qt::StatusTipPropertyRole";

//    case Qt::WhatsThisPropertyRole:
//        return "Qt::WhatsThisPropertyRole";

//    case Qt::UserRole:
//        return "Qt::UserRole";

//    default:
//        return "Qt:: unknown role";
//    }
//}


//const  QString qp::dbg_core::meta_info(QObject * obj)
//{
//    QString str;
//    const QMetaObject *mo = obj->metaObject();

//    str.append("------------------ "+obj->objectName()+" ----------------------\n");
//    str.append("                methods\n");
//    str.append(QString("    className: %1\n").arg( mo->className()));

//    for(int nn=0; nn < mo->methodOffset(); nn++)
//    {

//        str.append( QString::number(nn) +
//                    mo->method(nn).typeName()+
//                    " signature:"+ mo->method(nn).signature()+
//                    "\n");
//    }

//    int propertyOffset = mo->propertyOffset();

//    str.append("\n----------------- properties -----------------------\n");
//    //str.append(QString("    className: %1\n").arg(mo->className()));

//    if( propertyOffset >0)
//    {
//        for(int nn=0; nn < propertyOffset; nn++)
//        {
//            str.append( QString("%1 %2 %3\n").arg(nn).
//                        arg(mo->property(nn).typeName()).
//                        arg(mo->property(nn).name()));
//        }
//    }

//    int classInfoOffset = mo->classInfoOffset();

//    str.append("\n----------------- QMetaClassInfo -----------------------\n");
//    //str.append(QString("    className: %1\n").arg(mo->className()));

//    if( classInfoOffset >0)
//    {
//        for(int nn=0; nn < classInfoOffset; nn++)
//        {
//            QMetaClassInfo clinfo = mo->classInfo(nn);
//            str.append( QString("%1 %2 %3\n")
//                        .arg(nn)
//                        .arg(clinfo.name())
//                        .arg(clinfo.value()));
//        }
//    }

//    int enumeratorOffset = mo->enumeratorOffset();

//    str.append("\n----------------- QMetaEnum -----------------------\n");

//    if( enumeratorOffset >0)
//    {
//        for(int nn=0; nn < enumeratorOffset; nn++)
//        {
//            QMetaEnum metaEnum = mo->enumerator(nn);
//            str.append( QString("%1 %2 %3 %4 isValid:%5\n")
//                        .arg(metaEnum.name())
//                        .arg(metaEnum.key(nn))
//                        .arg(metaEnum.value(nn))
//                        .arg(metaEnum.keyCount())
//                        .arg(metaEnum.isValid())
//                        );
//        }
//    }

//    int constructorCount = mo->constructorCount();

//    str.append("\n----------------- QMetaMethod -----------------------\n");

//    if( constructorCount >0)
//    {
//        for(int nn=0; nn < constructorCount; nn++)
//        {
//            QMetaMethod mm = mo->constructor(nn);
//            str.append( QString("%1 signature::%2 signature:%3\n")
//                        .arg(nn)
//                        .arg(mo->method(nn).typeName())
//                        .arg(mo->method(nn).signature())
//                        );
//        }
//    }

//    qDebug()<<"\n\n";
//    return str;


//}
