#ifndef QP_NETWORKACCESSMANAGER_H
#define QP_NETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>

#include "qp/ntw/dll_qp_ntw_global.h"

class LIB_PREFIX_QP_NTW QpNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit QpNetworkAccessManager(QObject *parent = 0);
    
signals:
    
public slots:
    void slot_sslErrors(QNetworkReply* reply, QList<QSslError> list);
};

#endif // QP_NETWORKACCESSMANAGER_H
