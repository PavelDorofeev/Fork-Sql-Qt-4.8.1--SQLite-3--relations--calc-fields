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
#include "pbltableview.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QDebug>
#include "some_tests.h"
#include "pblsqlrelationaltablemodel.h"
#include <QSqlError>
#include "btn_toolbox.h"
#include <QSqlDatabase>
#include <QSqlIndex>
#include "table_dlg.h"
#include <QHeaderView>
#include <QSqlField>
#include <QDoubleSpinBox>
#include <QStyledItemDelegate>
#include <QApplication>
#include "pbltableview/my_sql.h"


static QIcon getIcon(int nn) //
{
    /*
      this function exists because of below code occure errors by onloading application

    const QIcon * PblTableView::icon1 = new QIcon(":icon/img/btn-db/select-by-value-1-100x100.png");

      Error: "Pixmap must construct a QApplication before a QPaintDevice"
    */

    static QIcon icon1 = QIcon(":icon/img/btn-db/select-by-value-1-100x100.png");

    static QIcon icon2 = QIcon(":icon/img/btn-db/select-by-value-2-100x100.png");

    if(nn==1)
        return icon1;
    else
        return icon2;
}

PblTableView::PblTableView(PblSqlRelationalTableModel * mdl_,
                           QVBoxLayout * lo,
                           QSqlDatabase db_,
                           QWidget *parent,
                           bool editable):
    QTableView(parent),
    priCol(-1),
    editable(false),
    dblDlg(0)
{

    //icon1 = new QIcon(":icon/img/btn-db/select-by-value-1-100x100.png");

    mdl = mdl_;

    db = db_;

    setSelectionMode(QAbstractItemView::SingleSelection);

    setModel(mdl);

    primaryIndex = mdl->database().primaryIndex(mdl->tableName());

    //qDebug() << "primaryIndex " <<primaryIndex;

    for(int nn=0;  nn <primaryIndex.count(); nn++)
    {
        QSqlField ff = primaryIndex.field(nn);

        //qDebug() << "ff " <<ff << ff.name() << mdl->fieldIndex(ff.name());

        priCol = mdl->fieldIndex(ff.name());
    }

    formMode =  (SETTINGS)( FM_ROW_WILL_BE_CHOSEN | FM_CHK_EDIT_ON) ;

    // ----------------------------------------------------
    //              контекстное меню
    // ----------------------------------------------------

    contextMenu = new QMenu(this);

    fillContextMenu();

    _CONNECT_(this, SIGNAL(customContextMenuRequested(const QPoint &)),
              this, SLOT(slot_CustomMenuRequested(const QPoint &)));

    setContextMenuPolicy(Qt::CustomContextMenu);



    tlbx = new Btn_ToolBox(this , mdl);

    lo->addWidget(tlbx);
    lo->addWidget(this);

    QSqlRecord baseRec = mdl->baseRecord();
    QSqlRecord rec = mdl->record();

    // -----------------------------------------------------------------

    int searchedRelationTxtDefaultColumn = -1;
    int searchedTxtDefaultColumn = -1;
    int searchedDblDefaultColumn = -1;

    for(int col=0; col< baseRec.count(); col++)
    {
        if(col == priCol)
            continue;

        if(mdl->getRelIdColumn(col) >=0)
        {
            mdl->setHeaderData(col, Qt::Horizontal, baseRec.fieldName(col),Qt::EditRole);

            if(searchedRelationTxtDefaultColumn == -1)
                searchedRelationTxtDefaultColumn= col;

        }
        else if(rec.field(col).type() == QVariant::String
                && searchedTxtDefaultColumn == -1)
        {
            searchedTxtDefaultColumn = col;
        }
        else if(rec.field(col).type() == QVariant::Double)
        {
            if(mdl->colInfo.contains(col) && mdl->colInfo.value(col).precision>2)
            {
                if( ! dblDlg)
                    dblDlg = new DoubleDelegate(mdl, this);

                setItemDelegateForColumn(col , (QAbstractItemDelegate *)dblDlg);

                QStyledItemDelegate * stI = qobject_cast<DoubleDelegate*>(itemDelegateForColumn(col));

            }

        }
        if( rec.field(col).type() == QVariant::Int)
        {
            searchedDblDefaultColumn = col;

        }
    }



    if(searchedRelationTxtDefaultColumn >= 0)
    {
        find_settings.searchedField = searchedRelationTxtDefaultColumn;
        find_settings.seachType = Search_Settings_Dlg::FIND_SETTINGS::SEARCH_RELATION_TEXT;
    }
    else if(searchedTxtDefaultColumn >= 0)
    {
        find_settings.searchedField = searchedTxtDefaultColumn;
        find_settings.seachType = Search_Settings_Dlg::FIND_SETTINGS::SEARCH_TEXT;
    }
    else if (searchedDblDefaultColumn >=0)
    {
        find_settings.searchedField = searchedDblDefaultColumn;
        find_settings.seachType = Search_Settings_Dlg::FIND_SETTINGS::SEARCH_NUMBER;
    }
    else
    {
        find_settings.seachType = Search_Settings_Dlg::FIND_SETTINGS::SEARCH_UNDEFINED_TYPE;
    }


    qDebug() << "PblTableView headerData : " << mdl->headerData(0 , Qt::Horizontal, Qt::BackgroundRole);


    find_settings.caseSensitive = false;
    find_settings.exactly = false;


    setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);

    verticalHeader()->setVisible(false);


    _CONNECT_( this , SIGNAL(doubleClicked(QModelIndex)),
               this , SLOT(slot_doubleClicked(QModelIndex)));

    _CONNECT_( mdl , SIGNAL(rowsInserted(QModelIndex, int, int )),
               this , SLOT(slot_rowsInserted(QModelIndex , int , int )));


    setSortingEnabled(false);

    setEditable(editable);
    slot_setVisibleExRelIdColumns(false);

    resizeRowsToContents();
    resizeColumnsToContents();


}

