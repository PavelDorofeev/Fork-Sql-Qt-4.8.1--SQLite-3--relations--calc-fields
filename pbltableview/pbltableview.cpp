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


PblTableView::PblTableView(
        QWidget *parent,
        bool editable_,
        bool selectable_)

    :

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
      selectable(selectable_),
      editable( editable_),
      act_switch_editable(0)
{

    setSelectionMode(QAbstractItemView::SingleSelection);


    // ----------------------------------------------------
    //              context menu
    // ----------------------------------------------------

    contextMenu = new QMenu(this);


    _CONNECT_(this, SIGNAL(customContextMenuRequested(const QPoint &)),
              this, SLOT(slot_CustomMenuRequested(const QPoint &)));

    setContextMenuPolicy(Qt::CustomContextMenu);


    tlbx = new Btn_ToolBox(this );

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


    find_settings.caseSensitive = false;
    find_settings.exactly = false;


    setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);

    verticalHeader()->setVisible(false);



    _CONNECT_( this , SIGNAL(doubleClicked(QModelIndex)),
               this , SLOT(slot_doubleClicked(QModelIndex)));

    setSortingEnabled(false);


    //------------------------------------------------------------

    act_switch_editable = new QAction( trUtf8("show chk editable"),
                                       this);


    _CONNECT_(act_switch_editable, SIGNAL(triggered(bool)),
              this, SLOT(slot_setEditEnabled(bool)));

    _CONNECT_(tlbx->ui->chk_editable, SIGNAL(clicked(bool)),
              act_switch_editable, SIGNAL(triggered(bool)));

    //------------------------------------------------------------

    if( editable)
    {
        //set_Actions(PblTableView::ACT_SWITCH_EDIT_ENABLED , true);
        set_Actions(PblTableView::ACT_ALL_EDIT, true);

        tlbx->ui->chk_editable->setVisible(true);
        tlbx->ui->chk_editable->setEnabled(true);
        tlbx->ui->chk_editable->setChecked(true); // slot_setEditable


        // if selectable & editable that is default chk_editable is  off

        if( selectable )
        {

            slot_setEditEnabled( false );

            tlbx->ui->chk_editable->setChecked(false); // slot_setEditable
        }

        else if( !selectable )

            slot_setEditEnabled( true );
    }
    else
    {
        slot_setEditEnabled( false );

        tlbx->ui->chk_editable->setVisible(true);
        tlbx->ui->chk_editable->setEnabled(false);
        tlbx->ui->chk_editable->setChecked(false); // slot_setEditable
    }



    //slot_setMouseBehavior( selectable );

}

PblTableView::~PblTableView()
{
    //qDebug() << "~PblTableView()";

}

