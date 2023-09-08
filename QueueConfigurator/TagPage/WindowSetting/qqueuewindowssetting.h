#ifndef QQUEUEWINDOWSSETTING_H
#define QQUEUEWINDOWSSETTING_H

#include <QWidget>

#include "../../DataStruct/qqueuewindowdefinition.h"

namespace Ui {
class QQueueWindowsSetting;
}

class QQueueWindowsSetting : public QWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit QQueueWindowsSetting(QWidget *parent = nullptr);
    Q_INVOKABLE explicit QQueueWindowsSetting(const QQueueWindowsSetting& object);
    Q_INVOKABLE void SaveUpdated();
    ~QQueueWindowsSetting();

private:
    void initData();
    QQueueWindowsDefinition* findWindowCounterInfo(const QString &displayName);
    Q_INVOKABLE void clearControl(bool enable = false);

private slots:
        void onAddBtnClicked();
        void onRemBtnClicked();
        void onClrBtnClicked();
        void onListWidgetItemSelectionChanged();
        void onOkBtnClicked();

private:
    Ui::QQueueWindowsSetting *ui;
    QVector<QQueueWindowsDefinition*>* windowList;
    QString tempName;
};
Q_DECLARE_METATYPE(QQueueWindowsSetting)
#endif // QQUEUEWINDOWSSETTING_H
