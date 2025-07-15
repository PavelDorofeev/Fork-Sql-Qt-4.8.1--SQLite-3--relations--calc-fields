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

#ifndef QP_ABSTRACTITEMVIEW_H
#define QP_ABSTRACTITEMVIEW_H

#include <QtGui/qabstractscrollarea.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtGui/qitemselectionmodel.h>
#include <QtGui/qabstractitemdelegate.h>
#include "qp/qp.h"
#include <QAbstractScrollArea>
#include <QAbstractItemView>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

#ifndef QT_NO_ITEMVIEWS

class QpAbstractItemViewPrivate;

class Q_DECL_EXPORT QpAbstractItemView : public QAbstractItemView
{
    Q_OBJECT

public:

    explicit QpAbstractItemView(QWidget *parent = 0);

    ~QpAbstractItemView();

    //static const bool debug_timers;

    virtual QModelIndex indexAt(const QPoint &point) const ;

protected:

    explicit QpAbstractItemView(QAbstractItemViewPrivate & , QWidget *parent = 0);

};

#endif // QT_NO_ITEMVIEWS

QT_END_NAMESPACE

QT_END_HEADER

#endif // QP_ABSTRACTITEMVIEW_H
