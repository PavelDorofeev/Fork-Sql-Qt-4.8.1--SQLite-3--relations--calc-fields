#ifndef QCOMBOBOX2_H
#define QCOMBOBOX2_H

#include <QComboBox>
#include <QList>
#include <QHash>
#include <QPair>
#include <QVariantList>

#include "qp/gui/dll_qp_gui_global.h"
class LIB_PREFIX_QP_GUI QComboBox2 : public QComboBox
{
    Q_OBJECT
public:
    explicit QComboBox2( const QVariantList &lst, QWidget *parent = 0);
    
    QVariantList lst;

    QList< QPair < int , QString > > pair_lst;

    QHash<int,int> hashLst;
    QHash<int,int> hashLst2;

    void setCurrentIndex(int index);

    int currentIndex();

signals:
    
public slots:
    
};

#endif // QCOMBOBOX2_H
