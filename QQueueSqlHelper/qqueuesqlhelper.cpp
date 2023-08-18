#include "qqueuesqlhelper.h"
#include <QSettings>
#include <QTextCodec>
#include <QFile>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>
#include <QByteArray>
#include <QSqlRecord>
#include <QDebug>

QQueueSqlHelper* QQueueSqlHelper::entity = nullptr;
QQueueSqlHelper::QQueueSqlHelper()
{
    databaseName = "data";
    databasePath = ".";
    if (true == QFile::exists("./config/setting.ini"))
    {
        QSettings settings ("./config/setting.ini",QSettings::IniFormat);
        settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
        settings.beginGroup("SQL");
        databaseName = QObject::tr(settings.value("DATABASE_NAME","data").toString().toUtf8());
        databasePath = QObject::tr(settings.value("DATABASE_PATH",".").toString().toUtf8());
        settings.endGroup();
    }
    this->init();
}

QQueueSqlHelper* QQueueSqlHelper::getQQueueSqlHelper()
{
    if(nullptr == QQueueSqlHelper::entity)
    {
        QQueueSqlHelper::entity = new QQueueSqlHelper();
    }
    return QQueueSqlHelper::entity;
}

void QQueueSqlHelper::init()
{
    QDir dir(this->databasePath);
    this->database = QSqlDatabase::addDatabase("QSQLITE");
    ///this->database.setConnectOptions("QSQLITE_OPEN_READONLY");
    if( true == this->database.isValid())
    {
        QDir dir(this->databasePath);
        this->database.setDatabaseName(dir.absoluteFilePath(this->databaseName));
        bool needInit = !QFile::exists(dir.absoluteFilePath(this->databaseName));
        isOpen = this->database.open();
        if((true == isOpen) && needInit)
        {
            QString command = "";
            QFile file(":/script/sql_init_script.script");
            file.open(QFile::ReadOnly);
            if (file.isOpen())
            {
                if( true == this->database.transaction())
                {
                    QSqlQuery query(this->database);
                    QByteArray buf;
                    buf = file.readLine();
                    bool isDone = true;
                    while(buf.size() > 0)
                    {
                        command = QTextCodec::codecForName("UTF-8")->toUnicode(buf).trimmed();
                        if(false == query.exec(command))
                        {
                            isDone =false;
                            break;
                        }
                        buf = file.readLine();
                    }
                    if(true == isDone)
                    {
                        this->database.commit();
                    }
                    else
                    {
                        this->database.rollback();
                    }
                }
            }
            file.close();
        }
    }
}

void QQueueSqlHelper::deleteOneRecord(const QString& tableName, const int& id)
{
    if(true == isOpen)
    {
        QString command = "udpate " + tableName + " set isSoftDeleted = 1 where id = :id" ;
        if( true == this->database.transaction())
        {
            QSqlQuery query(this->database);
            query.prepare(command);
            query.bindValue(":id",id);
            if(true == query.exec())
            {
                this->database.commit();
            }
            else
            {
                this->database.rollback();
            }
        }
    }
}

void QQueueSqlHelper::updateOneRecord(const QString& tableName, const int& id, const QStringList& columnName, const QVector<QVariant>& values)
{
    if((true == isOpen) && (columnName.count() == values.count()) && (columnName.count() > 0))
    {
        QSqlQuery query(this->database);
        QString command = "udpate " + tableName ;
        for(int index = 0; index < columnName.count(); index ++)
        {
            command += (" set " + columnName[index] + " = :" + columnName[index] + ",");
        }
        command = command.left(command.length() - 1);
        command +=  "where id = :id" ;
        query.prepare(command);
        for(int index = 0; index < values.count(); index ++)
        {
            query.addBindValue(values[index]);
        }
        query.bindValue(":id",id);
        if( true == this->database.transaction())
        {
            if(true == query.exec())
            {
                this->database.commit();
            }
            else
            {
                this->database.rollback();
            }
        }
    }
}

void QQueueSqlHelper::insertOneRecord(const QString &tableName, const QStringList &columnName, const QVector<QVariant>&values)
{
    if((true == isOpen) && (columnName.count() == values.count()) && (columnName.count() > 0))
    {
        QSqlQuery query(this->database);
        QString command = "insert into " + tableName + " (";
        QString values_com = " values (";
        for(int index = 0; index < columnName.count(); index ++)
        {
            command += (" " + columnName[index]+ ",");
            values_com += (" :" + columnName[index] + ",");
        }
        command += " isSoftDeleted";
        values_com += " 0";
        command +=  " ) " ;
        values_com +=  " ) " ;
        command += values_com;
        if( true == query.prepare(command))
        {
            for(int index = 0; index < values.count(); index ++)
            {
                query.addBindValue(values[index]);
            }
            if( true == this->database.transaction())
            {
                if(true == query.exec())
                {
                    this->database.commit();
                }
                else
                {
                    this->database.rollback();
                }
            }
        }
    }
}

const QVector<QHash<QString, QVariant>> QQueueSqlHelper::queryRecord(const QString& tableName, const QStringList& columnName, const QVector<QVariant>& values, const bool& isSoftDeleted)
{
    QSqlQuery query(this->database);
    QVector<QHash<QString, QVariant>> result;
    if((true == isOpen) && (columnName.count() == values.count()))
    {
        QString command = "select * from " + tableName + " where ";
        for(int index = 0; index < columnName.count(); index ++)
        {
            if(index != 0)
            {
                command += " and ";
            }
            command += (" " + columnName[index]+ "= :") + columnName[index];
        }
        command += "isSoftDeleted = " + QString::number(isSoftDeleted == true ? 1:0);
        if( true == query.prepare(command))
        {
            for(int index = 0; index < values.count(); index ++)
            {
                query.addBindValue(values[index]);
            }
            if(true == query.exec())
            {

                while(true == query.next())
                {
                    auto record = query.record();
                    QHash<QString, QVariant> item;
                    for(int index = 0; index < record.count(); index ++)
                    {
                        item[record.fieldName(index)] = record.value(index);
                    }
                    result.push_back(item);
                }
            }
        }
    }
    return result;
}
