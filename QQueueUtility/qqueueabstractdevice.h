#ifndef QQUEUEABSTRACTDEVICE_H
#define QQUEUEABSTRACTDEVICE_H

#include "QQueueUtility_global.h"
#include "qqueuedevicedefinition.h"
#include <QObject>
#include <QVector>

/// 前置声明
class QQueueDeviceInfo;
class QQueueDeviceMessage;

class QQueueAbstractDevice : public QObject
{
    Q_OBJECT
public:
    explicit QQueueAbstractDevice(QObject *parent = nullptr);

public:
    virtual QVector<QQueueDeviceInfo> getDeviceList() = 0;
    virtual QQueueDeviceMessage readMessage() = 0;
    virtual bool sendMessage() = 0;
    virtual bool init() = 0;
signals:

};

#endif // QQUEUEABSTRACTDEVICE_H
