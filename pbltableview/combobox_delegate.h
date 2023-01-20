#ifndef COMBOBOX_DELEGATE_H
#define COMBOBOX_DELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>
#include <QSqlTableModel>
#include <QItemDelegate>

//#include "db/pblsqlrelationaltablemodel_ex.h"
//#include "db/dll_db_global.h"
//#include "db1/table_description.h"

#include "pbltableview/PblSqlRelationalTableModel.h"

class ComboBoxDelegate  : public QStyledItemDelegate
{
    Q_OBJECT
public:


    explicit ComboBoxDelegate(PblSqlRelationalTableModel *mdl,
                              int column,
                              QStringList &lst,
                              QWidget *parent);


    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    QString displayText(const QVariant &value, const QLocale &locale) const ;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

protected:

public slots:
    void slot_currentIndexChanged(int pos);

private slots:
    //void slot_commitAndCloseEditor(int);

private:
    int col;
    QStringList lst;
    QComboBox *cmb;
    PblSqlRelationalTableModel *mdl;

};


#endif // COMBOBOX_DELEGATE_H
