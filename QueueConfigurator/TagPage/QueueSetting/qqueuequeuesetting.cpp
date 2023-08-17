#include "qqueuequeuesetting.h"
#include "ui_qqueuequeuesetting.h"

QQueueQueueSetting::QQueueQueueSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQueueQueueSetting)
{
    ui->setupUi(this);
}

QQueueQueueSetting::~QQueueQueueSetting()
{
    delete ui;
}
