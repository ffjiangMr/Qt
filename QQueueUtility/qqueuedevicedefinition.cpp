#include "qqueuedevicedefinition.h"
#include <QDataStream>

QDataStream& operator<<(QDataStream &stream, const QQueueDeviceInfo &data)
{
    stream << data.deviceName;
    stream << static_cast<quint32>(data.deviceType);
    stream << data.deviceIndex;
    stream << static_cast<quint32>(data.deviceStatus);

    return stream;
};

QDataStream& operator>>(QDataStream &stream, QQueueDeviceInfo &data)
{
    quint32 temp = 0;
    stream >> data.deviceName;
    stream >> temp;
    data.deviceType = static_cast<QQueueDeviceInfo::DeviceType>(temp);
    stream >> data.deviceIndex;
    stream >> temp;
    data.deviceStatus = static_cast<QQueueDeviceInfo::DeviceStatus>(temp);
    return stream;
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

QQueueDeviceInfo::QQueueDeviceInfo(const QQueueDeviceInfo& entity)
{
    this->deviceName = entity.deviceName;
    this->deviceType = entity.deviceType;
    this->deviceIndex = entity.deviceIndex;
}

QQueueDeviceInfo::QQueueDeviceInfo(const QString& name, DeviceType type)
{
    this->deviceName = name;
    this->deviceType = type;
    this->deviceIndex = -1;
}

void QQueueDeviceInfo::setDeviceIndex(quint64 index)
{
    this->deviceIndex = index;
}

void QQueueDeviceInfo::setDeviceStatus(DeviceStatus status)
{
    this->deviceStatus = status;
}

quint64 QQueueDeviceInfo::getDeviceIndex()
{
    return this->deviceIndex;
}

QQueueDeviceInfo::DeviceStatus QQueueDeviceInfo::getDeviceStatus()
{
    return this->deviceStatus;
}


QQueueDeviceInfo& QQueueDeviceInfo::operator=(const QQueueDeviceInfo& entity)
{
    if(this != &entity)
    {
        this->deviceName = entity.deviceName;
        this->deviceType = entity.deviceType;
        this->deviceIndex = entity.deviceIndex;
    }
    return *this;
}




QQueueDeviceMessage::QQueueDeviceMessage(const QQueueDeviceMessage& entity)
{
    this->deviceInfo = new QQueueDeviceInfo(*entity.deviceInfo);
    this->message = entity.message;
}

QQueueDeviceMessage& QQueueDeviceMessage::operator=(const QQueueDeviceMessage& entity)
{
    if(this != &entity)
    {
        this->message = entity.message;
        (*this->deviceInfo) = (*entity.deviceInfo);
    }
    return *this;
}

QQueueDeviceMessage::QQueueDeviceMessage(const QQueueDeviceInfo& info)
{
    this->deviceInfo = new QQueueDeviceInfo(info);
    this->message = "";
}

void QQueueDeviceMessage::setMessage(const QString& msg)
{
    this->message = msg;
}

QString QQueueDeviceMessage::getMessage()
{
    return this->message;
}
