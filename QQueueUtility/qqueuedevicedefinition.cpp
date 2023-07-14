#include "qqueuedevicedefinition.h"
#include <QDataStream>

/// 重载"<<",">>" 操作符
/// 声明"QDataStream"友元函数
/// 对象序列化
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

/// QQueueDeviceInfo
QQueueDeviceInfo::QQueueDeviceInfo(const QQueueDeviceInfo& entity)
{
    this->deviceName = entity.deviceName;
    this->deviceType = entity.deviceType;
    this->deviceIndex = entity.deviceIndex;
    this->deviceEntity = entity.deviceEntity;
}

QQueueDeviceInfo::QQueueDeviceInfo(const QObject* device,const QString& name, DeviceType type)
{    
    this->deviceName = name;
    this->deviceType = type;
    this->deviceIndex = -1;
    if(nullptr != device)
    {
        this->deviceEntity.reset(const_cast<QObject*>(device));
    }
}

QQueueDeviceInfo& QQueueDeviceInfo::operator=(const QQueueDeviceInfo& entity)
{
    if(this != &entity)
    {
        auto temp = entity.deviceEntity;
        this->deviceEntity.swap(temp);
        this->deviceName = entity.deviceName;
        this->deviceType = entity.deviceType;
        this->deviceIndex = entity.deviceIndex;
    }
    return *this;
}

QQueueDeviceInfo::~QQueueDeviceInfo()
{
    //ToDo
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

const QSharedPointer<QObject>& QQueueDeviceInfo::getDevice()
{
    return this->deviceEntity;
}

QQueueDeviceInfo::DeviceStatus QQueueDeviceInfo::getDeviceStatus()
{
    return this->deviceStatus;
}


