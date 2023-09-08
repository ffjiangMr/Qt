#include "qqueueemployeesetting.h"
#include "ui_qqueueemployeesetting.h"
#include "../../include/qqueuesqlhelper.h"

#include <QSettings>
#include <QTextCodec>
#include <QIntValidator>
#include <QTime>
#include <QMessageBox>
#include <QCryptographicHash>

QQueueEmployeeSetting::QQueueEmployeeSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQueueEmployeeSetting)
{
    ui->setupUi(this);
    this->employeeList = new QVector<QQueueEmployeeDefinition*>();
    auto validator = new QIntValidator(0,INT32_MAX,this);
    this->ui->lineEdit_id->setValidator(validator);
    this->initData();
    connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(onAddBtnClicked()));
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(onClrBtnClicked()));
    connect(ui->pushButton_remove, SIGNAL(clicked()), this, SLOT(onRemBtnClicked()));
    connect(ui->listWidget_list, SIGNAL(itemSelectionChanged()), this, SLOT(onListWidgetItemSelectionChanged()));
    connect(ui->pushButton_ok, SIGNAL(clicked()), this, SLOT(onOkBtnClicked()));
}

QQueueEmployeeSetting::QQueueEmployeeSetting(const QQueueEmployeeSetting& object)
{
    QQueueEmployeeSetting(static_cast<QWidget*>(object.parent()));
}

QQueueEmployeeSetting::~QQueueEmployeeSetting()
{
    if(nullptr != this->employeeList)
    {
        for(auto item = this->employeeList->begin(); item != this->employeeList->end(); item++)
        {
            if(nullptr != *item)
            {
                delete (*item);
                (*item) = nullptr;
            }
        }
        delete this->employeeList;
        this->employeeList = nullptr;
    }
    delete ui;
}

