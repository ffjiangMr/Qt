#include "qqueuewindowssetting.h"
#include "ui_qqueuewindowssetting.h"

QQueueWindowsSetting::QQueueWindowsSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQueueWindowsSetting)
{
    ui->setupUi(this);
}

QQueueWindowsSetting::QQueueWindowsSetting(const QQueueWindowsSetting& object)
{
    QQueueWindowsSetting(static_cast<QWidget*>(object.parent()));
}

QQueueWindowsSetting::~QQueueWindowsSetting()
{
    delete ui;
}