QSize PblTableView::sizeHint() const
{
    return QSize(700,500);
}

void PblTableView::fillContextMenu()
{
    contextMenu->clear();

    // ---------------------------------------------------------------

    act_InsertRow = new QAction( QIcon(":icon/img/btn-db/insert-100x100.png") , trUtf8("create row"), this);
    act_InsertRow->setShortcut(Qt::Key_Insert);

    _CONNECT_(act_InsertRow, SIGNAL(triggered()), this, SLOT(slot_insertRowBtnClick()));

    contextMenu->addAction(act_InsertRow);
    addAction(act_InsertRow);

    contextMenu->addSeparator();

    // ---------------------------------------------------------------

    act_CopyRow = new QAction( QIcon(":icon/img/btn-db/copy-100x100.png") , trUtf8("copy row"), this);
    act_CopyRow->setShortcut(Qt::Key_F9);

    _CONNECT_(act_CopyRow, SIGNAL(triggered()), this, SLOT(slot_copyRowBtnClick()));

    contextMenu->addAction(act_CopyRow);
    addAction(act_CopyRow);

    // ---------------------------------------------------------------

    act_EditRow = new QAction( QIcon(":icon/img/btn-db/edit-100x100.png") , trUtf8("edit row"), this );
    act_EditRow->setShortcut(Qt::Key_F4);

    _CONNECT_(act_EditRow, SIGNAL(triggered()), this, SLOT(slot_editRowBtnClick()));

    contextMenu->addAction(act_EditRow);
    addAction(act_EditRow);

    // ---------------------------------------------------------------

    act_DeleteRow = new QAction(QIcon(":icon/img/btn-db/delete-100x100.png"), trUtf8("remove row"), this);
    act_DeleteRow->setShortcut(Qt::Key_Delete);

    _CONNECT_(act_DeleteRow, SIGNAL(triggered()), this, SLOT(slot_removeRowBtnClick()));

    contextMenu->addAction(act_DeleteRow);
    addAction(act_DeleteRow);

    // ---------------------------------------------------------------

    act_textsearch = new QAction(QIcon(":icon/img/btn-db/text-find-100x100.png"), trUtf8("search"), this);
    act_textsearch->setShortcut(Qt::Key_F3);

    _CONNECT_(act_textsearch, SIGNAL(triggered()), this, SLOT(slot_removeRowBtnClick()));

    //contextMenu->addAction(act_textsearch);
    addAction(act_textsearch);

    // ---------------------------------------------------------------

    act_choiseCurrentRecord = new QAction(trUtf8("choise row"), this);
    act_choiseCurrentRecord->setShortcut(Qt::Key_Enter);

    if( formMode & FM_ROW_WILL_BE_CHOSEN)
        contextMenu->addAction(act_choiseCurrentRecord);

    // -------------------------------------------------------

    contextMenu->addSeparator();

    act_ClearField = new QAction(QIcon(":icon/img/btn-db/clear-field-100x100.png"), trUtf8("clear field"), this);

    _CONNECT_(act_ClearField, SIGNAL(triggered()), this, SLOT(slot_clearFieldClick()));

    contextMenu->addAction(act_ClearField);

    // ---------------------------------------------------------------

    act_selectByFieldValue = new QAction( getIcon(1),
                                          trUtf8("select by field value"),
                                          this);
    act_selectByFieldValue->setShortcut(Qt::Key_F8);
    //act_selectByFieldValue->setCheckable(true); // draw square border around btn
    act_selectByFieldValue->setChecked(false);


    _CONNECT_(act_selectByFieldValue, SIGNAL(triggered(bool)), this, SLOT(slot_triggeredSelectByFieldValue(bool)));

    contextMenu->addAction(act_selectByFieldValue);
    addAction(act_selectByFieldValue);


}

