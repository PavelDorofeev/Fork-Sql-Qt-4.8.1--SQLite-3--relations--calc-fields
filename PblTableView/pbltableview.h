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

#ifndef PBLTABLEVIEW_H
#define PBLTABLEVIEW_H

#include <QTableView>
#include <QHBoxLayout>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QSqlIndex>
#include "search_settings_dlg.h"
#include <QSqlDatabase>
#include <QIcon>
#include <QDoubleSpinBox>
#include "doubledelegate.h"

class PblSqlRelationalTableModel;
class Btn_ToolBox;

class PblTableView : public QTableView
{
    Q_OBJECT
public:
    enum SETTINGS
    {
        FORM_IS_ONLY_READ =1,
        FM_ROW_WILL_BE_CHOSEN =2,
        FM_CHK_EDIT_ON = 4
    };

    enum ACTIONS
    {
        ACTION_CHOSE_ROW =1,
        ACTION_INSERT_ROW,
        ACTION_COPY_ROW,
        ACTION_EDIT_ROW,
        ACTION_DELETE_ROW,
        ACTION_CLEAR_FIELD

    };


    explicit PblTableView(PblSqlRelationalTableModel *mdl,
                          QVBoxLayout * lo,
                          QSqlDatabase db,
                          QWidget *parent = 0,
                          bool editable = false);


    QHBoxLayout *topLO;

    Btn_ToolBox *tlbx;

    QSize sizeHint() const;

    QAction * act_InsertRow;
    QAction * act_CopyRow;
    QAction * act_EditRow;
    QAction * act_DeleteRow;


    QAction * act_selectByFieldValue;
    QAction * act_ClearField;
    QAction * act_choiseCurrentRecord;
    QAction * act_textsearch;

    QMenu * contextMenu;

    DoubleDelegate *dblDlg;

    void setEditable(bool);
    int priCol;

    virtual bool insertRow(int row);
    virtual bool editRow(int row);
    virtual bool copyRow(int row);
    virtual bool removeRow(int row);

    void setActionVisible(ACTIONS , bool );

    void fillContextMenu();
    void setContextMenuItemsVisibleAfterFieldSelected();
    virtual bool clearField(const QModelIndex &currIdx);

    Search_Settings_Dlg::FIND_SETTINGS find_settings;

    //void setEditable(bool editable);

    bool editable;
    PblSqlRelationalTableModel * mdl;

    QSqlDatabase db;

protected:


signals:
    void sig_rowSelected(QModelIndex);

public slots:
    void slot_CustomMenuRequested(const QPoint &pos);
    bool slot_clearFieldClick();

    bool slot_insertRowBtnClick();
    bool slot_editRowBtnClick();
    bool slot_copyRowBtnClick();
    bool slot_removeRowBtnClick();

    bool slot_searchInTable(QString & filter);

    void slot_setVisibleExRelIdColumns(bool);

    bool slot_selectByFieldValue(QModelIndex idx);

    void slot_triggeredSelectByFieldValue(bool on);

    void slot_rowsInserted(const QModelIndex &parent, int first, int last);

private slots:
    void slot_doubleClicked(QModelIndex );

private:
    SETTINGS formMode;
    QSqlIndex primaryIndex;

    QString filter;

};

#endif // PBLTABLEVIEW_H
