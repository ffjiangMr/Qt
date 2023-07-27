#ifndef QQUEUESQLHELPER_H
#define QQUEUESQLHELPER_H

#include "QQueueSqlHelper_global.h"
#include <QSqlDatabase>
#include <QString>

class QQUEUESQLHELPER_EXPORT QQueueSqlHelper
{
private:
    QQueueSqlHelper();    
    void init();

public:
    QQUEUESQLHELPER_EXPORT static QQueueSqlHelper* getQQueueSqlHelper();
    inline bool getStatus()
    {
        return this->isOpen;
    }

private:
    QQUEUESQLHELPER_EXPORT static QQueueSqlHelper* entity;
    QString databaseName;
    QString databasePath;
    QSqlDatabase database;
    bool isOpen;
};

#endif // QQUEUESQLHELPER_H
