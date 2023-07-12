#ifndef QQUEUEDEVICEDEFINITION_H
#define QQUEUEDEVICEDEFINITION_H

#include "QQueueUtility_global.h"
#include <QObject>
#include <QString>


class QQUEUEUTILITY_EXPORT QQueueDeviceInfo
{
public:
    enum DeviceType{
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

public:
    QQueueDeviceInfo(const QString& name, DeviceType type);
    QQueueDeviceInfo(const QQueueDeviceInfo& entity);
    QQueueDeviceInfo& operator=(const QQueueDeviceInfo& entity);
private:
    QString deviceName;
    DeviceType deviceType;
    quint64 deviceIndex;

public:
    void setDeviceIndex(quint64 index);
    quint64 getDeviceIndex();
    QQUEUEUTILITY_EXPORT friend QDataStream& operator<<(QDataStream &stream, const QQueueDeviceInfo &data);
    QQUEUEUTILITY_EXPORT friend QDataStream& operator>>(QDataStream &stream, QQueueDeviceInfo &data);
};

class QQUEUEUTILITY_EXPORT QQueueDeviceMessage
{

public:
    QQueueDeviceMessage(const QQueueDeviceInfo& info);
    QQueueDeviceMessage(const QQueueDeviceMessage& entity);
    QQueueDeviceMessage& operator=(const QQueueDeviceMessage& entity);
private:
    QQueueDeviceInfo* deviceInfo;
    QString message;

public:
    void setMessage(const QString& msg);
    QString getMessage();
    QQUEUEUTILITY_EXPORT friend QDataStream& operator<<(QDataStream &stream, const QQueueDeviceMessage &data);
    QQUEUEUTILITY_EXPORT friend QDataStream& operator>>(QDataStream &stream, QQueueDeviceMessage &data);
};
#endif // QQUEUEDEVICEDEFINITION_H
