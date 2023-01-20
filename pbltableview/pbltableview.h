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
#include "my_sql.h"

class PblSqlRelationalTableModel;
class Btn_ToolBox;
class ComboBoxDelegate;

class PblTableView : public QTableView
{
    Q_OBJECT
public:
    /*enum SETTINGS
    {
        FORM_IS_ONLY_READ =1,
        FM_ROW_WILL_BE_CHOSEN =2,
        FM_CHK_EDIT_ON = 4
    };*/

    enum ACTION
    {
        ACT_INSERT_ROW =1,
        ACT_COPY_ROW = 2,
        ACT_EDIT_ROW = 4,
        ACT_DELETE_ROW = 8,

        ACT_CLEAR_FIELD = 16,

        ACT_ALL_EDIT = ACT_INSERT_ROW | ACT_COPY_ROW | ACT_EDIT_ROW | ACT_DELETE_ROW | ACT_CLEAR_FIELD,

        ACT_CHOICE_ROW =32,

        ACT_SEARCH = 64,

        ACT_SELECT_BY_FIELD_VALUE = 128,

        ACT_SORT = 256,

        ACT_CLEAR_SEARCH_RESULTS = 512,

        ACT_SWITCH_EDIT_ENABLED = 0x0400,

        ACT_SELECT_STRATEGY_ENABLED = 0x0800,

        ACT_SHOW_EXTENDED_RELATION_COLUMNS = 0x1000,

        ACT_EDIT_ON = 0x2000,

        ACT_VIEW = 0x4000,

        ACT_SELECT_AND_CLOSE = 0x8000,

        ACT_ALL_SEARCH = ACT_SEARCH | ACT_SELECT_BY_FIELD_VALUE | ACT_SORT | ACT_CLEAR_SEARCH_RESULTS,


        ACT_ALL = ACT_ALL_EDIT | ACT_CHOICE_ROW | ACT_CLEAR_FIELD | ACT_SEARCH | ACT_SELECT_BY_FIELD_VALUE | ACT_SORT | ACT_SELECT_STRATEGY_ENABLED | ACT_SHOW_EXTENDED_RELATION_COLUMNS | ACT_SWITCH_EDIT_ENABLED | ACT_CLEAR_SEARCH_RESULTS | ACT_EDIT_ON


    };
    Q_DECLARE_FLAGS(ACTIONS, ACTION)

    explicit PblTableView(PblSqlRelationalTableModel *mdl,
                          QVBoxLayout * lo,
                          QSqlDatabase &db,
                          QWidget *parent = 0,
                          bool editable = false,
                          bool selectable = false);

    virtual ~PblTableView();

    void reset();

    static QIcon getActIcon(PblTableView::ACTION act);

    static QIcon PblTableView::getIcon(int nn);

    QHBoxLayout *topLO;

    Btn_ToolBox *tlbx;


    QSize sizeHint() const;

    QAction * act_InsertRow;
    QAction * act_CopyRow;
    QAction * act_EditRow;
    QAction * act_DeleteRow;


    QAction * act_selectByFieldValue;
    QAction * act_ClearField;
    QAction * act_choiceCurrentRecord;
    QAction * act_search;
    QAction * act_view;

    QAction * act_selectAndClose;

    QMenu * contextMenu;

    DoubleDelegate *dblDlg;

    void initStrategy(QSqlTableModel::EditStrategy);

    void setEditState(bool);
    int priCol;

    virtual bool insertRow(int row);
    virtual bool editRow(int row);
    virtual bool copyRow(int row);
    virtual bool removeRow(int row);

    virtual bool viewRow(int row);

    void setSelectAndClose();

    void set_Actions(PblTableView::ACTIONS , bool );


    PblSqlRelationalTableModel* model() const;

    void fillContextMenu();

    void setContextMenuItemsVisibleAfterFieldSelected();

    virtual bool clearField(const QModelIndex &currIdx);

    void setEditStrategyVisible(bool on);

    void setExRelIdColumnsVisible(bool visible);

    bool prepare(const QString & tableName );

    Search_Settings_Dlg::FIND_SETTINGS find_settings;

    void setComboBoxDelegate(int col, QStringList &lst);

    void setDateTimeDelegate(int col);

    void setCheckBoxDelegate(int col);

    QHash<int , QStyledItemDelegate*> dlgts;

    PblSqlRelationalTableModel * mdl;

    QSqlDatabase db;

    void show_view_Btn();

    bool selectable;
    bool editable;

protected:


signals:
    void sig_rowSelected(QModelIndex);

    bool sig_setRelations(QString tableName);

    bool sig_editRow(int);

    bool sig_viewRow(int row);

public Q_SLOTS:

    void slot_CustomMenuRequested(const QPoint &pos);

    bool slot_clearFieldClick();

    bool slot_insertRowBtnClick();

    bool slot_editRowBtnClick();

    bool slot_viewRowBtnClick();

    bool slot_copyRowBtnClick();

    bool slot_removeRowBtnClick();

    bool slot_searchInTable(QString & filter);

    void slot_setVisibleExRelIdColumns(bool);

    bool slot_selectByFieldValue(QModelIndex idx);

    void slot_triggeredSelectByFieldValue(bool on);

    void slot_setEditable(bool on);

    void slot_doubleClicked(const QModelIndex & );

    void slot_cmb_Strategy_currentIndexChanged(int index);

    void slot_editStrategyClicked(int);

protected Q_SLOTS:
    virtual void rowsInserted(const QModelIndex &parent, int start, int end);
    virtual void rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end);
    virtual void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    virtual void currentChanged(const QModelIndex &current, const QModelIndex &previous);
    virtual void updateEditorData();
    virtual void updateEditorGeometries();
    virtual void updateGeometries();
    virtual void verticalScrollbarAction(int action);
    virtual void horizontalScrollbarAction(int action);
    virtual void verticalScrollbarValueChanged(int value);
    virtual void horizontalScrollbarValueChanged(int value);
    virtual void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);
    virtual void commitData(QWidget *editor);
    virtual void editorDestroyed(QObject *editor);

private slots:


    void slot_editStrategyChanged(QSqlTableModel::EditStrategy);

private:
    //SETTINGS formMode;

    QString filter;

    bool selectAndClose;


};

#endif // PBLTABLEVIEW_H
