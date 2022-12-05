#ifndef BTNTOOLBOX_H
#define BTNTOOLBOX_H

#include <QWidget>
#include "search_settings_dlg.h"
#include <QAbstractItemModel>


namespace Ui {
class BtnToolBox;
}

class PblTableView;
class PblSqlRelationalTableModel;

class BtnToolBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit BtnToolBox(PblTableView *view,
                        PblSqlRelationalTableModel *mdl);
    ~BtnToolBox();

    PblTableView *view;

    void setVisible_strategyBox(bool);
    void setVisible_searchBox(bool visible);
    void setEnabled_actionBtns(bool);

    void setEditable(bool on);

signals:

public slots:
    void slot_setEditable(bool on);
    void setSelectionByValue(bool on);

private slots:

     void on_ledt_filter_returnPressed();

    void on_btn_find_clicked();

    void on_cmb_Strategy_currentIndexChanged(int index);

    void on_btn_submitAll_clicked();


    void on_btn_selectByValue_clicked();

private:
    Ui::BtnToolBox *ui;

    PblSqlRelationalTableModel * mdl;



};

#endif // BTNTOOLBOX_H
