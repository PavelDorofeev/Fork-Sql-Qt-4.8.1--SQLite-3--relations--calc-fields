#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QBoxLayout>


namespace Ui {
class Dialog;
}

class PblTableView_Purchases;
class PblSqlRelationalTableModel;
class Tlb_Btns;

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    PblSqlRelationalTableModel *mdl;
    PblTableView_Purchases * view;
    QPushButton * btn;

    Tlb_Btns *tlbx;
    
signals:
    bool sig_openLoggingOnToOnNotepad();

private slots:

    void on_btn_Close_clicked();

    void on_btn_Grip_clicked();

    void on_btn_save_clicked();

    void on_btn_goods_clicked();

    void on_btn_checks_clicked();

    void on_btn_logView_clicked();

private:
    Ui::Dialog *ui;
    QBoxLayout * lo;
    QHBoxLayout * hlo;

    void openTable(const QString & tableName);

};

#endif // DIALOG_H