void PblTableView::slot_setVisibleExRelIdColumns(bool visible)
{
    //for(int col = mdl->baseRecord().count(); col < mdl->record().count(); col++)
    for(int col = 0; col < mdl->baseRecord().count(); col++)
    {
        int relIdCol = mdl->getRelIdColumn(col);

        if( relIdCol >=0)
        {
            PblColumn::COLUMN_TYPE type = mdl->getRelationInfoForColumn(col).type;

            if(type  == PblColumn::COLUMN_TYPE_RELATION_ID)

                setColumnHidden(relIdCol , ! visible);
        }

    }
}

void PblTableView::slot_CustomMenuRequested(const QPoint &pos)
{
    //qDebug() << "PblTableView::slot_CustomMenuRequested";

    setContextMenuItemsVisibleAfterFieldSelected();

    contextMenu->popup(this->viewport()->mapToGlobal(pos));
}
void PblTableView::setContextMenuItemsVisibleAfterFieldSelected()
{
    if( ! currentIndex().isValid()) // когда еще нет записей(строк)
        return;

    int col = currentIndex().column();
    int row = currentIndex().row();

    // сначала все очищием
    //act_openCurrentRecord->setVisible(false);
    //act_openRelRecord->setVisible(false);
    act_ClearField->setVisible(false);

    act_EditRow->setVisible(false);
    act_DeleteRow->setVisible(false);
    act_CopyRow->setVisible(false);
    act_InsertRow->setVisible(false);

    act_EditRow->setEnabled(false);
    act_DeleteRow->setEnabled(false);
    act_CopyRow->setEnabled(false);
    act_InsertRow->setEnabled(false);

    //act_openCurrentRecord->setEnabled(false);
    //act_openRelRecord->setEnabled(false);
    act_ClearField->setEnabled(false);


    if( ! editable )
    {
        //        если ONLY READ
        //  контекстное меню все убрано

        //act_openCurrentRecord->setVisible(true);
        //act_openCurrentRecord->setEnabled(true);

        if( formMode & FM_ROW_WILL_BE_CHOSEN)
        {
            //act_selectCurrentRecord->setVisible(true);
            //act_selectCurrentRecord->setEnabled(true);
        }


        if( col < mdl->record().count() )
        {

            if( mdl->getRelIdColumn(col)>0 )
            {
                QString str= mdl->data(mdl->index(row,col)).toString();

                if(str != "")
                {
                    //act_openRelRecord->setText(str);
                    //act_openRelRecord->setVisible(true);
                    //act_openRelRecord->setEnabled(true);
                }
            }
        }

    }
    else        // форма редактируемая
    {
        act_EditRow->setVisible(true);
        act_DeleteRow->setVisible(true);
        act_CopyRow->setVisible(true);
        act_InsertRow->setVisible(true);
        act_ClearField->setVisible(true);

        if(formMode &  FM_CHK_EDIT_ON)
        {
            act_EditRow->setEnabled(true);
            act_DeleteRow->setEnabled(true);
            act_CopyRow->setEnabled(true);
            act_InsertRow->setEnabled(true);

            if(col < mdl->baseRecord().count())
            {
                act_ClearField->setVisible(true);
                act_ClearField->setEnabled(true);
            }

        }
        else
        {
            //act_openCurrentRecord->setVisible(true);
            //act_openCurrentRecord->setEnabled(true);
        }


        if( formMode  &  FM_ROW_WILL_BE_CHOSEN)
        {
            //act_selectCurrentRecord->setVisible(true);
            //act_selectCurrentRecord->setEnabled(true);
        }
        //act_openRelRecord->setVisible(false);
    }

    act_selectByFieldValue->setVisible(true);

    //act_selectByFieldValue->setChecked( filter.isEmpty() );

}

