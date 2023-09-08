#include "qqueuewindowssetting.h"
#include "ui_qqueuewindowssetting.h"

#include "../../include/qqueuesqlhelper.h"

#include <QSettings>
#include <QTextCodec>
#include <QIntValidator>
#include <QTime>
#include <QMessageBox>
#include <QCryptographicHash>

QQueueWindowsSetting::QQueueWindowsSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQueueWindowsSetting)
{
    ui->setupUi(this);
    this->windowList = new QVector<QQueueWindowsDefinition*>();
    auto validator = new QIntValidator(0,INT32_MAX,this);
    this->ui->lineEdit_operatorAddr->setValidator(validator);
    this->ui->lineEdit_ScreenAddr->setValidator(validator);
    this->ui->lineEdit_evaluateAddr->setValidator(validator);
    this->ui->lineEdit_windowsId->setValidator(validator);
    this->initData();
    connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(onAddBtnClicked()));
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(onClrBtnClicked()));
    connect(ui->pushButton_remove, SIGNAL(clicked()), this, SLOT(onRemBtnClicked()));
    connect(ui->listWidget_list, SIGNAL(itemSelectionChanged()), this, SLOT(onListWidgetItemSelectionChanged()));
    connect(ui->pushButton_ok, SIGNAL(clicked()), this, SLOT(onOkBtnClicked()));
}

QQueueWindowsSetting::QQueueWindowsSetting(const QQueueWindowsSetting& object)
{
    QQueueWindowsSetting(static_cast<QWidget*>(object.parent()));
}

QQueueWindowsSetting::~QQueueWindowsSetting()
{
    if(nullptr != this->windowList)
    {
        for(auto item = this->windowList->begin(); item != this->windowList->end(); item++)
        {
            if(nullptr != *item)
            {
                delete (*item);
                (*item) = nullptr;
            }
        }
        delete this->windowList;
        this->windowList = nullptr;
    }
    delete ui;
}

