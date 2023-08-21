#ifndef QQUEUEWINDOWSSETTING_H
#define QQUEUEWINDOWSSETTING_H

#include <QWidget>

namespace Ui {
class QQueueWindowsSetting;
}

class QQueueWindowsSetting : public QWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit QQueueWindowsSetting(QWidget *parent = nullptr);
    Q_INVOKABLE explicit QQueueWindowsSetting(const QQueueWindowsSetting& object);
    ~QQueueWindowsSetting();

private:
    Ui::QQueueWindowsSetting *ui;
};
Q_DECLARE_METATYPE(QQueueWindowsSetting)
#endif // QQUEUEWINDOWSSETTING_H
