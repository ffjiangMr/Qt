#include "qqueuemachinewindow.h"
#include "ui_qqueuemachinewindow.h"

#include <QDrag>
#include <QPixmap>
#include <QByteArray>
#include <QMimeData>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QStyleFactory>
#include <QPainter>
#include "qqueuelabel.h"

QQueueMachineWindow::QQueueMachineWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QQueueMachineWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

QQueueMachineWindow::~QQueueMachineWindow()
{
    delete ui;
}

void QQueueMachineWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mousePressEvent";
    auto child = childAt(event->pos());
    if(true == child->inherits("QLabel"))
    {
        if((true == child->inherits("QQueueLabel")) && (false == static_cast<QQueueLabel*>(child)->IsZoom()))
        {
            this->onLabelEvent(event);
        }
    }
    else if(true == child->inherits("QPushButton"))
    {
        this->onPushbuttonEvent(event);
    }
    else
    {
        QMainWindow::mousePressEvent(event);
    }
}

void QQueueMachineWindow::onLabelEvent(QMouseEvent *event)
{
    auto label = static_cast<QLabel*>(childAt(event->pos()));
    this->onDropEvent(label->text(),event,label);
}

void QQueueMachineWindow::onDropEvent(QString text,QMouseEvent* event, QWidget* child)
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream<< QPoint(event->pos() - child->pos());
    dataStream<< event->pos();
    QMimeData* mimeData = new QMimeData();
    QDrag *drag = new QDrag(this->centralWidget());
    mimeData->setText(text);
    mimeData->setData("QQueueMachine/drag",itemData);
    QPixmap pix(":/image/hand_icon.png");
    drag->setDragCursor(pix,Qt::DropAction::MoveAction);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - child->pos());
    QPixmap temp(":/image/temp.png");
    QLabel tempLabel;
    tempLabel.setPixmap(temp);
    tempLabel.resize(child->size());
    tempLabel.setScaledContents(true);
    QPixmap pix_drag(tempLabel.pixmap()->scaled(child->size()));
    drag->setPixmap(pix_drag);
    child->setStyleSheet("background-color:rgba(211, 211, 211,211)");
    if(drag->exec(Qt::MoveAction) == Qt::MoveAction)
    {
        child->close();
    }
    else
    {
        child->show();
        child->setStyleSheet("{background-color:rgba(0, 0, 0,0);}");
    }
    mimeData->deleteLater();
    drag->deleteLater();
}

void QQueueMachineWindow::onPushbuttonEvent(QMouseEvent *event)
{
    auto btn = static_cast<QPushButton*>(childAt(event->pos()));
    this->onDropEvent(btn->text(),event,btn);
}

void QQueueMachineWindow::mouseMoveEvent(QMouseEvent *event)
{
    QMainWindow::mouseMoveEvent(event);
}

void QQueueMachineWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat(QObject::tr("QQueueMachine/drag")))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void QQueueMachineWindow::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->mimeData()->hasFormat(QObject::tr("QQueueMachine/drag")))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void QQueueMachineWindow::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasFormat(QObject::tr("QQueueMachine/drag")))
    {
        QByteArray itemData = event->mimeData()->data("QQueueMachine/drag");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPoint offset, eventPos;
        dataStream>>offset>>eventPos;
        auto event_child = childAt(eventPos);
        QWidget* child = nullptr;
        if(true == event_child->inherits("QLabel"))
        {
            child = new QQueueLabel(this);
            static_cast<QLabel*>(child)->setText(event->mimeData()->text());
        }
        else if(true == event_child->inherits("QPushButton"))
        {
            child = new QPushButton(event->mimeData()->text(),this);
        }
        child->resize(event_child->size());
        child->move(event->pos() - offset);
        child->show();
        child->setAttribute(Qt::WA_DeleteOnClose);
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
