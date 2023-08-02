#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qqueuemachinewindow.h"
#include <QSettings>
#include <QString>
#include <QTextCodec>
#include <QFile>
#include <QtWidgets/QVBoxLayout>
#include "include/qqueuesqlhelper.h"
#include <QDir>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    this->init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    /// 读取配置文件
    /// 设置 窗口标题
    QSettings *settings = new QSettings(":/config/setting.ini",QSettings::IniFormat);
    settings->setIniCodec(QTextCodec::codecForName("UTF-8"));
    settings->beginGroup("SYSTEM_INFO");
    QString title = QObject::tr(settings->value("TITLE","").toString().toUtf8());
    QString version = QObject::tr(settings->value("VERSION","").toString().toUtf8());
    settings->endGroup();

    settings->beginGroup("SQL");
    auto databaseName = QObject::tr(settings->value("DATABASE_NAME","").toString().toUtf8());
    auto databasePath = QObject::tr(settings->value("DATABASE_PATH","").toString().toUtf8());
    settings->endGroup();

    this->setWindowTitle(QString("%1 %2").arg("配置工具").arg(version));
    /// 设置全局默认样式表
    QFile file(":/config/styleSheet.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        this->setStyleSheet(file.readAll());
    }
    file.close();

    this->ui->tabWidget->setTabText(this->ui->tabWidget->indexOf(this->ui->sys_tab),QObject::tr("系统设置"));
    this->ui->tabWidget->setTabText(this->ui->tabWidget->indexOf(this->ui->queue_tab),QObject::tr("队列设置"));
    this->ui->tabWidget->setTabText(this->ui->tabWidget->indexOf(this->ui->page_tab),QObject::tr("页面设置"));
//    this->ui->tabWidget->clear();
//    this->sysemSettingTab = new SystemSetttingTab(this);
//    this->ui->tabWidget->insertTab(0,this->sysemSettingTab,

    delete settings;
}

void MainWindow::on_pushButton_18_clicked()
{
    auto win = new QQueueMachineWindow(this);
    win->setWindowModality(Qt::ApplicationModal);
    win->show();
}
