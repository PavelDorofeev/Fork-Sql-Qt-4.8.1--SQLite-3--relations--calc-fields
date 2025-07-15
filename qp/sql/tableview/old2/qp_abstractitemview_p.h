#ifndef QP_ABSTRACTITEMVIEW_P_H
#define QP_ABSTRACTITEMVIEW_P_H

#include "private/qabstractscrollarea_p.h"
#include "private/qabstractitemmodel_p.h"
#include "private/qabstractitemview_p.h"
#include "QtGui/qapplication.h"
#include "QtGui/qevent.h"
#include "QtGui/qmime.h"
#include "QtGui/qpainter.h"
#include "QtCore/qpair.h"
#include "QtGui/qregion.h"
#include "QtCore/qdebug.h"
#include "QtGui/qpainter.h"
#include "QtCore/qbasictimer.h"
#include "QtCore/qelapsedtimer.h"
#include <QAbstractItemModel>
#include <QAbstractItemView>

#ifndef QT_NO_ITEMVIEWS

QT_BEGIN_NAMESPACE


class Q_DECL_EXPORT QpAbstractItemViewPrivate : public QAbstractItemViewPrivate
{
    //Q_DECLARE_PUBLIC(QpAbstractItemView)

public:
    QpAbstractItemViewPrivate();

    virtual ~QpAbstractItemViewPrivate();

    //static const bool debug_timers;


};

//QT_BEGIN_INCLUDE_NAMESPACE
//#include <qvector.h>
//QT_END_INCLUDE_NAMESPACE


QT_END_NAMESPACE

#endif // QT_NO_ITEMVIEWS

#endif // QABSTRACTITEMVIEW_P_H
