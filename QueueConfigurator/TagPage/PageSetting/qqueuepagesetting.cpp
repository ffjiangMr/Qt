#include "qqueuepagesetting.h"
#include "ui_qqueuepagesetting.h"

QQueuePageSetting::QQueuePageSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQueuePageSetting)
{
    ui->setupUi(this);
}


QQueuePageSetting::QQueuePageSetting(const QQueuePageSetting& object)
{
    QQueuePageSetting(static_cast<QWidget*>(object.parent()));
}

QQueuePageSetting::~QQueuePageSetting()
{
    delete ui;
}