bool PblTableView::slot_clearFieldClick()
{

    QModelIndex currIdx = currentIndex();

    if( ! currIdx.isValid())
    {
        qCritical() << "PblTableView::slot_clearField   currentIndex !isValid  " << currIdx;
        return false;
    }

    int col = currIdx.column();

    if (col == priCol)
        return false;



    return clearField(currIdx);

}

bool PblTableView::clearField(const QModelIndex &currIdx)
{
    int col=currIdx.column();

    int row=currIdx.row();

    //qDebug() << QString("PblTableView::slot_clearField   index [%1x%2]").arg(currIdx.row()).arg(currIdx.column());

    if(! currIdx.isValid())
    {
        qWarning()<<"!!!! error  PblTableView::slot_clearField ! index.isValid()";
        return false;
    }

    QModelIndex idx= mdl->index(currIdx.row(),currIdx.column());

    if(! idx.isValid())
    {
        qCritical()<<"!!!! error  PblTableView::slot_clearField ! idx.isValid()";
        return false;
    }

    //int id = mdl->data(mdl->index(row,mdl->fieldIndex("id"))).toInt();

    bool resSetData=false;

    if ( mdl->columnType(col) == PblColumn::COLUMN_TYPE_RELATION_TEXT)
    {
        QList<QVariant> lst;
        lst << "" << 0;
        resSetData = mdl->setData(currIdx ,lst);

    }
    else
    {
        QVariant defaultVal =  mdl->record().field(col).defaultValue();
        resSetData = mdl->setData(currIdx , defaultVal);

    }

    return resSetData;
}

//-------------------------------------------------

