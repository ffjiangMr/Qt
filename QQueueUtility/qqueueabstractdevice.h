#ifndef QQUEUEABSTRACTDEVICE_H
#define QQUEUEABSTRACTDEVICE_H

#include "QQueueUtility_global.h"
#include "qqueuedevicedefinition.h"
#include "qqueuemessage.h"
#include <QObject>
#include <QVector>
#include <QSharedPointer>

/// 前置声明

class QQUEUEUTILITY_EXPORT QQueueAbstractDevice : public QObject
{
    Q_OBJECT
public:
    explicit QQueueAbstractDevice(QObject *parent = nullptr);

public:
    virtual QVector<QQueueDeviceInfo> getDeviceList() = 0;
    virtual QQueueDeviceMessage readMessage() = 0;
    virtual bool sendMessage() = 0;
    virtual bool init() = 0;
protected:

    inline void setDeviceIndex(QQueueDeviceInfo& info, quint64 index)
    {
        info.setDeviceIndex(index);
    }

    inline void setDeviceStatus(QQueueDeviceInfo& info, QQueueDeviceInfo::DeviceStatus status)
    {
        info.setDeviceStatus(status);
    }

    inline void setMessage(QQueueDeviceMessage& msg, const QString&  data)
    {
        msg.setMessage(data);
    }

signals:

};

#endif // QQUEUEABSTRACTDEVICE_H
