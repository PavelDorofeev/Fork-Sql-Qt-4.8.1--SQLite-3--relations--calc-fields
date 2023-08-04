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
#include <QPainter>
#include <QPaintEvent>
#include "pbltableview/my_sql.h"
#include "pbltableview/combobox_delegate.h"
#include "config.h"
//#include "pbltableview/pblrelcolumn.h"
#include "pbltableview/checkbox_delegate.h"
#include "pbltableview/defaultstyleditemdelegate.h"
#include "pbltableview/pblsqlrelationaltablemodel.h"

#include "pbltableview/pblheaderview.h"
#include "pbltableview/pbl.h"
#include "ui_btn_toolbox.h"
#include "date_delegate.h"
#include "horizontal_header.h"
#include "pblsubaccnt.h"

const QString PblTableView::s_submit= QObject::tr("submit");
const QString PblTableView::s_submitAll= QObject::tr("submit All");
int   PblTableView::margin_hor = 0;



PblTableView::PblTableView(
        QWidget *parent,
        cb_setting_mdl pMdl,
        cb_setting_view pView,
        const bool Selectable)

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
      act_selectAndClose(0),
      dblDlg(0),
      selectAndClose(0),
      selectable(Selectable),
      //editable( false), //
      contextMenuEnabled(false),
      search_wgts_visible(false),
      showRelExColumns(false),
      changeEditStrategyEnable(false),
      hideEditBtns(true),
      p_cb_setting_view(pView),
      p_cb_setting_mdl(pMdl),
      mdl(0)

{

    setSelectionMode(QAbstractItemView::SingleSelection);


    setAttribute(Qt::WA_PaintOutsidePaintEvent, true);

    // ----------------------------------------------------
    //              context menu
    // ----------------------------------------------------

    contextMenu = new QMenu(this);

    hor = new Horizontal_Header(Qt::Horizontal , this);

    setHorizontalHeader(hor);

    _CONNECT_(hor, SIGNAL(sig_needsReselect(QList<int>)),
              this, SLOT(slot_needsReselect(QList<int>)));

    horizontalHeader()->setDragEnabled(true);
    horizontalHeader()->setAcceptDrops(true);
    horizontalHeader()->setDragDropMode(QAbstractItemView::DragDrop );


    _CONNECT_(this, SIGNAL(customContextMenuRequested(const QPoint &)),
              this, SLOT(slot_CustomMenuRequested(const QPoint &)));

    setContextMenuPolicy(Qt::CustomContextMenu);

    mainVl = new QVBoxLayout(this);

    tlbx = new Btn_ToolBox(this );

    tlbx->ui->chk_editable->setChecked(false);

    tlbx->ui->btn_insert->setVisible(false);
    tlbx->ui->btn_copy->setVisible(false);
    tlbx->ui->btn_edit->setVisible(false);
    tlbx->ui->btn_delete->setVisible(false);

    tlbx->ui->btn_view->setVisible(false);



    tlbx->ui->cmb_Strategy->setVisible(false);
    tlbx->ui->btn_submitAll->setVisible(false);
    tlbx->ui->btn_sortEnabled->setVisible(false);

    tlbx->ui->wgt_search_block->setVisible(false);
    //tlbx->ui->btn_search_settings->setVisible(false);
    //tlbx->ui->ledt_filter->setVisible(false);

    tlbx->ui->btn_selectByValue->setVisible(false);

    qDebug( ) << "width PblTableView tlbx" << this->width() << tlbx->width();

    if( tlbx->width() > this->width())
    {
        //qDebug()<< " tlbx->layoutDirection " << tlbx->layoutDirection();
        //tlbx->setLayoutDirection(Qt::RightToLeft);

    }

    verticalHeader()->setVisible(true);


    _CONNECT_( this , SIGNAL(doubleClicked(QModelIndex)),
               this , SLOT(slot_doubleClicked(QModelIndex)));

    setSortingEnabled(false);

    //------------------------------------------------------------


    tlbx->ui->chk_editable->setShortcut(Qt::Key_F2);

    _CONNECT_(tlbx->ui->chk_editable, SIGNAL(toggled(bool)),
              this, SLOT(slot_editingEnabled_clicked(bool)));

    //------------------------------------------------------------

    tlbx->ui->chk_showRelExColumns->setVisible(false); // default

    tlbx->ui->chk_showRelExColumns->setShortcut(Qt::Key_F12);

    _CONNECT_(tlbx->ui->chk_showRelExColumns, SIGNAL(toggled(bool)),
              this, SLOT(slot_setVisibleExRelIdColumns(bool)));

    //------------------------------------------------------------

    _CONNECT_(tlbx->ui->cmb_Strategy, SIGNAL(currentIndexChanged(int)),
              this, SLOT(slot_editStrategyChange_clicked(int)));



    // ----------------------------------------------------------
    //                      SEARCHING
    // ----------------------------------------------------------

    find_settings.caseSensitive = false;
    find_settings.exactly = false;



    // ----------------------------------------------------------
    //                       SELECT_AND_CLOSE
    // ----------------------------------------------------------

    act_selectAndClose = new QAction(  QIcon(":icon/img/btn-db/selection.svg"),
                                       trUtf8("select and close window"), this);

    act_selectAndClose->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Return) );

    contextMenu->addAction(act_selectAndClose);

    addAction(act_selectAndClose);

    //tlbx->setFixedHeight(100);

    mainVl->addWidget( tlbx );


    setLayout(mainVl);

    act_selectAndClose->setVisible(true);



    ////tlbx->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Maximum);

    QFont font = QApplication::font();

    QFontMetrics fm(font);

    int hh = fm.height();

    QString emH1 = QString::number(hh);

    int toolBtnSz = hh*2;

    foreach( QToolButton * tlb , findChildren<QToolButton *>() )
    {
        tlb->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));

        tlb->setFixedSize(toolBtnSz , toolBtnSz);
    }
    //setIconSize( QSize(toolBtnSz , toolBtnSz));

    //    tlbx->ui->cmb_Strategy->setMaximumHeight(toolBtnSz);
    //    tlbx->ui->btn_submitAll->setMaximumHeight(toolBtnSz);


    // Мы здесь (в контсрукторе ) еще не знаем редактирование включено или нет
    //set_behavoir( editable );

    verticalHeader()->setDefaultAlignment( Qt::AlignCenter);

    horizontalHeader()->setDefaultAlignment( Qt::AlignCenter);

    verticalHeader()->setResizeMode(QHeaderView::ResizeToContents); // влияет существенно

    horizontalHeader()->setResizeMode(QHeaderView::Interactive); // ResizeToContents не дает менять ширину


}

void PblTableView::set_tlbx_visible(bool visible)
{
    tlbx->setVisible( visible);
}

void PblTableView::set_editEnabledChkBoxVisible( bool visible)
{
    tlbx->ui->chk_editable->setVisible( visible);
}

void PblTableView::slot_needsReselect(QList<int> lst)
{
    return; //?????


    qDebug() << "lst " <<lst;
    QList<QString> lst2;

    for(int col=0; col< lst.count(); col++)
    {
        int cl = lst.at( col );

        QString fldName = model()->baseRec.fieldName( cl );

        //Q_ASSERT (fldName.isEmpty() == false);

        if ( fldName.isEmpty())
        {
            qDebug() << " baseRec " << model()->baseRec;
            qDebug() << " cl " <<cl;
        }

        lst2.append( fldName );

    }
    qDebug() << "lst2 " << lst2;

    //    horizontalHeader()->reset();

    //    horizontalHeader()->restoreState( stt);




    mdl->change_fld_list( lst2 );


    setModel( mdl );


    model()->select();

    setContentsMargins(20,20,20,20);

}

