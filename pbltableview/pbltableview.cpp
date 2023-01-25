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
#include "pbltableview/pblsqlrelationaltablemodel.h"
#include <QSqlError>
#include "btn_toolbox.h"
#include <QSqlDatabase>
#include <QSqlIndex>
#include "pbl_table_dlg.h"
#include <QHeaderView>
#include <QSqlField>
#include <QDoubleSpinBox>
#include <QStyledItemDelegate>
#include <QApplication>
#include <QComboBox>
#include <QSqlQuery>
#include "pbltableview/my_sql.h"
#include "pbltableview/combobox_delegate.h"
#include "pbltableview/checkbox_delegate.h"
#include "config.h"
#include "ui_btn_toolbox.h"
#include "date_delegate.h"

const QString PblTableView::s_submit= QObject::tr("submit");
const QString PblTableView::s_submitAll= QObject::tr("submit All");


PblTableView::PblTableView(PblSqlRelationalTableModel * mdl_,
                           QVBoxLayout * lo,
                           QSqlDatabase &db_,
                           QWidget *parent,
                           bool editable_,
                           bool selectable_):
    QTableView(parent),
    priCol(-1),
    act_InsertRow(0),
    act_CopyRow(0),
    act_EditRow(0),
    act_DeleteRow(0),
    act_ClearField(0),
    act_choiceCurrentRecord(0),
    act_search(0),
    act_selectByFieldValue(0),
    act_view(0),
    act_selectAndClose(0),
    dblDlg(0),
    selectAndClose(0),
    act_showRelExColumns(0),
    //db(db_),
    selectable(selectable_),
    editable(editable_)
{

    db = QSqlDatabase::database();
    mdl = mdl_;


    setSelectionMode(QAbstractItemView::SingleSelection);

    if( ! mdl )
    {
        qCritical("error mdl is null");
        return;
    }

    setModel(mdl);

    // ----------------------------------------------------
    //              context menu
    // ----------------------------------------------------

    contextMenu = new QMenu(this);

    //fillContextMenu();

    _CONNECT_(this, SIGNAL(customContextMenuRequested(const QPoint &)),
              this, SLOT(slot_CustomMenuRequested(const QPoint &)));

    setContextMenuPolicy(Qt::CustomContextMenu);

    _CONNECT_(mdl, SIGNAL(sig_editStrategyChanged(QSqlTableModel::EditStrategy)),
              this, SLOT(slot_editStrategyChanged(QSqlTableModel::EditStrategy)));

    _CONNECT_(mdl, SIGNAL(sig_rowIsDirty(int)),
              this, SLOT(slot_rowIsDirty(int)));

    tlbx = new Btn_ToolBox(this , mdl);

    lo->addWidget(tlbx);
    lo->addWidget(this);


    qDebug() << "PblTableView headerData : " << mdl->headerData(0 , Qt::Horizontal, Qt::BackgroundRole);


    find_settings.caseSensitive = false;
    find_settings.exactly = false;


    setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);

    verticalHeader()->setVisible(false);


    _CONNECT_( this , SIGNAL(doubleClicked(QModelIndex)),
               this , SLOT(slot_doubleClicked(QModelIndex)));

    setSortingEnabled(false);

    tlbx->ui->btn_insert->setVisible(false);
    tlbx->ui->btn_copy->setVisible(false);
    tlbx->ui->btn_edit->setVisible(false);
    tlbx->ui->btn_delete->setVisible(false);

    tlbx->ui->btn_view->setVisible(false);

    tlbx->ui->chk_showRelExColumns->setVisible(false);
    tlbx->ui->chk_editable->setVisible(false);

    tlbx->ui->cmb_Strategy->setVisible(false);
    tlbx->ui->btn_submitAll->setVisible(false);
    tlbx->ui->btn_sortEnabled->setVisible(false);

    tlbx->ui->btn_searchInTable->setVisible(false);
    tlbx->ui->btn_search_settings->setVisible(false);
    tlbx->ui->ledt_filter->setVisible(false);

    tlbx->ui->btn_selectByValue->setVisible(false);

    //slot_setVisibleExRelIdColumns(false);

    if( editable )
    {
        PblTableView::ACTIONS acts = PblTableView::ACT_ALL_EDIT
                | PblTableView::ACT_SWITCH_EDIT_ENABLED
                | PblTableView::ACT_ALL_SEARCH;

        set_Actions(acts , editable);
    }

    PblTableView::ACTIONS acts = PblTableView::ACT_VIEW;

    set_Actions(acts , true);

    setEditState(editable);

    _CONNECT_(tlbx->ui->cmb_Strategy, SIGNAL(currentIndexChanged(int)),
              this , SLOT(slot_cmb_Strategy_currentIndexChanged(int)));


}

PblTableView::~PblTableView()
{
    qDebug() << "~PblTableView()";

}

