#include "dbg.h"

#include <QEvent>
#include <QMessageBox>
#include <QDebug>
#include <QStyle>

namespace qp
{

namespace dbg
{

const QString toStr_SectionPosition(QStyleOptionHeader::SectionPosition SectionPosition)
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
const QString toStr_SelectedPosition(QStyleOptionHeader::SelectedPosition SelectedPosition)
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
const QString toStr_StateFlag(QStyle::StateFlag StateFlag)
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

QString toStr_ColorGroup(QPalette::ColorGroup colorGroup)
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
QString toStr_ColorRole(QPalette::ColorRole colorRole)
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


QString toStr_ItemFlag(int ItemFlag)
{
    QString str="";

    if(ItemFlag & Qt::NoItemFlags)
        str=str+"NoItemFlags";

    if(ItemFlag & Qt::ItemIsSelectable)
        str=str + " | ItemIsSelectable";

    if(ItemFlag & Qt::ItemIsEditable)
        str=str+"| ItemIsEditable";

    if(ItemFlag & Qt::ItemIsDragEnabled)
        str=str+" | ItemIsDragEnabled";

    if(ItemFlag & Qt::ItemIsDropEnabled)
        str=str+" | ItemIsDropEnabled";

    if(ItemFlag & Qt::ItemIsUserCheckable)
        str=str+" | ItemIsUserCheckable";

    if(ItemFlag & Qt::ItemIsEnabled)
        str=str+" | ItemIsEnabled";

    if(ItemFlag & Qt::ItemIsTristate)
        str=str+" | ItemIsTristate";

    return str;
}



const QString toStr_InputMethodQuery(Qt::InputMethodQuery mtd)
{
    switch(mtd)
    {
    case Qt::ImMicroFocus       :  return "ImMicroFocus";
    case Qt::ImFont             :  return "ImFont";
    case Qt::ImCursorPosition   :  return "ImCursorPosition";
    case Qt::ImSurroundingText  :  return "ImSurroundingText";
    case Qt::ImCurrentSelection :  return "ImCurrentSelection";
    case Qt::ImMaximumTextLength:  return "ImMaximumTextLength";
    case Qt::ImAnchorPosition   :  return "ImAnchorPosition";

    default:  return "? unknown ?  InputMethodQuery";
    }
}

//void message2(QWidget *parent, QString header , QString  signal , QString slot)
//{
//    QMessageBox::warning(parent,
//                         header,
//                         signal+"\n\n"+ slot);

//}


QString toStr_Event_Type(int event)
{
    switch(event)
    {
    case QEvent::None :  return "None";
    case QEvent::Timer :return "Timer";
    case QEvent::MouseButtonPress :return "MouseButtonPress";
    case QEvent::MouseButtonRelease :return "MouseButtonRelease";
    case QEvent::MouseButtonDblClick :return "MouseButtonDblClick";
    case QEvent::MouseMove :return "MouseMove";
    case QEvent::KeyPress :return "KeyPress";
    case QEvent::KeyRelease :return "KeyRelease";
    case QEvent::FocusIn :return "FocusIn";
    case QEvent::FocusOut :return "FocusOut";
    case QEvent::Enter :return "Enter";
    case QEvent::Leave :return "Leave";
    case QEvent::Paint :return "Paint";
    case QEvent::Move :return "Move";
    case QEvent::Resize :return "Resize";
    case QEvent::Create :return "Create";
    case QEvent::Destroy :return "Destroy";
    case QEvent::Show :return "Show";
    case QEvent::Hide :return "Hide";
    case QEvent::Close :return "Close";
    case QEvent::Quit :return "Quit";
    case QEvent::ParentChange :return "ParentChange";
    case QEvent::ParentAboutToChange :return "ParentAboutToChange";
    case QEvent::ThreadChange :return "ThreadChange";
    case QEvent::WindowActivate :return "WindowActivate";
    case QEvent::WindowDeactivate :return "WindowDeactivate";
    case QEvent::ShowToParent :return "ShowToParent";
    case QEvent::HideToParent :return "HideToParent";
    case QEvent::Wheel :return "Wheel";
    case QEvent::WindowTitleChange :return "WindowTitleChange";
    case QEvent::WindowIconChange :return "WindowIconChange";

    case QEvent::ApplicationWindowIconChange :return "ApplicationWindowIconChange";
    case QEvent::ApplicationFontChange :return "ApplicationFontChange";
    case QEvent::ApplicationLayoutDirectionChange :return "ApplicationLayoutDirectionChange";
    case QEvent::ApplicationPaletteChange :return "ApplicationPaletteChange";
    case QEvent::PaletteChange :return "PaletteChange";
    case QEvent::Clipboard :return "Clipboard";
    case QEvent::Speech :return "Speech";
    case QEvent::MetaCall :return "MetaCall";
    case QEvent::WinEventAct :return "WinEventAct";
    case QEvent::DeferredDelete :return "DeferredDelete";
    case QEvent::DragEnter :return "DragEnter";

    case QEvent::DragMove :return "DragMove";
    case QEvent::DragLeave :return "DragLeave";
    case QEvent::Drop :return "Drop";
    case QEvent::DragResponse :return "DragResponse";
    case QEvent::ChildAdded :return "ChildAdded";
    case QEvent::ChildPolished :return "ChildPolished";
    case QEvent::ChildRemoved :return "ChildRemoved";
    case QEvent::ShowWindowRequest :return "ShowWindowRequest";
    case QEvent::PolishRequest :return "PolishRequest";
    case QEvent::Polish :return "Polish";
    case QEvent::LayoutRequest :return "LayoutRequest";
    case QEvent::UpdateRequest :return "UpdateRequest";
    case QEvent::UpdateLater :return "UpdateLater";
    case QEvent::EmbeddingControl :return "EmbeddingControl";
    case QEvent::ActivateControl :return "ActivateControl";
    case QEvent::DeactivateControl :return "DeactivateControl";
    case QEvent::ContextMenu :return "ContextMenu";
    case QEvent::InputMethod :return "InputMethod";
    case QEvent::AccessibilityPrepare :return "AccessibilityPrepare";
    case QEvent::TabletMove :return "TabletMove";
    case QEvent::LocaleChange :return "LocaleChange";

    case QEvent::LanguageChange :return "LanguageChange";
    case QEvent::LayoutDirectionChange :return "LayoutDirectionChange";
    case QEvent::Style :return "Style";
    case QEvent::TabletPress :return "TabletPress";
    case QEvent::TabletRelease :return "TabletRelease";
    case QEvent::OkRequest :return "OkRequest";
    case QEvent::IconDrag :return "IconDrag";
    case QEvent::FontChange :return "FontChange";
    case QEvent::EnabledChange :return "EnabledChange";
    case QEvent::ActivationChange :return "ActivationChange";
    case QEvent::StyleChange :return "StyleChange";
    case QEvent::IconTextChange :return "IconTextChange";
    case QEvent::ModifiedChange :return "ModifiedChange";
    case QEvent::MouseTrackingChange :return "MouseTrackingChange";
    case QEvent::WindowBlocked :return "WindowBlocked";

    case QEvent::WindowUnblocked :return "WindowUnblocked";
    case QEvent::WindowStateChange :return "WindowStateChange";
    case QEvent::ToolTip :return "ToolTip";

    case QEvent::WhatsThis :return "WhatsThis";
    case QEvent::StatusTip :return "StatusTip";
    case QEvent::ActionChanged :return "ActionChanged";
    case QEvent::ActionAdded :return "ActionAdded";
    case QEvent::ActionRemoved :return "ActionRemoved";
    case QEvent::FileOpen :return "FileOpen";
    case QEvent::Shortcut :return "Shortcut";
    case QEvent::ShortcutOverride :return "ShortcutOverride";
    case QEvent::WhatsThisClicked :return "WhatsThisClicked";
    case QEvent::ToolBarChange :return "ToolBarChange";
    case QEvent::ApplicationActivate :return "ApplicationActivate";
    case QEvent::ApplicationDeactivate :return "ApplicationDeactivate";

    case QEvent::QueryWhatsThis :return "QueryWhatsThis";
    case QEvent::EnterWhatsThisMode :return "EnterWhatsThisMode";
    case QEvent::LeaveWhatsThisMode :return "LeaveWhatsThisMode";
    case QEvent::ZOrderChange :return "ZOrderChange";
    case QEvent::HoverEnter :return "HoverEnter";
    case QEvent::HoverLeave :return "HoverLeave";
    case QEvent::HoverMove :return "HoverMove";
    case QEvent::AccessibilityHelp :return "AccessibilityHelp";
    case QEvent::AccessibilityDescription :return "AccessibilityDescription";
    case QEvent::AcceptDropsChange :return "AcceptDropsChange";
    case QEvent::MenubarUpdated :return "MenubarUpdated";
    case QEvent::ZeroTimerEvent :return "ZeroTimerEvent";
    case QEvent::GraphicsSceneMouseMove :return "GraphicsSceneMouseMove";
    case QEvent::GraphicsSceneMousePress :return "GraphicsSceneMousePress";
    case QEvent::GraphicsSceneMouseRelease :return "GraphicsSceneMouseRelease";
    case QEvent::GraphicsSceneMouseDoubleClick :return "GraphicsSceneMouseDoubleClick";
    case QEvent::GraphicsSceneContextMenu :return "GraphicsSceneContextMenu";
    case QEvent::GraphicsSceneHoverEnter :return "GraphicsSceneHoverEnter";
    case QEvent::GraphicsSceneHoverMove :return "GraphicsSceneHoverMove";

    case QEvent::GraphicsSceneHoverLeave :return "GraphicsSceneHoverLeave";
    case QEvent::GraphicsSceneHelp :return "GraphicsSceneHelp";
    case QEvent::GraphicsSceneDragEnter :return "GraphicsSceneDragEnter";
    case QEvent::GraphicsSceneDragMove :return "GraphicsSceneDragMove";
    case QEvent::GraphicsSceneDragLeave :return "GraphicsSceneDragLeave";
    case QEvent::GraphicsSceneDrop :return "GraphicsSceneDrop";
    case QEvent::GraphicsSceneWheel :return "GraphicsSceneWheel";
    case QEvent::KeyboardLayoutChange :return "KeyboardLayoutChange";
    case QEvent::DynamicPropertyChange :return "DynamicPropertyChange";
    case QEvent::TabletEnterProximity :return "TabletEnterProximity";
    case QEvent::TabletLeaveProximity :return "TabletLeaveProximity";
    case QEvent::NonClientAreaMouseMove :return "NonClientAreaMouseMove";
    case QEvent::NonClientAreaMouseButtonPress :return "NonClientAreaMouseButtonPress";
    case QEvent::NonClientAreaMouseButtonRelease :return "NonClientAreaMouseButtonRelease";
    case QEvent::NonClientAreaMouseButtonDblClick :return "NonClientAreaMouseButtonDblClick";
    case QEvent::MacSizeChange :return "MacSizeChange";
    case QEvent::ContentsRectChange :return "ContentsRectChange";
    case QEvent::MacGLWindowChange :return "MacGLWindowChange";
    case QEvent::FutureCallOut :return "FutureCallOut";


    case QEvent::GraphicsSceneResize :return "GraphicsSceneResize";
    case QEvent::GraphicsSceneMove :return "GraphicsSceneMove";
    case QEvent::CursorChange :return "CursorChange";
    case QEvent::ToolTipChange :return "ToolTipChange";
    case QEvent::NetworkReplyUpdated :return "NetworkReplyUpdated";
    case QEvent::GrabMouse :return "GrabMouse";
    case QEvent::UngrabMouse :return "UngrabMouse";
    case QEvent::GrabKeyboard :return "GrabKeyboard";
    case QEvent::UngrabKeyboard :return "UngrabKeyboard";
    case QEvent::MacGLClearDrawable :return "MacGLClearDrawable";
    case QEvent::StateMachineSignal :return "StateMachineSignal";
    case QEvent::StateMachineWrapped :return "StateMachineWrapped";
    case QEvent::TouchBegin :return "TouchBegin";
    case QEvent::TouchUpdate :return "TouchUpdate";
    case QEvent::TouchEnd :return "TouchEnd";
    case QEvent::NativeGesture :return "NativeGesture";
    case QEvent::RequestSoftwareInputPanel :return "RequestSoftwareInputPanel";

    case QEvent::CloseSoftwareInputPanel :return "CloseSoftwareInputPanel";
    case QEvent::UpdateSoftKeys :return "UpdateSoftKeys";
    case QEvent::WinIdChange :return "WinIdChange";
    case QEvent::Gesture :return "Gesture";
    case QEvent::GestureOverride :return "GestureOverride";
    case QEvent::User :return "User";
    case QEvent::MaxUser :return "MaxUser";

    default:  return "unknown event";
    }
    return "unknown event";
}

QString toStr_modelRole(int role)
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

}

}