void PblTableView::setModel(PblSqlRelationalTableModel *newMdl)
{

    if( model() !=0 )
    {
        _DISCONNECT_(model(), SIGNAL(sig_editStrategyChanged(QSqlTableModel::EditStrategy)),
                     this, SLOT(slot_editStrategyChanged(QSqlTableModel::EditStrategy)));

        _DISCONNECT_(model(), SIGNAL(sig_rowIsDirty(int)),
                     this, SLOT(slot_rowIsDirty(int)));

        _DISCONNECT_(model(), SIGNAL(sig_afterSelect( bool)),
                     this, SLOT(slot_afterSelect( bool )));

        _DISCONNECT_(tlbx->ui->cmb_Strategy, SIGNAL(currentIndexChanged(int)),
                     this , SLOT(slot_cmb_Strategy_currentIndexChanged(int)));

    }

    QTableView::setModel(newMdl);

    //mdl = qobject_cast<PblSqlRelationalTableModel*>( QTableView::model() ); // QAbstractItemModel *

    if( ! qobject_cast<PblSqlRelationalTableModel*>( QTableView::model() ))
    {
        QMessageBox::warning( this ,
                              mySql::error_,
                              tr("cast object error (43563565)"));
        return;
    }


    _CONNECT_(newMdl , SIGNAL(sig_editStrategyChanged(QSqlTableModel::EditStrategy)),
              this, SLOT(slot_editStrategyChanged(QSqlTableModel::EditStrategy)));

    _CONNECT_(newMdl, SIGNAL(sig_rowIsDirty(int)),
              this, SLOT(slot_rowIsDirty(int)));

    _CONNECT_(newMdl, SIGNAL(sig_afterSelect( bool)),
              this, SLOT(slot_afterSelect( bool )));

    _CONNECT_(tlbx->ui->cmb_Strategy, SIGNAL(currentIndexChanged(int)),
              this , SLOT(slot_cmb_Strategy_currentIndexChanged(int)));


    tlbx->ui->cmb_Strategy->setCurrentIndex(newMdl->editStrategy());

    qDebug() << "newMdl->editStrategy() "<<newMdl->editStrategy();


    qDebug() << "PblTableView headerData : " << model()->headerData(0 , Qt::Horizontal, Qt::BackgroundRole);


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

    for(int col = 0; col < model()->baseRecord().count(); col++)
    {
        // after select only

        int relIdCol = model()->getRelIdColumn(col);

        if( relIdCol >=0)
        {
            PblColumn::COLUMN_TYPE type = model()->getRelationInfoForColumn(col).type; //??

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


        if( col < model()->record().count() )
        {

            if( model()->getRelIdColumn(col)>0 )
            {
                QString str= model()->data(model()->index(row,col)).toString();

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

            if(col < model()->baseRecord().count())
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



    return vrt_clearField(currIdx);

}

bool PblTableView::vrt_clearField(const QModelIndex &currIdx)
{
    int col=currIdx.column();

    int row=currIdx.row();

    //qDebug() << QString("PblTableView::slot_clearField   index [%1x%2]").arg(currIdx.row()).arg(currIdx.column());

    if(! currIdx.isValid())
    {
        return false;
    }

    QModelIndex idx = model()->index(currIdx.row(),currIdx.column());

    if( ! idx.isValid())
    {
        qCritical()<<"!!!! error  PblTableView::slot_clearField ! idx.isValid()";
        return false;
    }


    bool resSetData=false;

    if ( model()->isRelationalColumn( col ) == PblColumn::COLUMN_TYPE_RELATION_TEXT)
    {
        int extCol = model()->getRelIdColumn(col);

        QModelIndex exIdx = model()->index( row, extCol);

        resSetData = model()->setData(exIdx , 0 );

        if(currIdx.isValid()) // submit/select
            resSetData = model()->setData(currIdx ,"");


    }
    else
    {
        QVariant def;

        if(model()->defaultVal.contains( col))
            def = model()->defaultVal.value( col);

        resSetData = model()->setData(currIdx , def);

    }

    return resSetData;
}


//-------------------------------------------------

bool PblTableView::vrt_insertRow(int srcRow)
{
    //qDebug() << "PblTableView::insertRow()";

    model()->submit(); // forever first call submit, result is not important


    int newRow = model()->rowCount();// forever insert at end

    if( ! model()->insertRow(newRow))
    {
        qCritical() << "PblTableView::insertRow ???? " ;
        return false;
    }

    model()->isInsertRow = newRow;

    setCurrentIndex( model()->index( newRow , 0 ) );

    emit sig_showSubmitBtn( true);

    return true;
}

bool PblTableView::slot_insertRowBtnClick()
{
    int row = 0;

    if( currentIndex().isValid())
        row = currentIndex().row();

    return vrt_insertRow(row);
}



//-------------------------------------------------

bool PblTableView::vrt_viewRow(int row)
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


    emit sig_viewRow(currentIndex().row());
}

//-------------------------------------------------

int PblTableView::restoreCurrentRowPositionAfterSubmit(int srcRow)
{
    QModelIndex priIdx = model()->index( srcRow , model()->getPriColumn());

    if(priIdx.isValid())
    {
        bool ok = false;

        int id = model()->data(priIdx).toInt(&ok);

        if( ! ok)
            return -1;

        int foundRow = model()->findRowById( id );

        if ( foundRow != -1)
        {
            return foundRow;
        }
    }

    return -1;
}

//-------------------------------------------------

bool PblTableView::vrt_editRowDlg(int row)
{
    QMessageBox::warning(this,
                         mySql::error_,
                         tr("You should realize this code yourself")
                         );

    return true;
}

bool PblTableView::slot_editRowBtnClick()
{

    if(! currentIndex().isValid())
    {
        QMessageBox::warning(this ,
                             mySql::warning ,
                             tr("before editing a line you should select it\ntable '%1'\nerror:%2").
                             arg(model()->tableName()).
                             arg(model()->lastError().text()));
        return false;
    }

    int row = currentIndex().row();

    return vrt_editRowDlg( row);

    //emit sig_editRow(currentIndex().row());

}
//------------------------------------------

bool PblTableView::vrt_copyRow(int srcRow)
{

    int id = model()->getRowPriValue( srcRow );

    if ( model()->submit() && id >=0)
    {
        srcRow = model()->findRowById(id);

        if(srcRow == -1)
        {
            QMessageBox::warning(this ,
                                 mySql::error_ ,
                                 tr("copying row,\nneeds submit, after submit lost row focus,\ntable %1, error: %2").
                                 arg(model()->tableName()).
                                 arg(model()->lastError().text()));
            return false;
        }
    }

    int newRow = model()->rowCount();

    QSqlRecord src = model()->record(srcRow);

    bool bb = model()->insertRow( newRow );

    if( ! bb )
    {
        qCritical() << "PblTableView::copyRow  insertRow ERROR : " << model()->lastError();
        return false;
    }


    bool bbb = model()->setRecord_withoutPriCol( newRow , src, PblSqlRelationalTableModel::INSERT );

    if(model()->editStrategy() == QSqlTableModel::OnManualSubmit)
    {
        emit sig_showSubmitBtn( true);
    }

    model()->submit();

    return true;
}


// ---------------------------------------------------

bool PblTableView::slot_copyRowBtnClick()
{
    int row = currentIndex().row();

    if(! currentIndex().isValid())
    {
        QMessageBox::warning(this ,
                             mySql::warning ,
                             tr("before copying a line you should select it\ntable '%1'\nerror:%2").
                             arg(model()->tableName()).
                             arg(model()->lastError().text()));
        return false;
    }

    bool bbb= vrt_copyRow(row);

    return bbb;
}
//-------------------------------------------------

bool PblTableView::vrt_removeRow(int row)
{
    qDebug() << "PblTableView::removeRow : " << row << " rowCount() " << model()->rowCount();

    if( model()->isInsertRow != -1) //
    {
        bool bb = model()->removeRow(model()->isInsertRow);

        if( ! bb )
        {

            QMessageBox::warning(this ,
                                 mySql::warning ,
                                 tr("before removing a line you should submit dirty row %2 (id : %3)\ntable '%1'\nerror:%4").
                                 arg(model()->tableName()).
                                 arg(model()->isInsertRow).
                                 arg(model()->getRelIdColumn(model()->isInsertRow)).
                                 arg(model()->lastError().text()));
            return false;
        }
        model()->isInsertRow = -1;

    }

    if(row >= model()->rowCount() || row < 0)
        return false;

    bool bb = model()->removeRow(row);

    if(bb)
    {
        int col = config::get_defaultColumn(model());

        QModelIndex idx = model()->index(row , col);

        if(row < model()->rowCount())
            if( idx.isValid())
                setCurrentIndex(idx );
    }

    return bb;

}

bool PblTableView::slot_removeRowBtnClick()
{
    int row = currentIndex().row();

    bool bbb = vrt_removeRow(row);

    if( bbb)
    {
        slot_showSubmitBtn( true);

        //adjustSize();
    }

    return bbb;
}
//-------------------------------------------------

/*void PblTableView::set_chkEditable_isVisible(bool editOn)
{
    tlbx->ui->chk_editable->setEnabled( editOn );


    //PblTableView::ACTION act = PblTableView::ACT_SWITCH_EDIT_ENABLED;

    //set_Actions(act , editOn);


    //slot_setEditable(editOn);

    // just in case
    //tlbx->ui->chk_editable->setVisible(true);

    //tlbx->ui->chk_editable->setEnabled(editOn);
}*/

//-------------------------------------------------

void PblTableView::setSelectAndClose()
{
    selectAndClose = true;

}


bool PblTableView::vrt_doubleClicked(const QModelIndex & idx)
{
    //qDebug() << "vrt_doubleClicked" << model()->tableName();

    /*if(selectable &&  ! tlbx->ui->chk_editable->isChecked())
    {
        act_selectAndClose->trigger();

        return true;
    }*/

    int col = idx.column();
    int row = idx.row();

    if( ! editable )
    {
        if( selectable) //selecting row and close dlg

            emit act_selectAndClose->trigger();

        else    // only view row

            vrt_viewRow( row);

        return false;
    }
    else if( editable )
    {
        if( selectable && ! tlbx->ui->chk_editable->isChecked())
            //selecting row and close dlg
        {
            emit act_selectAndClose->trigger();

            return false;
        }
        else if( ! selectable && ! tlbx->ui->chk_editable->isChecked())
        {
            vrt_viewRow( row);

            return false;
        }

    }

    // edit row through line

    if(model()->isRelationalColumn( col) ) // relations
    {
        PblColumn inf = model()->getRelationInfoForColumn(col);

        if( ! inf.isValid())
            return false;

        PblTableDlg dlg ( inf.ext_table , model()->database(), this, true , true );

        //dlg.view->set_chkEditable_isVisible(false);

        dlg.exec();

        if(dlg.result() == QDialog::Rejected)
            return false;

        // save id just in case

        int idCurrRow = model()->getRowPriValue( row );

        if(dlg.chosenRec == QSqlRecord())
        {
            QMessageBox::critical(this ,
                                  mySql::error_ ,
                                  tr("the choice is not defined"));
            return false;
        }

        QVariant txt = dlg.chosenRec.value(inf.destField);


        if(dlg.chosenId == -1)
        {
            QMessageBox::critical(this , "error" , tr("the choise is not defined"));
            return false;
        }

        int id = model()->getRowPriValue( row );

        if(! idx.isValid()) // submit
        {
            qDebug() << " model()->editStrategy() " << model()->editStrategy();
        }

        QModelIndex exIdx = model()->index(row, model()->getRelIdColumn(col));

        if( model()->editStrategy() <= QSqlTableModel::OnRowChange)
        {
            // will be submit/select

            if( ! model()->setData( exIdx , dlg.chosenId ,Qt::EditRole))
            {
                QMessageBox::critical(this ,
                                      "error" ,
                                      tr(
                                          "setData returns  false\n"\
                                          "field : '%1'\n"\
                                          "value : '%2'\n"\
                                          "sql error: %3").
                                      arg(model()->record().fieldName(exIdx.column())).
                                      arg(dlg.chosenId).
                                      arg(model()->lastError().text())
                                      );
                return false;
            }

            if( ! exIdx.isValid()) // submit occure, it is OK, nothing more
            {
                ;//return true;
            }

            else if( ! idx.isValid()) // submit occure, it is OK
            {
                ;//return true;
            }
            else
            {

                // it does't matter what value we write to idx bacause of will be set value from extCol and after submit/select
                QVariant anyVal;

                if( ! model()->setData( idx , anyVal ,Qt::EditRole))
                {
                    QMessageBox::critical(this ,
                                          "error" ,
                                          tr(
                                              "setData returns  false\n"\
                                              "field : '%1'\n"\
                                              "value : '%2'\n"\
                                              "sql error: %3").
                                          arg(model()->record().fieldName(exIdx.column())).
                                          arg(dlg.chosenId).
                                          arg(model()->lastError().text())
                                          );
                    return false;
                }

                if( model()->editStrategy() <= QSqlTableModel::OnRowChange)
                    model()->submit(); // ENTER
                // i.e. When we set relational field then we call forever a submit/select chain
            }

        }

        else if ( model()->editStrategy() == QSqlTableModel::OnManualSubmit)
        {
            if( ! model()->setData( exIdx , dlg.chosenId ,Qt::EditRole))
            {
                QMessageBox::critical(this ,
                                      "error" ,
                                      tr(
                                          "setData returns  false\n"\
                                          "field : '%1'\n"\
                                          "value : '%2'\n"\
                                          "sql error: %3").
                                      arg(model()->record().fieldName(exIdx.column())).
                                      arg(dlg.chosenId).
                                      arg(model()->lastError().text())
                                      );
                return false;
            }

            if(! exIdx.isValid()) // submit  - Why?
            {
                qDebug() << " model()->editStrategy() " << model()->editStrategy();
            }

            if( ! idx.isValid()) // submit occure
            {
                if( model()->editStrategy() == QSqlTableModel::OnFieldChange) // it is ok
                    ;

                //qDebug() << " model()->editStrategy() " << model()->editStrategy();

                //return true;
            }
            else
            {
                if( ! model()->setData(idx , txt.toString() ,Qt::EditRole))
                {
                    QMessageBox::critical(this ,
                                          "error" ,
                                          tr("setData returns  false\n"\
                                             "field : '%1'\n"\
                                             "value : '%2'\n"\
                                             "sql error: %3").
                                          arg(model()->record().fieldName(idx.column())).
                                          arg(txt.toString()).
                                          arg(model()->lastError().text())
                                          );
                    return false;
                }
            }

        }

        bool bbb= vrt_afterSelectingValue(idCurrRow, col , idx, dlg.chosenRec);

        if ( ! bbb )
            return bbb;


    }
    else if(dlgts.contains(col))
    {
        if(qobject_cast<checkBox_Delegate *>(dlgts.value(col)))
        {
            checkBox_Delegate * chk = qobject_cast<checkBox_Delegate *>(dlgts.value(col));

            bool b = model()->data(idx).toBool();

            if ( ! model()->setData(idx , (int)! b) )
            {
                qCritical("error setData checkbox field");
                return false;
            }
            return true;
        }
    }

}

void PblTableView::slot_doubleClicked(const QModelIndex & index)
{
    qDebug() << "PblTableView::slot_doubleClicked";

    vrt_doubleClicked(index);

}


bool PblTableView::slot_searchInTable(QString & txt)
{

    if( find_settings.searchedField == -1) //еще не понятно по какому полю искать
    {
        QMessageBox::warning(this , "error" , "please select a field than searched in it");

        return false;
    }

    int col = find_settings.searchedField;

    QString fieldName = model()->baseRecord().fieldName(find_settings.searchedField);

    if(fieldName.isEmpty() || model()->tableName().isEmpty())
    {
        qCritical("on_ledt_filter_returnPressed error");
        return false;
    }

    if (model()->getRelIdColumn(find_settings.searchedField) >=0 )

        find_settings.seachType = Search_Settings_Dlg::FIND_SETTINGS::SEARCH_RELATION_TEXT;

    else if (model()->record().field((int)find_settings.searchedField).type() == QVariant::String )

        find_settings.seachType = Search_Settings_Dlg::FIND_SETTINGS::SEARCH_TEXT;

    else
        find_settings.seachType = Search_Settings_Dlg::FIND_SETTINGS::SEARCH_NUMBER;

    QString filter("");

    if( ! txt.isEmpty())
    {
        // Слева

        if(find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_RELATION_TEXT)
        {
            QString str = model()->getRelationInfoForColumn(find_settings.searchedField).destField;

            filter.append(QString::fromLatin1(" relTblAl_%1.%2 ").
                          arg(col).
                          arg(str));
        }
        else
        {
            filter.append(model()->tableName()+"."+fieldName);
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

    model()->setFilter(filter);

    bool selectOk = model()->select();

    if(! filter.isEmpty() )
    {
        if( ! model()->setHeaderData(col , Qt::Horizontal, getActIcon(ACT_CLEAR_SEARCH_RESULTS), Qt::DecorationRole))
            QMessageBox::critical(this , "error" , "setHeaderData return false 6575637657");

        if(selectOk)
        {
            tlbx->ui->btn_searchInTable->setVisible(true);
            tlbx->ui->btn_searchInTable->setEnabled(true);

        }
    }
    else
    {
        model()->setHeaderData(col , Qt::Horizontal, QVariant(), Qt::DecorationRole);
        if(selectOk)
        {
            tlbx->ui->btn_searchInTable->setVisible(true);
            tlbx->ui->btn_searchInTable->setEnabled(false);

        }
    }

    return selectOk;
}


bool PblTableView::prepare( PblSqlRelationalTableModel * Mdl )
{
    //qWarning() << "PblTableView::prepare Mdl " << Mdl;

    //qWarning() << " PblTableView::prepare  setModel " ;

    setModel(Mdl);

    if ( ! model()->select())
    {
        QMessageBox::warning(this,
                             mySql::error_,
                             tr("error in select query:\n\n%1\n\n\n%2").
                             arg(model()->query().lastQuery()).
                             arg(model()->lastError().text()));
        return false;
    }

    //qWarning() << " PblTableView::prepare setting_view " ;

    if ( ! config::setting_view( this ) )
    {
        QMessageBox::warning(this,
                             mySql::error_,
                             tr("error in setting_view\n table :%1").arg(model()->tableName()));
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
        //tlbx->ui->btn_insert->setEnabled(On);
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

                _CONNECT_(tlbx->ui->btn_edit, SIGNAL(clicked()), act_EditRow, SLOT( trigger() ));

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
        //tlbx->ui->btn_edit->setEnabled(On);
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
        //tlbx->ui->btn_copy->setEnabled(On);
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
        //tlbx->ui->btn_delete->setEnabled(On);
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

        _CONNECT_(this, SIGNAL(sig_showSubmitBtn( bool )),
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

    /*if(act & ACT_SWITCH_EDIT_ENABLED)
    {


    }*/

    // ----------------------------------------------------------
    //
    // ----------------------------------------------------------

    /*if(act & ACT_EDIT_ON)
    {
        //tlbx->ui->chk_editable->setVisible(visible);

        //set_chkEditable_isVisible(On);


    }*/

}


void PblTableView::slot_triggeredSelectByFieldValue(bool on)
{
    if(act_selectByFieldValue ==0)
        return;

    if( ! currentIndex().isValid())
    {
        model()->setFilter("");
        model()->select();
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
    if(col <0 || col >= model()->record().count())
    {
        QMessageBox::warning(this , mySql::error_ , tr("column is out of range , field : %1").arg(col));
        return;
    }

    if(dlgts.contains(col))
    {
        QMessageBox::warning(this , mySql::error_ , tr("second attempting adding QCheckBox to field : %1").arg(col));
        return;
    }


    dlgts.insert( col, new checkBox_Delegate(model() , this) );

    QStyledItemDelegate * cmbDeleg = dlgts.value(col);

    setItemDelegateForColumn(col, cmbDeleg);
}

void PblTableView::setComboBoxDelegate(int col, QStringList &lst)
{
    if(col <0 || col>=model()->record().count())
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
                      model() ,
                      col,
                      lst,
                      this)
                  );

    QStyledItemDelegate * cmbDeleg = dlgts.value(col);

    setItemDelegateForColumn(col, cmbDeleg);

    model()->defaultVal.insert( col , -1);

}

void PblTableView::setDateTimeDelegate(int col)
{
    if(col <0 || col>=model()->record().count())
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

            QVariant val = model()->data(idx);

            QString fieldName = model()->baseRecord().field(col).name();

            if(fieldName.isEmpty() || model()->tableName().isEmpty())
            {
                qCritical() <<"error : fieldName is empty, i.e. is not detected";
                return false;
            }

            if(model()->getRelIdColumn(col) >=0 ) // relation
            {
                QModelIndex exIdx = model()->index(row , model()->getRelIdColumn(col));

                val = model()->data(exIdx);

                if(val.isNull())
                    val=(int)0;
            }

            QString strVal;

            if(val.type() == QVariant::String)
                strVal = val.toString().prepend("'").append("'");
            else
                strVal = val.toString();

            filter.append(QString::fromLatin1(" %1.%2=%3 ").
                          arg(model()->tableName()).
                          arg(fieldName).
                          arg(strVal));
        }

    }

    model()->setFilter(filter);

    bool bb = model()->select();

    return bb;
}


PblSqlRelationalTableModel* PblTableView::model() const
{
    /*PblSqlRelationalTableModel * mdl = qobject_cast<PblSqlRelationalTableModel*>(QTableView::model());


    if( ! mdl )
    {
        QMessageBox::warning( 0,
                              mySql::error_,
                              tr("qobject_cast PblSqlRelationalTableModel* wrong (5746)"),
                              "");
        return 0;

        sometimes occures  mdl == 0
    }*/

    return qobject_cast<PblSqlRelationalTableModel*>(QTableView::model());
}

void PblTableView::slot_setMouseBehavior(bool editOn)
{

    if( editOn)
    {
        setSelectionBehavior(QAbstractItemView::SelectItems);

        setEditTriggers(QAbstractItemView::DoubleClicked
                        |QAbstractItemView::AnyKeyPressed); //EditKeyPressed);//AllEditTriggers);

    }
    else if ( ! editOn )
    {

        setSelectionBehavior(QAbstractItemView::SelectRows);

        setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

}

void PblTableView::slot_setEditEnabled(bool editOn)
{

    if(editOn)
    {
        if(act_DeleteRow != 0)
            tlbx->ui->btn_delete->setVisible(editOn);

        if(act_CopyRow != 0)
            tlbx->ui->btn_copy->setVisible(editOn);

        if(act_EditRow != 0)
            tlbx->ui->btn_edit->setVisible(editOn);

        if(act_InsertRow != 0)
            tlbx->ui->btn_insert->setVisible(editOn);

        if(act_view != 0)
            tlbx->ui->btn_view->setVisible(editOn);

    }
    else if ( ! editOn )
    {

        if(act_view != 0)
            tlbx->ui->btn_view->setVisible(true);
    }


    if(act_DeleteRow != 0)
        tlbx->ui->btn_delete->setEnabled(editOn);

    if(act_CopyRow != 0)
        tlbx->ui->btn_copy->setEnabled(editOn);

    if(act_EditRow != 0)
        tlbx->ui->btn_edit->setEnabled(editOn);

    if(act_InsertRow != 0)
        tlbx->ui->btn_insert->setEnabled(editOn);

    slot_setMouseBehavior( editOn);

}

void PblTableView::slot_editStrategyChanged(QSqlTableModel::EditStrategy newStrategy)
{
    qDebug() << "PblTableView::slot_editStrategyChanged " << model()->editStrategy() << " newStrategy " << newStrategy;

    /*if( model()->editStrategy() == newStrategy )
        return;*/

    //setModel(model());
    //model()->select()
    //reset();


    qDebug() << "PblTableView::slot_editStrategyChanged model()->editStrategy" << model()->editStrategy();


}


void PblTableView::commitData(QWidget *editor)
{
    qDebug() << "PblTableView::commitData";

    QTableView::commitData(editor);
}

void PblTableView::updateEditorData()
{
    //qDebug() << "PblTableView::updateEditorData";

    QTableView::updateEditorData();
}


void PblTableView::updateEditorGeometries()
{
    //qDebug() << "PblTableView::updateEditorGeometries";

    QTableView::updateEditorGeometries();

}

void PblTableView::updateGeometries()
{
    //qDebug() << "PblTableView::updateGeometries";

    QTableView::updateGeometries();

}

void PblTableView::editorDestroyed(QObject *editor)
{
    //qDebug() << "PblTableView::editorDestroyed";

    QTableView::editorDestroyed(editor);

}

void PblTableView::closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint)
{
    //qDebug() << "PblTableView::closeEditor";

    QTableView::closeEditor(editor , hint);
}

void PblTableView::verticalScrollbarAction(int action)
{
    //qDebug() << "PblTableView::verticalScrollbarAction";

    QTableView::verticalScrollbarAction(action);
}

void PblTableView::horizontalScrollbarAction(int action)
{
    //qDebug() << "PblTableView::horizontalScrollbarAction";

    QTableView::horizontalScrollbarAction(action);
}

void PblTableView::verticalScrollbarValueChanged(int value)
{
    //qDebug() << "PblTableView::verticalScrollbarValueChanged";

    QTableView::verticalScrollbarValueChanged(value);
}

void PblTableView::horizontalScrollbarValueChanged(int value)
{
    //qDebug() << "PblTableView::horizontalScrollbarValueChanged";

    QTableView::horizontalScrollbarValueChanged(value);
}

void PblTableView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    //qDebug() << "PblTableView::selectionChanged";

    QTableView::selectionChanged(selected , deselected);
}


void PblTableView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    //qDebug() << "PblTableView::currentChanged";

    QTableView::currentChanged(current , previous);
}


void PblTableView::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
    //qDebug() << "PblTableView::rowsAboutToBeRemoved";

    int priCol = model()->getPriColumn();

    for( int row = start; row <= end; row++ )
    {
        bool ok = false;

        int id = model()->data(model()->index( row, priCol)).toInt(&ok);

        if(! ok )
            continue;

        //qDebug() << "   row id " << id;// << " <> " << model()->lastDirtyRowId;
    }

}

void PblTableView::rowsInserted(const QModelIndex &parent, int start, int end)
{

    qDebug() << "PblTableView::rowsInserted start/end " << start << end;

    int isPriIdRowFound = -1;
    int isRowFound = -1;

    QTableView::rowsInserted( parent , start, end);

    // start and end are line numbers

    if(model()->lastDirtyRowId != -1)
    {
        int priCol = model()->getPriColumn();

        for( int row = start; row <= end; row++ )
        {
            bool ok = false;

            int id = model()->data( model()->index( row, priCol)).toInt(&ok);

            if(! ok )
                continue;

            if( id == model()->lastDirtyRowId)
            {
                isPriIdRowFound = id;
                isRowFound = row;

                qDebug() << "restore last row position that was before submit/select,    id " << id << "  row is found " << isRowFound;

                break;
            }

        }
    }


    if(isPriIdRowFound >= 0)
    {
        // set position to last before select query
        int col =0;
        if(model()->lastDirtyCol != -1)
            col = model()->lastDirtyCol;

        setCurrentIndex( model()->index( isRowFound , col));
        model()->isSelectedLine = isRowFound;

        qDebug() << "   setCurrentIndex row id " << isPriIdRowFound << "  row " << isRowFound << " lastDirtyCol "<< model()->lastDirtyCol << " isSelectedLine " <<model()->isSelectedLine;
        //
    }
}

void PblTableView::slot_cmb_Strategy_currentIndexChanged(int newStrategy)
{
    QSqlTableModel::EditStrategy strat = model()->editStrategy();

    if(newStrategy != model()->editStrategy())
    {
        model()->submitAll();

        model()->setEditStrategy((QSqlTableModel::EditStrategy)newStrategy);
    }

    if(newStrategy != model()->editStrategy())
    {
        QMessageBox::warning( this ,
                              mySql::error_,
                              tr("editStrategy dont settable"));
        //return;
    }

    qDebug() << "slot_cmb_Strategy_currentIndexChanged model() " << model() << "editStrategy " <<model()->editStrategy() << model()->tableName();

    if(model()->editStrategy() == QSqlTableModel::OnFieldChange)
    {
        tlbx->ui->btn_submitAll->setText(PblTableView::s_submit);
        tlbx->ui->btn_submitAll->setEnabled(false);
    }
    else if(model()->editStrategy() == QSqlTableModel::OnRowChange)
    {
        tlbx->ui->btn_submitAll->setText(PblTableView::s_submit);
        tlbx->ui->btn_submitAll->setEnabled(false);
    }
    else if(model()->editStrategy() == QSqlTableModel::OnManualSubmit)
    {
        tlbx->ui->btn_submitAll->setText(PblTableView::s_submitAll);
        tlbx->ui->btn_submitAll->setEnabled(false);
    }

}


void PblTableView::reset()
{
    //qDebug() << "PblTableView::reset() model()->lastDirtyRowId " << model()->lastDirtyRowId << model()->tableName();

    QTableView::reset();

    // mdl maybe not init here
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
    //qDebug() << "   slot_rowIsDirty " << row;

    setCurrentIndex(model()->index( row , model()->lastDirtyCol));


}

bool PblTableView::vrt_afterSelectingValue(int idRow,
                                           int col,
                                           const QModelIndex & idx,
                                           const QSqlRecord &rec)
{
    qDebug() << "PblTableView::vrt_afterSelectingValue";
    return true;
}

void PblTableView::slot_afterSelect( bool ok)
{
    if( ok)
        emit sig_showSubmitBtn( false);
}

void PblTableView::setToLayout(QVBoxLayout * lo)
{
    lo->addWidget(tlbx);
    lo->addWidget(this);
}
