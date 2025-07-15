#ifndef TREE_COLUMN_COMPOSIZE_DELEGATE_H
#define TREE_COLUMN_COMPOSIZE_DELEGATE_H

#include <QStyledItemDelegate>
#include <QWidget>
#include <QHash>
#include <QMetaType>
#include <tag_value.h>
#include "a_kkt.h"

class TreeColumnCompositeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:

    explicit TreeColumnCompositeDelegate( const QMap<int, Tag_Value> &map,
                                QWidget *parent = 0);
    
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

    QString displayText(const QVariant &value, const QLocale &locale) const ;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

signals:
    
public slots:

private:

    QHash<int,QWidget*> wgt;

    QList< QPair < int , QString > > pair_lst;

    QHash<int,int> hashLst;
    QWidget* parent_;

    QAbstractItemModel* mdl;
    
};

#endif // TREE_COLUMN_COMPOSIZE_DELEGATE_H
