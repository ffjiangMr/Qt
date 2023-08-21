#ifndef QQUEUEEMPLOYEESETTING_H
#define QQUEUEEMPLOYEESETTING_H

#include <QWidget>

namespace Ui {
class QQueueEmployeeSetting;
}

class QQueueEmployeeSetting : public QWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit QQueueEmployeeSetting(QWidget *parent = nullptr);
    Q_INVOKABLE explicit QQueueEmployeeSetting(const QQueueEmployeeSetting& object);

    ~QQueueEmployeeSetting();

private:
    Ui::QQueueEmployeeSetting *ui;
};
Q_DECLARE_METATYPE(QQueueEmployeeSetting)
#endif // QQUEUEEMPLOYEESETTING_H
