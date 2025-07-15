#ifndef QP_DBG_GUI_H
#define QP_DBG_GUI_H

#include <QString>
#include <QWidget>
#include <QAbstractItemView>

#include <QEvent>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>
#include <QEvent>
#include <QFile>
#include <QObject>
#include <QStyle>

#include "qp/gui/dll_qp_gui_global.h"

namespace qp
{

/*
  static when used in a function at namespace level means internal linkage.
*/

class LIB_PREFIX_QP_GUI dbg_gui
{
public:
    dbg_gui(){};



    static const QString toStr_StateFlag(QStyle::StateFlag StateFlag);

    static const QString toStr_ColorGroup(QPalette::ColorGroup colorGroup);


    static const QString toStr_ColorRole(QPalette::ColorRole colorRole);


    static const QString toStr_SelectedPosition(QStyleOptionHeader::SelectedPosition SelectedPosition);

    static const QString toStr_SectionPosition(QStyleOptionHeader::SectionPosition SectionPosition);


    static const QString meta_info(QObject * obj);
};
}


#endif // QP_DBG_GUI_H
