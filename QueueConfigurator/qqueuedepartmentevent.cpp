#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QString>
#include <QDebug>

void MainWindow::on_dep_add_btn_clicked()
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
    QQueueDepartmentInfo* info = new QQueueDepartmentInfo(this->tempDepName, id);
    this->depList->push_back(info);
    this->ui->dep_list_widget->addItem(info->getName() + "(" +  QString::number(info->getId()) +")");
}


void MainWindow::on_dep_rem_btn_clicked()
{
    this->ui->dep_list_widget->takeItem(this->ui->dep_list_widget->currentRow());
    if(this->ui->dep_list_widget->count() < 1)
    {
        this->ui->dep_rem_btn->setEnabled(false);
        this->ui->dep_name_line->clear();
        this->ui->dep_id_line->clear();
    }
}


void MainWindow::on_dep_clr_btn_clicked()
{
    this->ui->dep_list_widget->clear();
    this->ui->dep_rem_btn->setEnabled(false);
    this->ui->dep_name_line->clear();
    this->ui->dep_id_line->clear();
}


void MainWindow::on_dep_list_widget_itemSelectionChanged()
{
    this->ui->dep_rem_btn->setEnabled(true);
    if(-1 != this->ui->dep_list_widget->currentRow())
    {
        auto info = this->findDepInfo(this->ui->dep_list_widget->currentItem()->text());
        this->ui->dep_name_line->setText(info->getName());
        this->ui->dep_id_line->setText(QString::number(info->getId()));
    }
}

QQueueDepartmentInfo* MainWindow::findDepInfo(const QString &displayName)
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