bool PblTableView::insertRow(int row) // функцию можно переопределить и вызвать метод наследника
{
    //qDebug() << "PblTableView::insertRow()";

    // We are insert row at row number xx!
    // xx in QTableView is not id of data model

    if ( mdl->isInsertingRow >= 0)
    {
      if( mdl->editStrategy() <= QSqlTableModel::OnRowChange)
      {
          if( ! mdl->submit()) // this is important to make before insert new row because of new record already was initialized but maybe not saved
          {
              QMessageBox::warning(this, mySql::error, tr("You are already inserted a row, that should editing and saved"));

              QModelIndex idxIns = mdl->index(mdl->isInsertingRow,0);
              setCurrentIndex(idxIns);
              selectRow(idxIns.row());

              return false;

          }
          else
              mdl->isInsertingRow = -1; // clear flag

          // isDirty is not helpы for you because of this tests only by update row, not inserting

          // rowsAboutToBeInserted
          //      emit rowsAboutToBeInserted
          // emit primeInsert
          // endInsertRows
          //      emit rowsInserted -- we use this signal


      }
    }



    if( ! mdl->insertRow(row))
    {
        qCritical() << "PblTableView::insertRow ???? " ;
        return false;
    }

    // ------------------------------------------------------------------------
    // для модели OnManualSubmit надо поля выставить по умолчанию (дефолтные)
    // ------------------------------------------------------------------------

    if(mdl->editStrategy() == QSqlTableModel::OnManualSubmit)
    {
        for(int col =0; col< mdl->rowCount(); col++)
        {
            QVariant def = mdl->record().field(col).defaultValue();

            if( def != QVariant() )
                if( ! mdl->setData( mdl->index(row , col), def, Qt::EditRole ))
                {
                    qCritical() << "PblTableView::my_insertRow  setData : " << def ;
                }
                else
                    qDebug() << "   my_insertRow  setData : true for col " << col ;
        }
    }


    setCurrentIndex( mdl->index(row,0) );

    return true;
}

bool PblTableView::slot_insertRowBtnClick()
{
    int row = 0;

    if( currentIndex().isValid())
        row = currentIndex().row();

    return insertRow(row);
}

//-------------------------------------------------

bool PblTableView::editRow(int row)
{
    return true;//slot_editRow(row);
}

bool PblTableView::slot_editRowBtnClick()
{
    int row = currentIndex().row();
    return editRow(row);
}

//-------------------------------------------------

bool PblTableView::copyRow(int srcRow)
{

    int newRow = srcRow + 1;

    bool bb = mdl->insertRow(newRow);

    if( ! bb )
    {
        qCritical() << "PblTableView::copyRow  insertRow ERROR : " << mdl->lastError();
        return false;
    }

    qDebug() << "mdl->columnCount() " << mdl->columnCount();

    for (int col=0; col < mdl->columnCount(); col++)
    {
        if ( mdl->record().field(col).isAutoValue() ) // dont works i dont understand
            continue;

        if( primaryIndex.contains(mdl->record().fieldName(col) ))
            continue;

        QVariant value = mdl->data(mdl->index(srcRow , col), Qt::DisplayRole);

        if( mdl->columnType(col) == PblColumn::COLUMN_TYPE_RELATION_TEXT )
        {
            int idCol = mdl->getRelIdColumn(col);

            QVariant exValue;

            if(idCol >= 0 && idCol < mdl->columnCount())
            {
                exValue = mdl->data(mdl->index(srcRow , idCol ), Qt::DisplayRole);
            }
            else
            {
                QMessageBox::warning(this , "error" , "copy line is wrong");
                value = QVariant();
            }

            qDebug() << "setData lst " << value << exValue;
            QList<QVariant> lstValue;

            lstValue << value << exValue;

            if( ! mdl->setData ( mdl->index ( newRow , col), lstValue ,Qt::EditRole))
            {
                qCritical("setData false 45466554654");
                continue;
            }
        }
        else
        {
            if( ! mdl->setData ( mdl->index ( newRow , col), value ,Qt::EditRole))
            {
                qCritical("setData false 465846205456");
                continue;
            }
        }
    }

    if(mdl->editStrategy() == QSqlTableModel::OnRowChange
            || mdl->editStrategy() == QSqlTableModel::OnFieldChange)
        if ( ! mdl->submit() )
            QMessageBox::warning(this , mySql::warning , mySql::submitFalse.arg(mdl->tableName()).arg(mdl->lastError().text()));

    return true;
}

bool PblTableView::slot_copyRowBtnClick()
{
    int row = currentIndex().row();
    bool bbb= copyRow(row);
    resizeRowsToContents();
    return bbb;
}
//-------------------------------------------------

