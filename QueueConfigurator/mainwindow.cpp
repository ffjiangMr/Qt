#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qqueuemachinewindow.h"
#include "include/qqueuesqlhelper.h"
#include "TagPage/SystemSetting/qqueuesystemsetting.h"
#include "TagPage/QueueSetting/qqueuequeuesetting.h"
#include "TagPage/PageSetting/qqueuepagesetting.h"
#include "TagPage/DepartmentSetting/qqueuedepartmentsetting.h"

#include <QSettings>
#include <QString>
#include <QTextCodec>
#include <QFile>
#include <QtWidgets/QVBoxLayout>
#include <QDir>
#include <QIntValidator>
#include <QMetaType>
#include <QMetaObject>
#include <QSqlQuery>


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
    this->isCurrentTabChg = false;
    QSettings *settings = new QSettings(":/config/setting.ini",QSettings::IniFormat);
    settings->setIniCodec(QTextCodec::codecForName("UTF-8"));
    settings->beginGroup("SYSTEM_INFO");
    QString title = QObject::tr(settings->value("TITLE","").toString().toUtf8());
    QString version = QObject::tr(settings->value("VERSION","").toString().toUtf8());
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
    this->ui->tabWidget->addTab(new QQueueSystemSetting(this), "系统设置");
    this->ui->tabWidget->addTab(new QQueueQueueSetting(this), "队列设置");
    this->ui->tabWidget->addTab(new QQueuePageSetting(this), "页面设置");
    this->ui->tabWidget->addTab(new QQueueDepartmentSetting(this), "部门设置");
    delete settings;    
} 

//void MainWindow::on_pushButton_18_clicked()
//{
//    auto win = new QQueueMachineWindow(this);
//    win->setWindowModality(Qt::ApplicationModal);
//    win->show();
//}

void MainWindow::on_applyBtn_clicked()
{
    auto methodName = "SaveUpdated";
    for (int flag = 0; flag < this->ui->tabWidget->count(); flag++)
    {
        QMetaObject::invokeMethod(this->ui->tabWidget->widget(flag),  methodName, Qt::DirectConnection);
    }
}
