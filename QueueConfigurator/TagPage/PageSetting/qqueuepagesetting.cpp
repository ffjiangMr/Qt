#include "qqueuepagesetting.h"
#include "ui_qqueuepagesetting.h"
#include "../../qqueuemachinewindow.h"

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

void QQueuePageSetting::on_pushButton_18_clicked()
{
        auto win = new QQueueMachineWindow(this);
        win->setWindowModality(Qt::ApplicationModal);
        win->show();
}
