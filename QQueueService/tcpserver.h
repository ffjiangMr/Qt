#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include "./qtservice/src/qtservice.h"
#include "../QQueueUtility/qqueueabstractdevice.h"

class TcpServer :public QQueueAbstractDevice
{
    Q_OBJECT
public:
    TcpServer(quint16 port, QObject* parent = 0);

    QVector<QQueueDeviceInfo> getDeviceList() override;
    QQueueDeviceMessage readMessage() override;
    bool sendMessage() override;
    bool init() override;

    
private slots:
    void readClient();
    void discardClient();
    void incomingConnection(qintptr handle);
    
private:
    QVector<QQueueDeviceInfo>* deviceList;
    QTcpServer* server;

};

#endif // TCPSERVER_H
