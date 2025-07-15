/******************************************************************************
**
** Contact: BIT Ltd Company (p@kkmspb.ru) Individual Taxpayer Number (ITN Russia) 7826152874
**
** This file is not part of the Qt Sources.
** This is a little convenient fork of QTableView (Qt 4.8.1) version 4.0
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

#include "qp/sql/tableview/qp_abstractitemview.h"

#ifndef QT_NO_ITEMVIEWS


#include "qp/sql/tableview/qp_abstractitemview_p.h"
#include "qp/qp.h"
#include "qp/gui/qp_gui.h"


QT_BEGIN_NAMESPACE

//const bool QpAbstractItemView::debug_timers = false;
///const bool QpAbstractItemViewPrivate::debug_timers = false;


QpAbstractItemViewPrivate::QpAbstractItemViewPrivate()
    : QAbstractItemViewPrivate()
{

}

QpAbstractItemViewPrivate::~QpAbstractItemViewPrivate()
{


}
QpAbstractItemView::QpAbstractItemView( QWidget *parent)
    : QAbstractItemView( parent)
{

}

QpAbstractItemView::~QpAbstractItemView()
{

}

QModelIndex QpAbstractItemView::indexAt(const QPoint &point) const
{
    Q_ASSERT (1 == 0 );
    return QModelIndex();
}

QpAbstractItemView::QpAbstractItemView( QAbstractItemViewPrivate & , QWidget *parent)
    :
      QAbstractItemView( parent)
{

}


QT_END_NAMESPACE

#include "moc_qp_abstractitemview.cpp"

#endif // QT_NO_ITEMVIEWS
