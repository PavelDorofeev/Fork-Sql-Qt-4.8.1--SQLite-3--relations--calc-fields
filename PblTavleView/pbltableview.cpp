#include "pbltableview.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QDebug>
#include "some_tests.h"
#include "PblSqlRelationalTableModel.h"
#include <QSqlError>
#include "btntoolbox.h"
#include <QSqlDatabase>
#include <QSqlIndex>
#include "table_dlg.h"


PblTableView::PblTableView(PblSqlRelationalTableModel * mdl_,
                           QVBoxLayout * lo,
                           QWidget *parent,
                           bool editable) :
    QTableView(parent),
    priCol(-1),
    editable(false)
{

    mdl = mdl_;

    setSelectionMode(QAbstractItemView::SingleSelection);

    setModel(mdl);

    primaryIndex = mdl->database().primaryIndex(mdl->tableName());

    qDebug() << "primaryIndex " <<primaryIndex;

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



    tlbx = new BtnToolBox(this , mdl);

    lo->addWidget(tlbx);
    lo->addWidget(this);

    QSqlRecord baseRec = mdl->baseRecord();
    QSqlRecord rec = mdl->record();

    qDebug() << " mdl->columnCount() " << mdl->columnCount() << baseRec.count();

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
            mdl->setHeaderData(col, Qt::Horizontal, baseRec.fieldName(col));

            if(searchedRelationTxtDefaultColumn == -1)
                searchedRelationTxtDefaultColumn= col;

        }
        else if(rec.field(col).type() == QVariant::String
                && searchedTxtDefaultColumn == -1)
        {
            searchedTxtDefaultColumn = col;
        }
        else if((
                    rec.field(col).type() == QVariant::Double
                    || rec.field(col).type() == QVariant::Int)
                && searchedDblDefaultColumn == -1)
        {
            searchedDblDefaultColumn = col;
        }
        qDebug() << "col " <<col << baseRec.fieldName(col);

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



    find_settings.caseSensitive = false;
    find_settings.exactly = false;


    setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);

    verticalHeader()->setVisible(false);

    /*_CONNECT_( this , SIGNAL(pressed(QModelIndex)),
               this , SLOT(slot_pressed(QModelIndex)));*/

    _CONNECT_( this , SIGNAL(doubleClicked(QModelIndex)),
               this , SLOT(slot_doubleClicked(QModelIndex)));

    tlbx->setEditable(editable);

    resizeRowsToContents();
    resizeColumnsToContents();

}

QSize PblTableView::sizeHint() const
{
    //setVerticalScrollMode(false);
    //qDebug() << " viewport()->size() " << viewport()->size();
    //qDebug() << "   size() " << size();
    //qDebug() << "   horizontalPolicy() " << sizePolicy().horizontalPolicy();
    //qDebug() << "   verticalPolicy() " << sizePolicy().verticalPolicy();


    //return size();

    //QSize sz = QTableView::sizeHint()+QSize(200,100);

    //qDebug() << "sizeHint " << QTableView::sizeHint() << " sz " << sz ;

    return QSize(700,500);
}

void PblTableView::fillContextMenu()
{
    contextMenu->clear();


    // ---------------------------------------------------------------

    act_InsertRow = new QAction( QIcon(":icon/img/btn-db/insert-100x100.png") , trUtf8("новая строка"), this);
    act_InsertRow->setShortcut(Qt::Key_Insert);

    _CONNECT_(act_InsertRow, SIGNAL(triggered()), this, SLOT(slot_insertRowBtnClick()));

    contextMenu->addAction(act_InsertRow);
    addAction(act_InsertRow);

    contextMenu->addSeparator();

    // ---------------------------------------------------------------

    act_CopyRow = new QAction( QIcon(":icon/img/btn-db/copy-100x100.png") , trUtf8("копировать строку"), this);
    act_CopyRow->setShortcut(Qt::Key_F9);

    _CONNECT_(act_CopyRow, SIGNAL(triggered()), this, SLOT(slot_copyRowBtnClick()));

    contextMenu->addAction(act_CopyRow);
    addAction(act_CopyRow);

    // ---------------------------------------------------------------

    act_EditRow = new QAction( QIcon(":icon/img/btn-db/edit-100x100.png") , trUtf8("редактировать строку"), this );
    act_EditRow->setShortcut(Qt::Key_F4);

    _CONNECT_(act_EditRow, SIGNAL(triggered()), this, SLOT(slot_editRowBtnClick()));

    contextMenu->addAction(act_EditRow);
    addAction(act_EditRow);

    // ---------------------------------------------------------------

    act_DeleteRow = new QAction(QIcon(":icon/img/btn-db/delete-100x100.png"), trUtf8("удалить строку"), this);
    act_DeleteRow->setShortcut(Qt::Key_Delete);

    _CONNECT_(act_DeleteRow, SIGNAL(triggered()), this, SLOT(slot_removeRowBtnClick()));

    contextMenu->addAction(act_DeleteRow);
    addAction(act_DeleteRow);

    // ---------------------------------------------------------------

    act_choiseCurrentRecord = new QAction(trUtf8("выбрать строку"), this);
    act_choiseCurrentRecord->setShortcut(Qt::Key_Enter);

    if( formMode & FM_ROW_WILL_BE_CHOSEN)
        contextMenu->addAction(act_choiseCurrentRecord);

    // -------------------------------------------------------

    contextMenu->addSeparator();

    act_ClearField = new QAction(QIcon(":icon/img/btn-db/clear-field-100x100.png"), trUtf8("очистить поле"), this);

    _CONNECT_(act_ClearField, SIGNAL(triggered()), this, SLOT(slot_clearFieldClick()));

    contextMenu->addAction(act_ClearField);

    // ---------------------------------------------------------------

    act_selectByFieldValue = new QAction(QIcon(":icon/img/btn-db/select-by-value-2-100x100.png"), trUtf8("отбор по значению"), this);
    act_selectByFieldValue->setShortcut(Qt::Key_F12);

    _CONNECT_(act_selectByFieldValue, SIGNAL(triggered()), this, SLOT(slot_clickSelectByFieldValue()));

    contextMenu->addAction(act_selectByFieldValue);


}
void PblTableView::slot_CustomMenuRequested(const QPoint &pos)
{
    //qDebug() << "my_QTableView::slot_CustomMenuRequested";

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
    act_selectByFieldValue->setEnabled(true);

}

