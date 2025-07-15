#include "qp_networkaccessmanager.h"

#include "qp/core/qp_core.h"
#include <QDebug>

QpNetworkAccessManager::QpNetworkAccessManager(QObject *parent) :
    QNetworkAccessManager(parent)
{

    qp::meta::cnct( this, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
                   this, SLOT(slot_sslErrors(QNetworkReply*,QList<QSslError>)));

}



void QpNetworkAccessManager::slot_sslErrors(QNetworkReply* reply, QList<QSslError> list)
{

    reply->ignoreSslErrors();

    foreach(QSslError err, list)
    {
        qWarning()<<"sslErrors : " << err.errorString();

        //QSslCertificate cert=err.certificate();
        //qWarning()<<"   cert version : " << cert.version();
        //qWarning()<<"   cert serialNumber : " << cert.serialNumber();
        //qWarning()<<"   cert serialNumber : " << cert.serialNumber();
        //QSslKey publicKey=cert.publicKey();
        //qWarning()<<"   cert publicKey : " << publicKey.type()<< " length : " << publicKey.length();
        //QDateTime expiryDate=cert.expiryDate();
        //qWarning()<<"   cert expiryDate : " << expiryDate.toString();

    }


}
