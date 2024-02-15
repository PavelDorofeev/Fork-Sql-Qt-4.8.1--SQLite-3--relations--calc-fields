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
#include "qp_tableview_wrapper.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QDebug>
#include "some_tests.h"
#include "qp/db/model/qp_sqltablemodel.h"
#include <QSqlError>
#include "btn_toolbox.h"
#include <QSqlDatabase>
#include <QSqlIndex>
#include "qp_table_dlg.h"
#include <QHeaderView>
#include <QSqlField>
#include <QDoubleSpinBox>
#include <QStyledItemDelegate>
#include <QApplication>
#include <QComboBox>
#include <QSqlQuery>
#include <QPainter>
#include <QPaintEvent>
#include "delegates/combobox_delegate.h"
#include "delegates/comboboxdelegate2.h"
#include "config.h"
#include "delegates/checkbox_delegate.h"
#include "delegates/defaultstyleditemdelegate.h"
#include "qp/qp.h"
#include "qp/db/db.h"
#include "qp/dbg/dbg.h"


#include "qp/tableview/qp_vertheaderview.h"
#include "qp/tableview/qp_horheaderview.h"

#include "ui_btn_toolbox.h"
#include "delegates/date_delegate.h"
#include "horizontal_header.h"
#include "qp/db/model/qp_subaccnt.h"
#include "qp/gui/qp_gui.h"

const QString QpTableViewWrapper::s_submit= QObject::tr("submit");
const QString QpTableViewWrapper::s_submitAll= QObject::tr("submit All");
int   QpTableViewWrapper::margin_hor = 0;



QpTableViewWrapper::QpTableViewWrapper(
        QWidget *parent,
        cb_setting_view pView,
        const bool Selectable)

    :

      QTableView( parent ),
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
      contextMenuEnabled(false),
      search_wgts_visible(false),
      showRelExColumns(false),
      changeEditStrategyEnable(false),
      hideEditBtns(true),
      p_cb_setting_view(pView),
      mdl(0)

{

    setSelectionMode(QAbstractItemView::SingleSelection);


    setAttribute(Qt::WA_SetCursor, true);

    setAttribute(Qt::WA_InputMethodEnabled , true);

    //setAttribute(Qt::WA_PaintOutsidePaintEvent, true);

    // ----------------------------------------------------
    //              context menu
    // ----------------------------------------------------

    contextMenu = new QMenu(this);

    //hor = new Horizontal_Header(Qt::Horizontal , this);

    //setHorizontalHeader( hor );

    //    qp::meta::cnct (hor, SIGNAL(sig_needsReselect(QList<int>)),
    //              this, SLOT(slot_needsReselect(QList<int>)));

    horizontalHeader()->setDragEnabled(false);
    horizontalHeader()->setAcceptDrops(false);
    //horizontalHeader()->setDragDropMode(QAbstractItemView::DragDrop );


    qp::meta::cnct (this, SIGNAL(customContextMenuRequested(const QPoint &)),
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

    //qDebug( ) << "width QpTableViewWrapper tlbx" << this->width() << tlbx->width();

    if( tlbx->width() > this->width())
    {
        //qDebug()<< " tlbx->layoutDirection " << tlbx->layoutDirection();
        //tlbx->setLayoutDirection(Qt::RightToLeft);

    }

    verticalHeader()->setVisible(true);


    qp::meta::cnct ( this , SIGNAL(doubleClicked(QModelIndex)),
                     this , SLOT(slot_doubleClicked(QModelIndex)));

    setSortingEnabled(false);

    //------------------------------------------------------------


    tlbx->ui->chk_editable->setShortcut(Qt::Key_F2);

    qp::meta::cnct (tlbx->ui->chk_editable, SIGNAL(toggled(bool)),
                    this, SLOT(slot_editingEnabled_clicked(bool)));

    //------------------------------------------------------------

    tlbx->ui->chk_showRelExColumns->setVisible(false); // default

    tlbx->ui->chk_showRelExColumns->setShortcut(Qt::Key_F12);

    qp::meta::cnct (tlbx->ui->chk_showRelExColumns, SIGNAL(toggled(bool)),
                    this, SLOT(slot_setVisibleExRelIdColumns(bool)));

    //------------------------------------------------------------

    qp::meta::cnct (tlbx->ui->cmb_Strategy, SIGNAL(currentIndexChanged(int)),
                    this, SLOT(slot_editStrategyChange_clicked(int)));



    // ----------------------------------------------------------
    //                      SEARCHING
    // ----------------------------------------------------------

    find_settings.caseSensitive = false;
    find_settings.exactly = false;



    // ----------------------------------------------------------
    //                       SELECT_AND_CLOSE
    // ----------------------------------------------------------

    act_selectAndClose = new QAction(  QIcon(":/view/img/btn-db/selection.svg"),
                                       trUtf8("select and close window"), this);

    act_selectAndClose->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Return) );

    contextMenu->addAction(act_selectAndClose);

    addAction(act_selectAndClose);

    //tlbx->setFixedHeight(100);

    mainVl->addWidget( tlbx );



    setLayout( mainVl );

    act_selectAndClose->setVisible(true);

    ////tlbx->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Maximum);

    QFont font = QApplication::font();

    QFontMetrics fm(font);

    int hh = fm.height();

    QString emH1 = QString::number(hh);

    int toolBtnSz = hh*3;

    foreach( QToolButton * tlb , findChildren<QToolButton *>() )
    {
        tlb->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));

        tlb->setFixedSize(toolBtnSz , toolBtnSz);
    }
    setIconSize( QSize(toolBtnSz , toolBtnSz));
    //verticalHeader()->setMinimumHeight( toolBtnSz );
    //horizontalHeader()->setMinimumHeight( toolBtnSz );

    //    tlbx->ui->cmb_Strategy->setMaximumHeight(toolBtnSz);
    //    tlbx->ui->btn_submitAll->setMaximumHeight(toolBtnSz);


    // Мы здесь (в конструкторе ) еще не знаем редактирование включено или нет
    //set_behavoir( editable );

    verticalHeader()->setDefaultAlignment( Qt::AlignCenter);

    horizontalHeader()->setDefaultAlignment( Qt::AlignCenter);

    //verticalHeader()->setResizeMode(QpVertHeaderView::ResizeToContents); // влияет существенно

    //horizontalHeader()->setResizeMode(QpHorHeaderView::Interactive); // ResizeToContents не дает менять ширину

    installEventFilter( this ); // !!!

}

void QpTableViewWrapper::set_tlbx_visible(bool visible)
{
    tlbx->setVisible( visible);
}

void QpTableViewWrapper::set_editEnabledChkBoxVisible( bool visible)
{
    tlbx->ui->chk_editable->setVisible( visible);
}