QIcon PblTableView::getActIcon(PblTableView::ACTION act)
{

    static QIcon insert = QIcon(":icon/img/btn-db/insert-100x100.png");
    static QIcon copy   = QIcon(":icon/img/btn-db/copy-100x100.png");
    static QIcon edit   = QIcon(":icon/img/btn-db/edit-100x100.png");
    static QIcon remove = QIcon(":icon/img/btn-db/delete-100x100.png");
    static QIcon search = QIcon(":icon/img/btn-db/text-find-100x100.png");
    static QIcon clrFld = QIcon(":icon/img/btn-db/clear-field-100x100.png");
    static QIcon txtFind = QIcon(":icon/img/btn-db/text-find-100x100.png");
    static QIcon view = QIcon(":icon/img/btn-db/view-100x100.png");
    static QIcon selectAndClose = QIcon(":icon/img/btn-db/select-and-close-100x100.png");

    if(act == PblTableView::ACT_INSERT_ROW)
        return insert;

    else if(act == PblTableView::ACT_COPY_ROW)
        return copy;

    else if(act == PblTableView::ACT_EDIT_ROW)
        return edit;

    else if(act == PblTableView::ACT_DELETE_ROW)
        return remove;

    else if(act == PblTableView::ACT_SEARCH)
        return search;

    else if(act == PblTableView::ACT_CLEAR_SEARCH_RESULTS)
        return txtFind;

    else if(act == PblTableView::ACT_CLEAR_FIELD)
        return clrFld;

    else if(act == PblTableView::ACT_VIEW)
        return view;

    else if(act == PblTableView::ACT_SELECT_AND_CLOSE)
        return selectAndClose;



}

QIcon PblTableView::getIcon(int nn) //
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


QSize PblTableView::sizeHint() const
{
    return QSize(700,500);
}

void PblTableView::fillContextMenu()
{


}

