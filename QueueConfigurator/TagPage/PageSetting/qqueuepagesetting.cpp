#include "qqueuepagesetting.h"
#include "ui_qqueuepagesetting.h"

QQueuePageSetting::QQueuePageSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQueuePageSetting)
{
    ui->setupUi(this);
}

QQueuePageSetting::~QQueuePageSetting()
{
    delete ui;
}
