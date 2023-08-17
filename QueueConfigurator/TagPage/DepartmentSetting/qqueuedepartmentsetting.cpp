#include "qqueuedepartmentsetting.h"
#include "ui_qqueuedepartmentsetting.h"
#include "../../include/qqueuesqlhelper.h"

#include <QTime>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QVector>
#include <QHash>
#include <QIntValidator>
#include <QSettings>
#include <QTextCodec>

QQueueDepartmentSetting::QQueueDepartmentSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQueueDepartmentSetting)
{
    ui->setupUi(this);
    this->depList = new QVector<QQueueDepartmentInfo*>();
    auto validator = new QIntValidator(0,INT32_MAX,this);
    this->ui->dep_id_line->setValidator(validator);
    this->initData();
    connect(ui->dep_add_btn, SIGNAL(clicked()), this, SLOT(onDepAddBtnClicked()));
    connect(ui->dep_rem_btn, SIGNAL(clicked()), this, SLOT(onDepRemBtnClicked()));
    connect(ui->dep_clr_btn, SIGNAL(clicked()), this, SLOT(onDepClrBtnClicked()));
    connect(ui->dep_list_widget, SIGNAL(itemSelectionChanged()), this, SLOT(onDepListWidgetItemSelectionChanged()));
    connect(ui->dep_ok_btn, SIGNAL(clicked()), this, SLOT(onDepOkBtnClicked()));
}

QQueueDepartmentSetting::QQueueDepartmentSetting(const QQueueDepartmentSetting& object)
{
    Q_UNUSED(object)
}

QQueueDepartmentSetting& QQueueDepartmentSetting::operator=(const QQueueDepartmentSetting& object)
{
     Q_UNUSED(object)
     return *this;
}

QQueueDepartmentSetting::~QQueueDepartmentSetting()
{
    if(nullptr != this->depList)
    {
        for(auto item = this->depList->begin(); item != this->depList->end(); item++)
        {
            if(nullptr != *item)
            {
                delete (*item);
                (*item) = nullptr;
            }
        }
        delete this->depList;
        this->depList = nullptr;
    }
    delete ui;
}

void QQueueDepartmentSetting::onDepAddBtnClicked()
{
    qsrand(QTime::currentTime().msec() * QTime::currentTime().minute()*QTime::currentTime().second());
    quint32 id = qrand();
    auto item = this->depList->begin();
    while(item!= this->depList->end())
    {
        if(id == (*item)->getId())
        {
            id = qrand();
            item = this->depList->begin();
            continue;
        }
        item++;
    }
    QQueueDepartmentInfo* info = new QQueueDepartmentInfo(this->tempDepName, id,true);
    this->depList->push_back(info);
    this->ui->dep_list_widget->addItem(info->getName() + "(" +  QString::number(info->getId()) +")");
    this->isChanged = true;
}

void QQueueDepartmentSetting::onDepRemBtnClicked()
{
    this->ui->dep_list_widget->takeItem(this->ui->dep_list_widget->currentRow());
    if(this->ui->dep_list_widget->count() < 1)
    {
        this->ui->dep_rem_btn->setEnabled(false);
        this->ui->dep_ok_btn->setEnabled(false);
        this->ui->dep_name_line->clear();
        this->ui->dep_id_line->clear();
    }
    this->isChanged = true;
}

void QQueueDepartmentSetting::onDepClrBtnClicked()
{
    this->ui->dep_list_widget->clear();
    this->ui->dep_rem_btn->setEnabled(false);
    this->ui->dep_ok_btn->setEnabled(false);
    this->ui->dep_name_line->clear();
    this->ui->dep_id_line->clear();
    this->isChanged = true;
}

void QQueueDepartmentSetting::onDepListWidgetItemSelectionChanged()
{
    this->ui->dep_rem_btn->setEnabled(true);
    this->ui->dep_ok_btn->setEnabled(true);
    if(-1 != this->ui->dep_list_widget->currentRow())
    {
        auto info = this->findDepInfo(this->ui->dep_list_widget->currentItem()->text());
        this->ui->dep_name_line->setText(info->getName());
        this->ui->dep_id_line->setText(QString::number(info->getId()));
    }
}

void QQueueDepartmentSetting::onDepOkBtnClicked()
{
    if(-1 != this->ui->dep_list_widget->currentRow())
    {
        bool isDup = false;
        auto item = this->depList->begin();
        while(item!= this->depList->end())
        {
            if(this->ui->dep_id_line->text().toUInt() == (*item)->getId())
            {
                isDup = true;
                break;
            }
            item++;
        }
        if(false == isDup)
        {
            auto info = this->findDepInfo(this->ui->dep_list_widget->currentItem()->text());
            info->setName(this->ui->dep_name_line->text());
            info->setId( this->ui->dep_id_line->text().toUInt());
            auto item = this->ui->dep_list_widget->currentItem();
            item->setText(this->ui->dep_name_line->text() + "(" + this->ui->dep_id_line->text() +")");
            this->isChanged = true;
        }
    }
}

QQueueDepartmentInfo* QQueueDepartmentSetting::findDepInfo(const QString &displayName)
{
    QQueueDepartmentInfo* result = nullptr;
    if(nullptr != this->depList)
    {
        QString tempName = "";
        for(auto item = this->depList->begin(); item != this->depList->end();item++)
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

void QQueueDepartmentSetting::initData()
{
    QSettings settings(":/config/setting.ini",QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    settings.beginGroup("DEPARTMENT");
    this->tempDepName = QObject::tr(settings.value("TEMPLATE_DEPARTMENT_NAME","部门").toString().toUtf8());
    settings.endGroup();


    /// 从数据库中进行检索
    QStringList columns;
    QVector<QVariant> values;
    auto records = QQueueSqlHelper::getQQueueSqlHelper()->queryRecord("Department",columns,values);
    foreach(auto item , records)
    {
        auto info = new QQueueDepartmentInfo(item["name"].toString(), item["dep_id"].toInt(),false, item["id"].toInt());
        this->depList->push_back(info);
        this->ui->dep_list_widget->addItem(info->getName() + "(" +  QString::number(info->getId()) +")");
    }
}

void QQueueDepartmentSetting::SaveUpdated()
{
    auto db = QQueueSqlHelper::getQQueueSqlHelper();
    QStringList columns;
    QVector<QVariant> values;
    columns.append("name");
    columns.append("dep_id");
    foreach(auto item , *this->depList)
    {
        if(item->getIsChanged())
        {
            values.clear();
            values.append(item->getName());
            values.append(QString::number(item->getId()));
            if(-1 == item->getRecordId())
            {
                db->insertOneRecord("Department", columns, values);
            }
            else
            {
                db->updateOneRecord("Department", item->getRecordId(), columns, values);
            }
        }
    }
}


