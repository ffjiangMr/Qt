#ifndef QQUEUEQUEUESETTING_H
#define QQUEUEQUEUESETTING_H

#include <QWidget>

namespace Ui {
class QQueueQueueSetting;
}

class QQueueQueueSetting : public QWidget
{
    Q_OBJECT

public:
    explicit QQueueQueueSetting(QWidget *parent = nullptr);
    ~QQueueQueueSetting();

private:
    Ui::QQueueQueueSetting *ui;
};

#endif // QQUEUEQUEUESETTING_H
