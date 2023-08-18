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
    Q_INVOKABLE explicit QQueueQueueSetting(QWidget *parent = nullptr);
    Q_INVOKABLE explicit QQueueQueueSetting(const QQueueQueueSetting& object);
    ~QQueueQueueSetting();

private:
    Ui::QQueueQueueSetting *ui;
};
Q_DECLARE_METATYPE(QQueueQueueSetting)
#endif // QQUEUEQUEUESETTING_H
