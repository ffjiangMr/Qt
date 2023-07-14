#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
//#include "./qtservice/src/qtservice.h"
#include "../QQueueUtility/qqueueabstractdevice.h"

class TcpServer :public QQueueAbstractDevice
{
    Q_OBJECT
public:
    TcpServer(quint16 port, QObject* parent = 0);
    ~TcpServer();

    QVector<QQueueDeviceInfo> getDeviceList() override;
    QQueueDeviceMessage readMessage() override;
    bool sendMessage() override;
    bool init() override;

    
private slots:
    void readClient();
    void discardClient();
    void incomingConnection(QTcpSocket* client);
    
private:
    QVector<QQueueDeviceInfo*>* deviceList;
    QTcpServer* server;
    quint16 port;

};

#endif // TCPSERVER_H
