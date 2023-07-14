#ifndef QQUEUEDEVICEDEFINITION_H
#define QQUEUEDEVICEDEFINITION_H

#include "QQueueUtility_global.h"
#include <QObject>
#include <QString>
#include <QSharedPointer>

class QQueueAbstractDevice;

class QQUEUEUTILITY_EXPORT QQueueDeviceInfo
{
public:
    enum class DeviceType{
        /// 未知设备
        UNKNOW = 0,
        /// 叫号机主机
        HOST = 1,
        /// 安卓综合屏
        ANDROID_INTERGRATED_SCREEN = 2,
        /// 安卓液晶窗口屏
        ANDROID_WINDOWS_SCREEN = 3,
        /// LED窗口屏
        LED_WINDOWS_SCREEN = 4,
        /// 多卡大LED窗口屏
        LED_MULTI_WINDOWS_SCREEN = 5,
        /// 能效屏
        PRODUCTIVITY_SCREEN = 6,
        /// 安卓评价器
        ANDROID_EVALUATOR = 7,
        /// 串口评价器
        Serial_EVALUATOR = 8,
        /// 21键呼叫器
        KEYS_PAGER = 9,
        /// 软件虚拟呼叫器
        SOFT_VIRTUAL_PAGER = 10
    };

    enum class DeviceStatus
    {
        UNKNOW = 0,
        UNINIT = 1,
        CONNECTED = 2,
        CLOSED = 3
    };

public:
    QQueueDeviceInfo(const QObject* device, const QString& name, DeviceType type);
    QQueueDeviceInfo(const QQueueDeviceInfo& entity);
    ~QQueueDeviceInfo();
    QQueueDeviceInfo& operator=(const QQueueDeviceInfo& entity);
    friend class QQueueAbstractDevice;
private:
    QString deviceName;
    DeviceType deviceType;
    quint64 deviceIndex;
    DeviceStatus deviceStatus;
    QSharedPointer<QObject> deviceEntity;

public:    
    quint64 getDeviceIndex();    
    DeviceStatus getDeviceStatus();
    const QSharedPointer<QObject>& getDevice();
    QQUEUEUTILITY_EXPORT friend QDataStream& operator<<(QDataStream &stream, const QQueueDeviceInfo &data);
    QQUEUEUTILITY_EXPORT friend QDataStream& operator>>(QDataStream &stream, QQueueDeviceInfo &data);

private:
    void setDeviceStatus(DeviceStatus status);
    void setDeviceIndex(quint64 index);
};
#endif // QQUEUEDEVICEDEFINITION_H
