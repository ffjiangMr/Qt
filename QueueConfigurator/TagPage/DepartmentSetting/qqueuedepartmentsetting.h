#ifndef QQUEUEDEPARTMENTSETTING_H
#define QQUEUEDEPARTMENTSETTING_H

#include "../../DataStruct/qqueuedepartmentdefinition.h"

#include <QWidget>

namespace Ui {
class QQueueDepartmentSetting;
}

class QQueueDepartmentSetting : public QWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit QQueueDepartmentSetting(QWidget *parent = nullptr);
    Q_INVOKABLE explicit QQueueDepartmentSetting(const QQueueDepartmentSetting& object);
    ~QQueueDepartmentSetting();

    inline bool getIsChanged(){return this->isChanged;}
    Q_INVOKABLE void SaveUpdated();

private:
    QQueueDepartmentSetting& operator=(const QQueueDepartmentSetting& object);
    QQueueDepartmentInfo* findDepInfo(const QString &displayName);
    void initData();

private slots:
        void onDepAddBtnClicked();
        void onDepRemBtnClicked();
        void onDepClrBtnClicked();
        void onDepListWidgetItemSelectionChanged();
        void onDepOkBtnClicked();

private:
    Ui::QQueueDepartmentSetting *ui;
    QVector<QQueueDepartmentInfo*>* depList;
    bool isChanged;
    QString tempDepName;
};
Q_DECLARE_METATYPE(QQueueDepartmentSetting)
#endif // QQUEUEDEPARTMENTSETTING_H