void QQueueEmployeeSetting::initData()
{
    QSettings settings("./config/setting.ini",QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    settings.beginGroup("EMPLOYEE");
    this->tempName = QObject::tr(settings.value("TEMPLATE_EMPLOYEE_NAME",QObject::tr("员工")).toString().toUtf8());
    settings.endGroup();

    this->employeeList->clear();
    this->ui->listWidget_list->clear();
    QString tempLevel = "";
    for (int flag = 5; flag >0; flag --)
    {
        tempLevel = "";
        for (int tempIndex = 0; tempIndex < flag; tempIndex++)
        {
            tempLevel += QObject::tr("★");
        }
        this->ui->comboBox_starLevel->addItem(tempLevel,flag);
    }
    /// 从数据库中进行检索
    QStringList columns;
    QVector<QVariant> values;
    auto dep_records = QQueueSqlHelper::getQQueueSqlHelper()->queryRecord("Department",columns,values);
    foreach(auto item , dep_records)
    {
        this->ui->comboBox_dep->addItem(item["name"].toString(), item["dep_id"].toInt());
    }
    auto emp_records = QQueueSqlHelper::getQQueueSqlHelper()->queryRecord("Employee",columns,values);
    foreach(auto item , emp_records)
    {
        auto info = new QQueueEmployeeDefinition(item["name"].toString(), item["employee_id"].toInt(), item["password"].toString(), item["startLevel"].toInt(), item["department_id"].toInt(), item["title"].toString(), item["summary"].toString(),  item["id"].toInt());
        this->employeeList->push_back(info);
        this->ui->listWidget_list->addItem(info->getName() + "(" +  QString::number(info->getId()) +")");
    }
    this->clearControl();
}

void QQueueEmployeeSetting::onAddBtnClicked()
{
    qsrand(QTime::currentTime().msec() * QTime::currentTime().minute()*QTime::currentTime().second());
    quint32 id = qrand();
    auto item = this->employeeList->begin();
    while(item!= this->employeeList->end())
    {
        if(id == (*item)->getId())
        {
            id = qrand();
            item = this->employeeList->begin();
            continue;
        }
        item++;
    }
    QQueueEmployeeDefinition* info = new QQueueEmployeeDefinition(this->tempName, id);
    this->employeeList->push_back(info);
    this->ui->listWidget_list->addItem(info->getName() + "(" +  QString::number(info->getId()) +")");
}

void QQueueEmployeeSetting::onRemBtnClicked()
{
    auto info = this->findEmployeeInfo(this->ui->listWidget_list->currentItem()->text());
    if(nullptr != info)
    {
        this->employeeList->removeOne(info);
    }
    this->ui->listWidget_list->takeItem(this->ui->listWidget_list->currentRow());
    if(this->ui->listWidget_list->count() < 1)
    {
        this->clearControl();
    }
}

void QQueueEmployeeSetting::onClrBtnClicked()
{
    this->ui->listWidget_list->clear();
    this->employeeList->clear();
    this->clearControl();
}

void QQueueEmployeeSetting::onListWidgetItemSelectionChanged()
{
    if(this->employeeList->count()> 0)
    {
        this->clearControl(true);
        if(-1 != this->ui->listWidget_list->currentRow())
        {
            auto info = this->findEmployeeInfo(this->ui->listWidget_list->currentItem()->text());
            if(nullptr != info)
            {
                this->ui->lineEdit_name->setText(info->getName());
                this->ui->lineEdit_id->setText(QString::number(info->getId()));
                this->ui->lineEdit_title->setText(info->getTitle());
                this->ui->lineEdit_summary->setText(info->getSummary());
                this->ui->comboBox_dep->setCurrentIndex(this->ui->comboBox_dep->findData(info->getDepartment()));
                this->ui->comboBox_starLevel->setCurrentIndex(this->ui->comboBox_starLevel->findData(info->getLevel()));
            }
        }
    }
    else
    {
        this->clearControl();
    }
}

void QQueueEmployeeSetting::onOkBtnClicked()
{
    if(-1 != this->ui->listWidget_list->currentRow())
    {
        bool isDup = false;
        auto item = this->employeeList->begin();
        while(item!= this->employeeList->end())
        {
            if((false == this->ui->listWidget_list->currentItem()->text().contains(this->ui->lineEdit_id->text())) &&
                    (this->ui->lineEdit_id->text().toUInt() == (*item)->getId()))
            {
                isDup = true;
                QMessageBox msgBox(this);
                msgBox.setText(QObject::tr(""
                                           "\r\n     员工ID设置重复.     \r\n"
                                           ""));
                msgBox.exec();
                break;
            }
            item++;
        }
        if(false == isDup)
        {
            auto info = this->findEmployeeInfo(this->ui->listWidget_list->currentItem()->text());
            info->setName(this->ui->lineEdit_name->text());
            info->setId( this->ui->lineEdit_id->text().toUInt());
            info->setPassword(this->ui->lineEdit_psw->text());
            info->setStarLevel(this->ui->comboBox_starLevel->currentData().toInt());
            info->setDepartment(this->ui->comboBox_dep->currentData().toInt());
            info->setTitle(this->ui->lineEdit_title->text());
            info->setSummary(this->ui->lineEdit_summary->text());
            auto item = this->ui->listWidget_list->currentItem();
            item->setText(this->ui->lineEdit_name->text() + "(" + this->ui->lineEdit_id->text() +")");
        }
    }
}

void QQueueEmployeeSetting::clearControl(bool enable)
{
    this->ui->pushButton_clear->setEnabled(enable);
    this->ui->pushButton_remove->setEnabled(enable);
    this->ui->pushButton_ok->setEnabled(enable);
    this->ui->lineEdit_name->clear();
    this->ui->lineEdit_id->clear();
    this->ui->lineEdit_psw->clear();
    this->ui->comboBox_dep->setCurrentIndex(-1);
    this->ui->comboBox_starLevel->setCurrentIndex(-1);
    this->ui->lineEdit_title->clear();
    this->ui->lineEdit_summary->clear();
}

QQueueEmployeeDefinition* QQueueEmployeeSetting::findEmployeeInfo(const QString &displayName)
{
    QQueueEmployeeDefinition* result = nullptr;
    if(nullptr != this->employeeList)
    {
        QString tempName = "";
        for(auto item = this->employeeList->begin(); item != this->employeeList->end();item++)
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

void QQueueEmployeeSetting::SaveUpdated()
{
    auto db = QQueueSqlHelper::getQQueueSqlHelper();
    QStringList columns{"name","employee_id","password","startLevel","department_id","title","summary"};
    QVector<QVariant> values;
    db->deleteRecord("Employee");
    foreach(auto item , *this->employeeList)
    {
        values.clear();
        values.append(item->getName());
        values.append(QString::number(item->getId()));
        values.append(QString(QCryptographicHash::hash(item->getPassword().toLocal8Bit(),QCryptographicHash::Md5)));
        values.append(QString::number(item->getLevel()));
        values.append(QString::number(item->getDepartment()));
        values.append(item->getTitle());
        values.append(item->getSummary());
        if(-1 == item->getRecordId())
        {
            db->insertOneRecord("Employee", columns, values);
        }
        else
        {
            db->updateOneRecord("Employee", item->getRecordId(), columns, values);
        }
    }
    this->initData();
}
