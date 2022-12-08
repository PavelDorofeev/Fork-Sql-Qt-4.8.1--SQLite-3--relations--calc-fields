#ifndef PBLTABLEVIEW_H
#define PBLTABLEVIEW_H

#include <QTableView>
#include <QHBoxLayout>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QSqlIndex>
#include "search_settings_dlg.h"

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

    /*enum EDITABLE
    {
        EDIT_NO,
        EDIT_YES
    };*/

    explicit PblTableView(PblSqlRelationalTableModel *mdl,
                          QVBoxLayout * lo,
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

    void repaint_selectionByValueBtns(bool on, int col=-1);

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

private slots:
    void slot_doubleClicked(QModelIndex );
    void slot_clickSelectByFieldValue();
private:
    SETTINGS formMode;
    QSqlIndex primaryIndex;


};

#endif // PBLTABLEVIEW_H