bool PblTableView::removeRow(int row)
{
    qDebug() << "PblTableView::removeRow : " << row << " rowCount() " << mdl->rowCount();

    if(row >= mdl->rowCount() || row<0)
        return false;

    bool bb = mdl->removeRow(row);

    return bb;

}

bool PblTableView::slot_removeRowBtnClick()
{
    int row = currentIndex().row();

    bool bbb = removeRow(row);

    resizeRowsToContents();

    adjustSize();

    return bbb;
}
//-------------------------------------------------

void PblTableView::setEditable(bool on)
{
    tlbx->setEditable(on);
}

void PblTableView::slot_doubleClicked(QModelIndex index)
{

    qDebug() << "slot_doubleClicked" << mdl->tableName();

    if( ! editable) // chosing
    {
        emit sig_rowSelected(index);
        return;
    }

    int col = index.column();

    if(mdl->getRelIdColumn( col) >=0 ) // relations
    {
        PblColumn inf = mdl->getRelationInfoForColumn(col);

        if( ! inf.isValid())
            return;


        Table_Dlg dlg = Table_Dlg("goods" , db, this);

        dlg.exec();

        if(dlg.result() == QDialog::Rejected)
            return;

        QVariantList lst;

        if(dlg.chosenRec == QSqlRecord())
        {
            QMessageBox::critical(this , "error" , tr("the choise is not defined"));
            return;
        }

        QVariant txtVal = dlg.chosenRec.value(inf.exTextFieldName);

        lst << txtVal << dlg.chosenId;

        if(dlg.chosenId == -1)
        {
            QMessageBox::critical(this , "error" , tr("the choise is not defined"));
            return;
        }

        if( ! mdl->setData(index , lst ,Qt::EditRole))
        {
            QMessageBox::critical(this , "error" , tr("setData returned  false"));
            return;
        }


    }


}



bool PblTableView::slot_searchInTable(QString & txt)
{

    if( find_settings.searchedField == -1) //еще не понятно по какому полю искать
    {
        QMessageBox::warning(this , "error" , "please select a field than searched in it");

        return false;
    }

    int col = find_settings.searchedField;

    QString fieldName = mdl->baseRecord().fieldName(find_settings.searchedField);

    if(fieldName.isEmpty() || mdl->tableName().isEmpty())
    {
        qCritical("on_ledt_filter_returnPressed error");
        return false;
    }

    if (mdl->getRelIdColumn(find_settings.searchedField) >=0 )

        find_settings.seachType = Search_Settings_Dlg::FIND_SETTINGS::SEARCH_RELATION_TEXT;

    else if (mdl->record().field((int)find_settings.searchedField).type() == QVariant::String )

        find_settings.seachType = Search_Settings_Dlg::FIND_SETTINGS::SEARCH_TEXT;

    else
        find_settings.seachType = Search_Settings_Dlg::FIND_SETTINGS::SEARCH_NUMBER;

    QString filter("");

    if( ! txt.isEmpty())
    {
        // Слева

        if(find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_RELATION_TEXT)
        {
            QString str = mdl->getRelationInfoForColumn(find_settings.searchedField).exTextFieldName;

            filter.append(QString::fromLatin1(" relTblAl_%1.%2 ").
                          arg(col).
                          arg(str));
        }
        else
        {
            filter.append(mdl->tableName()+"."+fieldName);
        }

        if( ! find_settings.caseSensitive )
        {
            if(find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_RELATION_TEXT
                    ||find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_TEXT)
            {
                filter.prepend(" lower(").append(") ");
            }
        }

        //  справа

        if(find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_TEXT
                || find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_RELATION_TEXT)
        {
            if ( find_settings.exactly)
            {
                if( ! find_settings.caseSensitive)
                    filter.append(" LIKE '"+ txt.trimmed().toLower()+"'");
                else
                    filter.append(" LIKE '"+ txt.trimmed()+"'");

            }
            else
            {
                if( ! find_settings.caseSensitive)
                    filter.append(" LIKE '%"+ txt.trimmed().toLower()+"%'");
                else
                    filter.append(" LIKE '%"+ txt.trimmed()+"%'");

            }
        }
        else if(find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_NUMBER)
        {
            filter.append(" = "+ txt.trimmed()+" ");
        }

    }

    mdl->setFilter(filter);

    bool bbb = mdl->select();

    if(! filter.isEmpty() )
    {
        if( ! mdl->setHeaderData(col , Qt::Horizontal, tlbx->icon_textSearchedInTable, Qt::DecorationRole))
            QMessageBox::critical(this , "error" , "setHeaderData return false 6575637657");

        if(bbb)
            tlbx->setBtn_searchInTable(true , true);
    }
    else
    {
        mdl->setHeaderData(col , Qt::Horizontal, QVariant(), Qt::DecorationRole);
        if(bbb)
            tlbx->setBtn_searchInTable(true , false);

    }

    return bbb;
}

