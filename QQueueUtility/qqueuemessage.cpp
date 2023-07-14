#include "qqueuemessage.h"


/// QQueueDeviceMessage
QQueueDeviceMessage::QQueueDeviceMessage(const QQueueDeviceMessage& entity)
{
    this->deviceInfo = new QQueueDeviceInfo(*entity.deviceInfo);
    this->message = entity.message;
}

QQueueDeviceMessage& QQueueDeviceMessage::operator=(const QQueueDeviceMessage& entity)
{
    if(this != &entity)
    {
        delete this->deviceInfo;
        this->message = entity.message;
        this->deviceInfo = new QQueueDeviceInfo(*entity.deviceInfo);
    }
    return *this;
}

QQueueDeviceMessage::QQueueDeviceMessage(const QQueueDeviceInfo& info)
{
    this->deviceInfo = new QQueueDeviceInfo(info);
    this->message = "";
}

QQueueDeviceMessage::~QQueueDeviceMessage()
{
    delete  this->deviceInfo;
}

void QQueueDeviceMessage::setMessage(const QString& msg)
{
    this->message = msg;
}

QString QQueueDeviceMessage::getMessage()
{
    return this->message;
}

QDataStream& operator<<(QDataStream &stream, const QQueueDeviceMessage &data)
{
    if(nullptr != data.deviceInfo)
    {
        stream << (*data.deviceInfo);
        stream << data.message;
    }
    return stream;
};

QDataStream& operator>>(QDataStream &stream, QQueueDeviceMessage &data)
{
    if(nullptr != data.deviceInfo)
    {
        stream >> (*data.deviceInfo);
        stream >> data.message;
    }
    return stream;
}
