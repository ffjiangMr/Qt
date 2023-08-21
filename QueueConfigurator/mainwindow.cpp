#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qqueuemachinewindow.h"
#include "include/qqueuesqlhelper.h"
#include "TagPage/SystemSetting/qqueuesystemsetting.h"
#include "TagPage/QueueSetting/qqueuequeuesetting.h"
#include "TagPage/PageSetting/qqueuepagesetting.h"
#include "TagPage/DepartmentSetting/qqueuedepartmentsetting.h"
#include "TagPage/EmployeeSetting/qqueueemployeesetting.h"

#include <QDebug>
#include <QSettings>
#include <QString>
#include <QTextCodec>
#include <QFile>
#include <QtWidgets/QVBoxLayout>
#include <QDir>
#include <QIntValidator>
#include <QMetaType>
#include <QMetaObject>
#include <QGenericArgument>
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
    this->registerPageMetaType();

    /// 读取配置文件
    /// 设置 窗口标题
    QSettings settings("./config/setting.ini",QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    settings.beginGroup("SYSTEM_INFO");
    QString title = QObject::tr(settings.value("TITLE","").toString().toStdString().c_str());
    QString version = QObject::tr(settings.value("TITLE","").toString().toStdString().c_str());
    this->setWindowTitle(QString("%1 %2").arg(title).arg(version));
    settings.endGroup();

    /// 配置Tag page
    settings.beginGroup("PAGE");
    auto allkeys = settings.allKeys();
    auto utf8 = QTextCodec::codecForName("UTF-8");
    foreach(auto key, allkeys)
    {
        auto className = settings.value(key,"").toString();
        auto metaIndex = QMetaType::type(className.toStdString().c_str());
        auto page = static_cast<QWidget*>(QMetaType::create(metaIndex));
        this->ui->tabWidget->addTab(page,utf8->toUnicode(key.toLatin1()));
    }
    QString pageClass = QObject::tr(settings.value(allkeys[1],"").toString().toUtf8());

    settings.endGroup();


    /// 设置全局默认样式表
    QFile file(":/config/styleSheet.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        this->setStyleSheet(file.readAll());
    }
    file.close();
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

void MainWindow::registerPageMetaType()
{
    qRegisterMetaType<QQueueDepartmentSetting>();
    qRegisterMetaType<QQueuePageSetting>();
    qRegisterMetaType<QQueueQueueSetting>();
    qRegisterMetaType<QQueueSystemSetting>();
    qRegisterMetaType<QQueueEmployeeSetting>();
}
