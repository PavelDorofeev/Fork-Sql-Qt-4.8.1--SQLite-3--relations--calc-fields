#ifndef DIALOG_TEST_H
#define DIALOG_TEST_H

#include <QDialog>
#include <QBoxLayout>
#include <QSqlDatabase>
#include "qp/db/view/qp_table_dlg.h"

namespace Ui {
class Dialog;
}

class QpTableViewWrapper;
class QpSqlTableModel2;
class Tlb_Btns;

class DialogTest : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogTest(QString langId,
                        QSqlDatabase &db,
                        QWidget *parent = 0);
    ~DialogTest();

    static const QString progName;
    static const QString fontDir;

    QpSqlTableModel2 *mdl_purch;
    QpTableViewWrapper * view;
    QPushButton * btn;


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

    void on_btn_font_clicked();


    void on_btn_test_clicked();

    void on_btn_resizeColumnsToContents_clicked();

    void on_btn_resizeRowsToContents_clicked();

private:
    Ui::Dialog *ui;

    QpTableDlg *tbl;

    QBoxLayout * lo;
    QHBoxLayout * hlo;

    void openTable(const QString & tableName);

};

#endif // DIALOG_TEST_H
