#ifndef DOUBLEDELEGATE_H
#define DOUBLEDELEGATE_H

#include <QStyledItemDelegate>


class Q_DECL_EXPORT DoubleDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:

    explicit DoubleDelegate( int Precision,
                             QObject *parent = 0);

   virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;


signals:
    
public slots:

private:
    int precision;
    
};

#endif // DOUBLEDELEGATE_H
