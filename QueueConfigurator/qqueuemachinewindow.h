#ifndef QQUEUEMACHINEWINDOW_H
#define QQUEUEMACHINEWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDrag>


namespace Ui {
class QQueueMachineWindow;
}

class QQueueMachineWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QQueueMachineWindow(QWidget *parent = nullptr);    
    ~QQueueMachineWindow();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void dragEnterEvent(QDragEnterEvent *event)override;
    void dragMoveEvent(QDragMoveEvent *event)override;
    void dropEvent(QDropEvent *event)override;


private:
    void onLabelEvent(QMouseEvent* event);
    void onPushbuttonEvent(QMouseEvent* event);
    void onDropEvent(QString text,QMouseEvent* event, QWidget* child);

private:
    Ui::QQueueMachineWindow *ui;
};

#endif // QQUEUEMACHINEWINDOW_H
