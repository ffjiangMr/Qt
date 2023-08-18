#include "qqueuequeuesetting.h"
#include "ui_qqueuequeuesetting.h"

QQueueQueueSetting::QQueueQueueSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQueueQueueSetting)
{
    ui->setupUi(this);
}

QQueueQueueSetting::QQueueQueueSetting(const QQueueQueueSetting& object)
{
    QQueueQueueSetting(static_cast<QWidget*>(object.parent()));
}

QQueueQueueSetting::~QQueueQueueSetting()
{
    delete ui;
}
