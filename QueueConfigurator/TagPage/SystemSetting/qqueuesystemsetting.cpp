#include "qqueuesystemsetting.h"
#include "ui_qqueuesystemsetting.h"

QQueueSystemSetting::QQueueSystemSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQueueSystemSetting)
{
    ui->setupUi(this);
}

QQueueSystemSetting::~QQueueSystemSetting()
{
    delete ui;
}
