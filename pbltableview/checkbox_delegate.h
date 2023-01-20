#ifndef CHECKBOX_DELEGATE_H
#define CHECKBOX_DELEGATE_H

#include <QStyledItemDelegate>
#include <QCheckBox>
#include "pbltableview/PblSqlRelationalTableModel.h"

class checkBox_Delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit checkBox_Delegate(PblSqlRelationalTableModel * Mdl,
                               QWidget *parent = 0);

    ~checkBox_Delegate();
    
    /*bool editorEvent(QEvent *event,
                     QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index);*/

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void paint(QPainter *painter,
                  const QStyleOptionViewItem &option,
                  const QModelIndex &index) const;

signals:

public slots:

private:
    PblSqlRelationalTableModel * mdl;
};

#endif // CHECKBOX_DELEGATE_H
