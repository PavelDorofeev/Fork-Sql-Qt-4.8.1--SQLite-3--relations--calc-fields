#ifndef DOUBLEDELEGATE_H
#define DOUBLEDELEGATE_H

#include <QStyledItemDelegate>
#include "pblsqlrelationaltablemodel.h"


class DoubleDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:

    explicit DoubleDelegate(PblSqlRelationalTableModel *mdl, QObject *parent = 0);

   virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;


signals:
    
public slots:

private:
    PblSqlRelationalTableModel *mdl;
    
};

#endif // DOUBLEDELEGATE_H
