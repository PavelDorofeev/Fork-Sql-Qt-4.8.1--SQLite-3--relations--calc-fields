#ifndef SMART_PROCESS_DLG2_H
#define SMART_PROCESS_DLG2_H

#include <QDialog>
#include "qp/meta/qpsingleshottimer.h"

#include "my_lib/qp/gui/qp_gui.h"

namespace Ui {
class Smart_Process_Dlg2;
}

class Smart_Process_Dlg2 : public QDialog
{
    Q_OBJECT
    
public:
    explicit Smart_Process_Dlg2(QWidget *parent = 0,
                                QObject * slotOwn =0 ,
                                const QString &hdr=QString(),
                                const QString &txt1=QString(),
                                const QString &txt2=QString(),
                                const QString &slotName=QString() ,
                                const QList<QObject*> &objLst = QList<QObject*>(),
                                const QList<QVariant>& pars = QList<QVariant>(),
                                bool closeWindowOnFinished = true
            );

    ~Smart_Process_Dlg2();


    QpSingleShotTimer * tmr;


    bool getInvokeMethodResult();

    QVariant getRetValue();

signals:
    
public slots:

    void slot_log( const QString &description , qp_gui::LOG_STYLE style );

    void slot_finished(QString str, bool error); // default values are just in sig_finish

    void slot_linkActivated(QString);

    void slot_rangeChanged(int,int);

private slots:
    void on_btn_Close_clicked();

    void slot_retResult(bool resInvokeMethod,const QVariant&);

private:
    Ui::Smart_Process_Dlg2 *ui;
    QVariant retVal;
    bool resInvokeMethod;

    const QString &slot_name;
    const QList<QVariant>& pars;
    QObject * slotOwner;
    bool closeWindowOnFinished;
};

#endif // SMART_PROCESS_DLG2_H