void PblTableView::setActionVisible(ACTIONS act, bool visible)
{
    if(act == ACTION_CHOSE_ROW)
        act_choiseCurrentRecord->setVisible(visible);

    else if(act == ACTION_INSERT_ROW)
        act_InsertRow->setVisible(visible);

    else if(act == ACTION_EDIT_ROW)
        act_EditRow->setVisible(visible);

    else if(act == ACTION_COPY_ROW)
        act_CopyRow->setVisible(visible);

    else if(act == ACTION_DELETE_ROW)
        act_DeleteRow->setVisible(visible);

    else if(act == ACTION_CLEAR_FIELD)
        act_ClearField->setVisible(visible);


}

void PblTableView::slot_triggeredSelectByFieldValue(bool on)
{
    if( ! currentIndex().isValid())
    {
        mdl->setFilter("");
        mdl->select();
        act_selectByFieldValue->setIcon(getIcon(1));

    }

    if( slot_selectByFieldValue(currentIndex()))
    {
        if( ! filter.isEmpty())
        {
            tlbx->setBtn_selectByValue(true , true);
            act_selectByFieldValue->setChecked(true);
            act_selectByFieldValue->setIcon(getIcon(2));
        }
        else
        {
            tlbx->setBtn_selectByValue(true , false);
            act_selectByFieldValue->setChecked(false);
            act_selectByFieldValue->setIcon(getIcon(1));
        }
    }
}

void PblTableView::slot_rowsInserted(const QModelIndex &parent, int first, int last)
{
    qDebug() << "PblTableView::slot_rowsInserted " << parent << first << last;
    // start insert row
    mdl->isInsertingRow = first;
}

bool PblTableView::slot_selectByFieldValue(QModelIndex idx)
{
    qDebug() << "PblTableView::slot_selectByFieldValue idx " << idx;

    if(! idx.isValid())
    {
        filter.clear();
    }
    else
    {
        if(! filter.isEmpty())
        {
            filter.clear();
        }
        else
        {
            int col = idx.column();
            int row = idx.row();

            QVariant val = mdl->data(idx);

            QString fieldName = mdl->baseRecord().field(col).name();

            if(fieldName.isEmpty() || mdl->tableName().isEmpty())
            {
                qCritical() <<"error : fieldName is empty, i.e. is not detected";
                return false;
            }

            if(mdl->getRelIdColumn(col) >=0 ) // relation
            {
                QModelIndex exIdx = mdl->index(row , mdl->getRelIdColumn(col));

                val = mdl->data(exIdx);

                if(val.isNull())
                    val=(int)0;
            }

            QString strVal;

            if(val.type() == QVariant::String)
                strVal = val.toString().prepend("'").append("'");
            else
                strVal = val.toString();

            filter.append(QString::fromLatin1(" %1.%2=%3 ").
                          arg(mdl->tableName()).
                          arg(fieldName).
                          arg(strVal));
        }

    }

    mdl->setFilter(filter);

    bool bb = mdl->select();

    return bb;
}