void QpTableViewWrapper::set_searchingEnabled( bool On)
{
    search_wgts_visible = On;

    if( On )
    {
        // ----------------------------------------------------------
        //                       SEARCH BY TEXT
        // ----------------------------------------------------------

        if(act_search  == 0)
        {
            QIcon icn(":/view/img/btn-db/search.svg");

            act_search = new QAction( icn , trUtf8("search"), this);

            act_search->setShortcut(Qt::Key_F6);

            addAction(act_search);

            act_search->setVisible(On);

        }

        // ----------------------------------------------------------
        //                       SELECT_BY_FIELD_VALUE
        // ----------------------------------------------------------

        if(act_selectByFieldValue  == 0)
        {
            act_selectByFieldValue = new QAction( QIcon(":/view/img/btn-db/choice.svg"),
                                                  trUtf8("select by field value"),
                                                  this);

            act_selectByFieldValue->setShortcut(Qt::Key_F8);

            act_selectByFieldValue->setCheckable( true ); // !!! for triggered signal

            act_selectByFieldValue->setChecked(false);

            //qDebug() << ;

            qp::meta::cnct (act_selectByFieldValue, SIGNAL( triggered(bool)),
                            this, SLOT(slot_selectByFieldValue_Triggered(bool)));

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
            qp::meta::dis_cnct ( act_selectByFieldValue, SIGNAL(triggered(bool)),
                                 this, SLOT(slot_selectByFieldValue_Triggered(bool)));

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
void QpTableViewWrapper::slot_editStrategyChange_clicked(int strat)
{
    //qDebug()<< " QpTableViewWrapper::slot_editStrategyChanged_clicked " <<strat;

    QP_ASSERT( strat >= QSqlTableModel::OnFieldChange && strat <= QSqlTableModel::OnManualSubmit);

    Model()->setEditStrategy((QSqlTableModel::EditStrategy)strat);
}

void QpTableViewWrapper::set_editStrategyEnable(bool On , QSqlTableModel::EditStrategy def)
{

    // ----------------------------------------------------------
    //                       EDIT STRATEGY ENABLED
    // ----------------------------------------------------------

    tlbx->ui->btn_submitAll->setVisible(On);
    tlbx->ui->cmb_Strategy->setVisible(On);

    tlbx->ui->cmb_Strategy->setCurrentIndex(def);

}

void QpTableViewWrapper::set_ExtColumnsVisible(bool On , bool showExtCol_byDefault)
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

void QpTableViewWrapper::set_sortingEnabled(bool On)
{

    tlbx->ui->btn_sortEnabled->setVisible(On);

}

void QpTableViewWrapper::set_behavoir(bool editOn)
{
    // setting inertactive behavoir with combo boxes
    // this will be called from ctor and click check box (edit enable)

    set_repaintEditBtns( editOn , editOn , hideEditBtns); // On , On !!!

    set_SelectionModel( editOn );

    set_Edit_Triggers( editOn);




}

void QpTableViewWrapper::slot_editingEnabled_clicked(bool editOn) // from chk box toggled
{
    QModelIndex idx =  currentIndex();

    //qDebug() << " slot_editingEnabled_clicked " << editOn;

    //if( ! editOn )
    horizontalHeader()->setHighlightSections( editOn );

    Model()->set_editable( editOn ); // !!!!!

    set_behavoir( editOn);

    setCurrentIndex( idx ); // repaint selections

}

void QpTableViewWrapper::set_editingEnabled(bool On,
                                            bool defVisibleWithOn,
                                            bool hideBtns ) // from external code
{
    //qDebug() << " set_editingEnabled " << On << defVisibleWithOn << hideBtns;

    //editable = On;
    defaultEditOn = defVisibleWithOn;
    hideEditBtns = hideBtns;


    if( On && defVisibleWithOn)

        tlbx->ui->chk_editable->setChecked( true ); // !!!!

    else

        tlbx->ui->chk_editable->setChecked( false ); // !!!!


    Model()->set_editable( On ); // !!!!!

    if( ! On )
    {
        tlbx->ui->chk_editable->setVisible( false ); // !!!!
        tlbx->ui->chk_editable->setEnabled( false ); // !!!!

    }



}

void QpTableViewWrapper::set_SelectionModel( bool EditMode)
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

void QpTableViewWrapper::set_repaintEditBtns(bool On,
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

            QString file = ":view/img/btn-db/insert.svg";

            QP_ASSERT ( QFile::exists( file ) == true );

            QIcon icn( file );

            QP_ASSERT ( icn.isNull() == false );

            act_InsertRow = new QAction( icn , trUtf8("create row"), this);

            act_InsertRow->setShortcut(Qt::Key_Insert);

            qp::meta::cnct (act_InsertRow, SIGNAL(triggered()),
                            this, SLOT(slot_insertRowBtnClick()));

            qp::meta::cnct (tlbx->ui->btn_insert, SIGNAL(clicked()),
                            act_InsertRow, SLOT( trigger() ));

            contextMenu->addAction(act_InsertRow);

            addAction(act_InsertRow);


        }


        if(act_EditRow  == 0)
        {

            act_EditRow = new QAction( QIcon(":/view/img/btn-db/edit.svg") , trUtf8("edit row"), this);

            act_EditRow->setShortcut(Qt::Key_F4);

            qp::meta::cnct (act_EditRow, SIGNAL(triggered()), this, SLOT(slot_editRowBtnClick()));

            qp::meta::cnct (tlbx->ui->btn_edit, SIGNAL(clicked()), act_EditRow, SLOT( trigger() ));

            contextMenu->addAction(act_EditRow);

            addAction(act_EditRow);

        }

        // ----------------------------------------------------------
        //                       COPY_ROW
        // ----------------------------------------------------------

        if(act_CopyRow  == 0)
        {

            act_CopyRow = new QAction( QIcon(":/view/img/btn-db/copy.svg") , trUtf8("copy row"), this);

            act_CopyRow->setShortcut(Qt::Key_F9);

            qp::meta::cnct (act_CopyRow, SIGNAL(triggered()), this, SLOT(slot_copyRowBtnClick()));

            qp::meta::cnct (tlbx->ui->btn_copy, SIGNAL(clicked()), act_CopyRow, SLOT( trigger() ));

            contextMenu->addAction(act_CopyRow);

            addAction(act_CopyRow);


        }


        // ----------------------------------------------------------
        //                       DELETE_ROW
        // ----------------------------------------------------------


        if(act_DeleteRow  == 0)
        {

            act_DeleteRow = new QAction( QIcon(":/view/img/btn-db/remove.svg"),
                                         trUtf8("remove row"), this);

            act_DeleteRow->setShortcut(Qt::Key_Delete);

            qp::meta::cnct (act_DeleteRow, SIGNAL(triggered()), this, SLOT(slot_removeRowBtnClick()));

            qp::meta::cnct (tlbx->ui->btn_delete, SIGNAL(clicked()), act_DeleteRow, SLOT( trigger() ));

            contextMenu->addAction(act_DeleteRow);

            addAction(act_DeleteRow);


        }

        // ----------------------------------------------------------
        //                       CLEAR FIELD
        // ----------------------------------------------------------

        if(act_ClearField ==0)
        {
            act_ClearField = new QAction( QIcon(":/view/img/btn-db/clear_field.svg"),
                                          trUtf8("clear field"), this);

            act_ClearField->setShortcut(Qt::CTRL + Qt::Key_Backspace);

            qp::meta::cnct (act_ClearField, SIGNAL(triggered()), this, SLOT(slot_clearFieldClick()));

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
            qp::meta::dis_cnct (act_InsertRow, SIGNAL(triggered()), this, SLOT(slot_insertRowBtnClick()));

            qp::meta::dis_cnct (tlbx->ui->btn_insert, SIGNAL(clicked()), act_InsertRow, SLOT( trigger() ));

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
            qp::meta::dis_cnct (act_EditRow, SIGNAL(triggered()), this, SLOT(slot_editRowBtnClick()));

            qp::meta::dis_cnct (tlbx->ui->btn_edit, SIGNAL(clicked()), act_EditRow, SLOT( trigger() ));

            contextMenu->removeAction(act_EditRow);

            removeAction(act_EditRow);

            act_EditRow->setVisible(On);

            delete(act_EditRow);

            act_EditRow=0;
        }
        tlbx->ui->btn_edit->setEnabled(false);


        if(act_CopyRow  != 0)
        {

            qp::meta::dis_cnct (act_CopyRow, SIGNAL(triggered()), this, SLOT(slot_copyRowBtnClick()));

            qp::meta::dis_cnct (tlbx->ui->btn_copy, SIGNAL(clicked()), act_CopyRow, SLOT( trigger() ));

            contextMenu->removeAction(act_CopyRow);

            removeAction(act_CopyRow);

            act_CopyRow->setVisible(On);

            delete(act_CopyRow);

            act_CopyRow=0;
        }

        tlbx->ui->btn_copy->setEnabled(false);

        if(act_DeleteRow  != 0)
        {
            qp::meta::dis_cnct (act_DeleteRow, SIGNAL(triggered()), this, SLOT(slot_removeRowBtnClick()));

            qp::meta::dis_cnct (tlbx->ui->btn_delete, SIGNAL(clicked()), act_DeleteRow, SLOT( trigger() ));

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

            qp::meta::dis_cnct (act_ClearField, SIGNAL(triggered()), this, SLOT(slot_clearFieldClick()));

            contextMenu->removeAction(act_ClearField);

            removeAction(act_ClearField);

            delete act_ClearField;

            act_ClearField = 0;
        }



    }





}


//tlbx->ui->btn_edit->setEnabled(On);






QpTableViewWrapper::~QpTableViewWrapper()
{
    //qDebug() << "~QpTableViewWrapper()";

    delegts.clear();

}

void QpTableViewWrapper::setModel(QpSqlTableModel *newMdl)
{
    mdl = newMdl;

    set_behavoir( newMdl->editable );

    if( model() !=0 )
    {
        qp::meta::dis_cnct (model(), SIGNAL(sig_editStrategyChanged(QSqlTableModel::EditStrategy)),
                            this, SLOT(slot_editStrategyChanged(QSqlTableModel::EditStrategy)));

        qp::meta::dis_cnct (model(), SIGNAL(sig_rowIsDirty(int)),
                            this, SLOT(slot_rowIsDirty(int)));

        qp::meta::dis_cnct (model(), SIGNAL(sig_afterSelect( bool)),
                            this, SLOT(slot_afterSelect( bool )));

        qp::meta::dis_cnct (tlbx->ui->cmb_Strategy, SIGNAL(currentIndexChanged(int)),
                            this , SLOT(slot_cmb_Strategy_currentIndexChanged(int)));

    }

    QTableView::setModel( newMdl );

    if( ! qobject_cast<QpSqlTableModel*>( QTableView::model() ))
    {
        QMessageBox::warning( this ,
                              qp::dbg::error_,
                              tr("cast object error (43563565)"));
        return;
    }


    qp::meta::cnct (newMdl , SIGNAL(sig_editStrategyChanged(QSqlTableModel::EditStrategy)),
                    this, SLOT(slot_editStrategyChanged(QSqlTableModel::EditStrategy)));

    qp::meta::cnct (newMdl, SIGNAL(sig_rowIsDirty(int)),
                    this, SLOT(slot_rowIsDirty(int)));

    qp::meta::cnct (newMdl, SIGNAL(sig_afterSelect( bool)),
                    this, SLOT(slot_afterSelect( bool )));

    qp::meta::cnct (newMdl, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                    this, SLOT(slot_dataChanged( QModelIndex,QModelIndex )));

    qp::meta::cnct (newMdl, SIGNAL(beforeUpdate(int,QSqlRecord&)),
                    this, SLOT(slot_beforeUpdate(int,QSqlRecord&)));

    qp::meta::cnct (newMdl, SIGNAL(beforeInsert(QSqlRecord&)),
                    this, SLOT(slot_beforeInsert(QSqlRecord&)));

    qp::meta::cnct (tlbx->ui->cmb_Strategy, SIGNAL(currentIndexChanged(int)),
                    this , SLOT(slot_cmb_Strategy_currentIndexChanged(int)));


    tlbx->ui->cmb_Strategy->setCurrentIndex(newMdl->editStrategy());


}

void QpTableViewWrapper::slot_beforeInsert(QSqlRecord &record)
{

    //qDebug() << "slot_beforeInsert " << Model()->editStrategy();
    tlbx->ui->btn_submitAll->setEnabled(true);
}

void QpTableViewWrapper::slot_beforeUpdate(int row ,QSqlRecord&rec)
{

    if(Model()->editStrategy() == QSqlTableModel::OnRowChange)
    {
        //qDebug() << "slot_beforeUpdate OnRowChange";
        tlbx->ui->btn_submitAll->setEnabled(true);
    }
    else if(Model()->editStrategy() == QSqlTableModel::OnFieldChange)
        ;//qDebug() << "slot_beforeUpdate OnFieldChange";

}

void QpTableViewWrapper::slot_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    //qDebug() << "QpTableViewWrapper::slot_dataChanged  topLeft" <<topLeft << " bottomRight" <<bottomRight;

    //setDirtyRegion( );
    //delayed_Repaint();

    if(Model()->editStrategy() == QSqlTableModel::OnManualSubmit)
    {
        //qDebug() << "slot_dataChanged OnManualSubmit";
        tlbx->ui->btn_submitAll->setEnabled(true);
    }
}



