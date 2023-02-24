#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QBoxLayout>
#include <QSqlDatabase>
#include "pbltableview/pbl_table_dlg.h"

namespace Ui {
class Dialog;
}

class PblTableView;
class PblSqlRelationalTableModel2;
class Tlb_Btns;

class DialogTest : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogTest(QString langId,
                        QSqlDatabase &db,
                        QWidget *parent = 0);
    ~DialogTest();

    PblSqlRelationalTableModel2 *mdl;
    PblTableView * view;
    QPushButton * btn;

    //Tlb_Btns *tlbx;
    QSqlDatabase db;

signals:
    void sig_changeLanguage(QString name);

public slots:


private slots:

    void on_btn_Close_clicked();

    void on_btn_save_clicked();

    void on_btn_goods_clicked();

    void on_btn_checks_clicked();

    void on_btn_logView_clicked();

    void on_cmb_Language_currentIndexChanged(const QString &arg1);

    void slot_recalculate_tbl(int);

private:
    Ui::Dialog *ui;

    PblTableDlg *tbl;

    QBoxLayout * lo;
    QHBoxLayout * hlo;

    void openTable(const QString & tableName);

};

#endif // DIALOG_H
