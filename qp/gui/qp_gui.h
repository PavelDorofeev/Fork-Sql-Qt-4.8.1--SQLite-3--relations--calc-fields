#ifndef QP_GUI_H
#define QP_GUI_H

#include <QWidget>

namespace qp
{
namespace gui
{

    enum LOG_STYLE{
        LOG_STYLE_SEND=0,
        LOG_STYLE_RECEIVE,
        LOG_STYLE_ERROR,
        LOG_STYLE_PLAINTEXT
    };

QString styleToHtmlAttr(LOG_STYLE stl);

bool call_slot(
        QWidget *parent, // this is parent
        QObject * slotOwner,
        const QString &hdr,
        const QString &txt1,
        const QString &txt2,
        const QString &slot_name ,
        const QList<QObject*> &ObjLst,
        const QList<QVariant>& pars,
        QVariant &retVal,
        bool closeWindowOnFinish = true
        );

void setWindow_woTitle(QWidget * wgt);
void setWindow_woFrame(QWidget * wgt);
void setWindow_woToolsBtn(QWidget * wgt);
void setWindow_woTitle__woFrame_woToolsBtn(QWidget * wgt);
void setWindow_woTitle__woFrame_woToolsBtn2(QWidget * wgt);

}
}
#endif // QP_GUI_H
