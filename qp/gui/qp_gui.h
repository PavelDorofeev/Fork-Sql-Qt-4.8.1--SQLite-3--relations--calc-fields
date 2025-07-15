#ifndef QP_GUI_H
#define QP_GUI_H

#include <QWidget>
#include <QMetaObject>
#include <QtCore/QtGlobal>

#include "qp/core/qp_core.h"

#include "qp/gui/qp_doublespinbox.h"
#include "qp/gui/dll_qp_gui_global.h"

#include <QMetaType>

QT_BEGIN_NAMESPACE

namespace qp
{
//Q_NAMESPACE_EXPORT(qp);

QT_BEGIN_NAMESPACE

namespace gui
{
//Q_NAMESPACE_EXPORT ( gui );

    enum LIB_PREFIX_QP_GUI LOG_STYLE{
        LOG_STYLE_SEND      =1,
        LOG_STYLE_RECEIVE   =2,
        LOG_STYLE_ERROR     =4,
        LOG_STYLE_SEND2     =8,
        LOG_STYLE_RECEIVE2  =16,
        LOG_STYLE_PLAINTEXT =32,
        LOG_STYLE_CODE_PRE  =64,
        LOG_STYLE_ERROR2    =128

    };

    Q_DECLARE_FLAGS(LOG_STYLES, LOG_STYLE)



LIB_PREFIX_QP_GUI QString styleToHtmlAttr(int stl);

LIB_PREFIX_QP_GUI bool call_slot(
        QWidget *parent, // this is parent
        const QObject * slotOwner,
        const QString &hdr,
        const QString &txt1,
        const QString &txt2,
        const QString &slot_name ,
        const QList<const QObject*> &ObjLst,
        const QList<QVariant>& pars,
        QVariant &retVal,
        bool closeWindowOnFinish = true,
        bool silent = false
        )  ;

LIB_PREFIX_QP_GUI void setWindow_woTitle(QWidget * wgt);
LIB_PREFIX_QP_GUI void setWindow_woFrame_and_woTiltle(QWidget * wgt);
LIB_PREFIX_QP_GUI void setWindow_woToolsBtn(QWidget * wgt);
LIB_PREFIX_QP_GUI void setWindow_woTitle__woFrame_woToolsBtn(QWidget * wgt);
LIB_PREFIX_QP_GUI void setWindow_woTitle__woFrame_woToolsBtn2(QWidget * wgt);


LIB_PREFIX_QP_GUI void setWindow_restore(QWidget * wgt);

LIB_PREFIX_QP_GUI void set_window_rounded_wo_title( QWidget  *wgt);

LIB_PREFIX_QP_GUI void center_window( QWidget  *wgt);
LIB_PREFIX_QP_GUI QSize screen_size( );

}
QT_END_NAMESPACE

}
QT_END_NAMESPACE

Q_DECLARE_METATYPE(qp::gui::LOG_STYLE);

//Q_DECLARE_METATYPE(qp::gui::LOG_STYLE);

#endif // QP_GUI_H
