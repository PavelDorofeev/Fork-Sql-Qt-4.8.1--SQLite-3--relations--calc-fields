#include "dbg_network.h"
#include <QNetworkReply>
#include <QMetaMethod>



const QString qp::dbg_ntw::toStr_QLocalSocket_Error(QLocalSocket::LocalSocketError err)
{
    switch(err)
    {
    case QLocalSocket::ConnectionRefusedError: return "ConnectionRefusedError";
    case QLocalSocket::PeerClosedError: return "PeerClosedError";
    case QLocalSocket::ServerNotFoundError: return "ServerNotFoundError";
    case QLocalSocket::SocketAccessError: return "SocketAccessError";
    case QLocalSocket::SocketResourceError: return "SocketResourceError";
    case QLocalSocket::SocketTimeoutError: return "SocketTimeoutError";
    case QLocalSocket::DatagramTooLargeError: return "DatagramTooLargeError";
    case QLocalSocket::ConnectionError: return "ConnectionError";
    case QLocalSocket::UnsupportedSocketOperationError: return "UnsupportedSocketOperationError";
    case QLocalSocket::UnknownSocketError: return "UnknownSocketError";
    default: return "Unknown QLocalSocket::LocalSocketError";
    }
}


const QString qp::dbg_ntw::toStr_NetworkError( int err)
{
    switch (err)
    {
    case QNetworkReply::ConnectionRefusedError:
        return "QNetworkReply::ConnectionRefusedError";

    case QNetworkReply::RemoteHostClosedError:
        return "QNetworkReply::RemoteHostClosedError";

    case QNetworkReply::HostNotFoundError:
        return "QNetworkReply::HostNotFoundError "+QObject::tr("(скореее всего нет выхода в  интернет)");

    case QNetworkReply::TimeoutError:
        return "QNetworkReply::TimeoutError";

    case QNetworkReply::OperationCanceledError:
        return "QNetworkReply::OperationCanceledError";

    case QNetworkReply::SslHandshakeFailedError:
        return "QNetworkReply::SslHandshakeFailedError";

    case QNetworkReply::TemporaryNetworkFailureError:
        return "QNetworkReply::TemporaryNetworkFailureError";

    case QNetworkReply::UnknownNetworkError:
        return "QNetworkReply::UnknownNetworkError "+QObject::tr("(скорее всего IP адрес в сети или порт указан(ы) неверно");

    case QNetworkReply::ProxyConnectionRefusedError:
        return "QNetworkReply::ProxyConnectionRefusedError";

    case QNetworkReply::ProxyConnectionClosedError:
        return "QNetworkReply::ProxyConnectionClosedError";

    case QNetworkReply::ProxyNotFoundError:
        return "QNetworkReply::ProxyNotFoundError";

    case QNetworkReply::ProxyTimeoutError:
        return "QNetworkReply::ProxyTimeoutError";

    case QNetworkReply::ProxyAuthenticationRequiredError:
        return "QNetworkReply::ProxyAuthenticationRequiredError";

    case QNetworkReply::UnknownProxyError:
        return "QNetworkReply::UnknownProxyError";

    case QNetworkReply::ContentAccessDenied:
        return "QNetworkReply::ContentAccessDenied";

    case QNetworkReply::ContentOperationNotPermittedError:
        return "QNetworkReply::ContentOperationNotPermittedError";

    case QNetworkReply::ContentNotFoundError:
        return "QNetworkReply::ContentNotFoundError";

    case QNetworkReply::AuthenticationRequiredError:
        return "QNetworkReply::AuthenticationRequiredError";

    case QNetworkReply::ContentReSendError:
        return "QNetworkReply::ContentReSendError";

    case QNetworkReply::UnknownContentError:
        return "QNetworkReply::UnknownContentError";

    case QNetworkReply::ProtocolUnknownError:
        return "QNetworkReply::ProtocolUnknownError";

    case QNetworkReply::ProtocolInvalidOperationError:
        return "QNetworkReply::ProtocolInvalidOperationError";

    case QNetworkReply::ProtocolFailure:
        return "QNetworkReply::ProtocolFailure";


    default:
        return "QNetworkReply:: unknown error number";
    }
};

