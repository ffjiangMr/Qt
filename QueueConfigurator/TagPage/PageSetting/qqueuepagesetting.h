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
    explicit QQueuePageSetting(QWidget *parent = nullptr);
    ~QQueuePageSetting();

private:
    Ui::QQueuePageSetting *ui;
};

#endif // QQUEUEPAGESETTING_H