bool PblTableView::slot_clearFieldClick()
{
    qDebug() << "my_QTableView::slotClearField";

    QModelIndex currIdx = currentIndex();

    if( ! currIdx.isValid())
    {
        qDebug() << "my_QTableView::slot_clearField   currentIndex !isValid  " << currIdx;
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

    qDebug() << "clearField " << mdl->record(row);

    qDebug() << QString("my_QTableView::slot_clearField   index [%1x%2]").arg(currIdx.row()).arg(currIdx.column());

    if(! currIdx.isValid())
    {
        qWarning()<<"!!!! error  my_QTableView::slot_clearField ! index.isValid()";
        return false;
    }

    QModelIndex idx= mdl->index(currIdx.row(),currIdx.column());

    if(! idx.isValid())
    {
        qCritical()<<"!!!! error  my_QTableView::slot_clearField ! idx.isValid()";
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
    qDebug() << "PblTableView::insertRow()";

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
                    qCritical() << "my_QTableView::my_insertRow  setData : " << def ;
                }
                else
                    qDebug() << "   my_insertRow  setData : true for col " << col ;
        }
    }

    /*if( ! mdl_->submit()) // тут не надо делать submit,
                // submit при setData в соответсвии с моделью данных
                {
                    sig_messageDlg(tr("Ошибка операции добавления строки") ,tr("Добаление строки завершилось неуспешно..."));
                    return;
              }
        */

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
        if ( mdl->record().field(col).isAutoValue() ) // dont work
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
            QMessageBox::warning(this , tr("warning") , tr("такого не должно быть\n копирование строки\nsubmit при OnRowChange должен быть true"));

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


void PblTableView::slot_doubleClicked(QModelIndex index)
{

    qDebug() << "slot_doubleClicked" << mdl->tableName();
    if( ! editable) // chosing
    {
        emit sig_line_is_chosen(index);
        return;
    }

    int col = index.column();

    if(mdl->getRelIdColumn( col) >=0 ) // relations
    {
        PblColumn inf = mdl->getRelationInfoForColumn(col);

        if( ! inf.isValid())
            return;


        Table_Dlg dlg = Table_Dlg("goods" , this);

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
        //on_btn_find_clicked();
        return false;
    }

    QString fieldName = mdl->record().fieldName(find_settings.searchedField);

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

        if( find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_TEXT
                && ! find_settings.caseSensitive)
        {
            filter.append(" lower("+mdl->tableName()+"."+fieldName+")");
        }
        else if(find_settings.seachType == Search_Settings_Dlg::FIND_SETTINGS::SEARCH_RELATION_TEXT)
        {
            int col = find_settings.searchedField;
            QString str = mdl->getRelationInfoForColumn(find_settings.searchedField).exTextFieldName;

            filter.append(QString::fromLatin1(" relTblAl_%1.%2 ").
                          arg(col).
                          arg(str));
        }
        else
        {
            filter.append(mdl->tableName()+"."+fieldName);
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

    return mdl->select();
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
void PblTableView::slot_pressed(QModelIndex index)
{
    qDebug() << "PblTableView::slot_pressed " << index;

    if( ! index.isValid())
        return;

    if(editable)
        return;

    //emit sig_accept(index);

}

bool PblTableView::slot_clickSelectByFieldValue()
{
    qDebug() << "PblTableView::slot_clickSelectByFieldValue " << currentIndex();

    if( ! currentIndex().isValid())
        return false;

    QModelIndex idx = currentIndex();

    int col = idx.column();
    int row = idx.row();

    QVariant val = mdl->data(idx);

    QString fieldName = mdl->baseRecord().field(col).name();

    if(fieldName.isEmpty() || mdl->tableName().isEmpty())
    {
        qCritical() <<"error : fieldName is empty, i.e. is not detected";
        return false;
    }

    if(mdl->getRelIdColumn(col) >=0) // relation
    {
        QModelIndex exIdx = mdl->index(row , mdl->getRelIdColumn(col));
        val = mdl->data(exIdx);
        if(val.isNull())
            val=(int)0;
    }


    QString filter("");
    QString strVal;

    if(val.type() == QVariant::String)
        strVal = val.toString().prepend("'").append("'");
    else
        strVal = val.toString();

    filter.append(QString::fromLatin1(" %1.%2=%3 ").
                  arg(mdl->tableName()).
                  arg(fieldName).
                  arg(strVal));


    mdl->setFilter(filter);

    bool bb = mdl->select();

    if( bb)
        tlbx->setSelectionByValue(bb);

    return bb;

}

