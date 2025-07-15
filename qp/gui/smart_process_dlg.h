#ifndef SMART_PROCESS_DLG_H
#define SMART_PROCESS_DLG_H

#include <QDialog>

#include "qp/core/qp_core.h"
#include "qp/gui/qp_gui.h"
#include "qp/gui/sizerememberdlg.h"


namespace Ui {
class Smart_Process_Dlg;
}


#include "qp/gui/dll_qp_gui_global.h"

class LIB_PREFIX_QP_GUI Smart_Process_Dlg : public SizeRememberDlg
{
    Q_OBJECT
    
public:
    //using namespace gui;

    explicit Smart_Process_Dlg( QWidget *parent = 0,
                                const QObject * slotOwn =0 ,
                                const QString &hdr=QString(),
                                const QString &txt1=QString(),
                                const QString &txt2=QString(),
                                const QString &slotName=QString() ,
                                const QList<const QObject*> &objLst = QList<const QObject*>(),
                                const QList<QVariant>& pars = QList<QVariant>(),
                                bool closeWindowOnFinished = true, // если false, то окно будет оставаться только при ошибке
                                bool silent = false
            );

    ~Smart_Process_Dlg();


    QpSingleShotTimer * tmr;

//    void mouseMoveEvent(QMouseEvent* event);
//    void mousePressEvent(QMouseEvent* event);

    bool getInvokeMethodResult() const ;

    QVariant getRetValue() const ;

    virtual QString getReestrPrefix() const;
    QSize getMinimumSize() const;

signals:
    
public slots:


    void slot_log( const QString &description , qp::gui::LOG_STYLE style ); // при экспорте библиотеки проблем нет
    void slot_finished(QString str, bool error); // default values are just in sig_finish

    void slot_linkActivated(QString);

    void slot_rangeChanged(int,int);

private slots:
    void on_btn_Close_clicked();

    void slot_retResult(bool resInvokeMethod,const QVariant&);

private:
    Ui::Smart_Process_Dlg *ui;
    QVariant retVal;
    bool resInvokeMethod;

    const QString &slot_name;
    const QList<QVariant>& pars;
    const QObject * slotOwner;
    bool closeWindowOnFinished;
    bool silent;                    // если true, то на окно всегда закрывается автоматом
    //QPointF m_mousePoint;
};

#endif // Smart_Process_Dlg_H
