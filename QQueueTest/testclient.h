#ifndef TESTCLIENT_H
#define TESTCLIENT_H

#include <QObject>
#include "include/qqueuedevicedefinition.h"
#include "include/qqueuemessage.h"
#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <QTcpSocket>
#include <QHostAddress>

class TestClient:QObject
{
    Q_OBJECT
public:
    TestClient();
    void Test();
};

#endif // TESTCLIENT_H