void PblTableView::slot_setVisibleExRelIdColumns(bool visible)
{

    for(int col = 0; col < mdl->baseRecord().count(); col++)
    {
        // after select only

        int relIdCol = mdl->getRelIdColumn(col);

        if( relIdCol >=0)
        {
            PblColumn::COLUMN_TYPE type = mdl->getRelationInfoForColumn(col).type; //??

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

    if( act_ClearField != 0)
        act_ClearField->setVisible(false);

    if( act_EditRow != 0)
        act_EditRow->setVisible(false);

    if( act_DeleteRow != 0)
        act_DeleteRow->setVisible(false);

    if( act_CopyRow != 0)
        act_CopyRow->setVisible(false);

    if( act_InsertRow != 0)
        act_InsertRow->setVisible(false);

    if( act_EditRow != 0)
        act_EditRow->setEnabled(false);

    if( act_DeleteRow != 0)
        act_DeleteRow->setEnabled(false);

    if( act_CopyRow != 0)
        act_CopyRow->setEnabled(false);

    if( act_InsertRow != 0)
        act_InsertRow->setEnabled(false);

    //act_openCurrentRecord->setEnabled(false);
    //act_openRelRecord->setEnabled(false);

    if( act_ClearField != 0)
        act_ClearField->setEnabled(false);


    if( ! editable )
    {
        //        если ONLY READ
        //  контекстное меню все убрано

        //act_openCurrentRecord->setVisible(true);
        //act_openCurrentRecord->setEnabled(true);

        if( selectable )
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
    else if( editable )       // форма редактируемая
    {
        if( act_EditRow != 0)
            act_EditRow->setVisible(true);

        if( act_DeleteRow != 0)
            act_DeleteRow->setVisible(true);

        if( act_CopyRow != 0)
            act_CopyRow->setVisible(true);

        if( act_InsertRow != 0)
            act_InsertRow->setVisible(true);

        if( act_ClearField != 0)
            act_ClearField->setVisible(true);

        if( editable )
        {
            if( act_EditRow != 0)
                act_EditRow->setEnabled(true);

            if( act_DeleteRow != 0)
                act_DeleteRow->setEnabled(true);

            if( act_CopyRow != 0)
                act_CopyRow->setEnabled(true);

            if( act_InsertRow != 0)
                act_InsertRow->setEnabled(true);

            if(col < mdl->baseRecord().count())
            {
                if( act_ClearField != 0)
                {
                    act_ClearField->setVisible(true);
                    act_ClearField->setEnabled(true);
                }
            }

        }
        else
        {
            //act_openCurrentRecord->setVisible(true);
            //act_openCurrentRecord->setEnabled(true);
        }


        if( selectable )
        {
            //act_selectCurrentRecord->setVisible(true);
            //act_selectCurrentRecord->setEnabled(true);
        }
        //act_openRelRecord->setVisible(false);
    }


    if( act_selectByFieldValue != 0)
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

bool PblTableView::insertRow(int srcRow) // функцию можно переопределить и вызвать метод наследника
{
    //qDebug() << "PblTableView::insertRow()";

    mdl->submit(); // forever first call submit, result is not important


    int newRow = mdl->rowCount();// forever insert at end

    if( ! mdl->insertRow(newRow))
    {
        qCritical() << "PblTableView::insertRow ???? " ;
        return false;
    }

    mdl->isInsertRow = newRow;

    setCurrentIndex( mdl->index( newRow , 0 ) );

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
    QMessageBox::warning(this,
                         mySql::error_,
                         tr("You should realize this code yourself"));
    return true;//slot_editRow(row);
}

bool PblTableView::slot_editRowBtnClick()
{
    int row = currentIndex().row();

    return emit sig_editRow(row);

    //return editRow(row);
}

//-------------------------------------------------

bool PblTableView::viewRow(int row)
{
    // this code you implement youself
    QMessageBox::warning(this,
                         mySql::error_,
                         tr("You should implement this code yourself"));
    return false;
}

bool PblTableView::slot_viewRowBtnClick()
{
    if( ! currentIndex().isValid())
        return false;


    return sig_viewRow(currentIndex().row());
}

//-------------------------------------------------

int PblTableView::restoreCurrentRowPositionAfterSubmit(int srcRow)
{
    QModelIndex priIdx = mdl->index( srcRow , mdl->getPriColumn());

    if(priIdx.isValid())
    {
        bool ok = false;

        int id = mdl->data(priIdx).toInt(&ok);

        if( ! ok)
            return -1;

        int foundRow = mdl->findRowById( id );

        if ( foundRow != -1)
        {
            return foundRow;
        }
    }

    return -1;
}

bool PblTableView::copyRow(int srcRow)
{

    int id = mdl->getRowPriValue( srcRow );

    if ( mdl->submit() && id >=0)
    {
        srcRow = mdl->findRowById(id);

        if(srcRow == -1)
        {
            QMessageBox::warning(this ,
                                 mySql::error_ ,
                                 tr("copying row,\nneeds submit, after submit lost row focus,\ntable %1, error: %2").
                                 arg(mdl->tableName()).
                                 arg(mdl->lastError().text()));
            return false;
        }
    }

    int newRow = srcRow + 1;


    bool bb = mdl->insertRow(newRow);

    // emit primeInsert

    if( ! bb )
    {
        qCritical() << "PblTableView::copyRow  insertRow ERROR : " << mdl->lastError();
        return false;
    }

    //mdl->isDirtyRow = newRow;

    // qDebug() << "mdl->columnCount() " << mdl->columnCount();

    for (int col=0; col < mdl->columnCount(); col++)
    {
        if ( mdl->record().field(col).isAutoValue() ) // dont works i dont understand
            continue;

        if( mdl->primaryIndex.contains(mdl->record().fieldName(col) ))
            continue;

        if( mdl->isCalcColumn(col) )
            continue;

        QVariant value = mdl->data(mdl->index(srcRow , col), Qt::DisplayRole);

        QModelIndex idx = mdl->index ( newRow , col);

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


            if( ! mdl->setData ( idx , lstValue ,Qt::EditRole))
            {
                QMessageBox::warning(this ,
                                     mySql::error_ ,
                                     tr("copying row,\nrelational field %3,\n setData returns false,\ntable %1, error: %2").
                                     arg(mdl->tableName()).
                                     arg(mdl->lastError().text()).
                                     arg(mdl->record().fieldName(col)));

                qCritical("setData false 45466554654");

                continue;
            }

            if( ! idx.isValid())
            {
                qDebug() << "setData calls submit/select";
            }
        }
        else // generic column
        {

            if( ! mdl->setData ( idx , value ,Qt::EditRole))
            {
                QMessageBox::warning(this ,
                                     mySql::error_ ,
                                     tr("copying row:\n setData returns false,\ntable %1, error: %2").
                                     arg(mdl->tableName()).
                                     arg(mdl->lastError().text()));

                qCritical("setData false 465846205456");
                continue;
            }

        }

        if( ! idx.isValid())
        {
            QMessageBox::warning(this ,
                                 mySql::error_ ,
                                 tr("copying row:\n setData returns true,\nbut submit/select occures\ntable %1, error: %2").
                                 arg(mdl->tableName()).
                                 arg(mdl->lastError().text()));
            return false;
        }
    }

    if(mdl->editStrategy() <= QSqlTableModel::OnRowChange)
    {
        if ( ! mdl->submit() )
            QMessageBox::warning(this ,
                                 mySql::warning ,
                                 mySql::submitFalse.
                                 arg(mdl->tableName()).
                                 arg(mdl->lastError().text()));
    }

    return true;
}

bool PblTableView::slot_copyRowBtnClick()
{
    int row = currentIndex().row();

    if(! currentIndex().isValid())
    {
        QMessageBox::warning(this ,
                             mySql::warning ,
                             tr("before copying a line you should select it\ntable '%1'\nerror:%2").
                             arg(mdl->tableName()).
                             arg(mdl->lastError().text()));
        return false;
    }

    bool bbb= copyRow(row);

    resizeRowsToContents();

    return bbb;
}
//-------------------------------------------------

bool PblTableView::removeRow(int row)
{
    qDebug() << "PblTableView::removeRow : " << row << " rowCount() " << mdl->rowCount();

    if( mdl->isInsertRow != -1) //
    {
        bool bb = mdl->removeRow(mdl->isInsertRow);

        if( ! bb )
        {

            QMessageBox::warning(this ,
                                 mySql::warning ,
                                 tr("before removing a line you should submit dirty row %2 (id : %3)\ntable '%1'\nerror:%4").
                                 arg(mdl->tableName()).
                                 arg(mdl->isInsertRow).
                                 arg(mdl->getRelIdColumn(mdl->isInsertRow)).
                                 arg(mdl->lastError().text()));
            return false;
        }
        mdl->isInsertRow = -1;

    }

    if(row >= mdl->rowCount() || row < 0)
        return false;

    bool bb = mdl->removeRow(row);

    if(bb)
    {
        int col = config::get_defaultColumn(mdl);

        QModelIndex idx = mdl->index(row , col);

        if(row < mdl->rowCount())
            if( idx.isValid())
                setCurrentIndex(idx );
    }

    return bb;

}

bool PblTableView::slot_removeRowBtnClick()
{
    int row = currentIndex().row();

    bool bbb = removeRow(row);

    if( bbb)
    {
        slot_showSubmitBtn( true);

        resizeRowsToContents();

        adjustSize();
    }

    return bbb;
}
//-------------------------------------------------

void PblTableView::setEditState(bool editOn)
{

    tlbx->ui->chk_editable->setChecked(editOn);

    slot_setEditable(editOn);

}

//-------------------------------------------------

void PblTableView::setSelectAndClose()
{
    selectAndClose = true;

}


void PblTableView::slot_doubleClicked(const QModelIndex & index)
{

    qDebug() << "slot_doubleClicked" << mdl->tableName();

    if(selectable &&  ! tlbx->ui->chk_editable->isChecked())
    {
        act_selectAndClose->trigger();
        return;
    }

    int col = index.column();

    if(mdl->isRelationalColumn( col) ) // relations
    {
        PblColumn inf = mdl->getRelationInfoForColumn(col);

        if( ! inf.isValid())
            return;


        PblTableDlg dlg = PblTableDlg( db, this, true , true );

        if( ! dlg.view->prepare(inf.ext_table) )
        {
            QMessageBox::critical(this , "error" , tr("table '%1' is not opened").arg(inf.ext_table));
            return;
        }

        dlg.view->setEditState(false);

        dlg.exec();

        if(dlg.result() == QDialog::Rejected)
            return;

        QVariantList lst;

        if(dlg.chosenRec == QSqlRecord())
        {
            QMessageBox::critical(this , "error" , tr("the choise is not defined"));
            return;
        }

        QVariant txtVal = dlg.chosenRec.value(inf.destField);

        lst << txtVal << dlg.chosenId;

        qDebug() << "lst " << lst;

        if(dlg.chosenId == -1)
        {
            QMessageBox::critical(this , "error" , tr("the choise is not defined"));
            return;
        }

        if( ! mdl->setData(index , lst ,Qt::EditRole))
        {
            QMessageBox::critical(this ,
                                  "error" ,
                                  tr("setData returns  false\n%1").
                                  arg(mdl->lastError().text()));
            return;
        }

    }
    else if(dlgts.contains(col))
    {
        if(qobject_cast<checkBox_Delegate *>(dlgts.value(col)))
        {
            checkBox_Delegate * chk = qobject_cast<checkBox_Delegate *>(dlgts.value(col));

            bool b = mdl->data(index).toBool();

            if ( ! mdl->setData(index , (int)! b) )
                qCritical("error setData checkbox field");

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
            QString str = mdl->getRelationInfoForColumn(find_settings.searchedField).destField;

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

    bool selectOk = mdl->select();

    if(! filter.isEmpty() )
    {
        if( ! mdl->setHeaderData(col , Qt::Horizontal, getActIcon(ACT_CLEAR_SEARCH_RESULTS), Qt::DecorationRole))
            QMessageBox::critical(this , "error" , "setHeaderData return false 6575637657");

        if(selectOk)
        {
            tlbx->ui->btn_searchInTable->setVisible(true);
            tlbx->ui->btn_searchInTable->setEnabled(true);

        }
    }
    else
    {
        mdl->setHeaderData(col , Qt::Horizontal, QVariant(), Qt::DecorationRole);
        if(selectOk)
        {
            tlbx->ui->btn_searchInTable->setVisible(true);
            tlbx->ui->btn_searchInTable->setEnabled(false);

        }
    }

    return selectOk;
}

void PblTableView::setEditStrategyVisible(bool on)
{
    set_Actions(PblTableView::ACT_SELECT_STRATEGY_ENABLED , on);

}
bool PblTableView::prepare(const QString & tableName )
{


    if ( ! mdl->set_Table(tableName))
    {
        QMessageBox::warning(this,
                             mySql::error_,
                             tr("table '%1' not exists in database\n error : %2").
                             arg(tableName).
                             arg(mdl->lastError().text()));

        return false;
    }

    if ( ! config::setting_mdl( mdl ) )
    {
        QMessageBox::warning(this,
                             mySql::error_,
                             tr("error in setting_mdl"));
        return false;
    }

    if ( ! mdl->select())
    {
        QMessageBox::warning(this,
                             mySql::error_,
                             tr("error in select query:\n\n%1\n\n\n%2").
                             arg(mdl->query().lastQuery()).
                             arg(mdl->lastError().text()));
        return false;
    }

    if ( ! config::setting_view( this ) )
    {
        QMessageBox::warning(this,
                             mySql::error_,
                             tr("error in setting_view\n table :%1").arg(tableName));
        return false;
    }


    return true;

}

void PblTableView::set_Actions(PblTableView::ACTIONS act, bool On)
{

    // ----------------------------------------------------------
    //                       INSERT_ROW
    // ----------------------------------------------------------

    if(act & ACT_INSERT_ROW)
    {
        if(On)
        {
            if(act_InsertRow  == 0)
            {

                act_InsertRow = new QAction( getActIcon(ACT_INSERT_ROW) , trUtf8("create row"), this);
                act_InsertRow->setShortcut(Qt::Key_Insert);

                _CONNECT_(act_InsertRow, SIGNAL(triggered()), this, SLOT(slot_insertRowBtnClick()));

                _CONNECT_(tlbx->ui->btn_insert, SIGNAL(clicked()),
                          act_InsertRow, SLOT( trigger() ));

                contextMenu->addAction(act_InsertRow);

                addAction(act_InsertRow);

            }
        }
        else if ( ! On)
        {
            if(act_InsertRow  != 0)
            {
                act_InsertRow->setVisible(On);
            }

        }
        tlbx->ui->btn_insert->setVisible(On);
        tlbx->ui->btn_insert->setEnabled(On);
    }

    // ----------------------------------------------------------
    //                       EDIT_ROW
    // ----------------------------------------------------------
    if(act & ACT_EDIT_ROW)
    {
        if(On)
        {
            if(act_EditRow  == 0)
            {

                act_EditRow = new QAction( getActIcon(ACT_EDIT_ROW) , trUtf8("edit row"), this);

                act_EditRow->setShortcut(Qt::Key_F4);

                _CONNECT_(act_EditRow, SIGNAL(triggered()), this, SLOT(slot_editRowBtnClick()));

                _CONNECT_(tlbx->ui->btn_edit, SIGNAL(clicked()),
                          act_EditRow, SLOT( trigger() ));

                contextMenu->addAction(act_EditRow);

                addAction(act_EditRow);
            }
        }
        else if ( ! On)
        {
            if(act_EditRow  != 0)
            {
                act_EditRow->setVisible(On);
            }


        }
        tlbx->ui->btn_edit->setVisible(On);
        tlbx->ui->btn_edit->setEnabled(On);
    }

    // ----------------------------------------------------------
    //                       COPY_ROW
    // ----------------------------------------------------------

    if(act & ACT_COPY_ROW)
    {
        if(On)
        {
            if(act_CopyRow  == 0)
            {

                act_CopyRow = new QAction( getActIcon(ACT_COPY_ROW) , trUtf8("copy row"), this);

                act_CopyRow->setShortcut(Qt::Key_F9);

                _CONNECT_(act_CopyRow, SIGNAL(triggered()), this, SLOT(slot_copyRowBtnClick()));


                _CONNECT_(tlbx->ui->btn_copy, SIGNAL(clicked()), act_CopyRow, SLOT( trigger() ));

                contextMenu->addAction(act_CopyRow);

                addAction(act_CopyRow);
            }
        }
        else if ( ! On)
        {
            if(act_CopyRow  != 0)
            {
                act_CopyRow->setVisible(On);
            }


        }
        tlbx->ui->btn_copy->setVisible(On);
        tlbx->ui->btn_copy->setEnabled(On);
    }

    // ----------------------------------------------------------
    //                       DELETE_ROW
    // ----------------------------------------------------------

    if(act & ACT_DELETE_ROW)
    {
        if(On)
        {
            if(act_DeleteRow  == 0)
            {

                act_DeleteRow = new QAction( getActIcon(ACT_DELETE_ROW), trUtf8("remove row"), this);

                act_DeleteRow->setShortcut(Qt::Key_Delete);

                _CONNECT_(act_DeleteRow, SIGNAL(triggered()), this, SLOT(slot_removeRowBtnClick()));

                _CONNECT_(tlbx->ui->btn_delete, SIGNAL(clicked()), act_DeleteRow, SLOT( trigger() ));

                contextMenu->addAction(act_DeleteRow);

                addAction(act_DeleteRow);

            }
        }
        else if ( ! On)
        {
            if(act_DeleteRow  != 0)
            {
                act_DeleteRow->setVisible(On);
            }

        }
        tlbx->ui->btn_delete->setVisible(On);
        tlbx->ui->btn_delete->setEnabled(On);
    }

    // ----------------------------------------------------------
    //                       VIEW
    // ----------------------------------------------------------

    if(act & ACT_VIEW)
    {

        if( On )
        {
            if(act_view  == 0)
            {

                act_view = new QAction( getActIcon(ACT_VIEW), trUtf8("view"), this);

                act_view->setShortcut(Qt::Key_F3);

                _CONNECT_(act_view, SIGNAL(triggered()), this, SLOT(slot_viewRowBtnClick()));

                addAction(act_view);

                contextMenu->addAction(act_view);

                act_view->setVisible(On);

            }
        }
        else if ( ! On )
        {
            if(act_view  != 0)
            {
                act_view->setVisible(On);
            }

        }

        if(act_view  != 0)
            tlbx->ui->btn_view->setVisible(On);

    }


    // ----------------------------------------------------------
    //                       SEARCH
    // ----------------------------------------------------------

    if(act & ACT_SEARCH)
    {

        if( On )
        {
            if(act_search  == 0)
            {

                act_search = new QAction( getActIcon(ACT_SEARCH), trUtf8("search"), this);

                act_search->setShortcut(Qt::Key_F2);

                //_CONNECT_(act_search, SIGNAL(triggered()), this, SLOT(slot_removeRowBtnClick()));

                addAction(act_search);

                act_search->setVisible(On);

            }
        }
        else if ( ! On )
        {
            if(act_search  != 0)
            {
                act_search->setVisible(On);
            }

        }

        tlbx->ui->btn_searchInTable->setVisible(On);
        tlbx->ui->ledt_filter->setVisible(On);
        tlbx->ui->btn_search_settings->setVisible(On);
    }

    // ----------------------------------------------------------
    //                       CLEAR_FIELD
    // ----------------------------------------------------------

    if(act & ACT_CLEAR_FIELD)
    {
        if(On)
        {
            if(act_ClearField  == 0)
            {

                act_ClearField = new QAction( getActIcon(ACT_CLEAR_FIELD), trUtf8("clear field"), this);

                _CONNECT_(act_ClearField, SIGNAL(triggered()), this, SLOT(slot_clearFieldClick()));

                contextMenu->addAction(act_ClearField);

                addAction(act_ClearField);

            }
        }
        else if ( ! On)
        {
            if(act_ClearField  != 0)
            {
                act_ClearField->setVisible(On);
            }


        }
    }

    // ----------------------------------------------------------
    //                       SELECT_BY_FIELD_VALUE
    // ----------------------------------------------------------

    if(act & ACT_SELECT_BY_FIELD_VALUE)
    {
        if(On)
        {
            if(act_selectByFieldValue  == 0)
            {
                act_selectByFieldValue = new QAction( getIcon(1),
                                                      trUtf8("select by field value"),
                                                      this);

                act_selectByFieldValue->setShortcut(Qt::Key_F8);

                act_selectByFieldValue->setChecked(false);


                _CONNECT_(act_selectByFieldValue, SIGNAL(triggered(bool)),
                          this, SLOT(slot_triggeredSelectByFieldValue(bool)));

                contextMenu->addAction(act_selectByFieldValue);

                addAction(act_selectByFieldValue);

            }
        }
        else if ( ! On)
        {
            if(act_selectByFieldValue  != 0)
            {
                _DISCONNECT_(act_selectByFieldValue, SIGNAL(triggered(bool)),
                             this, SLOT(slot_triggeredSelectByFieldValue(bool)));

                delete act_selectByFieldValue;
            }
        }
        tlbx->ui->btn_selectByValue->setVisible(On);
    }

    // ----------------------------------------------------------
    //                       SELECT_BY_FIELD_VALUE
    // ----------------------------------------------------------

    if(act & ACT_SORT)
    {
        tlbx->ui->btn_sortEnabled->setVisible(On);
    }

    // ----------------------------------------------------------
    //                       SELECT_STRATEGY_ENABLED
    // ----------------------------------------------------------

    if(act & ACT_SELECT_STRATEGY_ENABLED)
    {
        tlbx->ui->cmb_Strategy->setVisible(On);
        tlbx->ui->btn_submitAll->setVisible(On);

        _CONNECT_(mdl, SIGNAL(sig_showSubmit( bool )),
                  this, SLOT(slot_showSubmitBtn( bool )));
    }

    // ----------------------------------------------------------
    //                       SHOW_EXTENDED_RELATION_COLUMNS
    // ----------------------------------------------------------

    if(act & ACT_SHOW_EXTENDED_RELATION_COLUMNS)
    {
        if( On )
        {
            act_showRelExColumns = new QAction( getIcon(1),
                                                trUtf8("show rel extented columns"),
                                                this);

            _CONNECT_(act_showRelExColumns, SIGNAL(triggered(bool)),
                      this, SLOT(slot_setVisibleExRelIdColumns(bool)));

            _CONNECT_(tlbx->ui->chk_showRelExColumns, SIGNAL(toggled(bool)),
                      act_showRelExColumns, SIGNAL(triggered(bool)));

            tlbx->ui->chk_showRelExColumns->setVisible(On);

            slot_setVisibleExRelIdColumns( tlbx->ui->chk_showRelExColumns->isChecked() );


        }
        else if ( ! On & act_showRelExColumns != 0)
        {
            tlbx->ui->chk_showRelExColumns->setVisible(On);

            _DISCONNECT_(act_showRelExColumns, SIGNAL(clicked(bool)),
                         this, SLOT( slot_setVisibleExRelIdColumns(bool)));

            _DISCONNECT_(tlbx->ui->chk_showRelExColumns, SIGNAL(toggled(bool)),
                         act_showRelExColumns, SLOT(triggered(bool)));

            delete act_showRelExColumns;
        }


    }

    // ----------------------------------------------------------
    //                       SWITCH_EDIT_ENABLED
    // ----------------------------------------------------------

    if(act & ACT_SWITCH_EDIT_ENABLED)
    {
        if(On)
        {
            _CONNECT_(tlbx->ui->chk_editable, SIGNAL(clicked(bool)),
                      this, SLOT( slot_setEditable(bool)));
        }
        else
        {
            _DISCONNECT_(tlbx->ui->chk_editable, SIGNAL(clicked(bool)),
                         this, SLOT( slot_setEditable(bool)));
        }

        tlbx->ui->chk_editable->setVisible(On);

    }

    // ----------------------------------------------------------
    //
    // ----------------------------------------------------------

    if(act & ACT_EDIT_ON)
    {
        //tlbx->ui->chk_editable->setVisible(visible);

        setEditState(On);

        if(On)
        {

            /*_CONNECT_(tlbx->ui->chk_editable, SIGNAL(clicked(bool)),
                      this, SLOT( slot_setEditable(bool)));*/
        }
        else
        {
            /*_DISCONNECT_(tlbx->ui->chk_editable, SIGNAL(clicked(bool)),
                      this, SLOT( slot_setEditable(bool)));*/
        }
    }

}

void PblTableView::show_view_Btn()
{
    if(tlbx->ui->chk_editable->isChecked())
    {
        set_Actions(PblTableView::ACT_VIEW , false);
    }
    else
        set_Actions(PblTableView::ACT_VIEW, true);
}

void PblTableView::slot_triggeredSelectByFieldValue(bool on)
{
    if(act_selectByFieldValue ==0)
        return;

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

void PblTableView::setCheckBoxDelegate(int col)
{
    if(col <0 || col >= mdl->record().count())
    {
        QMessageBox::warning(this , mySql::error_ , tr("column is out of range , field : %1").arg(col));
        return;
    }

    if(dlgts.contains(col))
    {
        QMessageBox::warning(this , mySql::error_ , tr("second attempting adding QCheckBox to field : %1").arg(col));
        return;
    }


    dlgts.insert( col, new checkBox_Delegate(mdl , this) );

    QStyledItemDelegate * cmbDeleg = dlgts.value(col);

    setItemDelegateForColumn(col, cmbDeleg);
}

void PblTableView::setComboBoxDelegate(int col, QStringList &lst)
{
    if(col <0 || col>=mdl->record().count())
    {
        QMessageBox::warning(this , mySql::error_ , tr("column is out of range , field : %1").arg(col));
        return;
    }

    if(dlgts.contains(col))
    {
        QMessageBox::warning(this , mySql::error_ , tr("second attempting adding QComboBox to field : %1").arg(col));
        return;
    }


    dlgts.insert( col,
                  new ComboBoxDelegate(
                      mdl ,
                      col,
                      lst,
                      this)
                  );

    QStyledItemDelegate * cmbDeleg = dlgts.value(col);

    setItemDelegateForColumn(col, cmbDeleg);

}

void PblTableView::setDateTimeDelegate(int col)
{
    if(col <0 || col>=mdl->record().count())
    {
        QMessageBox::warning(this , mySql::error_ , tr("column is out of range , field : %1").arg(col));
        return;
    }

    if(dlgts.contains(col))
    {
        QMessageBox::warning(this , mySql::error_ , tr("second attempting add a date_Delegate to field : %1").arg(col));
        return;
    }


    dlgts.insert( col,
                  new date_Delegate( 0, this)
                  );

    setItemDelegateForColumn(col, dlgts.value(col));

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


PblSqlRelationalTableModel* PblTableView::model() const
{

    return mdl;
}

void PblTableView::slot_setEditable(bool on)
{

    editable = on;

    if(on)
    {
        setSelectionBehavior(QAbstractItemView::SelectItems);

        setEditTriggers(QAbstractItemView::DoubleClicked
                        |QAbstractItemView::AnyKeyPressed); //EditKeyPressed);//AllEditTriggers);

        if(act_DeleteRow != 0)
            tlbx->ui->btn_delete->setVisible(on);

        if(act_CopyRow != 0)
            tlbx->ui->btn_copy->setVisible(on);

        if(act_EditRow != 0)
            tlbx->ui->btn_edit->setVisible(on);

        if(act_InsertRow != 0)
            tlbx->ui->btn_insert->setVisible(on);

        if(act_view != 0)
            tlbx->ui->btn_view->setVisible(on);

    }
    else if ( ! on )
    {

        setSelectionBehavior(QAbstractItemView::SelectRows);

        setEditTriggers(QAbstractItemView::NoEditTriggers);

        if(act_view != 0)
            tlbx->ui->btn_view->setVisible(true);
    }


    if(act_DeleteRow != 0)
        tlbx->ui->btn_delete->setEnabled(on);

    if(act_CopyRow != 0)
        tlbx->ui->btn_copy->setEnabled(on);

    if(act_EditRow != 0)
        tlbx->ui->btn_edit->setEnabled(on);

    if(act_InsertRow != 0)
        tlbx->ui->btn_insert->setEnabled(on);

    //  view->repaint();
}

void PblTableView::slot_editStrategyChanged(QSqlTableModel::EditStrategy newStrategy)
{
    qDebug() << "editStrategy" << mdl->editStrategy();

    if(mdl->editStrategy() == newStrategy)
        return;

    if(mdl->isDirtyRow != -1)
        mdl->submitAll();

    if(newStrategy >=0 && newStrategy < tlbx->ui->cmb_Strategy->count())
        tlbx->ui->cmb_Strategy->setCurrentIndex(newStrategy);
}


void PblTableView::initStrategy(QSqlTableModel::EditStrategy strat)
{
    tlbx->ui->cmb_Strategy->setCurrentIndex( strat);

    // _CONNECT_ have to be after setCurrentIndex

    _CONNECT_(tlbx->ui->cmb_Strategy , SIGNAL(currentIndexChanged(int)),
              this, SLOT(slot_editStrategyClicked(int)));
}

void PblTableView::slot_editStrategyClicked(int newStrategy)
{
    if(mdl->editStrategy() == newStrategy)
        return;

    if(newStrategy < QSqlTableModel::OnFieldChange || newStrategy >QSqlTableModel::OnManualSubmit )
    {
        QMessageBox::warning(this,
                             mySql::error_,
                             tr("You are trying to set wrong edit strategy number %1").
                             arg(newStrategy));
        return;
    }

    mdl->setEditStrategy( ( QSqlTableModel::EditStrategy ) newStrategy);

}

void PblTableView::commitData(QWidget *editor)
{
    qDebug() << "PblTableView::commitData";

    QTableView::commitData(editor);
}

void PblTableView::updateEditorData()
{
    qDebug() << "PblTableView::updateEditorData";

    QTableView::updateEditorData();
}


void PblTableView::updateEditorGeometries()
{
    qDebug() << "PblTableView::updateEditorGeometries";

    QTableView::updateEditorGeometries();

}

void PblTableView::updateGeometries()
{
    qDebug() << "PblTableView::updateGeometries";

    QTableView::updateGeometries();

}

void PblTableView::editorDestroyed(QObject *editor)
{
    qDebug() << "PblTableView::editorDestroyed";

    QTableView::editorDestroyed(editor);

}

void PblTableView::closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint)
{
    qDebug() << "PblTableView::closeEditor";

    QTableView::closeEditor(editor , hint);
}

void PblTableView::verticalScrollbarAction(int action)
{
    qDebug() << "PblTableView::verticalScrollbarAction";

    QTableView::verticalScrollbarAction(action);
}

void PblTableView::horizontalScrollbarAction(int action)
{
    qDebug() << "PblTableView::horizontalScrollbarAction";

    QTableView::horizontalScrollbarAction(action);
}

void PblTableView::verticalScrollbarValueChanged(int value)
{
    qDebug() << "PblTableView::verticalScrollbarValueChanged";

    QTableView::verticalScrollbarValueChanged(value);
}

void PblTableView::horizontalScrollbarValueChanged(int value)
{
    qDebug() << "PblTableView::horizontalScrollbarValueChanged";

    QTableView::horizontalScrollbarValueChanged(value);
}

void PblTableView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    qDebug() << "PblTableView::selectionChanged";

    QTableView::selectionChanged(selected , deselected);
}


void PblTableView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    qDebug() << "PblTableView::currentChanged";

    QTableView::currentChanged(current , previous);
}


void PblTableView::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
    qDebug() << "PblTableView::rowsAboutToBeRemoved";

    int priCol = mdl->getPriColumn();

    for( int row = start; row <= end; row++ )
    {
        bool ok = false;

        int id = mdl->data(mdl->index( row, priCol)).toInt(&ok);

        if(! ok )
            continue;

        /*if( id == mdl->lastDirtyRowId)
        {
            qDebug() << "   found " <<id;
            isPriIdRowFound = row;
            break;
        }
        else*/
        qDebug() << "   row id " << id;// << " <> " << mdl->lastDirtyRowId;
    }

}

void PblTableView::rowsInserted(const QModelIndex &parent, int start, int end)
{

    qDebug() << "PblTableView::rowsInserted start/end " << start << end;

    int isPriIdRowFound = -1;
    int isRowFound = -1;

    QTableView::rowsInserted( parent , start, end);

    // start and end are line numbers

    if(mdl->lastDirtyRowId != -1)
    {
        int priCol = mdl->getPriColumn();

        for( int row = start; row <= end; row++ )
        {
            bool ok = false;

            int id = mdl->data( mdl->index( row, priCol)).toInt(&ok);

            if(! ok )
                continue;

            if( id == mdl->lastDirtyRowId)
            {
                isPriIdRowFound = id;
                isRowFound = row;

                qDebug() << "   row is found  isPriIdRowFound " << id << "  isRowFound " << isRowFound;

                break;
            }
            else
                qDebug() << "   row id " << id << " <> " << mdl->lastDirtyRowId;
        }
    }


    if(isPriIdRowFound >= 0)
    {
        // set position to last before select query
        int col =0;
        if(mdl->lastDirtyCol != -1)
            col = mdl->lastDirtyCol;

        setCurrentIndex( mdl->index( isRowFound , col));
        mdl->isSelectedLine = isRowFound;

        qDebug() << "   setCurrentIndex row id " << isPriIdRowFound << "  row " << isRowFound << " lastDirtyCol "<< mdl->lastDirtyCol << " isSelectedLine " <<mdl->isSelectedLine;
        //
    }
}

void PblTableView::slot_cmb_Strategy_currentIndexChanged(int index)
{
    QSqlTableModel::EditStrategy strat = mdl->editStrategy();

    if(strat != index)
        mdl->setEditStrategy((QSqlTableModel::EditStrategy)index);

    mdl->submitAll();

    if(index == QSqlTableModel::OnFieldChange)
    {
        tlbx->ui->btn_submitAll->setText(PblTableView::s_submit);
        tlbx->ui->btn_submitAll->setEnabled(false);
    }
    else if(index == QSqlTableModel::OnRowChange)
    {
        tlbx->ui->btn_submitAll->setText(PblTableView::s_submit);
        tlbx->ui->btn_submitAll->setEnabled(false);
    }
    else if(index == QSqlTableModel::OnManualSubmit)
    {
        tlbx->ui->btn_submitAll->setText(PblTableView::s_submitAll);
        tlbx->ui->btn_submitAll->setEnabled(false);
    }

}


void PblTableView::reset()
{
    qDebug() << "PblTableView::reset() mdl->lastDirtyRowId " << mdl->lastDirtyRowId << mdl->tableName();

    QTableView::reset();

    if(mdl->lastDirtyRowId != -1)
    {
        qDebug() << "   go to last row";
    }
}

void PblTableView::slot_showSubmitBtn(bool enabled)
{
    if( tlbx->ui->cmb_Strategy->currentIndex() == QSqlTableModel::OnManualSubmit )

        tlbx->ui->btn_submitAll->setText(PblTableView::s_submitAll);

    else

        tlbx->ui->btn_submitAll->setText(PblTableView::s_submit);

    tlbx->ui->btn_submitAll->setEnabled(enabled);

}

void PblTableView::slot_rowIsDirty(int row)
{
    qDebug() << "   slot_rowIsDirty " << row;

    setCurrentIndex(mdl->index( row , mdl->lastDirtyCol));


}
