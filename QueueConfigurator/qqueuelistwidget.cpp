#include "qqueuelistwidget.h"
#include <QDrag>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include <QLabel>
#include <QPixmap>

QQueueListWidget::QQueueListWidget(QWidget *parent):QListWidget(parent)
{
    setDragEnabled(true);
    setAcceptDrops(true);
}

void QQueueListWidget::mousePressEvent( QMouseEvent *event )
{
      QListWidget::mousePressEvent(event);
}

void QQueueListWidget::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    auto selectedItem = itemAt(event->pos());
    QListWidgetItem *item = currentItem();
    if((nullptr != selectedItem) && (selectedItem == item))
    {
        QMimeData* mimeData = new QMimeData();
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream<<QPoint(event->pos());
        mimeData->setData(QObject::tr("QueueList/item"),itemData);
        mimeData->setText(item->text());
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        QPixmap pix(":/image/hand_icon.png");
        drag->setDragCursor(pix,Qt::DropAction::MoveAction);
        Qt::DropAction dropAction = drag->exec(Qt::MoveAction);
        if(dropAction == Qt::MoveAction)
        {
            delete item;
        }
        mimeData->deleteLater();
        drag->deleteLater();
    }
}

void QQueueListWidget::dragEnterEvent( QDragEnterEvent *event )
{
    QQueueListWidget *source = (QQueueListWidget *)(event->source());
    if (source && source == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void QQueueListWidget::dragMoveEvent( QDragMoveEvent *event )
{
    QQueueListWidget *source = (QQueueListWidget *)((void*)(event->source()));
    if (source && source == this) {
        event->setDropAction(Qt::MoveAction);

        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void QQueueListWidget::dropEvent( QDropEvent *event )
{
    QQueueListWidget *source = (QQueueListWidget *)(event->source());
    if(event->mimeData()->hasFormat(QObject::tr("QueueList/item")))
    {
        if (source && source == this)
        {
            QByteArray itemData = event->mimeData()->data("QueueList/item");
            QDataStream dataStream(&itemData, QIODevice::ReadOnly);
            QPoint startPos;
            dataStream >> startPos;
            QListWidgetItem *rawRow = itemAt(startPos);
            auto endPos = event->pos();
            QListWidgetItem *itemRow = itemAt(endPos);
            if(rawRow != itemRow)
            {
                int rawCount = row(rawRow);
                int rowCount = row(itemRow);
                int moveRow = rawCount<rowCount ? rowCount +1 :
                              rowCount == -1 ? source->count():
                                               rowCount;
                insertItem(moveRow,event->mimeData()->text());
                source->setCurrentRow(moveRow);
                event->setDropAction(Qt::MoveAction);
                event->accept();
            }
            else
            {
                event->ignore();
            }
        }
        else
        {
            event->ignore();
        }
    }
    else
    {
        event->ignore();
    }
}