QSize QpTableViewWrapper::sizeHint() const
{
    return QSize(200,500);
}

void QpTableViewWrapper::fillContextMenu()
{


}


void QpTableViewWrapper::slot_setVisibleExRelIdColumns(bool visible)
{

    showRelExColumns = visible;

    foreach(QString fldName, Model()->baseRec.specialFld.keys())
    {
        //qDebug() << "specialFld setColumnHidden " << fldName << ! showRelExColumns;

        if( Model()->baseRec.specialFld[ fldName ] !=  QpSqlRecord::CALC_FLD)
        {
            int Col = Model()->baseRec.indexOf( fldName );

            setColumnHidden( Col , ! showRelExColumns);
        }
    }

    QHashIterator<QString , QpColumnInfo> it(Model()->colInfo);

    while( it.hasNext() )
    {
        it.next();

        //qDebug() << "COLUMN_INFO: " << it.value();

        if( ! it.value().is_visible )

            setColumnHidden( mdl->baseRec.indexOf( it.key( ) ) , ! showRelExColumns);

    }

    if( Model()->getPriColumn() >=0)
        setColumnHidden( Model()->getPriColumn() , ! showRelExColumns);

    if( Model()->subAccountingFilter.count()>0 )
    {
        foreach( QString col, Model()->subAccountingFilter.keys())
        {
            //qDebug() << "col "<< col <<  Model()->baseRec.indexOf( col );
            setColumnHidden( Model()->baseRec.indexOf( col ) , ! visible );
        }
    }

    //resizeColumnsToContents();

}

void QpTableViewWrapper::set_contextMenuEnabled(bool On)
{
    contextMenuEnabled = On;
}

void QpTableViewWrapper::slot_CustomMenuRequested(const QPoint &pos)
{
    if( ! contextMenuEnabled )
        return;

    //qDebug() << "QpTableViewWrapper::slot_CustomMenuRequested";

    setContextMenuItemsVisibleAfterFieldSelected();

    contextMenu->popup(this->viewport()->mapToGlobal(pos));
}

void QpTableViewWrapper::setContextMenuEnabled( bool enabled)
{
    contextMenuEnabled = enabled;
}

