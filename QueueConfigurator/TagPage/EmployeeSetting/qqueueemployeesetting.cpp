#include "qqueueemployeesetting.h"
#include "ui_qqueueemployeesetting.h"

QQueueEmployeeSetting::QQueueEmployeeSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQueueEmployeeSetting)
{
    ui->setupUi(this);
}

QQueueEmployeeSetting::QQueueEmployeeSetting(const QQueueEmployeeSetting& object)
{
    QQueueEmployeeSetting(static_cast<QWidget*>(object.parent()));
}

QQueueEmployeeSetting::~QQueueEmployeeSetting()
{
    delete ui;
}
