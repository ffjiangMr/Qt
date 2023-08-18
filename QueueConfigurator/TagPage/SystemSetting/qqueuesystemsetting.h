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
    Q_INVOKABLE explicit QQueueSystemSetting(QWidget *parent = nullptr);
    Q_INVOKABLE explicit QQueueSystemSetting(const QQueueSystemSetting& object);
    ~QQueueSystemSetting();

private:
    Ui::QQueueSystemSetting *ui;
};
Q_DECLARE_METATYPE(QQueueSystemSetting)
#endif // QQUEUESYSTEMSETTING_H
