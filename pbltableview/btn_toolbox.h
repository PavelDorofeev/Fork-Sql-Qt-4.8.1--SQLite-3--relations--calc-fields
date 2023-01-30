#ifndef BTN_TOOLBOX_H
#define BTN_TOOLBOX_H

#include <QWidget>
#include "search_settings_dlg.h"
#include <QAbstractItemModel>
#include <QIcon>
#include "my_sql.h"
#include <QSqlTableModel>


namespace Ui {
class Btn_ToolBox;
}

class PblTableView;
class PblSqlRelationalTableModel;

class Btn_ToolBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit Btn_ToolBox(PblTableView *view);

    ~Btn_ToolBox();

    PblTableView *view;

    //void setEditable(bool on);

    Ui::Btn_ToolBox *getUi();
    QIcon icon_selectedByField;
    QIcon icon_textSearchedInTable;

    void setBtn_searchInTable(bool visible , bool enabled);
    void setBtn_selectionByValue(bool visible , bool enabled);
    void setBtn_selectByValue(bool visible , bool enabled);


    Ui::Btn_ToolBox *ui;

signals:

public slots:


private slots:

     void on_ledt_filter_returnPressed();

    void on_btn_search_settings_clicked();

    void on_btn_submitAll_clicked();

    void on_btn_selectByValue_clicked(bool checked);

    void on_btn_searchInTable_clicked(bool checked);

    void on_btn_sortEnabled_clicked(bool checked);


    void on_btn_view_clicked();



private:


    //PblSqlRelationalTableModel * mdl;

};

#endif // BTN_TOOLBOX_H