void QpTableViewWrapper::setContextMenuItemsVisibleAfterFieldSelected()
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


    if( ! Model()->editable )
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


        if( col < Model()->baseRec.count() )
        {

            if( Model()->getRelIdColumn( col ) >= 0 )
            {
                QString str= Model()->data(Model()->index(row,col)).toString();

                if(str != "")
                {
                    //act_openRelRecord->setText(str);
                    //act_openRelRecord->setVisible(true);
                    //act_openRelRecord->setEnabled(true);
                }
            }
        }

    }
    else if( Model()->editable )       // форма редактируемая
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

        if( Model()->editable )
        {
            if( act_EditRow != 0)
                act_EditRow->setEnabled(true);

            if( act_DeleteRow != 0)
                act_DeleteRow->setEnabled(true);

            if( act_CopyRow != 0)
                act_CopyRow->setEnabled(true);

            if( act_InsertRow != 0)
                act_InsertRow->setEnabled(true);

            if(col < Model()->baseRecord().count())
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

bool QpTableViewWrapper::slot_clearFieldClick()
{

    QModelIndex currIdx = currentIndex();

    if( ! currIdx.isValid())
    {
        qCritical() << "QpTableViewWrapper::slot_clearField   currentIndex !isValid  " << currIdx;
        return false;
    }

    int col = currIdx.column();

    if (col == priCol)
        return false;



    return vrt_clearField(currIdx);

}

bool QpTableViewWrapper::vrt_clearField(const QModelIndex &idx)
{
    int col = idx.column();

    int row = idx.row();

    //qDebug() << QString("QpTableViewWrapper::slot_clearField   index [%1x%2]").arg(currIdx.row()).arg(currIdx.column());

    if( ! idx.isValid())
    {
        return false;
    }


    if ( Model()->isRelationalColumn( col ) )
    {
        return vrt_clearRelField( idx );
    }

    QVariant def;

    if(Model()->defaultVls.contains( col))

        def = Model()->defaultVls.value( col);

    return Model()->setData(idx , def);
}


bool QpTableViewWrapper::vrt_clearRelField(const QModelIndex &idx)
{
    int col = idx.column();

    int row = idx.row();

    if( ! idx.isValid())
    {
        return false;
    }

    if ( !  Model()->isRelationalColumn( col ) )

        return false;

    QString fldName = Model()->baseRec.fieldName( col );

    if(  fldName.isEmpty() )

        return false;

    // ------------------------------------------------------------------
    //                 first clear relation id field !
    // ------------------------------------------------------------------

    int extCol = Model()->getRelIdColumn( col );

    QModelIndex exIdx = Model()->index( row, extCol);

    if ( ! Model()->setData(exIdx , 0 ) ) // id field

        return false ;


    // ------------------------------------------------------------------
    //                  txt field has to clear
    // ------------------------------------------------------------------

    if( idx.isValid() ) // NOT submit/select
    {
        if( ! Model()->setData(idx , "")) // text
        {
            return false;
        }
    }

    // ------------------------------------------------------------------
    //                  sub accounting fields has to clear
    // ------------------------------------------------------------------

    if( idx.isValid() ) // NOT submit/select
    {
        if( Model()->subAccnt.contains( fldName ))
        {
            int subOnCol = Model()->getAccountingOnColumn( col );

            QP_ASSERT( subOnCol != -1);

            QModelIndex subOnColIdx = Model()->index( row, subOnCol );

            QP_ASSERT( subOnColIdx.isValid());

            if ( ! Model()->setData( subOnColIdx ,0) ) // sub on
            {
                return false;
            }
        }

    }

    if( Model()->subAccnt.contains( fldName ))
    {
        QString rel2FldName =  Model()->subAccnt.value( fldName ).fld2;

        int subCol = Model()->baseRec.indexOf( rel2FldName );

        QModelIndex subIdx = Model()->index( row , subCol );

        QP_ASSERT( subIdx.isValid() );

        return vrt_clearField( subIdx);

    }


    return true;
}
//-------------------------------------------------

bool QpTableViewWrapper::vrt_insertRow(int srcRow)
{
    qDebug() << "QpTableViewWrapper::vrt_insertRow("<<srcRow<<")";

    int newRow = Model()->rowCount();// forever insert at end

    if( ! Model()->insertRow(newRow))
    {
        qCritical() << "QpTableViewWrapper::insertRow ???? " ;
        return false;
    }

    Model()->isInsertRow = newRow;

    tlbx->ui->btn_submitAll->setEnabled(true); //

    setCurrentIndex( Model()->index( newRow , 0 ) );

    // better save row to db now but maybe this does later too

    emit sig_showSubmitBtn( true);

    return true;
}

bool QpTableViewWrapper::slot_insertRowBtnClick()
{

    qDebug() << "QpTableViewWrapper::slot_insertRowBtnClick()";
    bool needsToSubmit = false;

    QSqlTableModel::EditStrategy old = Model()->editStrategy();

    qDebug() << "QpTableViewWrapper::slot_insertRowBtnClick() old editStrategy() " << Model()->editStrategy();

    // ---------------------------------------------------
    // Important! with inserting a row we have immediately to submit for model strategy
    // OnFieldChange and OnFieldChange
    // ---------------------------------------------------

    if( old == QSqlTableModel::OnFieldChange )
    {
        // temporary set OnRowChange

        qDebug() << "     change editStrategy() QSqlTableModel::OnRowChange ";
        Model()->setEditStrategy(QSqlTableModel::OnRowChange); //!!!

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

        bool resSbmt = Model()->submit(); // !!!!!!!

        if ( ! resSbmt )
        {
            QMessageBox::critical(this ,
                                  "error" ,
                                  QString("submit returns  false\n"\
                                          "sql error: %1")
                                  .arg(Model()->lastError().text())
                                  );
        }

        qDebug() << "vrt_insertRow( "<<row <<" ) = " <<res<< " submit()="<<resSbmt ;

    }

    if( old == QSqlTableModel::OnFieldChange)

        Model()->setEditStrategy( QSqlTableModel::OnFieldChange ); // restore

    //updateGeometries();
    update();
    //delayed_Repaint();

    return res;
}



//-------------------------------------------------

bool QpTableViewWrapper::vrt_viewRow(int row)
{
    // this code you implement youself
    QMessageBox::warning(this,
                         qp::dbg::error_,
                         tr("Viewing a row."),
                         tr("You should implement this code yourself!")
                         );
    return false;
}

bool QpTableViewWrapper::slot_viewRowBtnClick()
{
    if( ! currentIndex().isValid())
        return false;


    emit sig_viewRow(currentIndex().row());
}

//-------------------------------------------------

int QpTableViewWrapper::restoreCurrentRowPositionAfterSubmit(int srcRow)
{
    QModelIndex priIdx = Model()->index( srcRow , Model()->getPriColumn());

    if(priIdx.isValid())
    {
        bool ok = false;

        int id = Model()->data(priIdx).toInt(&ok);

        if( ! ok)
            return -1;

        int foundRow = Model()->findRowById( id );

        if ( foundRow != -1)
        {
            return foundRow;
        }
    }

    return -1;
}

//-------------------------------------------------

bool QpTableViewWrapper::vrt_editRowDlg(int row)
{
    QMessageBox::warning(this,
                         qp::dbg::error_,
                         tr("You should realize this code yourself")
                         );

    return true;
}

bool QpTableViewWrapper::slot_editRowBtnClick()
{

    if(! currentIndex().isValid())
    {
        QMessageBox::warning(this ,
                             qp::dbg::warning ,
                             tr("before editing a line you should select it\ntable '%1'\nerror:%2").
                             arg(Model()->tableName()).
                             arg(Model()->lastError().text()));
        return false;
    }

    int row = currentIndex().row();

    bool rs = vrt_editRowDlg( row);

    return rs;

}
//------------------------------------------

bool QpTableViewWrapper::vrt_copyRow(int srcRow)
{

    int id = Model()->getRowPriValue( srcRow );

    if ( Model()->submit() && id >=0)
    {
        srcRow = Model()->findRowById(id);

        if(srcRow == -1)
        {
            QMessageBox::warning(this ,
                                 qp::dbg::error_ ,
                                 tr("copying row,\nneeds submit, after submit lost row focus,\ntable %1, error: %2").
                                 arg(Model()->tableName()).
                                 arg(Model()->lastError().text()));
            return false;
        }
    }

    int newRow = Model()->rowCount();

    QSqlRecord srcRec = Model()->record(srcRow);

    bool bb = Model()->insertRow( newRow );

    if( ! bb )
    {
        qCritical() << "QpTableViewWrapper::copyRow  insertRow ERROR : " << Model()->lastError().text();
        return false;
    }

    bool bbb = Model()->removePrimaryKeys_fromRec( srcRec, QpSqlTableModel::INSERT );

    bbb = Model()->setRecord( newRow , srcRec);

    if(Model()->editStrategy() == QSqlTableModel::OnManualSubmit)
    {
        emit sig_showSubmitBtn( true);
    }

    Model()->submit();

    return true;
}


// ---------------------------------------------------

bool QpTableViewWrapper::slot_copyRowBtnClick()
{
    int row = currentIndex().row();

    if( ! currentIndex().isValid())
    {
        QMessageBox::warning(this ,
                             qp::dbg::warning ,
                             tr("before copying a line you should select it\ntable '%1'\nerror:%2").
                             arg(Model()->tableName()).
                             arg(Model()->lastError().text()));
        return false;
    }

    bool bbb= vrt_copyRow(row);

    return bbb;
}
//-------------------------------------------------

bool QpTableViewWrapper::vrt_removeRow(int row)
{
    //qDebug() << "QpTableViewWrapper::removeRow : " << row << " rowCount() " << Model()->rowCount();

    if( Model()->isInsertRow != -1) //
    {
        bool bb = Model()->removeRow(Model()->isInsertRow);

        if( ! bb )
        {

            QMessageBox::warning(this ,
                                 qp::dbg::warning ,
                                 tr("before removing a line you should submit dirty row %2 \ntable '%1'\nerror:%3").
                                 arg(Model()->tableName()).
                                 arg(Model()->isInsertRow).
                                 arg(Model()->lastError().text()));
            return false;
        }
        Model()->isInsertRow = -1;

    }

    if(row >= Model()->rowCount() || row < 0)
        return false;

    bool bb = Model()->removeRow(row);

    if(bb)
    {
        //int col = config::get_defaultColumn( model());

        QModelIndex idx = Model()->index(row , 0);

        if(row < Model()->rowCount())
            if( idx.isValid())
                setCurrentIndex(idx );
    }

    return bb;

}

bool QpTableViewWrapper::slot_removeRowBtnClick()
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

/*void QpTableViewWrapper::set_chkEditable_isVisible(bool editOn)
        {
            tlbx->ui->chk_editable->setEnabled( editOn );


            //QpTableViewWrapper::ACTION act = QpTableViewWrapper::ACT_SWITCH_EDIT_ENABLED;

            //set_Actions(act , editOn);


            //slot_setEditable(editOn);

            // just in case
            //tlbx->ui->chk_editable->setVisible(true);

            //tlbx->ui->chk_editable->setEnabled(editOn);
        }*/

//-------------------------------------------------

void QpTableViewWrapper::setSelectAndClose()
{
    selectAndClose = true;

}

void QpTableViewWrapper::close()
{
    //qDebug() << "QpTableViewWrapper::close()";

}


bool QpTableViewWrapper::vrt_doubleClicked(const QModelIndex & idx_dblClk , bool &needsSubmitAfter)
{

    needsSubmitAfter = false;

    int col = idx_dblClk.column();
    int row = idx_dblClk.row();


    QString fldName = Model()->baseRec.fieldName( col );

    //qDebug() << "Model()->baseRec sdsds " << Model()->baseRec;
    if( fldName .isEmpty() )
        return false;

    int idCurrRow = Model()->getRowPriValue( row );

    if( ! Model()->editable )
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
    else if( Model()->editable )
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

    if( Model()->editStrategy() == QSqlTableModel::OnFieldChange)
    {
        QMessageBox::warning( this,
                              "error",
                              QString("you need to switch this model from OnFieldChange to OnRowChange (temporary)"));
        return false;
    }

    // ------------------------------------------------
    //          RELATION COLUMN
    // ------------------------------------------------


    if(Model()->isRelationalColumn( col ) ) // relations
    {

        QpSqlRelation relation = Model()->getRelationInfoForColumn( fldName );

        // ---------------------------------------------------------
        //  if is subaccounting presents but this toggled off
        // ---------------------------------------------------------

        if( Model()->rel_bindings.contains( fldName ) )
        {
            QpSubAccnt * subaccnt = Model()->rel_bindings[ fldName ];

            QString sub_on_fld_name = subaccnt->get_sub_on_fld_name();


            if( ! sub_on_fld_name.isEmpty() )
            {
                bool ok;

                int sub_on = Model()->data( Model()->index( row , Model()->baseRec.indexOf( sub_on_fld_name ))).toInt( );

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

        int relCol = Model()->baseRec.indexOf(relation.idField1Name);

        if( relCol == QpSqlRelation::COL_UNDEFINED)

            return false;

        // ------------------------------------------------
        //          GENERATE SUB ACCOUNTING FILTER
        // ------------------------------------------------

        QHash< QString , QVariant > Filter;

        if( Model()->rel_bindings.contains(fldName))
        {

            QpSubAccnt *subAccnt = Model()->rel_bindings.value( fldName );


            int parentCol =  Model()->baseRec.indexOf( subAccnt->fld1 );

            int relPrntIdCol = Model()->getRelIdColumn( parentCol );


            QP_ASSERT(relPrntIdCol != -1);


            QModelIndex prntIdx = Model()->index( row , relPrntIdCol);

            QVariant relPrntIdVal = Model()->data(prntIdx);

            QString fld = Model()->relations2[subAccnt->fld1].get_ext_fld_name();

            Filter.insert( fld, relPrntIdVal);


            //qDebug() << "Filter " << Filter;

        }

        // ------------------------------------------------
        //              OPEN DLG
        // ------------------------------------------------

        QpTableDlg dlg( relation.extTblName ,
                        Model()->database(),
                        Model()->callback_setting_mdl_func,
                        p_cb_setting_view,
                        this,
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
                                  qp::dbg::error_ ,
                                  tr("the choice is not defined"));
            return false;
        }

        QVariant txt = dlg.chosenRec.value(relation.dstFldName);

        //qDebug() << " dlg.chosenRec " << dlg.chosenRec;

        if(dlg.chosenId == -1)
        {
            QMessageBox::critical(this ,
                                  "error" ,
                                  tr("the choice is not defined"));
            return false;
        }

        if(! idx_dblClk.isValid() ) // just in time , submit occures
        {
            //qDebug() << " Model()->editStrategy() " << Model()->editStrategy();
            Q_ASSERT_X(idx_dblClk.isValid()==false,"464576576","43675465465");
        }

        QP_ASSERT(Model()->getRelIdColumn( col )>=0);

        QModelIndex extColIdx = Model()->index(row, Model()->getRelIdColumn( col ));

        if(  ! extColIdx.isValid())

            return false;


        if( Model()->editStrategy() >= QSqlTableModel::OnRowChange) // <=!!!
        {
            // ------------------------------------------------
            //         OnRowChange   OnManualSubmit !!!!
            // ------------------------------------------------


            // first time we set relExtIdCol

            if( ! Model()->setData( extColIdx , dlg.chosenId , Qt::EditRole))
            {
                QMessageBox::critical(this ,
                                      "error" ,
                                      tr(
                                          "setData returns  false\n"\
                                          "field : '%1'\n"\
                                          "value : '%2'\n"\
                                          "sql error: %3").
                                      arg(Model()->baseRec.fieldName(extColIdx.column())).
                                      arg(dlg.chosenId).
                                      arg(Model()->lastError().text())
                                      );

                return false;
            }


            needsSubmitAfter= true; //!!!!!!!!


            QVariant var =  Model()->data( extColIdx );

            if( ! extColIdx.isValid() || ! idx_dblClk.isValid() )
            {

                return false;
            }

            // submit not occures, it is OK, nothing more to do

            // -----------------------------------------------
            //          set text emulation field
            // -----------------------------------------------

            //qDebug() << "txt " << txt;

            if( ! Model()->setData( idx_dblClk , txt ,Qt::EditRole))
            {
                QMessageBox::critical(this ,
                                      "error" ,
                                      tr(
                                          "setData returns  false\n"\
                                          "field : '%1'\n"\
                                          "value : '%2'\n"\
                                          "sql error: %3").
                                      arg(Model()->baseRec.fieldName(extColIdx.column())).
                                      arg(dlg.chosenId).
                                      arg(Model()->lastError().text())
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

            if( Model()->isSubAccounting( fldName ))
            {
                // -----------------------------------------------
                //          set sub_on field true/false
                // -----------------------------------------------

                int subOnCol = Model()->getAccountingOnColumn( col );

                Q_ASSERT_X(subOnCol>=0, "65363565","8477857");

                QModelIndex subOnIdx = Model()->index( idx_dblClk.row() , subOnCol );

                if( ! subOnIdx.isValid())
                {
                    QMessageBox::critical(this ,
                                          "error" ,
                                          tr(
                                              "subOnIdx in not valid\n")
                                          );

                    return false;

                }

                QString fldName2 = Model()->baseRec.fieldName( col );

                if(fldName2.isEmpty())
                {
                    return false;
                }


                QString subOnFld_extTbl = Model()->subAccnt.value( fldName2 ).sub_on_fld_name_extTbl;


                if( ! dlg.chosenRec.contains( subOnFld_extTbl ))
                {

                    return false;
                }


                QVariant sub_on_val = dlg.chosenRec.value( subOnFld_extTbl );

                if( ! Model()->setData( subOnIdx , sub_on_val ,Qt::EditRole))
                {
                    QMessageBox::critical(this ,
                                          "error" ,
                                          tr(
                                              "setData returns  false\n"\
                                              "field : '%1'\n"\
                                              "value : '%2'\n"\
                                              "sql error: %3").
                                          arg(Model()->baseRec.fieldName(extColIdx.column())).
                                          arg(dlg.chosenId).
                                          arg(Model()->lastError().text())
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

            int checked = Model()->data( idx_dblClk , Qt::DisplayRole).toInt( &ok );

            if(checked == 0)
                checked = 1;
            else
                checked = 0;

            bool bbbb = Model()->setData( idx_dblClk , checked, Qt::EditRole );

            //qDebug() << "checked " << checked << " setData " << bbbb << Model()->editStrategy();

            needsSubmitAfter = true;

            return true;
        }


    }

    return false;

}

void QpTableViewWrapper::slot_doubleClicked(const QModelIndex & index)
{
    //qDebug() << "QpTableViewWrapper::slot_doubleClicked";


    bool needsRetTo_OnFieldChange = false;

    if( Model()->editStrategy() == QSqlTableModel::OnFieldChange)
    {
        // temporary set OnRowChange

        Model()->setEditStrategy(QSqlTableModel::OnRowChange); //!!!

        needsRetTo_OnFieldChange = true;
    }

    bool needsSubmitAfter;

    if ( vrt_doubleClicked( index , needsSubmitAfter ) )
    {

        if ( needsSubmitAfter )
        {
            bool submit_res = Model()->submit(); // !!!!!!!

            if ( ! submit_res )
            {
                QMessageBox::critical(this ,
                                      "error" ,
                                      QString("submit returns  false\n"\
                                              "sql error: %1")
                                      .arg(Model()->lastError().text())
                                      );
            }
        }

    }

    if(needsRetTo_OnFieldChange)

        Model()->setEditStrategy(QSqlTableModel::OnFieldChange); //!!!


}


bool QpTableViewWrapper::slot_searchInTable(const QString &txt)
{

    if( find_settings.searchedField == -1) //еще не понятно по какому полю искать
    {
        QMessageBox::warning(this , "error" , "please select a field than searched in table");

        return false;
    }

    int col = find_settings.searchedField;

    QString fieldName = Model()->baseRecord().fieldName(find_settings.searchedField);

    if(fieldName.isEmpty() || Model()->tableName().isEmpty())
    {
        qCritical("on_ledt_filter_returnPressed error");
        return false;
    }

    QP_ASSERT(find_settings.searchedField != qp::db::COL_UNDEFINED);

    QVariant::Type type = Model()->baseRec.field((int)find_settings.searchedField).type();

    //qDebug() << "QVariant::Type type : " << type;

    if (Model()->getRelIdColumn(  find_settings.searchedField ) != qp::db::COL_UNDEFINED )
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
            QString str = Model()->getRelationInfoForColumn(
                        Model()->baseRec.fieldName( find_settings.searchedField ) ).dstFldName;

            flt.append(QString::fromLatin1(" %3_%1.%2 ").
                       arg(col).
                       arg(str).
                       arg(Model()->prefix)
                       );
        }
        else
        {
            flt.append(Model()->tableName()+"."+fieldName);
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


    Model()->setFilter(flt); // select is into


    if(! flt.isEmpty() )
    {
        if( ! Model()->setHeaderData(col ,
                                     Qt::Horizontal,
                                     QIcon(":/view/img/btn-db/search.svg"), Qt::DecorationRole))

            QMessageBox::critical(this , "error" , "setHeaderData return false 6575637657");

        if(search_wgts_visible)
            tlbx->ui->wgt_search_block->setVisible(true);

        tlbx->ui->wgt_search_block->setEnabled(true);
        tlbx->ui->btn_clear_seached_text->setVisible(true);

    }
    else
    {
        Model()->setHeaderData(col , Qt::Horizontal, QVariant(), Qt::DecorationRole);

        if(search_wgts_visible)
            tlbx->ui->wgt_search_block->setVisible(true);

        tlbx->ui->btn_clear_seached_text->setVisible(false);


    }

    return true;
}

bool QpTableViewWrapper::prepare_view( QpSqlTableModel * mdl )
{
    if ( mdl->tableName().isEmpty() )
    {
        QMessageBox::warning(this,
                             qp::dbg::error_,
                             QString("Called prepare_view method but table model is not initialized "));

        return false;
    }


    setModel( mdl );

    qDebug() << " QpTableViewWrapper::prepare setting_view for table " <<  mdl->tableName()<< mdl->columnCount();

    if( p_cb_setting_view != 0 )
    {
        qDebug() << "call external function to configurate table view " << mdl->tableName();
        p_cb_setting_view( this ); // !!!!
    }

    return true;
}

void QpTableViewWrapper::set_viewEnabled( bool On)
{

    // ----------------------------------------------------------
    //                       VIEW
    // ----------------------------------------------------------

    tlbx->ui->btn_view->setVisible(On);

    if( On )
    {
        tlbx->ui->btn_view->setShortcut(Qt::Key_F3);

        qp::meta::cnct (tlbx->ui->btn_view, SIGNAL(clicked()), this, SLOT(slot_viewRowBtnClick()));

    }
    else if ( ! On )
    {
        tlbx->ui->btn_view->setShortcut(Qt::Key_unknown);

        qp::meta::dis_cnct (tlbx->ui->btn_view, SIGNAL(clicked()), this, SLOT(slot_viewRowBtnClick()));

    }

}


void QpTableViewWrapper::slot_selectByFieldValue_Triggered( bool set ) // set
{
    if( act_selectByFieldValue ==0 )

        return;



    if( ! set )
    {
        Model()->setFilter("");
        Model()->having.clear();

        bool bbb = Model()->select();

        act_selectByFieldValue->setChecked(false);

        tlbx->setBtn_selectByValue(true , false);

        act_selectByFieldValue->setIcon(QIcon(":/view/img/btn-db/choice_off.svg"));

        tlbx->ui->btn_selectByValue->setIcon(QIcon(":/view/img/btn-db/choice_off.svg"));

        // clear all icon from column headers

        for(int col=0; col < Model()->baseRec.count(); col++ )
        {
            if( Model()->headerData( col , Qt::Horizontal, Qt::DecorationRole).isValid() )
            {
                Model()->setHeaderData(col ,
                                       Qt::Horizontal,
                                       QVariant(),
                                       Qt::DecorationRole);
            }
        }

        return;

    }

    if( ! currentIndex().isValid())
        return;

    int col = currentIndex().column();

    if( slot_selectByFieldValue( currentIndex()))
    {
        if( ! Model()->filter().isEmpty()  || Model()->having.count() > 0)
        {
            tlbx->setBtn_selectByValue(true , true);

            act_selectByFieldValue->setChecked(true);

            act_selectByFieldValue->setIcon(QIcon(":/view/img/btn-db/choice.svg"));

            tlbx->ui->btn_selectByValue->setIcon(QIcon(":/view/img/btn-db/choice.svg"));


            bool bbb = Model()->setHeaderData( col ,
                                               Qt::Horizontal,
                                               QIcon(":/view/img/btn-db/choice.svg"),
                                               Qt::DecorationRole);
            //qDebug()<< bbb;

        }

        else
        {
            //QP_ASSERT(1==0);
        }
    }
}

//void QpTableViewWrapper::selectRow(int row)
//{
//    qDebug() << "QpTableViewWrapper::selectRow  emit sig_rowSelected " << row;
//    QTableView::selectRow( row);


//    //emit sig_rowSelected(row);
//}

void QpTableViewWrapper::setDefaultDelegate(int col)
{
    if( ! Model()->baseRec.field( col ).isValid() )
    {
        //        QMessageBox::warning(this ,
        //                             qp::dbg::error_ ,
        //                             tr("QpTableViewWrapper::setDefaultDelegate,\n"\
        //                                "table:%2,\ncolumn is out of range , field : %1")
        //                             .arg(col)
        //                             .arg(Model()->tableName())
        //                             );
        return;
    }

    QString fldName = Model()->baseRec.fieldName( col );

    if( delegts.contains( fldName ) )
    {
        QMessageBox::warning(this ,
                             qp::dbg::error_ ,
                             tr("second attempting adding QCheckBox to field : '%1'").arg( fldName ));

        return;
    }


    delegts.insert( fldName, new DefaultStyledItemDelegate( this ) );

    QStyledItemDelegate * delegate = delegts.value( fldName );
    //delegate->

    setItemDelegateForColumn( col , delegate); // is not important

}


void QpTableViewWrapper::setCheckBoxDelegate( const QString & fldName)
{
    if( ! Model()->baseRec.field( fldName ).isValid() )
    {
        QMessageBox::warning(this ,
                             qp::dbg::error_ ,
                             QString("column is out of range , field : %1")
                             .arg(fldName));
        return;
    }

    if(delegts.contains( fldName ))
    {
        QMessageBox::warning(this ,
                             qp::dbg::error_ ,
                             QString("second attempting adding QCheckBox to field : %1")
                             .arg(fldName));
        return;
    }


    delegts.insert( fldName , new checkBox_Delegate( this ) );

    QStyledItemDelegate * cmbDeleg = delegts.value( fldName );

    setItemDelegateForColumn( Model()->baseRec.indexOf( fldName ) , cmbDeleg);

}

void QpTableViewWrapper::setDoubleWithPrecision( const QString & fldName , int precision)
{
    if( ! Model()->baseRec.field( fldName ).isValid() )
    {
        QMessageBox::warning(this ,
                             qp::dbg::error_ ,
                             QString("column is out of range , field : %1")
                             .arg(fldName));
        return;
    }


    if(delegts.contains( fldName ))
    {
        QMessageBox::warning(this ,
                             qp::dbg::error_ ,
                             QString("second attempting adding QCheckBox to field : %1")
                             .arg(fldName));
        return;
    }


    delegts.insert( fldName , new DoubleDelegate( precision, this ) );

    QStyledItemDelegate * dblDeleg = delegts.value( fldName );

    setItemDelegateForColumn( Model()->baseRec.indexOf( fldName ) , dblDeleg);

}

void QpTableViewWrapper::setComboBoxDelegate(const QString & fldName, const QStringList &lst)
{
    if ( ! Model()->baseRec.field( fldName ).isValid() )
    {
        QMessageBox::warning(this ,
                             qp::dbg::error_ , QString("column is out of range , field : %1")
                             .arg(fldName));

        return;
    }

    if( delegts.contains( fldName ) )
    {
        QMessageBox::warning(this , qp::dbg::error_ , tr("second attempting adding QComboBox to field : %1")
                             .arg( fldName ));
        return;
    }


    delegts.insert( fldName ,
                    new ComboBoxDelegate( lst,
                                          this )
                    );

    QStyledItemDelegate * cmbDeleg = delegts.value( fldName );

    int col = Model()->baseRec.indexOf( fldName );


    setItemDelegateForColumn( col , cmbDeleg);

    Model()->defaultVls.insert( col , -1);

}

void QpTableViewWrapper::setComboBoxDelegate2(const QString & fldName, const QStringList &lst)
{
    if ( ! Model()->baseRec.field( fldName ).isValid() )
    {
        QMessageBox::warning(this ,
                             qp::dbg::error_ , QString("column is out of range , field : %1")
                             .arg(fldName));

        return;
    }

    if( delegts.contains( fldName ) )
    {
        QMessageBox::warning(this , qp::dbg::error_ , tr("second attempting adding QComboBox to field : %1")
                             .arg( fldName ));
        return;
    }


    delegts.insert( fldName ,
                    new ComboBoxDelegate2( lst,
                                           this )
                    );

    QStyledItemDelegate * cmbDeleg = delegts.value( fldName );

    int col = Model()->baseRec.indexOf( fldName );


    setItemDelegateForColumn( col , cmbDeleg);

    Model()->defaultVls.insert( col , -1);

}

void QpTableViewWrapper::setDateTimeDelegate(const QString & fldName)
{
    if( ! Model()->baseRec.field( fldName ).isValid() )
    {
        QMessageBox::warning(this ,
                             qp::dbg::error_ ,
                             tr("column is out of range , field : %1")
                             .arg(fldName));
        return;
    }

    int col = Model()->baseRec.indexOf( fldName );

    if(delegts.contains( fldName ))
    {
        QMessageBox::warning(this ,
                             qp::dbg::error_ ,
                             tr("second attempting add a date_Delegate to field : %1")
                             .arg( fldName ));
        return;
    }


    delegts.insert( fldName ,
                    new date_Delegate( 0 , this)
                    );


    setItemDelegateForColumn( col , delegts[fldName] );

}


bool QpTableViewWrapper::slot_selectByFieldValue(QModelIndex idx)
{
    //qDebug() << "QpTableViewWrapper::slot_selectByFieldValue idx " << idx;

    //    QMessageBox::warning( this ,
    //                          tr("...."),
    //                          tr("...."));

    if( ! idx.isValid() ) // clear filter by value
    {
        Model()->setFilter("");
        Model()->having.clear();

        act_selectByFieldValue->setChecked( false); // !!

    }
    else // set filter by value
    {
        int col = idx.column();
        int row = idx.row();

        QVariant val = Model()->data(idx);


        QString fldName = Model()->baseRecord().fieldName( col );

        //2qDebug()<< " slot_selectByFieldValue val :" << val<< "  fldName " <<fldName;

        if(fldName.isEmpty() || Model()->tableName().isEmpty())
        {
            qCritical() <<"error : fieldName is empty, i.e. is not detected";
            return false;
        }

        if( Model()->isRelationColumn( fldName ) ) // relation
        {
            QModelIndex exIdx = Model()->index(row , Model()->getRelIdColumn(col));

            val = Model()->data(exIdx);

            if( val.isNull())
                val=(int)0;

            Model()->having.clear();

            Model()->setFilter( fldName + "=" + Model()->sqlite_qoutes_for_value( val ) );


        }

        else if( Model()->isCalcColumn( fldName )  ) // CalcColumn
        {
            // ---------------------------------------------
            // do not use 'where',  jsut ues having
            // ---------------------------------------------

            //  "where" cannot be used on aggregate functions

            if(val.isNull())
                val=(int)0;

            Model()->having.clear();

            Model()->having.insert( fldName , Model()->sqlite_qoutes_for_value( val ) );


        }
        else
        {

            Model()->having.clear();

            Model()->setFilter( QString::fromLatin1("%1.%2=%3").
                                arg(Model()->tableName()).
                                arg(fldName)
                                .arg( Model()->sqlite_qoutes_for_value( val ) )) ;

        }

        act_selectByFieldValue->setChecked( true ); // !!

    }


    bool bb = Model()->select();

    return bb;
}

QpSqlTableModel* QpTableViewWrapper::Model() const
{
    return qobject_cast<QpSqlTableModel*>( QTableView::model() );
}


QAbstractItemModel* QpTableViewWrapper::model() const
{
    QAbstractItemModel * mdl = QTableView::model();

    return qobject_cast<QpSqlTableModel*>( mdl );
}

void QpTableViewWrapper::set_Edit_Triggers(bool editOn)
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

void QpTableViewWrapper::slot_setEditEnabled(bool editOn)
{

    set_editingEnabled( editOn );

    tlbx->ui->chk_editable->setVisible( true );

    //set_SelectionModel(); // !!

    set_Edit_Triggers( editOn);
}

void QpTableViewWrapper::slot_editStrategyChanged(QSqlTableModel::EditStrategy newStrategy)
{
    //qDebug() << "QpTableViewWrapper::slot_editStrategyChanged " << Model()->editStrategy() << " newStrategy " << newStrategy;

    if(tlbx->ui->cmb_Strategy->currentIndex() != newStrategy ) // setModel by programming
    {
        if( tlbx->ui->cmb_Strategy->isVisible() )
        {
            tlbx->ui->cmb_Strategy->setCurrentIndex(newStrategy);
        }
    }

}




void QpTableViewWrapper::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
    //qDebug() << "QpTableViewWrapper::rowsAboutToBeRemoved";

    int priCol = Model()->getPriColumn();

    for( int row = start; row <= end; row++ )
    {
        bool ok = false;

        int id = Model()->data(Model()->index( row, priCol)).toInt(&ok);

        if(! ok )
            continue;

        //qDebug() << "   row id " << id;// << " <> " << Model()->lastDirtyRowId;
    }

}

void QpTableViewWrapper::rowsInserted(const QModelIndex &parent, int start, int end)
{

    qDebug() << "QpTableViewWrapper::rowsInserted start/end " << start << end;

    int isPriIdRowFound = -1;
    int isRowFound = -1;

    QTableView::rowsInserted( parent , start, end);

    // start and end are line numbers

    if(Model()->lastDirtyRowId != -1)
    {
        int priCol = Model()->getPriColumn();

        for( int row = start; row <= end; row++ )
        {
            bool ok = false;

            int id = Model()->data( Model()->index( row, priCol)).toInt(&ok);

            if(! ok )
                continue;

            if( id == Model()->lastDirtyRowId)
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
        if(Model()->lastDirtyCol != -1)
            col = Model()->lastDirtyCol;

        setCurrentIndex( Model()->index( isRowFound , col));
        Model()->isSelectedLine = isRowFound;

        qDebug() << "   setCurrentIndex row id " << isPriIdRowFound << "  row " << isRowFound << " lastDirtyCol "<< Model()->lastDirtyCol << " isSelectedLine " <<Model()->isSelectedLine;
        //
    }
}

void QpTableViewWrapper::slot_cmb_Strategy_currentIndexChanged(int newStrategy)
{
    QSqlTableModel::EditStrategy strat = Model()->editStrategy();

    if(newStrategy != Model()->editStrategy())
    {
        Model()->submitAll();

        Model()->setEditStrategy((QSqlTableModel::EditStrategy)newStrategy);
    }

    if(newStrategy != Model()->editStrategy())
    {
        QMessageBox::warning( this ,
                              qp::dbg::error_,
                              tr("editStrategy dont settable"));
        //return;
    }

    //qDebug() << "slot_cmb_Strategy_currentIndexChanged model() " << model() << "editStrategy " <<Model()->editStrategy() << Model()->tableName();

    if(Model()->editStrategy() == QSqlTableModel::OnFieldChange)
    {
        tlbx->ui->btn_submitAll->setText(QpTableViewWrapper::s_submit);
        tlbx->ui->btn_submitAll->setEnabled(false);
    }
    else if(Model()->editStrategy() == QSqlTableModel::OnRowChange)
    {
        tlbx->ui->btn_submitAll->setText(QpTableViewWrapper::s_submit);
        tlbx->ui->btn_submitAll->setEnabled(false);
    }
    else if(Model()->editStrategy() == QSqlTableModel::OnManualSubmit)
    {
        tlbx->ui->btn_submitAll->setText(QpTableViewWrapper::s_submitAll);
        tlbx->ui->btn_submitAll->setEnabled(false);
    }

}


//void QpTableViewWrapper::reset()
//{
//    //qDebug() << "QpTableViewWrapper::reset() Model()->lastDirtyRowId " << Model()->lastDirtyRowId << Model()->tableName();

//    QTableView::reset();

//    //qDebug() << "QpTableViewWrapper::reset() styleSheet() = " << styleSheet();

//    // mdl maybe not init here
//}

void QpTableViewWrapper::slot_repaintSubmitBtn(bool enabled)
{
    if( tlbx->ui->cmb_Strategy->currentIndex() == QSqlTableModel::OnManualSubmit )

        tlbx->ui->btn_submitAll->setText(QpTableViewWrapper::s_submitAll);

    else

        tlbx->ui->btn_submitAll->setText(QpTableViewWrapper::s_submit);

    tlbx->ui->btn_submitAll->setEnabled(enabled);

}

void QpTableViewWrapper::slot_rowIsDirty(int row)
{
    //qDebug() << "   slot_rowIsDirty " << row;

    //setCurrentIndex(Model()->index( row , Model()->lastDirtyCol));


}

bool QpTableViewWrapper::vrt_afterSetFldValue(int idRow,
                                              const QString & fldName,
                                              const QModelIndex & idx,
                                              const QpSqlRecord &rec,
                                              bool &needsSubmitAfter)
{
    qDebug() << "QpTableViewWrapper::vrt_afterSetFldValue";

    if( Model()->isRelationColumn( fldName))
    {
        if( Model()->isSubAccounting( fldName ))
        {

            int row = idx.row();

            if ( ! idx.isValid())
            {
                row = Model()->findRowById(idRow);

                if(row == -1 && Model()->filter() == "")
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

            if( ! Model()->subAccnt.contains( fldName ) )

                return false;


            QString rel2ColName = Model()->subAccnt.value( fldName ).fld2;

            QP_ASSERT(rel2ColName.isEmpty()==false);

            int rel2Col = Model()->baseRec.indexOf( rel2ColName );

            QP_ASSERT( rel2Col >= 0 );

            QModelIndex rel2Idx = Model()->index( row , rel2Col );

            if( Model()->isSubAccountingOn_forFld( row, fldName ))
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

void QpTableViewWrapper::slot_afterSelect( bool ok)
{
    if( ! ok)

        return;

    emit sig_showSubmitBtn( false);

    if( ! showRelExColumns)
    {
        slot_setVisibleExRelIdColumns( showRelExColumns );
    }

    tlbx->ui->btn_submitAll->setEnabled(false);

    //qDebug() << "QpTableViewWrapper::slot_afterSelect";

    //resizeColumnsToContents();
}

void QpTableViewWrapper::setToLayout(QVBoxLayout * lo)
{
    if(lo->isEnabled())
    {
        lo->addWidget(tlbx);
        lo->addWidget(this);
    }
}

bool QpTableViewWrapper::edit(const QModelIndex &index, EditTrigger trigger, QEvent *event)
{
    return QTableView::edit( index, trigger, event);

}

bool QpTableViewWrapper::eventFilter( QObject *obj, QEvent *event)
{
    //qDebug() << "QpTableViewWrapper::eventFilter " << qp::db::toStr_Event_Type(event->type());

    QEvent::Type tt = event->type();

    if( tt == QEvent::Hide ) //  || tt == QEvent::Close || tt == QEvent::Quit )
    {
        //qDebug() << "QpTableViewWrapper::eventFilter " <<  qp::dbg::toStr_Event_Type( event->type() ) << " obj : " << obj->objectName();

        if( Model()->editStrategy() >= QSqlTableModel::OnRowChange )
        {
            if ( Model()->isDirtyRow != qp::db::ROW_UNDEFINED)
            {
                if( ! Model()->submitAll() )
                {
                    QMessageBox::warning( this,
                                          "error",
                                          QString("submitAll returns false [46556534565]")
                                          .arg(Model()->database().lastError().text()));
                }
            }
        }

    }

    bool bb = QTableView::eventFilter(obj , event);

    return bb;
}

void QpTableViewWrapper::closeEvent(QCloseEvent * evt)
{
    // -------------------------------------------
    //  not called, look to hide event
    // -------------------------------------------

    qDebug() << "QpTableViewWrapper::closeEvent ";

    if( Model()->isDirtyRow  != qp::db::ROW_UNDEFINED )
    {
        bool bbb = Model()->submit();
    }

    QTableView::closeEvent( evt );
}

void QpTableViewWrapper::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if( Model()->editStrategy() == QSqlTableModel::OnRowChange)
    {
        // -----------------------------------------------------------------------------------
        // this needs to call submit method whan current changed (dirty) row lost the focus
        // -----------------------------------------------------------------------------------

        qDebug() << "QpTableViewWrapper::currentChanged previous " << previous.row() << previous.column() << "  current row " << current.row() << " col " <<current.column();

        if( previous.row() != -1 && previous.row() != current.row())
        {
            bool to_submit = false;

            for(int col=0; col < Model()->baseRec.count(); col++)
            {
                const QString & fldName = Model()->baseRec.fieldName( col );

                if( Model()->baseRec.specialFld.contains( fldName )
                        && ( Model()->baseRec.specialFld[ fldName ] == QpSqlRecord::CALC_FLD
                             || Model()->baseRec.specialFld[ fldName ] == QpSqlRecord::SUBACCOUNT_ENABLE_FLD ))
                    continue;

                const QModelIndex idx = Model()->index( previous.row() , col );

                if( Model()->isDirty( idx ))
                {
                    qDebug() << "QpTableViewWrapper::currentChanged isDirty row : " << previous.row() << " col : " << col;
                    to_submit = true;
                }
            }

            if( to_submit )
            {

                if( ! Model()->submit() )
                {
                    QMessageBox::warning( this,
                                          "error",
                                          "submit() returns false [45633565]");
                }
            }
        }
    }
    QTableView::currentChanged( current , previous);

}

void QpTableViewWrapper::InitResources()
{
    Q_INIT_RESOURCE(resource2);
}

