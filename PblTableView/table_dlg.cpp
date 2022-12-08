#include "table_dlg.h"
#include "ui_table_dlg.h"

#include "pbltableview.h"
#include <QMessageBox>
#include "some_tests.h"

Table_Dlg::Table_Dlg(const QString & tableName,
                     QWidget *parent,
                     bool editable,
                     QList<CALC_COLUMN> &calcLst,
                     QList<PblSqlRelation> &relLst) :
    QDialog(parent),
    ui(new Ui::Table_Dlg),
    chosenRec(QSqlRecord()),
    chosenRow(-1)

{
    ui->setupUi(this);

    setSizeGripEnabled(true);

    mdl = new PblSqlRelationalTableModel(this);

    mdl->setTable(tableName);


    foreach( CALC_COLUMN calc , calcLst)
        mdl->setCalcField(calc);


    foreach( PblSqlRelation rel , relLst)
        mdl->setRelation(rel.col, rel);


    setWindowTitle("table : "+tableName);

    if( ! mdl->select())
    {
        QMessageBox::critical(this , tr("Error") , tr("false setTable ")+tableName);
        return;
    }

    view = new PblTableView ( mdl , ui->for_table_lo , this , editable);

    _CONNECT_(view, SIGNAL(sig_rowSelected(QModelIndex)),
              this, SLOT(slot_accepted(QModelIndex)));

    adjustSize();

}


Table_Dlg::~Table_Dlg()
{
    delete ui;
}

/*void Table_Dlg::slot_selectCurrentRecord()
{
    QModelIndex index = view->currentIndex();

    if( ! index.isValid())
        return;

    slot_entered(index);

}*/

void Table_Dlg::slot_accepted(QModelIndex index)
{
    if( ! index.isValid())
        return;

    chosenRow = index.row();

    chosenRec = mdl->record(chosenRow);

    QSqlIndex pk = mdl->primaryKey();

    //qDebug() << " pk " << pk;

    if(pk.count() != 1)
    {
        QMessageBox::critical(this,
                              "error" ,
                              "not defined index field name in " + mdl->tableName());
        return;
    }

    //qDebug() << "    pk.name() " << pk.name() << pk.cursorName() << pk.fieldName(0);
    //qDebug("    pk.value(0) %i" , pk.value(pk.fieldName(0)) );

    //qDebug() << " chosenRec " <<chosenRec;

    chosenId = chosenRec.value(pk.fieldName(0)).toInt();

    //chosenName = mdl_.data(mdl_.index(chosenRow , tDescr_->defaultNameCol)).toString();

    //qDebug() << "my_table_Dlg::the_choice_is_made    " << objectName()<< " chosenId : " << chosenId << " chosenName" << chosenName;

    accept();

}
