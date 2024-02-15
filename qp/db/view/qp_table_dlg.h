/******************************************************************************
**
** Contact: BIT Ltd Company (p@kkmspb.ru) Individual Taxpayer Number (ITN) 7826152874
**
** This file is not part of the Qt Sources.
** This is a little convenient fork of QSqlTableModel (Qt 4.8.1) version 4.0
** created by Pavel Dorofeev ( p@kkmspb.ru )
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.

*******************************************************************************/

#ifndef QP_TABLE_DLG_H
#define QP_TABLE_DLG_H

#include <QDialog>
#include <QSqlRecord>
#include <QModelIndex>
#include "qp/db/model/qp_sqltablemodel.h"
#include "qp/db/view/qp_tableview_wrapper.h"

#include <QVBoxLayout>
#include "qp/db/model/qp_sqlrelation.h"

namespace Ui {
class QpTableDlg;
}


typedef bool (*cb_setting_mdl) (QpSqlTableModel *);


class QSqlDatabase;

class   QpTableDlg : public QDialog
{
    Q_OBJECT
    
public:

    explicit QpTableDlg( const QString tableName,
                          QSqlDatabase &db_,
                          cb_setting_mdl p_cbMdl =0 ,
                          cb_setting_view p_cbView = 0 ,
                          QWidget *parent = 0,
                          bool selectable=false,
                          const QHash<QString,QVariant> &filter=QHash<QString,QVariant>(),
                          QSqlTableModel::EditStrategy edt = QSqlTableModel::OnRowChange
            );

    virtual ~QpTableDlg();
    
    bool init_form(QSqlDatabase &Db , bool editable, bool selectable);

    QpSqlRecord chosenRec;

    int chosenRow;

    int chosenId;

    QpSqlTableModel * mdl;

    bool init_for_public_ctor( QSqlDatabase &Db,
               const QString tableName,
              cb_setting_mdl p_cbMdl,
              cb_setting_view p_cbView,
               const QHash<QString,QVariant> &Filter);

    QpTableViewWrapper * view;

    QSqlDatabase *sqlite;


    virtual bool setRelation(QpSqlRelation &rel);

    QVBoxLayout * getUi();

protected:
    explicit QpTableDlg(
            const QString &tableName,
            QpSqlTableModel *mdl,
            QpTableViewWrapper *view,
            QSqlDatabase &sqlite,
            QWidget *parent = 0,
            cb_setting_mdl p_cbMdl = 0,
            cb_setting_view p_cbView = 0,
            bool selectable=false,
            const QHash<QString,QVariant> filter=QHash<QString,QVariant>(),
            QSqlTableModel::EditStrategy edt = QSqlTableModel::OnRowChange);

public slots:

    void slot_accepted();

    void slot_view_clicked(QModelIndex);


private slots:


    void on_btn_close_clicked();

    void on_btn_resizeColumnsToContents_clicked();

    void on_btn_resizeRowsToContents_clicked();

private:
    Ui::QpTableDlg *ui;

    bool editable;
    bool selectable;

};

#endif // QP_TABLE_DLG_H
