#include <QCoreApplication>
#include "include/qqueuedevicedefinition.h"
#include <QByteArray>
#include <QDataStream>
#include <QIODevice>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QByteArray buffer;
    QDataStream serial(&buffer, QIODevice::WriteOnly);
    QQueueDeviceInfo info(QObject::tr("test device"),QQueueDeviceInfo::UNKNOW);
    info.setDeviceIndex(0);
    QQueueDeviceMessage message(info);
    message.setMessage(QObject::tr("test message"));
    serial << message;
    QDataStream readSerial(&buffer, QIODevice::ReadOnly);
    QQueueDeviceMessage outMsg(QQueueDeviceInfo(QObject::tr(""), QQueueDeviceInfo::UNKNOW));
    readSerial>> outMsg;

    return a.exec();
}
