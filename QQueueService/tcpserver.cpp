#include "tcpserver.h"
#include <QDataStream>
#include <QDebug>
#include <QThread>

TcpServer::TcpServer(quint16 port, QObject* parent)
    :QQueueAbstractDevice(parent)
{
    this->deviceList = new  QVector<QQueueDeviceInfo*>();
    this->server = new QTcpServer(this);
    this->port = port;

}
TcpServer::~TcpServer()
{
    if(nullptr != this->deviceList)
    {
        for(auto info : *this->deviceList)
        {
            delete  info;
        }
        delete this->deviceList;
    }
    if(nullptr != this->server)
    {
        delete this->server;
    }
}


bool TcpServer::init()
{
    bool result = false;
    if( nullptr != this->server)
    {
        QObject::connect(this->server, &QTcpServer::newConnection,this, [this]{
            if(this->server->hasPendingConnections())
            {
                this->incomingConnection(this->server->nextPendingConnection());
            }
        });
        this->server->listen(QHostAddress::LocalHost, this->port);
        result = true;
    }
    return result;
}

void TcpServer::incomingConnection(QTcpSocket* client)
{
    QQueueDeviceInfo* info = new QQueueDeviceInfo(client, QObject::tr("TcpClient_") + QString::number(this->deviceList->length()),QQueueDeviceInfo::DeviceType::HOST);
    setDeviceIndex(*info, this->deviceList->length());
    setDeviceStatus(*info, QQueueDeviceInfo::DeviceStatus::CONNECTED);
    this->deviceList->append(info);
    connect(client, &QTcpSocket::readyRead, this, &TcpServer::readClient);
    connect(client, &QTcpSocket::disconnected, this, &TcpServer::discardClient);
   // QtServiceBase::instance()->logMessage("新的客户端链接");
}


void TcpServer::readClient()
{
    // This slot is called when the client sent data to the server. The
    // server looks if it was a get request and sends a very simple HTML
    // document back.
    QTcpSocket* socket = (QTcpSocket*)sender();
    //if (socket->canReadLine())
    {
        QByteArray message = socket->readAll();
        QDataStream stream(&message,QIODevice::ReadOnly);
        QQueueDeviceInfo* device = new QQueueDeviceInfo(socket, "", QQueueDeviceInfo::DeviceType::HOST);
        QQueueDeviceMessage outMsg(*device);
        stream >> outMsg;
        /// ToDo
        /// 处理接收到的数据
        /// 使用序列化与反序列化进行消息处理
    }
}
void TcpServer::discardClient()
{
    QTcpSocket* socket = (QTcpSocket*)sender();
    for(auto& client : *this->deviceList)
    {
        QTcpSocket* sock = static_cast<QTcpSocket*>(const_cast<QObject*>(client->getDevice().data()));
        if(sock == socket)
        {
            this->deviceList->removeOne(client);
        }
    }
    socket->deleteLater();
    //QtServiceBase::instance()->logMessage("Connection closed");
}

QVector<QQueueDeviceInfo> TcpServer::getDeviceList()
{
    QVector<QQueueDeviceInfo>  temp;
    return temp;
}
QQueueDeviceMessage TcpServer::readMessage()
{
    QQueueDeviceMessage  temp(*this->deviceList->at(0));
    return temp;
}

bool TcpServer::sendMessage()
{
    QByteArray buffer;
    QDataStream serial(&buffer, QIODevice::WriteOnly);
    QQueueDeviceInfo info(nullptr, QObject::tr("test device"),QQueueDeviceInfo::DeviceType::UNKNOW);
    this->setDeviceIndex(info,0);
    QQueueDeviceMessage message(info);
    this->setMessage(message,QObject::tr("test message"));
    serial << message;
    for(auto client : *this->deviceList)
    {
        QTcpSocket* sock = static_cast<QTcpSocket*>(client->getDevice().data());
        sock->write(buffer);
        QThread::sleep(10);
    }
    return false;
}
