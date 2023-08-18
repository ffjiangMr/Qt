#ifndef QQUEUEPAGESETTING_H
#define QQUEUEPAGESETTING_H

#include <QWidget>

namespace Ui {
class QQueuePageSetting;
}

class QQueuePageSetting : public QWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit QQueuePageSetting(QWidget *parent = nullptr);
    Q_INVOKABLE explicit QQueuePageSetting(const QQueuePageSetting& object);
    ~QQueuePageSetting();

private:
    Ui::QQueuePageSetting *ui;
};
Q_DECLARE_METATYPE(QQueuePageSetting)
#endif // QQUEUEPAGESETTING_H
