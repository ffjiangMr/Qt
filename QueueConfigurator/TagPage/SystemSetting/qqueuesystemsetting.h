#ifndef QQUEUESYSTEMSETTING_H
#define QQUEUESYSTEMSETTING_H

#include <QWidget>

namespace Ui {
class QQueueSystemSetting;
}

class QQueueSystemSetting : public QWidget
{
    Q_OBJECT

public:
    explicit QQueueSystemSetting(QWidget *parent = nullptr);
    ~QQueueSystemSetting();

private:
    Ui::QQueueSystemSetting *ui;
};

#endif // QQUEUESYSTEMSETTING_H
