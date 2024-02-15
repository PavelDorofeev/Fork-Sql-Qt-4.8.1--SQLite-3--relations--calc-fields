#ifndef SMART_PROCESS_DLG_H
#define SMART_PROCESS_DLG_H

#include <QDialog>
#include "qp/meta/qpsingleshottimer.h"

namespace Ui {
class Smart_Process_Dlg;
}

class Smart_Process_Dlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit Smart_Process_Dlg(QWidget *parent = 0,
                               const QString &hdr=QString(),
                               const QString &txt1=QString(),
                               const QString &txt2=QString(),
                               const QList<QObject*> &objLst = QList<QObject*>()
            );

    ~Smart_Process_Dlg();

    static bool call_slot( QWidget * parent,
                           QObject * slotOwner,
                           const QString & header,
                           const QString &txt1 ,
                           const QString &txt2,
                           const QString &cmd ,
                           QList<QObject*> &objLst,
                           const QList<QVariant>& pars = QList<QVariant>());

    bool res;

    static Smart_Process_Dlg * dlg;
    static QpSingleShotTimer * tmr;

    QString lbl2;

    static Smart_Process_Dlg *theStaticPointer;

    void fooFunc();

signals:
    void emitFunction();
    
public slots:

    void slot_finished(const QString &str, bool error); // default values are just in sig_finish

    void slot_linkActivated(QString);

private slots:
    void on_btn_Close_clicked();

private:
    Ui::Smart_Process_Dlg *ui;
};

#endif // SMART_PROCESS_DLG_H
