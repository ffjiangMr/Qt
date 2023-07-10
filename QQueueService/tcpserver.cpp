#include "tcpserver.h"

TcpServer::TcpServer(quint16 port, QObject* parent)
    :QTcpServer(parent), disabled(false)
{
    listen(QHostAddress::LocalHost, port);
}

void TcpServer::incomingConnection(int socket)
{
    if (disabled)
        return;

    // When a new client connects, the server constructs a QTcpSocket and all
    // communication with the client is done over this QTcpSocket. QTcpSocket
    // works asynchronously, this means that all the communication is done
    // in the two slots readClient() and discardClient().
    QTcpSocket* client = new QTcpSocket(this);
    connect(client, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(client, SIGNAL(disconnected()), this, SLOT(discardClient()));
    client->setSocketDescriptor(socket);
    QtServiceBase::instance()->logMessage("新的客户端链接");
}

void TcpServer::pause()
{
    disabled = true;
}

void TcpServer::resume()
{
    disabled = false;
}

void TcpServer::readClient()
{
    if (disabled)
        return;

    // This slot is called when the client sent data to the server. The
    // server looks if it was a get request and sends a very simple HTML
    // document back.
    QTcpSocket* socket = (QTcpSocket*)sender();
    if (socket->canReadLine()) {
        QByteArray message = socket->readAll();
        /// ToDo
        /// 处理接收到的数据
        /// 使用序列化与反序列化进行消息处理
    }
}
void TcpServer::discardClient()
{
    QTcpSocket* socket = (QTcpSocket*)sender();
    socket->deleteLater();

    QtServiceBase::instance()->logMessage("Connection closed");
}
