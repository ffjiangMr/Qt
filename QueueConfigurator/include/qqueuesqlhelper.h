#ifndef QQUEUESQLHELPER_H
#define QQUEUESQLHELPER_H

#include "QQueueSqlHelper_global.h"
#include <QSqlDatabase>
#include <QString>
#include <QVariant>
#include <QVector>
#include <QStringList>
#include <QHash>

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

    inline void closeDB()
    {
        if(true == this->isOpen)
        {
            delete QQueueSqlHelper::entity;
        }
        QQueueSqlHelper::entity = nullptr;
    }
    void deleteRecord(const QString& tableName);
    void updateOneRecord(const QString& tableName, const int& id, const QStringList& columnName, const QVector<QVariant>& values);
    void insertOneRecord(const QString& tableName, const QStringList& columnName, const QVector<QVariant>& values);
    const QVector<QHash<QString, QVariant>> queryRecord(const QString& tableName, const QStringList& columnName, const QVector<QVariant>& values, const bool& isSoftDeleted = false);

private:
    QQUEUESQLHELPER_EXPORT static QQueueSqlHelper* entity;
    QString databaseName;
    QString databasePath;
    QSqlDatabase database;
    bool isOpen;
};

#endif // QQUEUESQLHELPER_H
