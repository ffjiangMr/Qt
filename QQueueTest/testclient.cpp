#include "testclient.h"
#include <QThread>
#include <QDebug>
TestClient::TestClient()
{

}
void TestClient::Test()
{

    auto client = new QTcpSocket(nullptr);
    const QHostAddress address=QHostAddress(QObject::tr("127.0.0.1"));
    const unsigned short port=9988;
    //连接服务器
    connect(client, &QTcpSocket::connected, this, [&]{
        QByteArray buffer;
        QDataStream serial(&buffer, QIODevice::WriteOnly);
        QQueueDeviceInfo info(nullptr, QObject::tr("test device"),QQueueDeviceInfo::DeviceType::UNKNOW);
        QQueueDeviceMessage message(info);
        serial << message;
        client->write(buffer);
    });
    connect(client, &QTcpSocket::readyRead, this, [&]{
        QTcpSocket* socket = (QTcpSocket*)sender();
        //if (socket->canReadLine())
        {
            QByteArray message = socket->readAll();
            QDataStream stream(&message,QIODevice::ReadOnly);
            QQueueDeviceInfo* device = new QQueueDeviceInfo(socket, "", QQueueDeviceInfo::DeviceType::HOST);
            QQueueDeviceMessage outMsg(*device);
            stream >> outMsg;
            qDebug()<< outMsg.getMessage();
        }
    });
    connect(client, &QTcpSocket::disconnected, this, [&]{
        QTcpSocket* socket = (QTcpSocket*)sender();
        socket->deleteLater();
    });
    client->connectToHost(address,port);




}

