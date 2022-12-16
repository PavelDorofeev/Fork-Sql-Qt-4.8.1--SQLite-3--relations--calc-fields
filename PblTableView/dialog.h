#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QBoxLayout>
#include <QSqlDatabase>

namespace Ui {
class Dialog;
}

class PblTableView;
class PblSqlRelationalTableModel;
class Tlb_Btns;

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QString langId, QSqlDatabase &db,  QWidget *parent = 0);
    ~Dialog();

    PblSqlRelationalTableModel *mdl;
    PblTableView * view;
    QPushButton * btn;

    Tlb_Btns *tlbx;
    QSqlDatabase db;

signals:
    bool sig_openLoggingOnToOnNotepad();
    void sig_changeLanguage(QString name);

private slots:

    void on_btn_Close_clicked();

    void on_btn_save_clicked();

    void on_btn_goods_clicked();

    void on_btn_checks_clicked();

    void on_btn_logView_clicked();


    void on_cmb_Language_currentIndexChanged(const QString &arg1);

private:
    Ui::Dialog *ui;

    QBoxLayout * lo;
    QHBoxLayout * hlo;

    void openTable(const QString & tableName);

};

#endif // DIALOG_H
