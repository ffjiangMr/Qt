#ifndef QQUEUEMESSAGE_H
#define QQUEUEMESSAGE_H

#include <QObject>
#include <QQueueUtility_global.h>
#include <qqueuedevicedefinition.h>

class QQueueAbstractDevice;

class QQUEUEUTILITY_EXPORT QQueueDeviceMessage
{

public:
    QQueueDeviceMessage(const QQueueDeviceInfo& info);
    QQueueDeviceMessage(const QQueueDeviceMessage& entity);
    ~QQueueDeviceMessage();
    QQueueDeviceMessage& operator=(const QQueueDeviceMessage& entity);
    friend class QQueueAbstractDevice;
private:
    QQueueDeviceInfo* deviceInfo;
    QString message;

public:
    QString getMessage();
    QQUEUEUTILITY_EXPORT friend QDataStream& operator<<(QDataStream &stream, const QQueueDeviceMessage &data);
    QQUEUEUTILITY_EXPORT friend QDataStream& operator>>(QDataStream &stream, QQueueDeviceMessage &data);

private:
    void setMessage(const QString& msg);
};


#endif // QQUEUEMESSAGE_H
