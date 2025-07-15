#include "dbg_core.h"
#include <QMetaMethod>

const QString qp::dbg_core::error_ = QString::fromUtf8("error");
const QString qp::dbg_core::warning = QString::fromUtf8("warning");
//QString qp::dbg_core::submitAllFalse = QString::fromUtf8("submitAll returns false,\n table :  '%1',\n error: %2");
//QString qp::dbg_core::submitFalse = QString::fromUtf8("submit returns false,\n table : '%1',\n error: %2");

namespace qp
{
dbg_core::dbg_core()
{

}

}
const QString qp::dbg_core::toStr_Event_Type(QEvent::Type event)
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
    case QEvent::TouchEnd                   :return "TouchEnd";
    case QEvent::NativeGesture              :return "NativeGesture";
    case QEvent::RequestSoftwareInputPanel :return "RequestSoftwareInputPanel";

    case QEvent::CloseSoftwareInputPanel :return "CloseSoftwareInputPanel";
    case QEvent::UpdateSoftKeys     :return "UpdateSoftKeys";
    case QEvent::WinIdChange        :return "WinIdChange";
    case QEvent::Gesture            :return "Gesture";
    case QEvent::GestureOverride    :return "GestureOverride";
    case QEvent::User               :return "User";
    case QEvent::MaxUser :return "MaxUser";

    default:  return "unknown event";
    }
    //    /return "unknown event";
}

const QString qp::dbg_core::toStr_ProcessExitStatus(QProcess::ExitStatus status)
{
    switch(status)
    {
    case QProcess::NormalExit: return "NormalExit";
    case QProcess::CrashExit: return "CrashExit";
    default: return "Unknown QProcess::ExitStatus";
    }
}

const QString qp::dbg_core::toStr_KeyboardModifier(Qt::KeyboardModifiers mdf)
{
    QString str;

    if(mdf & Qt::ShiftModifier )
        str=str+"Shift ";

    if(mdf & Qt::ControlModifier )
        str=str+"Ctrl ";

    if(mdf & Qt::AltModifier )
        str=str+"Alt ";

    if(mdf & Qt::MetaModifier )
        str=str+"Meta ";

    if(mdf & Qt::KeypadModifier )
        str=str+"KeypadModifier ";

    if(mdf & Qt::GroupSwitchModifier )
        str=str+"GroupSwitchModifier ";

    if(mdf & Qt::KeyboardModifierMask )
        str=str+"KeyboardModifierMask ";

    return str;
}
const QString qp::dbg_core::toStr_File_Permissions(QFile::Permissions prm)
{
    QString str;

    if(prm & QFile::ReadOwner)
        str=str+"ReadOwner ";

    if(prm & QFile::ReadUser)
        str=str+"ReadUser ";

    if(prm & QFile::ReadGroup)
        str=str+"ReadGroup ";

    if(prm & QFile::ReadOther)
        str=str+"ReadOther ";

    if(prm & QFile::WriteOwner)
        str=str+"WriteOwner ";

    if(prm & QFile::WriteUser)
        str=str+"WriteUser ";

    if(prm & QFile::WriteGroup)
        str=str+"WriteGroup ";

    if(prm & QFile::WriteOther)
        str=str+"WriteOther ";

    if(prm & QFile::ExeOwner)
        str=str+"ExeOwner ";

    if(prm & QFile::ExeUser)
        str=str+"ExeUser ";

    if(prm & QFile::ExeGroup)
        str=str+"ExeGroup ";

    if(prm & QFile::ExeOther)
        str=str+"ExeOther ";

    return str;

}


enum Permission {
    ReadOwner = 0x4000, WriteOwner = 0x2000, ExeOwner = 0x1000,
    ReadUser  = 0x0400, WriteUser  = 0x0200, ExeUser  = 0x0100,
    ReadGroup = 0x0040, WriteGroup = 0x0020, ExeGroup = 0x0010,
    ReadOther = 0x0004, WriteOther = 0x0002, ExeOther = 0x0001
};

const QString qp::dbg_core::toStr_ProcessError(QProcess::ProcessError err)
{
    switch(err)
    {
    case QProcess::FailedToStart: return "FailedToStart";
    case QProcess::Crashed: return "Crashed";
    case QProcess::Timedout: return "Timedout";
    case QProcess::ReadError: return "ReadError";
    case QProcess::WriteError: return "WriteError";
    case QProcess::UnknownError: return "UnknownError";
    default: return "Unknown Result";
    }
}




const QString qp::dbg_core::toStr_ItemFlag(int ItemFlag)
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



const QString qp::dbg_core::toStr_InputMethodQuery(Qt::InputMethodQuery mtd)
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




const QString qp::dbg_core::toStr_modelRole(int role)
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
}


const  QString qp::dbg_core::meta_info(QObject * obj)
{
    QString str;
    const QMetaObject *mo = obj->metaObject();

    str.append("------------------ "+obj->objectName()+" ----------------------\n");
    str.append("                methods\n");
    str.append(QString("    className: %1\n").arg( mo->className()));

    for(int nn=0; nn < mo->methodOffset(); nn++)
    {

        str.append( QString::number(nn) +
                    mo->method(nn).typeName()+
                    " signature:"+ mo->method(nn).signature()+
                    "\n");
    }

    int propertyOffset = mo->propertyOffset();

    str.append("\n----------------- properties -----------------------\n");
    //str.append(QString("    className: %1\n").arg(mo->className()));

    if( propertyOffset >0)
    {
        for(int nn=0; nn < propertyOffset; nn++)
        {
            str.append( QString("%1 %2 %3\n").arg(nn).
                        arg(mo->property(nn).typeName()).
                        arg(mo->property(nn).name()));
        }
    }

    int classInfoOffset = mo->classInfoOffset();

    str.append("\n----------------- QMetaClassInfo -----------------------\n");
    //str.append(QString("    className: %1\n").arg(mo->className()));

    if( classInfoOffset >0)
    {
        for(int nn=0; nn < classInfoOffset; nn++)
        {
            QMetaClassInfo clinfo = mo->classInfo(nn);
            str.append( QString("%1 %2 %3\n")
                        .arg(nn)
                        .arg(clinfo.name())
                        .arg(clinfo.value()));
        }
    }

    int enumeratorOffset = mo->enumeratorOffset();

    str.append("\n----------------- QMetaEnum -----------------------\n");

    if( enumeratorOffset >0)
    {
        for(int nn=0; nn < enumeratorOffset; nn++)
        {
            QMetaEnum metaEnum = mo->enumerator(nn);
            str.append( QString("%1 %2 %3 %4 isValid:%5\n")
                        .arg(metaEnum.name())
                        .arg(metaEnum.key(nn))
                        .arg(metaEnum.value(nn))
                        .arg(metaEnum.keyCount())
                        .arg(metaEnum.isValid())
                        );
        }
    }

    int constructorCount = mo->constructorCount();

    str.append("\n----------------- QMetaMethod -----------------------\n");

    if( constructorCount >0)
    {
        for(int nn=0; nn < constructorCount; nn++)
        {
            QMetaMethod mm = mo->constructor(nn);
            str.append( QString("%1 signature::%2 signature:%3\n")
                        .arg(nn)
                        .arg(mo->method(nn).typeName())
                        .arg(mo->method(nn).signature())
                        );
        }
    }

    qDebug()<<"\n\n";
    return str;


}