void QQueueWindowsSetting::initData()
{
    QSettings settings("./config/setting.ini",QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    settings.beginGroup("WINDOW_COUNTER");
    this->tempName = QObject::tr(settings.value("TEMPLATE_COUNTER_NAME",QObject::tr("柜台")).toString().toUtf8());
    settings.endGroup();

    this->windowList->clear();
    this->ui->listWidget_list->clear();
    QString tempLevel = "";

    /// 从数据库中进行检索
    QStringList columns;
    QVector<QVariant> values;
    auto emp_records = QQueueSqlHelper::getQQueueSqlHelper()->queryRecord("Employee",columns,values);
    foreach(auto item, emp_records)
    {
        this->ui->comboBox_employee->addItem(item["name"].toString(), item["employee_id"].toInt());
    }
    auto counter_records = QQueueSqlHelper::getQQueueSqlHelper()->queryRecord("WindowCounter",columns,values);
    foreach(auto item , counter_records)
    {
        auto info = new QQueueWindowsDefinition(item["name"].toString(), item["windowId"].toInt(), item["callName"].toString(), item["operatorId"].toInt(), item["screenId"].toInt(), item["evaluateId"].toInt(), item["windowIP"].toString(),item["forwardIP"].toString(),item["employee_id"].toInt(), item["id"].toInt());
        this->windowList->push_back(info);
        this->ui->listWidget_list->addItem(info->getName() + "(" +  QString::number(info->getId()) +")");
    }
    this->clearControl();
}

QQueueWindowsDefinition* QQueueWindowsSetting::findWindowCounterInfo(const QString &displayName)
{
    QQueueWindowsDefinition* result = nullptr;
    if(nullptr != this->windowList)
    {
        QString tempName = "";
        for(auto item = this->windowList->begin(); item != this->windowList->end();item++)
        {
            tempName = (*item)->getName() + "(" +  QString::number((*item)->getId()) +")";
            if(tempName == displayName)
            {
                result = (*item);
                break;
            }
        }
    }
    return result;
}

void QQueueWindowsSetting::clearControl(bool enable)
{
    this->ui->pushButton_clear->setEnabled(enable);
    this->ui->pushButton_remove->setEnabled(enable);
    this->ui->pushButton_ok->setEnabled(enable);
    this->ui->lineEdit_windowName->clear();
    this->ui->lineEdit_callName->clear();
    this->ui->lineEdit_windowIP->clear();
    this->ui->lineEdit_operatorAddr->clear();
    this->ui->lineEdit_ScreenAddr->clear();
    this->ui->lineEdit_evaluateAddr->clear();
    this->ui->comboBox_employee->setCurrentIndex(-1);
    this->ui->lineEdit_forwardIP->clear();
    this->ui->lineEdit_windowsId->clear();
}

void QQueueWindowsSetting::onAddBtnClicked()
{
    qsrand(QTime::currentTime().msec() * QTime::currentTime().minute()*QTime::currentTime().second());
    quint32 id = qrand();
    auto item = this->windowList->begin();
    while(item!= this->windowList->end())
    {
        if(id == (*item)->getId())
        {
            id = qrand();
            item = this->windowList->begin();
            continue;
        }
        item++;
    }
    QQueueWindowsDefinition* info = new QQueueWindowsDefinition(this->tempName, id);
    this->windowList->push_back(info);
    this->ui->listWidget_list->addItem(info->getName() + "(" +  QString::number(info->getId()) +")");
}

void QQueueWindowsSetting::onRemBtnClicked()
{
    auto info = this->findWindowCounterInfo(this->ui->listWidget_list->currentItem()->text());
    if(nullptr != info)
    {
        this->windowList->removeOne(info);
    }
    this->ui->listWidget_list->takeItem(this->ui->listWidget_list->currentRow());
    if(this->ui->listWidget_list->count() < 1)
    {
        this->clearControl();
    }
}

void QQueueWindowsSetting::onClrBtnClicked()
{
    this->ui->listWidget_list->clear();
    this->windowList->clear();
    this->clearControl();
}

void QQueueWindowsSetting::onListWidgetItemSelectionChanged()
{
    if(this->windowList->count()> 0)
    {
        this->clearControl(true);
        if(-1 != this->ui->listWidget_list->currentRow())
        {
            auto info = this->findWindowCounterInfo(this->ui->listWidget_list->currentItem()->text());
            if(nullptr != info)
            {
                this->ui->lineEdit_windowName->setText(info->getName());
                this->ui->lineEdit_windowsId->setText(QString::number(info->getId()));
                this->ui->lineEdit_callName->setText(info->getCallName());
                this->ui->lineEdit_operatorAddr->setText(QString::number(info->getOperatorAddr()));
                this->ui->lineEdit_ScreenAddr->setText(QString::number(info->getScreenAddr()));
                this->ui->lineEdit_evaluateAddr->setText(QString::number(info->getEvaluateAddr()));
                this->ui->lineEdit_windowIP->setText(info->getWindowIP());
                this->ui->lineEdit_forwardIP->setText(info->getForwardIP());
                this->ui->comboBox_employee->setCurrentIndex(this->ui->comboBox_employee->findData(info->getEmployeeId()));
            }
        }
    }
    else
    {
        this->clearControl();
    }
}

void QQueueWindowsSetting::onOkBtnClicked()
{
    if(-1 != this->ui->listWidget_list->currentRow())
    {
        bool isDup = false;
        auto item = this->windowList->begin();
        while(item!= this->windowList->end())
        {
            if((false == this->ui->listWidget_list->currentItem()->text().contains(this->ui->lineEdit_windowsId->text())) &&
                    (this->ui->lineEdit_windowsId->text().toUInt() == (*item)->getId()))
            {
                isDup = true;
                QMessageBox msgBox(this);
                msgBox.setText(QObject::tr(""
                                           "\r\n     窗口ID设置重复.     \r\n"
                                           ""));
                msgBox.exec();
                break;
            }
            item++;
        }
        if(false == isDup)
        {
            auto info = this->findWindowCounterInfo(this->ui->listWidget_list->currentItem()->text());
            info->setName(this->ui->lineEdit_windowName->text());
            info->setId( this->ui->lineEdit_windowsId->text().toUInt());
            info->setCallName(this->ui->lineEdit_callName->text());
            info->setOperatorAddr(this->ui->lineEdit_operatorAddr->text().toInt());
            info->setScreenAddr(this->ui->lineEdit_ScreenAddr->text().toInt());
            info->setEvaluateAddr(this->ui->lineEdit_evaluateAddr->text().toInt());
            info->setWindowIP(this->ui->lineEdit_windowIP->text());
            info->setForwardIP(this->ui->lineEdit_forwardIP->text());
            info->setEmployee(this->ui->comboBox_employee->currentData().toInt());
            auto item = this->ui->listWidget_list->currentItem();
            item->setText(this->ui->lineEdit_windowName->text() + "(" + this->ui->lineEdit_windowsId->text() +")");
        }
    }
}

void QQueueWindowsSetting::SaveUpdated()
{
    auto db = QQueueSqlHelper::getQQueueSqlHelper();
    QStringList columns{"name","windowId","callName","operatorId","screenId","evaluateId","windowIP", "forwardIP", "employee_id"};
    QVector<QVariant> values;
    db->deleteRecord("WindowCounter");
    foreach(auto item , *this->windowList)
    {
        values.clear();
        values.append(item->getName());
        values.append(QString::number(item->getId()));
        values.append(item->getCallName());
        values.append(QString::number(item->getOperatorAddr()));
        values.append(QString::number(item->getScreenAddr()));
        values.append(QString::number(item->getEvaluateAddr()));
        values.append(item->getWindowIP());
        values.append(item->getForwardIP());
        values.append(QString::number(item->getEmployeeId()));
        if(-1 == item->getRecordId())
        {
            db->insertOneRecord("WindowCounter", columns, values);
        }
        else
        {
            db->updateOneRecord("WindowCounter", item->getRecordId(), columns, values);
        }
    }
    this->initData();
}
