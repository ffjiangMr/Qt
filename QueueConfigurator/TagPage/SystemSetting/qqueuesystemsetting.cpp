#include "qqueuesystemsetting.h"
#include "ui_qqueuesystemsetting.h"

QQueueSystemSetting::QQueueSystemSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQueueSystemSetting)
{
    ui->setupUi(this);
}

 QQueueSystemSetting::QQueueSystemSetting(const QQueueSystemSetting& object):
     QWidget(static_cast<QWidget*>(object.parent())),
     ui(new Ui::QQueueSystemSetting)
 {
     ui->setupUi(this);
 }

QQueueSystemSetting::~QQueueSystemSetting()
{
    delete ui;
}
