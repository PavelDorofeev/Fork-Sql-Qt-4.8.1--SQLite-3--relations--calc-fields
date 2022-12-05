#ifndef TABLE_DLG_H
#define TABLE_DLG_H

#include <QDialog>
#include <QSqlRecord>
#include <QModelIndex>
#include "PblSqlRelationalTableModel.h"

namespace Ui {
class Table_Dlg;
}

class PblSqlRelationalTableModel;
class PblTableView;

class Table_Dlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit Table_Dlg(const QString & tableName,
                       QWidget *parent = 0,
                       bool editable=false,
                       QList<CALC_COLUMN> &calcLst = QList<CALC_COLUMN>());
    ~Table_Dlg();
    
    QSqlRecord chosenRec;
    int chosenRow;
    int chosenId;

public slots:
    //void slot_selectCurrentRecord();
    void slot_accepted(QModelIndex index);
private slots:


private:
    Ui::Table_Dlg *ui;
    PblSqlRelationalTableModel * mdl;
    PblTableView * view;
};

#endif // TABLE_DLG_H
