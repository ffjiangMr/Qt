#ifndef QQUEUELISTWIDGET_H
#define QQUEUELISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QMouseEvent>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QPoint>
#include <QMimeData>

class QQueueListWidget : public QListWidget
{
    Q_OBJECT
public:
    QQueueListWidget(QWidget *parent = nullptr);
private:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

#endif // QQUEUELISTWIDGET_H
