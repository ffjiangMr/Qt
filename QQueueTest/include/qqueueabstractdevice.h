#ifndef QQUEUEABSTRACTDEVICE_H
#define QQUEUEABSTRACTDEVICE_H

#include "QQueueUtility_global.h"
#include <QObject>

class QQueueAbstractDevice : public QObject
{
    Q_OBJECT
public:
    explicit QQueueAbstractDevice(QObject *parent = nullptr);

public:

signals:

};

#endif // QQUEUEABSTRACTDEVICE_H