void PblTableView::set_searchingEnabled( bool On)
{
    search_wgts_visible = On;

    if( On )
    {
        // ----------------------------------------------------------
        //                       SEARCH BY TEXT
        // ----------------------------------------------------------

        if(act_search  == 0)
        {
            act_search = new QAction( QIcon(":icon/img/btn-db/search.svg"), trUtf8("search"), this);

            act_search->setShortcut(Qt::Key_F6);

            addAction(act_search);

            act_search->setVisible(On);

        }

        // ----------------------------------------------------------
        //                       SELECT_BY_FIELD_VALUE
        // ----------------------------------------------------------

        if(act_selectByFieldValue  == 0)
        {
            act_selectByFieldValue = new QAction( QIcon(":icon/img/btn-db/choice.svg"),
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
    else if ( ! On )
    {
        if(act_search  != 0)
        {
            act_search->setVisible(On);

            removeAction(act_search);

            delete act_search;

            act_search = 0;
        }

        if(act_selectByFieldValue  != 0)
        {
            _DISCONNECT_(act_selectByFieldValue, SIGNAL(triggered(bool)),
                         this, SLOT(slot_triggeredSelectByFieldValue(bool)));

            contextMenu->removeAction(act_selectByFieldValue);

            removeAction(act_selectByFieldValue);

            delete act_selectByFieldValue;

            act_selectByFieldValue = 0;
        }
    }

    tlbx->ui->wgt_search_block->setVisible(On);
    //tlbx->ui->ledt_filter->setVisible(On);

    tlbx->ui->btn_selectByValue->setVisible(On);

}
void PblTableView::slot_editStrategyChange_clicked(int strat)
{
    //qDebug()<< " PblTableView::slot_editStrategyChanged_clicked " <<strat;

    Q_ASSERT( strat >= QSqlTableModel::OnFieldChange && strat <= QSqlTableModel::OnManualSubmit);

    model()->setEditStrategy((QSqlTableModel::EditStrategy)strat);
}

void PblTableView::set_editStrategyEnable(bool On , QSqlTableModel::EditStrategy def)
{

    // ----------------------------------------------------------
    //                       EDIT STRATEGY ENABLED
    // ----------------------------------------------------------

    tlbx->ui->btn_submitAll->setVisible(On);
    tlbx->ui->cmb_Strategy->setVisible(On);

    tlbx->ui->cmb_Strategy->setCurrentIndex(def);

}

void PblTableView::set_ExtColumnsVisible(bool On , bool showExtCol_byDefault)
{

    if( On )
    {
        showRelExColumns = showExtCol_byDefault;

        // ----------------------------------------------------------
        //           SHOW_EXTENDED_RELATION_COLUMNS
        // ----------------------------------------------------------

        tlbx->ui->chk_showRelExColumns->setVisible( true );

        slot_setVisibleExRelIdColumns( showRelExColumns );

    }
    else if ( ! On )
    {
        showRelExColumns = false;

        tlbx->ui->chk_showRelExColumns->setVisible( false );

        slot_setVisibleExRelIdColumns( false );
    }


}

void PblTableView::set_sortingEnabled(bool On)
{

    tlbx->ui->btn_sortEnabled->setVisible(On);

}

void PblTableView::set_behavoir(bool editOn)
{
    // setting inertactive behavoir with combo boxes
    // this will be called from ctor and click check box (edit enable)

    set_repaintEditBtns( editOn , editOn , hideEditBtns); // On , On !!!

    set_SelectionModel( editOn );

    set_Edit_Triggers( editOn);




}

void PblTableView::slot_editingEnabled_clicked(bool editOn) // from chk box toggled
{
    QModelIndex idx =  currentIndex();

    qDebug() << " slot_editingEnabled_clicked " << editOn;

    //if( ! editOn )
    horizontalHeader()->setHighlightSections( editOn );

    model()->set_editable( editOn ); // !!!!!

    set_behavoir( editOn);

    setCurrentIndex( idx ); // repaint selections

}

void PblTableView::set_editingEnabled(bool On,
                                      bool defVisibleWithOn,
                                      bool hideBtns ) // from external code
{
    qDebug() << " set_editingEnabled " << On << defVisibleWithOn << hideBtns;

    //editable = On;
    defaultEditOn = defVisibleWithOn;
    hideEditBtns = hideBtns;


    if( On && defVisibleWithOn)

        tlbx->ui->chk_editable->setChecked( true ); // !!!!

    else

        tlbx->ui->chk_editable->setChecked( false ); // !!!!


    model()->set_editable( On ); // !!!!!

    if( ! On )
    {
        tlbx->ui->chk_editable->setVisible( false ); // !!!!
        tlbx->ui->chk_editable->setEnabled( false ); // !!!!

    }



}

void PblTableView::set_SelectionModel( bool EditMode)
{
    if( EditMode )
    {
        setSelectionBehavior(SelectItems);
        setSelectionMode(QAbstractItemView::SingleSelection);

    }
    else
    {
        setSelectionBehavior(SelectRows);
        setSelectionMode(QAbstractItemView::SingleSelection);
    }


}

void PblTableView::set_repaintEditBtns(bool On,
                                       bool def,
                                       bool hideBtns  )
{

    // ----------------------------------------------------------
    //              SWITCH_EDIT_ENABLED
    // ----------------------------------------------------------


    tlbx->ui->chk_editable->setVisible(true);
    //tlbx->ui->chk_editable->setChecked(def);


    bool en = false;
    if(On && def)
        en = true;

    tlbx->ui->btn_insert->setEnabled( en );
    tlbx->ui->btn_edit->setEnabled( en );
    tlbx->ui->btn_copy->setEnabled( en );
    tlbx->ui->btn_delete->setEnabled( en );

    bool btnVisible = true;

    if( ! On && hideBtns)
        btnVisible = false;

    tlbx->ui->btn_insert->setVisible(btnVisible);
    tlbx->ui->btn_edit->setVisible(btnVisible);
    tlbx->ui->btn_copy->setVisible(btnVisible);
    tlbx->ui->btn_delete->setVisible(btnVisible);



    if(On)
    {
        if(act_InsertRow  == NULL )
        {


            act_InsertRow = new QAction(QIcon(":icon/img/btn-db/insert.svg") , trUtf8("create row"), this);

            act_InsertRow->setShortcut(Qt::Key_Insert);

            _CONNECT_(act_InsertRow, SIGNAL(triggered()),
                      this, SLOT(slot_insertRowBtnClick()));

            _CONNECT_(tlbx->ui->btn_insert, SIGNAL(clicked()),
                      act_InsertRow, SLOT( trigger() ));

            contextMenu->addAction(act_InsertRow);

            addAction(act_InsertRow);


        }


        if(act_EditRow  == 0)
        {

            act_EditRow = new QAction( QIcon(":icon/img/btn-db/edit.svg") , trUtf8("edit row"), this);

            act_EditRow->setShortcut(Qt::Key_F4);

            _CONNECT_(act_EditRow, SIGNAL(triggered()), this, SLOT(slot_editRowBtnClick()));

            _CONNECT_(tlbx->ui->btn_edit, SIGNAL(clicked()), act_EditRow, SLOT( trigger() ));

            contextMenu->addAction(act_EditRow);

            addAction(act_EditRow);

        }

        // ----------------------------------------------------------
        //                       COPY_ROW
        // ----------------------------------------------------------

        if(act_CopyRow  == 0)
        {

            act_CopyRow = new QAction( QIcon(":icon/img/btn-db/copy.svg") , trUtf8("copy row"), this);

            act_CopyRow->setShortcut(Qt::Key_F9);

            _CONNECT_(act_CopyRow, SIGNAL(triggered()), this, SLOT(slot_copyRowBtnClick()));

            _CONNECT_(tlbx->ui->btn_copy, SIGNAL(clicked()), act_CopyRow, SLOT( trigger() ));

            contextMenu->addAction(act_CopyRow);

            addAction(act_CopyRow);


        }


        // ----------------------------------------------------------
        //                       DELETE_ROW
        // ----------------------------------------------------------


        if(act_DeleteRow  == 0)
        {

            act_DeleteRow = new QAction( QIcon(":icon/img/btn-db/remove.svg"),
                                         trUtf8("remove row"), this);

            act_DeleteRow->setShortcut(Qt::Key_Delete);

            _CONNECT_(act_DeleteRow, SIGNAL(triggered()), this, SLOT(slot_removeRowBtnClick()));

            _CONNECT_(tlbx->ui->btn_delete, SIGNAL(clicked()), act_DeleteRow, SLOT( trigger() ));

            contextMenu->addAction(act_DeleteRow);

            addAction(act_DeleteRow);


        }

        // ----------------------------------------------------------
        //                       CLEAR FIELD
        // ----------------------------------------------------------

        if(act_ClearField ==0)
        {
            act_ClearField = new QAction( QIcon(":icon/img/btn-db/clear_field.svg"),
                                          trUtf8("clear field"), this);

            act_ClearField->setShortcut(Qt::CTRL + Qt::Key_Backspace);

            _CONNECT_(act_ClearField, SIGNAL(triggered()), this, SLOT(slot_clearFieldClick()));

            contextMenu->addAction(act_ClearField);

            //addAction(act_ClearField);
        }


    }

    // ---------------------------------------------------
    // выключаем
    // ---------------------------------------------------

    else if ( ! On)

    {
        if(act_InsertRow  != 0)
        {
            _DISCONNECT_(act_InsertRow, SIGNAL(triggered()), this, SLOT(slot_insertRowBtnClick()));

            _DISCONNECT_(tlbx->ui->btn_insert, SIGNAL(clicked()), act_InsertRow, SLOT( trigger() ));

            contextMenu->removeAction(act_InsertRow);

            removeAction(act_InsertRow);

            act_InsertRow->setVisible(On);

            delete(act_InsertRow);

            act_InsertRow=0;

        }
        tlbx->ui->btn_insert->setEnabled(false);

        // ----------------------------------------------------------
        //                       EDIT_ROW
        // ----------------------------------------------------------

        if(act_EditRow  != 0)
        {
            _DISCONNECT_(act_EditRow, SIGNAL(triggered()), this, SLOT(slot_editRowBtnClick()));

            _DISCONNECT_(tlbx->ui->btn_edit, SIGNAL(clicked()), act_EditRow, SLOT( trigger() ));

            contextMenu->removeAction(act_EditRow);

            removeAction(act_EditRow);

            act_EditRow->setVisible(On);

            delete(act_EditRow);

            act_EditRow=0;
        }
        tlbx->ui->btn_edit->setEnabled(false);


        if(act_CopyRow  != 0)
        {

            _DISCONNECT_(act_CopyRow, SIGNAL(triggered()), this, SLOT(slot_copyRowBtnClick()));

            _DISCONNECT_(tlbx->ui->btn_copy, SIGNAL(clicked()), act_CopyRow, SLOT( trigger() ));

            contextMenu->removeAction(act_CopyRow);

            removeAction(act_CopyRow);

            act_CopyRow->setVisible(On);

            delete(act_CopyRow);

            act_CopyRow=0;
        }

        tlbx->ui->btn_copy->setEnabled(false);

        if(act_DeleteRow  != 0)
        {
            _DISCONNECT_(act_DeleteRow, SIGNAL(triggered()), this, SLOT(slot_removeRowBtnClick()));

            _DISCONNECT_(tlbx->ui->btn_delete, SIGNAL(clicked()), act_DeleteRow, SLOT( trigger() ));

            contextMenu->removeAction(act_DeleteRow);

            removeAction(act_DeleteRow);

            delete(act_DeleteRow);

            act_DeleteRow=0;

        }

        tlbx->ui->btn_delete->setEnabled(false);

        // ----------------------------------------------------------
        //                       CLEAR_FIELD
        // ----------------------------------------------------------

        if(act_ClearField !=0)
        {

            _DISCONNECT_(act_ClearField, SIGNAL(triggered()), this, SLOT(slot_clearFieldClick()));

            contextMenu->removeAction(act_ClearField);

            removeAction(act_ClearField);

            delete act_ClearField;

            act_ClearField = 0;
        }



    }





}


//tlbx->ui->btn_edit->setEnabled(On);






PblTableView::~PblTableView()
{
    //qDebug() << "~PblTableView()";

    delegts.clear();

}

void PblTableView::setModel(PblSqlRelationalTableModel *newMdl)
{
    mdl = newMdl;

    set_behavoir( newMdl->editable );

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

    QTableView::setModel( newMdl );

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

    _CONNECT_(newMdl, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
              this, SLOT(slot_dataChanged( QModelIndex,QModelIndex )));

    _CONNECT_(newMdl, SIGNAL(beforeUpdate(int,QSqlRecord&)),
              this, SLOT(slot_beforeUpdate(int,QSqlRecord&)));

    _CONNECT_(newMdl, SIGNAL(beforeInsert(QSqlRecord&)),
              this, SLOT(slot_beforeInsert(QSqlRecord&)));

    _CONNECT_(tlbx->ui->cmb_Strategy, SIGNAL(currentIndexChanged(int)),
              this , SLOT(slot_cmb_Strategy_currentIndexChanged(int)));


    tlbx->ui->cmb_Strategy->setCurrentIndex(newMdl->editStrategy());


}

void PblTableView::slot_beforeInsert(QSqlRecord &record)
{

    qDebug() << "slot_beforeInsert " << model()->editStrategy();
    tlbx->ui->btn_submitAll->setEnabled(true);
}

void PblTableView::slot_beforeUpdate(int row ,QSqlRecord&rec)
{

    if(model()->editStrategy() == QSqlTableModel::OnRowChange)
    {
        qDebug() << "slot_beforeUpdate OnRowChange";
        tlbx->ui->btn_submitAll->setEnabled(true);
    }
    else if(model()->editStrategy() == QSqlTableModel::OnFieldChange)
        qDebug() << "slot_beforeUpdate OnFieldChange";

}

void PblTableView::slot_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{

    if(model()->editStrategy() == QSqlTableModel::OnManualSubmit)
    {
        qDebug() << "slot_dataChanged OnManualSubmit";
        tlbx->ui->btn_submitAll->setEnabled(true);
    }
}

/*
QIcon PblTableView::getActIcon(PblTableView::ACTION act)
{

    //    static QIcon insert = QIcon(":icon/img/btn-db/insert.svg");
    //    static QIcon copy   = QIcon(":icon/img/btn-db/copy.svg");
    //    static QIcon edit   = QIcon(":icon/img/btn-db/edit.svg");
    //    static QIcon remove = QIcon(":icon/img/btn-db/remove.svg");
    static QIcon search = QIcon(":icon/img/btn-db/choice.svg");
    //static QIcon clrFld = QIcon(":icon/img/btn-db/clear_field.svg");
    static QIcon txtFind = QIcon(":icon/img/btn-db/search.svg");
    static QIcon view = QIcon(":icon/img/btn-db/view.svg");
    static QIcon selectAndClose = QIcon(":icon/img/btn-db/selection.svg");

    //    if(act == PblTableView::ACT_INSERT_ROW)
    //        return insert;

    //    if(act == PblTableView::ACT_COPY_ROW)
    //        return copy;

    //    else if(act == PblTableView::ACT_EDIT_ROW)
    //        return edit;

    //    else if(act == PblTableView::ACT_DELETE_ROW)
    //        return remove;

    //    if(act == PblTableView::ACT_SEARCH)
    //        return search;

    if(act == PblTableView::ACT_CLEAR_SEARCH_RESULTS)
        return txtFind;

    //    else if(act == PblTableView::ACT_CLEAR_FIELD)
    //        return clrFld;

    else if(act == PblTableView::ACT_VIEW)
        return view;

    else if(act == PblTableView::ACT_SELECT_AND_CLOSE)
        return selectAndClose;



}
*/

/*QIcon PblTableView::getIcon(int nn) //
{

    if( nn == 1 )
        return QIcon(":icon/img/btn-db/choice.svg");
    else
        return QIcon(":icon/img/btn-db/choice_off.svg");

}*/


QSize PblTableView::sizeHint() const
{
    return QSize(700,500);
}

void PblTableView::fillContextMenu()
{


}


void PblTableView::slot_setVisibleExRelIdColumns(bool visible)
{

    showRelExColumns = visible;

    foreach(QString fldName, model()->baseRec.specialFld.keys())
    {
        //qDebug() << "specialFld setColumnHidden " << fldName << ! showRelExColumns;

        if( model()->baseRec.specialFld[ fldName ] !=  PblSqlRecord::CALC_FLD)
        {
            int Col = model()->baseRec.indexOf( fldName );

            setColumnHidden( Col , ! showRelExColumns);
        }
    }

    QHashIterator<QString , PblColumnInfo> it(model()->colInfo);

    while( it.hasNext() )
    {
        it.next();

        //qDebug() << "COLUMN_INFO: " << it.value();

        if( ! it.value().is_visible )

            setColumnHidden( mdl->baseRec.indexOf( it.key( ) ) , ! showRelExColumns);

    }

    if( model()->getPriColumn() >=0)
        setColumnHidden( model()->getPriColumn() , ! showRelExColumns);

    //resizeColumnsToContents();

}

void PblTableView::set_contextMenuEnabled(bool On)
{
    contextMenuEnabled = On;
}

void PblTableView::slot_CustomMenuRequested(const QPoint &pos)
{
    if( ! contextMenuEnabled )
        return;

    //qDebug() << "PblTableView::slot_CustomMenuRequested";

    setContextMenuItemsVisibleAfterFieldSelected();

    contextMenu->popup(this->viewport()->mapToGlobal(pos));
}

void PblTableView::setContextMenuEnabled( bool enabled)
{
    contextMenuEnabled = enabled;
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


    if( ! model()->editable )
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


        if( col < model()->baseRec.count() )
        {

            if( model()->getRelIdColumn( col ) >= 0 )
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
    else if( model()->editable )       // форма редактируемая
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

        if( model()->editable )
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

bool PblTableView::vrt_clearField(const QModelIndex &idx)
{
    int col = idx.column();

    int row = idx.row();

    //qDebug() << QString("PblTableView::slot_clearField   index [%1x%2]").arg(currIdx.row()).arg(currIdx.column());

    if( ! idx.isValid())
    {
        return false;
    }


    if ( model()->isRelationalColumn( col ) )
    {
        return vrt_clearRelField( idx );
    }

    QVariant def;

    if(model()->defaultVls.contains( col))

        def = model()->defaultVls.value( col);

    return model()->setData(idx , def);
}


bool PblTableView::vrt_clearRelField(const QModelIndex &idx)
{
    int col = idx.column();

    int row = idx.row();

    if( ! idx.isValid())
    {
        return false;
    }

    if ( !  model()->isRelationalColumn( col ) )

        return false;

    QString fldName = model()->baseRec.fieldName( col );

    if(  fldName.isEmpty() )

        return false;

    // ------------------------------------------------------------------
    //                 first clear relation id field !
    // ------------------------------------------------------------------

    int extCol = model()->getRelIdColumn( col );

    QModelIndex exIdx = model()->index( row, extCol);

    if ( ! model()->setData(exIdx , 0 ) ) // id field

        return false ;


    // ------------------------------------------------------------------
    //                  txt field has to clear
    // ------------------------------------------------------------------

    if( idx.isValid() ) // NOT submit/select
    {
        if( ! model()->setData(idx , "")) // text
        {
            return false;
        }
    }

    // ------------------------------------------------------------------
    //                  sub accounting fields has to clear
    // ------------------------------------------------------------------

    if( idx.isValid() ) // NOT submit/select
    {
        if( model()->subAccnt.contains( fldName ))
        {
            int subOnCol = model()->getAccountingOnColumn( col );

            Q_ASSERT( subOnCol != -1);

            QModelIndex subOnColIdx = model()->index( row, subOnCol );

            Q_ASSERT( subOnColIdx.isValid());

            if ( ! model()->setData( subOnColIdx ,0) ) // sub on
            {
                return false;
            }
        }

    }

    if( model()->subAccnt.contains( fldName ))
    {
        QString rel2FldName =  model()->subAccnt.value( fldName ).fld2;

        int subCol = model()->baseRec.indexOf( rel2FldName );

        QModelIndex subIdx = model()->index( row , subCol );

        Q_ASSERT( subIdx.isValid() );

        return vrt_clearField( subIdx);

    }


    return true;
}
//-------------------------------------------------

bool PblTableView::vrt_insertRow(int srcRow)
{
    int newRow = model()->rowCount();// forever insert at end

    if( ! model()->insertRow(newRow))
    {
        qCritical() << "PblTableView::insertRow ???? " ;
        return false;
    }

    model()->isInsertRow = newRow;

    tlbx->ui->btn_submitAll->setEnabled(true); //

    setCurrentIndex( model()->index( newRow , 0 ) );

    // better save row to db now but maybe this does later too

    emit sig_showSubmitBtn( true);

    return true;
}

bool PblTableView::slot_insertRowBtnClick()
{
    bool needsToSubmit = false;

    QSqlTableModel::EditStrategy old = model()->editStrategy();

    // ---------------------------------------------------
    // Important! with inserting a row we have immediately to submit for model strategy
    // OnFieldChange and OnFieldChange
    // ---------------------------------------------------

    if( old == QSqlTableModel::OnFieldChange )
    {
        // temporary set OnRowChange

        model()->setEditStrategy(QSqlTableModel::OnRowChange); //!!!

    }

    if(old != QSqlTableModel::OnManualSubmit)

        needsToSubmit = true; // !!!!


    int row = 0;

    if( currentIndex().isValid())

        row = currentIndex().row();


    bool res = true;

    if ( res = vrt_insertRow( row ) )
    {
        // here may be called a virtual fuction that makes initializing new row
        // for example : open new dialog windows to select value for special field
    }



    if( res && needsToSubmit )
    {

        bool res = model()->submit(); // !!!!!!!

        if ( ! res )
        {
            QMessageBox::critical(this ,
                                  "error" ,
                                  QString("submit returns  false\n"\
                                          "sql error: %1")
                                  .arg(model()->lastError().text())
                                  );
        }

    }

    if( old == QSqlTableModel::OnFieldChange)

        model()->setEditStrategy( QSqlTableModel::OnFieldChange ); // restore

    return res;
}



//-------------------------------------------------

bool PblTableView::vrt_viewRow(int row)
{
    // this code you implement youself
    QMessageBox::warning(this,
                         mySql::error_,
                         tr("Viewing a row."),
                         tr("You should implement this code yourself!")
                         );
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

    QSqlRecord srcRec = model()->record(srcRow);

    bool bb = model()->insertRow( newRow );

    if( ! bb )
    {
        qCritical() << "PblTableView::copyRow  insertRow ERROR : " << model()->lastError().text();
        return false;
    }

    bool bbb = model()->removePrimaryKeys_fromRec( srcRec, PblSqlRelationalTableModel::INSERT );

    bbb = model()->setRecord( newRow , srcRec);

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

    if( ! currentIndex().isValid())
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
                                 tr("before removing a line you should submit dirty row %2 \ntable '%1'\nerror:%3").
                                 arg(model()->tableName()).
                                 arg(model()->isInsertRow).
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
        //int col = config::get_defaultColumn( model());

        QModelIndex idx = model()->index(row , 0);

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
        slot_repaintSubmitBtn( true);

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


bool PblTableView::vrt_doubleClicked(const QModelIndex & idx_dblClk , bool &needsSubmitAfter)
{

    needsSubmitAfter = false;

    int col = idx_dblClk.column();
    int row = idx_dblClk.row();


    QString fldName = model()->baseRec.fieldName( col );

    if( fldName .isEmpty() )
        return false;

    int idCurrRow = model()->getRowPriValue( row );

    if( ! model()->editable )
    {
        if( selectable) //selecting row and close dlg
        {
            emit act_selectAndClose->trigger();

        }
        else    // only view row
        {
            vrt_viewRow( row );

        }

        return false;
    }
    else if( model()->editable )
    {
        if( selectable && ! tlbx->ui->chk_editable->isChecked() )

        {
            //selecting row and close dlg

            emit act_selectAndClose->trigger();


            return false;
        }
        //        else if( ! selectable )//&& ! tlbx->ui->chk_editable->isChecked())
        //        {
        //            vrt_viewRow( row);


        //            return false;
        //        }

    }

    if( model()->editStrategy() == QSqlTableModel::OnFieldChange)
    {
        QMessageBox::warning( this,
                              "error",
                              QString("you need to switch this model from OnFieldChange to OnRowChange (temporary)"));
        return false;
    }

    // ------------------------------------------------
    //          RELATION COLUMN
    // ------------------------------------------------


    if(model()->isRelationalColumn( col ) ) // relations
    {

        PblSqlRelation relation = model()->getRelationInfoForColumn( fldName );

        // ---------------------------------------------------------
        //  if is subaccounting presents but this toggled off
        // ---------------------------------------------------------

        if( model()->rel_bindings.contains( fldName ) )
        {
            PblSubAccnt * subaccnt = model()->rel_bindings[ fldName ];

            QString sub_on_fld_name = subaccnt->get_sub_on_fld_name();


            if( ! sub_on_fld_name.isEmpty() )
            {
                bool ok;

                int sub_on = model()->data( model()->index( row , model()->baseRec.indexOf( sub_on_fld_name ))).toInt( );

                //                if( ok )
                //                {
                if ( sub_on == 0)
                {
                    QMessageBox::warning( this,
                                          "warning",
                                          QString("sub accounting toggled off for this row "),
                                          QString("look field %1").arg(subaccnt->fld1)
                                          );
                    return false;
                }
                //}

            }

        }

        // -----------------------------------------------------------------

        int relCol = model()->baseRec.indexOf(relation.idField1Name);

        if( relCol == PblSqlRelation::COL_UNDEFINED)

            return false;

        // ------------------------------------------------
        //          GENERATE SUB ACCOUNTING FILTER
        // ------------------------------------------------

        QHash< QString , QVariant > Filter;

        if( model()->rel_bindings.contains(fldName))
        {

            PblSubAccnt *subAccnt = model()->rel_bindings.value( fldName );


            int parentCol =  model()->baseRec.indexOf( subAccnt->fld1 );

            int relPrntIdCol = model()->getRelIdColumn( parentCol );


            Q_ASSERT(relPrntIdCol != -1);


            QModelIndex prntIdx = model()->index( row , relPrntIdCol);

            QVariant relPrntIdVal = model()->data(prntIdx);

            QString fld = model()->relations2[subAccnt->fld1].get_ext_fld_name();

            Filter.insert( fld, relPrntIdVal);


            qDebug() << "Filter " << Filter;

        }

        // ------------------------------------------------
        //              OPEN DLG
        // ------------------------------------------------

        PblTableDlg dlg ( relation.extTblName ,
                          &model()->database(),
                          this,
                          p_cb_setting_mdl,  // !!!!
                          p_cb_setting_view, // !!!!
                          true,
                          Filter

                          );

        if( ! dlg.mdl->select() )

            return false;

        if(relation.extTblName == "sub_accounting")
            dlg.showNormal();
        else
            dlg.showFullScreen();


        dlg.exec();

        if(dlg.result() == QDialog::Rejected)

            return false;

        // save id just in case


        if(dlg.chosenRec == QSqlRecord())
        {
            QMessageBox::critical(this ,
                                  mySql::error_ ,
                                  tr("the choice is not defined"));
            return false;
        }

        QVariant txt = dlg.chosenRec.value(relation.dstFldName);

        qDebug() << " dlg.chosenRec " << dlg.chosenRec;

        if(dlg.chosenId == -1)
        {
            QMessageBox::critical(this ,
                                  "error" ,
                                  tr("the choice is not defined"));
            return false;
        }

        if(! idx_dblClk.isValid() ) // just in time , submit occures
        {
            qDebug() << " model()->editStrategy() " << model()->editStrategy();
            Q_ASSERT_X(idx_dblClk.isValid()==false,"464576576","43675465465");
        }

        Q_ASSERT(model()->getRelIdColumn( col )>=0);

        QModelIndex extColIdx = model()->index(row, model()->getRelIdColumn( col ));

        if(  ! extColIdx.isValid())

            return false;


        if( model()->editStrategy() >= QSqlTableModel::OnRowChange) // <=!!!
        {
            // ------------------------------------------------
            //         OnRowChange   OnManualSubmit !!!!
            // ------------------------------------------------


            // first time we set relExtIdCol

            if( ! model()->setData( extColIdx , dlg.chosenId , Qt::EditRole))
            {
                QMessageBox::critical(this ,
                                      "error" ,
                                      tr(
                                          "setData returns  false\n"\
                                          "field : '%1'\n"\
                                          "value : '%2'\n"\
                                          "sql error: %3").
                                      arg(model()->baseRec.fieldName(extColIdx.column())).
                                      arg(dlg.chosenId).
                                      arg(model()->lastError().text())
                                      );

                return false;
            }


            needsSubmitAfter= true; //!!!!!!!!


            QVariant var =  model()->data( extColIdx );

            if( ! extColIdx.isValid() || ! idx_dblClk.isValid() )
            {

                return false;
            }

            // submit not occures, it is OK, nothing more to do

            // -----------------------------------------------
            //          set text emulation field
            // -----------------------------------------------

            qDebug() << "txt " << txt;

            if( ! model()->setData( idx_dblClk , txt ,Qt::EditRole))
            {
                QMessageBox::critical(this ,
                                      "error" ,
                                      tr(
                                          "setData returns  false\n"\
                                          "field : '%1'\n"\
                                          "value : '%2'\n"\
                                          "sql error: %3").
                                      arg(model()->baseRec.fieldName(extColIdx.column())).
                                      arg(dlg.chosenId).
                                      arg(model()->lastError().text())
                                      );


                return false;
            }


            if( ! idx_dblClk.isValid())
            {

                return false;
            }

            // ----------------------------
            //  submit NOT occures - ok
            // ----------------------------

            if( model()->isSubAccounting( fldName ))
            {
                // -----------------------------------------------
                //          set sub_on field true/false
                // -----------------------------------------------

                int subOnCol = model()->getAccountingOnColumn( col );

                Q_ASSERT_X(subOnCol>=0, "65363565","8477857");

                QModelIndex subOnIdx = model()->index( idx_dblClk.row() , subOnCol );

                if( ! subOnIdx.isValid())
                {
                    QMessageBox::critical(this ,
                                          "error" ,
                                          tr(
                                              "subOnIdx in not valid\n")
                                          );

                    return false;

                }

                QString fldName2 = model()->baseRec.fieldName( col );

                if(fldName2.isEmpty())
                {
                    return false;
                }


                QString subOnFld_extTbl = model()->subAccnt.value( fldName2 ).sub_on_fld_name_extTbl;


                if( ! dlg.chosenRec.contains( subOnFld_extTbl ))
                {

                    return false;
                }


                QVariant sub_on_val = dlg.chosenRec.value( subOnFld_extTbl );

                if( ! model()->setData( subOnIdx , sub_on_val ,Qt::EditRole))
                {
                    QMessageBox::critical(this ,
                                          "error" ,
                                          tr(
                                              "setData returns  false\n"\
                                              "field : '%1'\n"\
                                              "value : '%2'\n"\
                                              "sql error: %3").
                                          arg(model()->baseRec.fieldName(extColIdx.column())).
                                          arg(dlg.chosenId).
                                          arg(model()->lastError().text())
                                          );

                    return false;
                }

            }


            if( ! idx_dblClk.isValid()) // submit NOT occures
            {

                return false;
            }

            bool bbb= vrt_afterSetFldValue( idCurrRow,
                                            fldName ,
                                            idx_dblClk,
                                            dlg.chosenRec,
                                            needsSubmitAfter  );


            return true;

        }


    }
    else if( delegts.contains( fldName ) )
    {
        checkBox_Delegate * chk = qobject_cast<checkBox_Delegate *>(delegts.value( fldName ));

        if ( chk )
        {
            bool ok;

            int checked = model()->data( idx_dblClk , Qt::DisplayRole).toInt( &ok );

            if(checked == 0)
                checked = 1;
            else
                checked = 0;

            bool bbbb = model()->setData( idx_dblClk , checked, Qt::EditRole );

            //qDebug() << "checked " << checked << " setData " << bbbb << model()->editStrategy();

            needsSubmitAfter = true;

            return true;
        }


    }

    return false;

}

void PblTableView::slot_doubleClicked(const QModelIndex & index)
{
    //qDebug() << "PblTableView::slot_doubleClicked";


    bool needsRetTo_OnFieldChange = false;

    if( model()->editStrategy() == QSqlTableModel::OnFieldChange)
    {
        // temporary set OnRowChange

        model()->setEditStrategy(QSqlTableModel::OnRowChange); //!!!

        needsRetTo_OnFieldChange = true;
    }

    bool needsSubmitAfter;

    if ( vrt_doubleClicked(index , needsSubmitAfter ) )
    {

        if ( needsSubmitAfter )
        {
            bool submit_res = model()->submit(); // !!!!!!!

            if ( ! submit_res )
            {
                QMessageBox::critical(this ,
                                      "error" ,
                                      QString("submit returns  false\n"\
                                              "sql error: %1")
                                      .arg(model()->lastError().text())
                                      );
            }
        }

    }

    if(needsRetTo_OnFieldChange)

        model()->setEditStrategy(QSqlTableModel::OnFieldChange); //!!!


}


bool PblTableView::slot_searchInTable(const QString &txt)
{

    if( find_settings.searchedField == -1) //еще не понятно по какому полю искать
    {
        QMessageBox::warning(this , "error" , "please select a field than searched in table");

        return false;
    }

    int col = find_settings.searchedField;

    QString fieldName = model()->baseRecord().fieldName(find_settings.searchedField);

    if(fieldName.isEmpty() || model()->tableName().isEmpty())
    {
        qCritical("on_ledt_filter_returnPressed error");
        return false;
    }

    Q_ASSERT(find_settings.searchedField != PblSqlRelationalTableModel::FLD_UNDEFINED);

    QVariant::Type type = model()->baseRec.field((int)find_settings.searchedField).type();

    qDebug() << "QVariant::Type type : " << type;

    if (model()->getRelIdColumn(  find_settings.searchedField ) != PblSqlRelationalTableModel::FLD_UNDEFINED )
    {
        find_settings.seachType = Search_Settings_Dlg::FIND_SETTINGS::SEARCH_RELATION_TEXT;
    }
    else if (type == QVariant::String )
    {
        if( ! txt.isEmpty() &&  ! txt.isSimpleText() )
        {
            QMessageBox::warning( this ,
                                  tr("Error"),
                                  tr("searching value ['%1'] has not string type").
                                  arg(txt));
            return false;
        }

        find_settings.seachType = Search_Settings_Dlg::FIND_SETTINGS::SEARCH_TEXT;
    }
    else if (
             type == QVariant::Int
             || type == QVariant::UInt
             || type == QVariant::Char
             || type == QVariant::LongLong
             || type == QVariant::ULongLong
             )
    {
        bool ok = false;
        int foo = txt.toInt( &ok );

        if( ! txt.isEmpty() && ! ok)
        {
            QMessageBox::warning( this ,
                                  tr("Error"),
                                  tr("searching value ['%1'] has not integer type").
                                  arg(txt));
            return false;
        }

        find_settings.seachType = Search_Settings_Dlg::FIND_SETTINGS::SEARCH_NUMBER;
    }
    else if (type == QVariant::Double )
    {
        bool ok = false;
        double foo = txt.toDouble( &ok );

        if( ! txt.isEmpty() && ! ok)
        {
            QMessageBox::warning( this ,
                                  tr("Error"),
                                  tr("searching value ['%1'] has not double type").
                                  arg(txt));
            return false;
        }

        find_settings.seachType = Search_Settings_Dlg::FIND_SETTINGS::SEARCH_NUMBER;
    }
    else
    {
        QMessageBox::warning( this ,
                              tr("Error"),
                              tr("unknown searching value type ['%1'] ").
                              arg(txt));
        return false;

    }

    QString flt("");

    if( ! txt.isEmpty())
    {
        // Слева

        if(find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_RELATION_TEXT)
        {
            QString str = model()->getRelationInfoForColumn(
                        model()->baseRec.fieldName( find_settings.searchedField ) ).dstFldName;

            flt.append(QString::fromLatin1(" %3_%1.%2 ").
                       arg(col).
                       arg(str).
                       arg(model()->prefix)
                       );
        }
        else
        {
            flt.append(model()->tableName()+"."+fieldName);
        }

        if( ! find_settings.caseSensitive )
        {
            if( find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_RELATION_TEXT
                    || find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_TEXT)
            {
                flt.prepend(" lower(").append(") ");
            }
        }

        //  справа

        if(find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_TEXT
                || find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_RELATION_TEXT)
        {
            if ( find_settings.exactly)
            {
                if( ! find_settings.caseSensitive)
                    flt.append(" LIKE '"+ txt.trimmed().toLower()+"'");
                else
                    flt.append(" LIKE '"+ txt.trimmed()+"'");

            }
            else
            {
                if( ! find_settings.caseSensitive)
                    flt.append(" LIKE '%"+ txt.trimmed().toLower()+"%'");
                else
                    flt.append(" LIKE '%"+ txt.trimmed()+"%'");

            }
        }
        else if(find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_NUMBER)
        {
            flt.append(" = "+ txt.trimmed()+" ");
        }

    }


    QString subAccountingFilter = model()->getsubAccountingFilter();

    if ( ! subAccountingFilter.isEmpty() )
    {
        if( ! flt.isEmpty())
            flt.append(" AND ");

        flt.append(subAccountingFilter) ;
    }

    model()->setFilter(flt); // select is into


    if(! flt.isEmpty() )
    {
        if( ! model()->setHeaderData(col ,
                                     Qt::Horizontal,
                                     QIcon(":icon/img/btn-db/search.svg"), Qt::DecorationRole))

            QMessageBox::critical(this , "error" , "setHeaderData return false 6575637657");

        if(search_wgts_visible)
            tlbx->ui->wgt_search_block->setVisible(true);

        tlbx->ui->wgt_search_block->setEnabled(true);
        tlbx->ui->btn_clear_seached_text->setVisible(true);

    }
    else
    {
        model()->setHeaderData(col , Qt::Horizontal, QVariant(), Qt::DecorationRole);

        if(search_wgts_visible)
            tlbx->ui->wgt_search_block->setVisible(true);

        tlbx->ui->btn_clear_seached_text->setVisible(false);


    }

    return true;
}

//bool PblTableView::prepare_view( PblSqlRelationalTableModel * Mdl )
//{

//    setModel(Mdl);

//    //??    if ( ! model()->select())
//    //    {
//    //        QMessageBox::warning(this,
//    //                             mySql::error_,
//    //                             tr("error in select query:\n\n%1\n\n\n%2").
//    //                             arg(model()->query().lastQuery()).
//    //                             arg(model()->lastError().text()));
//    //        return false;
//    //    }

//    //qWarning() << " PblTableView::prepare setting_view " ;



//    return true;
//}

void PblTableView::set_viewEnabled( bool On)
{

    // ----------------------------------------------------------
    //                       VIEW
    // ----------------------------------------------------------

    tlbx->ui->btn_view->setVisible(On);

    if( On )
    {
        tlbx->ui->btn_view->setShortcut(Qt::Key_F3);

        _CONNECT_(tlbx->ui->btn_view, SIGNAL(clicked()), this, SLOT(slot_viewRowBtnClick()));

    }
    else if ( ! On )
    {
        tlbx->ui->btn_view->setShortcut(Qt::Key_unknown);

        _DISCONNECT_(tlbx->ui->btn_view, SIGNAL(clicked()), this, SLOT(slot_viewRowBtnClick()));

    }

}


void PblTableView::slot_triggeredSelectByFieldValue(bool forceClear)
{
    if(act_selectByFieldValue ==0)

        return;


    if( ! currentIndex().isValid())
        return;

    if( forceClear )
    {
        model()->setFilter("");

        model()->select();

        act_selectByFieldValue->setIcon(QIcon(":icon/img/btn-db/choice_off.svg"));

        act_selectByFieldValue->setChecked(false);

        return;

    }

    if( slot_selectByFieldValue( currentIndex())) // если filter <>"" то там сброс
    {
        if( ! filter.isEmpty())
        {
            tlbx->setBtn_selectByValue(true , true);

            act_selectByFieldValue->setChecked(true);

            act_selectByFieldValue->setIcon(QIcon(":icon/img/btn-db/choice.svg"));

            tlbx->ui->btn_selectByValue->setIcon(QIcon(":icon/img/btn-db/choice.svg"));
        }

        else
        {
            tlbx->setBtn_selectByValue(true , false);

            act_selectByFieldValue->setChecked(false);

            act_selectByFieldValue->setIcon(QIcon(":icon/img/btn-db/choice_off.svg"));

            tlbx->ui->btn_selectByValue->setIcon(QIcon(":icon/img/btn-db/choice_off.svg"));

        }
    }
}

//void PblTableView::selectRow(int row)
//{
//    qDebug() << "PblTableView::selectRow  emit sig_rowSelected " << row;
//    QTableView::selectRow( row);


//    //emit sig_rowSelected(row);
//}

void PblTableView::setDefaultDelegate(int col)
{
    if( ! model()->baseRec.field( col ).isValid() )
    {
        QMessageBox::warning(this ,
                             mySql::error_ ,
                             tr("column is out of range , field : %1")
                             .arg(col));
        return;
    }

    QString fldName = model()->baseRec.fieldName( col );

    if( delegts.contains( fldName ) )
    {
        QMessageBox::warning(this ,
                             mySql::error_ ,
                             tr("second attempting adding QCheckBox to field : '%1'").arg( fldName ));

        return;
    }


    delegts.insert( fldName, new DefaultStyledItemDelegate( this ) );

    QStyledItemDelegate * delegate = delegts.value( fldName );
    //delegate->

    setItemDelegateForColumn( col , delegate); // is not important

}


void PblTableView::setCheckBoxDelegate( const QString & fldName)
{
    if( ! model()->baseRec.field( fldName ).isValid() )
    {
        QMessageBox::warning(this ,
                             mySql::error_ ,
                             QString("column is out of range , field : %1")
                             .arg(fldName));
        return;
    }

    if(delegts.contains( fldName ))
    {
        QMessageBox::warning(this ,
                             mySql::error_ ,
                             QString("second attempting adding QCheckBox to field : %1")
                             .arg(fldName));
        return;
    }


    delegts.insert( fldName , new checkBox_Delegate( this ) );

    QStyledItemDelegate * cmbDeleg = delegts.value( fldName );

    setItemDelegateForColumn( model()->baseRec.indexOf( fldName ) , cmbDeleg);

}

void PblTableView::setDoubleWithPrecision( const QString & fldName , int precision)
{
    if( ! model()->baseRec.field( fldName ).isValid() )
    {
        QMessageBox::warning(this ,
                             mySql::error_ ,
                             QString("column is out of range , field : %1")
                             .arg(fldName));
        return;
    }


    if(delegts.contains( fldName ))
    {
        QMessageBox::warning(this ,
                             mySql::error_ ,
                             QString("second attempting adding QCheckBox to field : %1")
                             .arg(fldName));
        return;
    }


    delegts.insert( fldName , new DoubleDelegate( precision, this ) );

    QStyledItemDelegate * dblDeleg = delegts.value( fldName );

    setItemDelegateForColumn( model()->baseRec.indexOf( fldName ) , dblDeleg);

}

void PblTableView::setComboBoxDelegate(const QString & fldName, QStringList &lst)
{
    if ( ! model()->baseRec.field( fldName ).isValid() )
    {
        QMessageBox::warning(this ,
                             mySql::error_ , QString("column is out of range , field : %1")
                             .arg(fldName));

        return;
    }

    if( delegts.contains( fldName ) )
    {
        QMessageBox::warning(this , mySql::error_ , tr("second attempting adding QComboBox to field : %1")
                             .arg( fldName ));
        return;
    }


    delegts.insert( fldName ,
                    new ComboBoxDelegate( lst,
                                          this )
                    );

    QStyledItemDelegate * cmbDeleg = delegts.value( fldName );

    int col = model()->baseRec.indexOf( fldName );


    setItemDelegateForColumn( col , cmbDeleg);

    model()->defaultVls.insert( col , -1);

}

void PblTableView::setDateTimeDelegate(const QString & fldName)
{
    if( ! model()->baseRec.field( fldName ).isValid() )
    {
        QMessageBox::warning(this ,
                             mySql::error_ ,
                             tr("column is out of range , field : %1")
                             .arg(fldName));
        return;
    }


    if(delegts.contains( fldName ))
    {
        QMessageBox::warning(this ,
                             mySql::error_ ,
                             tr("second attempting add a date_Delegate to field : %1")
                             .arg( fldName ));
        return;
    }


    delegts.insert( fldName ,
                    new date_Delegate( 1 , this)
                    );

    int col =  model()->baseRec.indexOf( fldName );

    setItemDelegateForColumn( col , delegts[fldName] );

}


bool PblTableView::slot_selectByFieldValue(QModelIndex idx)
{
    qDebug() << "PblTableView::slot_selectByFieldValue idx " << idx;

    //    QMessageBox::warning( this ,
    //                          tr("...."),
    //                          tr("...."));

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
    return qobject_cast<PblSqlRelationalTableModel*>(QTableView::model());
}

void PblTableView::set_Edit_Triggers(bool editOn)
{

    if( editOn)
    {
        //setSelectionBehavior(QAbstractItemView::SelectItems);

        setEditTriggers( QAbstractItemView::DoubleClicked
                         //|QAbstractItemView::AnyKeyPressed
                         //|QAbstractItemView::EditKeyPressed
                         |QAbstractItemView::SelectedClicked
                         //|QAbstractItemView::CurrentChanged
                         //|QAbstractItemView::AllEditTriggers
                         );
    }
    else if ( ! editOn )
    {

        //setSelectionBehavior( QAbstractItemView::SelectRows);

        setEditTriggers( QAbstractItemView::NoEditTriggers );
    }

}

void PblTableView::slot_setEditEnabled(bool editOn)
{

    set_editingEnabled( editOn );

    tlbx->ui->chk_editable->setVisible( true );

    //set_SelectionModel(); // !!

    set_Edit_Triggers( editOn);
}

void PblTableView::slot_editStrategyChanged(QSqlTableModel::EditStrategy newStrategy)
{
    //qDebug() << "PblTableView::slot_editStrategyChanged " << model()->editStrategy() << " newStrategy " << newStrategy;

    if(tlbx->ui->cmb_Strategy->currentIndex() != newStrategy ) // setModel by programming
    {
        if( tlbx->ui->cmb_Strategy->isVisible() )
        {
            tlbx->ui->cmb_Strategy->setCurrentIndex(newStrategy);
        }
    }
    /*if( model()->editStrategy() == newStrategy )
                return;*/

    //setModel(model());
    //model()->select()
    //reset();


    //qDebug() << "PblTableView::slot_editStrategyChanged model()->editStrategy" << model()->editStrategy();


}


//void PblTableView::commitData(QWidget *editor)
//{
//    qDebug() << "PblTableView::commitData";

//    QTableView::commitData(editor);
//}

//void PblTableView::updateEditorData()
//{
//    //qDebug() << "PblTableView::updateEditorData";

//    QTableView::updateEditorData();
//}


//void PblTableView::updateEditorGeometries()
//{
//    //qDebug() << "PblTableView::updateEditorGeometries";

//    QTableView::updateEditorGeometries();

//}

//void PblTableView::updateGeometries()
//{
//    //qDebug() << "PblTableView::updateGeometries";

//    QTableView::updateGeometries();

//}

//void PblTableView::editorDestroyed(QObject *editor)
//{
//    //qDebug() << "PblTableView::editorDestroyed";

//    QTableView::editorDestroyed(editor);

//}

//void PblTableView::closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint)
//{
//    //qDebug() << "PblTableView::closeEditor";

//    QTableView::closeEditor(editor , hint);
//}

//void PblTableView::verticalScrollbarAction(int action)
//{
//    //qDebug() << "PblTableView::verticalScrollbarAction";

//    QTableView::verticalScrollbarAction(action);
//}

//void PblTableView::horizontalScrollbarAction(int action)
//{
//    //qDebug() << "PblTableView::horizontalScrollbarAction";

//    QTableView::horizontalScrollbarAction(action);
//}

//void PblTableView::verticalScrollbarValueChanged(int value)
//{
//    //qDebug() << "PblTableView::verticalScrollbarValueChanged";

//    QTableView::verticalScrollbarValueChanged(value);
//}

//void PblTableView::horizontalScrollbarValueChanged(int value)
//{
//    //qDebug() << "PblTableView::horizontalScrollbarValueChanged";

//    QTableView::horizontalScrollbarValueChanged(value);
//}

/*
void PblTableView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    //qDebug() << "PblTableView::selectionChanged " << selected << deselected;

    QTableView::selectionChanged(selected , deselected);
}
*/
/*
void PblTableView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    //qDebug() << "PblTableView::currentChanged";

    QTableView::currentChanged(current , previous);

    if(current.row() != previous.row())
        emit sig_rowSelected(current.row());

}
*/

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

    //qDebug() << "slot_cmb_Strategy_currentIndexChanged model() " << model() << "editStrategy " <<model()->editStrategy() << model()->tableName();

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

    //qDebug() << "PblTableView::reset() styleSheet() = " << styleSheet();

    // mdl maybe not init here
}

void PblTableView::slot_repaintSubmitBtn(bool enabled)
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

bool PblTableView::vrt_afterSetFldValue(int idRow,
                                        const QString & fldName,
                                        const QModelIndex & idx,
                                        const PblSqlRecord &rec,
                                        bool &needsSubmitAfter)
{
    qDebug() << "PblTableView::vrt_afterSetFldValue";

    if( model()->isRelationColumn( fldName))
    {
        if( model()->isSubAccounting( fldName ))
        {

            int row = idx.row();

            if ( ! idx.isValid())
            {
                row = model()->findRowById(idRow);

                if(row == -1 && model()->filter() == "")
                {
                    QMessageBox::critical(0,
                                          tr("Error"),
                                          tr("vrt_afterSetFldValue is not correct\n"\
                                             "dont restore current row after select"));
                    return false;
                }
            }


            if(fldName.isEmpty())

                return false;

            if( ! model()->subAccnt.contains( fldName ) )

                return false;


            QString rel2ColName = model()->subAccnt.value( fldName ).fld2;

            Q_ASSERT(rel2ColName.isEmpty()==false);

            int rel2Col = model()->baseRec.indexOf( rel2ColName );

            Q_ASSERT( rel2Col >= 0 );

            QModelIndex rel2Idx = model()->index( row , rel2Col );

            if( model()->isSubAccountingOn_forFld( row, fldName ))
            {

                vrt_doubleClicked( rel2Idx , needsSubmitAfter );

                return true;
            }
            else
            {
                vrt_clearRelField( rel2Idx );
            }

        }
    }

    return true;

}

void PblTableView::slot_afterSelect( bool ok)
{
    if( ! ok)

        return;

    emit sig_showSubmitBtn( false);

    if( ! showRelExColumns)
    {
        slot_setVisibleExRelIdColumns( showRelExColumns );
    }

    tlbx->ui->btn_submitAll->setEnabled(false);

    //qDebug() << "PblTableView::slot_afterSelect";

    resizeColumnsToContents();
}

void PblTableView::setToLayout(QVBoxLayout * lo)
{
    if(lo->isEnabled())
    {
        lo->addWidget(tlbx);
        lo->addWidget(this);
    }
}

bool PblTableView::edit(const QModelIndex &index, EditTrigger trigger, QEvent *event)
{
    return QTableView::edit( index, trigger, event);

}

void PblTableView::paintEvent(QPaintEvent *e)
{
    //qDebug() << "PblTableView::paintEvent " << e->rect() << e->region() ;
    //qDebug() << "Style_Sheet " << styleSheet();

    QTableView::paintEvent( e );

    //    QPainter painter(this);

    //    int radius = 6;

    //    painter.setRenderHint( QPainter::Antialiasing );

    //    QPen pen = painter.pen();

    //    painter.setPen( Qt::SolidLine);//NoPen );

    //    painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), radius, radius,
    //                            Qt::AbsoluteSize);
    //    painter.drawRoundedRect(rect().adjusted(1, 1, -1, -rect().height() + 10), 2, 2,
    //                            Qt::AbsoluteSize);

}



