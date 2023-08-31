#ifndef QQUEUEEMPLOYEESETTING_H
#define QQUEUEEMPLOYEESETTING_H

#include <QWidget>
#include <QVector>

#include "../../DataStruct/qqueueemployeedefinition.h"

namespace Ui {
class QQueueEmployeeSetting;
}

class QQueueEmployeeSetting : public QWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit QQueueEmployeeSetting(QWidget *parent = nullptr);
    Q_INVOKABLE explicit QQueueEmployeeSetting(const QQueueEmployeeSetting& object);
    Q_INVOKABLE void SaveUpdated();
    ~QQueueEmployeeSetting();

private:
    void initData();
    QQueueEmployeeDefinition* findEmployeeInfo(const QString &displayName);
    Q_INVOKABLE void clearControl(bool enable = false);

private slots:
        void onAddBtnClicked();
        void onRemBtnClicked();
        void onClrBtnClicked();
        void onListWidgetItemSelectionChanged();
        void onOkBtnClicked();

private:
    Ui::QQueueEmployeeSetting *ui;
    QVector<QQueueEmployeeDefinition*>* employeeList;
    QString tempName;
};
Q_DECLARE_METATYPE(QQueueEmployeeSetting)
#endif // QQUEUEEMPLOYEESETTING_H
