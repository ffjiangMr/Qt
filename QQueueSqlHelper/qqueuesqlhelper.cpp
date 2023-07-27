#include "qqueuesqlhelper.h"
#include <QSettings>
#include <QTextCodec>
#include <QFile>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>
#include <QByteArray>

QQueueSqlHelper* QQueueSqlHelper::entity = nullptr;
QQueueSqlHelper::QQueueSqlHelper()
{
    databaseName = "data";
    databasePath = ".";
    if (true == QFile::exists(":/config/setting.ini"))
    {
        QSettings settings (":/config/setting.ini",QSettings::IniFormat);
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
