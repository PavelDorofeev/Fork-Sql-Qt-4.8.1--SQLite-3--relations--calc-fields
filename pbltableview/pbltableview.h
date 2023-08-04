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
class PblTableDlg;
class Horizontal_Header;


typedef bool (*cb_setting_mdl) (PblSqlRelationalTableModel *);

typedef bool (*cb_setting_view) (PblTableView *);

class PblTableView : public QTableView
{
    Q_OBJECT
public:

    explicit PblTableView(
            QWidget *parent = 0,
            cb_setting_mdl pMdl =0,
            cb_setting_view = 0,
            const bool selectable = false);


    cb_setting_view p_cb_setting_view;
    cb_setting_mdl  p_cb_setting_mdl;

    virtual ~PblTableView();


    virtual bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);

    void paintEvent(QPaintEvent *e);

    virtual void setModel( PblSqlRelationalTableModel *model );

    void reset();

    void setContextMenuEnabled( bool yes);


    static const QString s_submit;

    static const QString s_submitAll;

    static int  margin_hor;

    QByteArray stt;

    PblSqlRelationalTableModel *mdl;

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
    //QAction * act_view;

    QAction * act_selectAndClose;

    //QAction * act_showRelExColumns;

    bool changeEditStrategyEnable;

    bool showRelExColumns;

    //QAction * act_switch_editable;

    QMenu * contextMenu;

    DoubleDelegate *dblDlg;

    void set_behavoir(bool On);

    //void set_chkEditable_isVisible(bool);

    int priCol;

    virtual bool vrt_insertRow(int row);

    virtual bool vrt_editRowDlg(int row);

    virtual bool vrt_copyRow(int row);

    virtual bool vrt_removeRow(int row);

    virtual bool vrt_viewRow(int row);

    virtual bool vrt_doubleClicked(const QModelIndex & index , bool &needsSubmitAfter);


    void setSelectAndClose();

    void set_editEnabledChkBoxVisible( bool yes);

    void set_tlbx_visible( bool yes);

    void set_contextMenuEnabled(bool );

    void set_editStrategyEnable(bool On ,
                                QSqlTableModel::EditStrategy def = QSqlTableModel::OnRowChange);

    void set_searchingEnabled( bool yes);

    void set_sortingEnabled(bool On);


    void set_ExtColumnsVisible(bool On , bool showExtCol_byDefault = false);

    void set_editingEnabled( bool yes ,
                             bool defVisibleWithOn = false,
                             bool hideBtns = true);

    void set_viewEnabled( bool yes );

    PblSqlRelationalTableModel* model() const;

    void fillContextMenu();

    void setContextMenuItemsVisibleAfterFieldSelected();

    virtual bool vrt_clearField(const QModelIndex &currIdx);

    virtual bool vrt_clearRelField(const QModelIndex &currIdx);

    //virtual bool prepare_view( PblSqlRelationalTableModel * Mdl );

    Search_Settings_Dlg::FIND_SETTINGS find_settings;

    void setComboBoxDelegate(const QString & fldName, QStringList &lst);

    void setDateTimeDelegate(const QString & fldName);

    void setCheckBoxDelegate(const QString & fldName);

    void setDoubleWithPrecision(const QString & fldName , int precision);

    void setDefaultDelegate(int col);

    QHash< QString , QStyledItemDelegate*> delegts;

    int restoreCurrentRowPositionAfterSubmit(int srcRow);

    virtual bool vrt_afterSetFldValue(int idRow,
                                      const QString & fldName,
                                      const QModelIndex & idx,
                                      const PblSqlRecord &rec,
                                      bool & needsSubmitAfter);

    bool selectable;
    //bool editable; // use editable flag only from model
    bool defaultEditOn;
    bool hideEditBtns;

    bool search_wgts_visible;

    void setToLayout(QVBoxLayout * lo);

    void set_Edit_Triggers(bool on);



protected:


signals:

    void sig_rowSelected(int);

    bool sig_setRelations(QString tableName);

    bool sig_editRow(int);

    bool sig_viewRow(int row);

    void sig_showSubmitBtn(bool);


public Q_SLOTS:

    void slot_CustomMenuRequested(const QPoint &pos);

    bool slot_clearFieldClick();

    bool slot_insertRowBtnClick();

    bool slot_editRowBtnClick();

    bool slot_viewRowBtnClick();

    bool slot_copyRowBtnClick();

    bool slot_removeRowBtnClick();

    bool slot_searchInTable(const QString & filter);

    void slot_setVisibleExRelIdColumns(bool);

    bool slot_selectByFieldValue(QModelIndex idx);

    void slot_triggeredSelectByFieldValue(bool on = true);

    void slot_setEditEnabled(bool on);


    virtual void slot_doubleClicked(const QModelIndex & );

    void slot_cmb_Strategy_currentIndexChanged(int index);

    void slot_repaintSubmitBtn(bool enabled);

    void slot_rowIsDirty(int);

    void slot_afterSelect( bool );


protected Q_SLOTS:


protected: // this are not slots

    //virtual void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    //virtual void currentChanged(const QModelIndex &current, const QModelIndex &previous);
    virtual void rowsInserted(const QModelIndex &parent, int start, int end);
    virtual void rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end);
    //    virtual void updateEditorData();
    //    virtual void updateEditorGeometries();
    //    virtual void updateGeometries();
    //    virtual void verticalScrollbarAction(int action);
    //    virtual void horizontalScrollbarAction(int action);
    //    virtual void verticalScrollbarValueChanged(int value);
    //    virtual void horizontalScrollbarValueChanged(int value);
    //    virtual void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);
    //    virtual void commitData(QWidget *editor);
    //    virtual void editorDestroyed(QObject *editor);

private slots:


    void slot_editStrategyChanged(QSqlTableModel::EditStrategy);

    void slot_editStrategyChange_clicked(int);

    void slot_editingEnabled_clicked(bool);

    void slot_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

    void slot_beforeUpdate(int,QSqlRecord&);

    void slot_beforeInsert(QSqlRecord &record);

    void slot_needsReselect(QList<int>);

private:
    void set_repaintEditBtns(bool On, bool def ,bool hideBtns );

    void set_SelectionModel( bool EditMode );

    QString filter;

    bool selectAndClose;

    QVBoxLayout * mainVl;

    QVBoxLayout * tlbxVl;

    bool contextMenuEnabled;

    Horizontal_Header * hor;



};

#endif // PBLTABLEVIEW_H
