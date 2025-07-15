#ifndef QP_DBG_NETWORK_H
#define QP_DBG_NETWORK_H

#include <QString>
#include <QWidget>
#include <QAbstractItemView>

#include <QEvent>
#include <QMessageBox>
#include <QDebug>
#include <QStyle>
#include <QProcess>
#include <QEvent>
#include <QNetworkReply>
#include <QFile>
#include <QLocalSocket>
#include <QObject>

#include "qp/ntw/dll_qp_ntw_global.h"

namespace qp
{

/*
  static when used in a function at namespace level means internal linkage.
*/

class LIB_PREFIX_QP_NTW dbg_ntw
{
public:

    dbg_ntw(){};

    static const QString toStr_QLocalSocket_Error(QLocalSocket::LocalSocketError err);


    static const QString toStr_NetworkError( int  err);

};
}

#endif // QP_DBG_H
