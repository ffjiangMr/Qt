#ifndef QQUEUESYSTEMSETTING_H
#define QQUEUESYSTEMSETTING_H

#include <QWidget>
#include <QFont>

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
    Q_INVOKABLE void SaveUpdated();

private:
    void initData();
    void initDefaultData();

private slots:
    void onShowPassword(int state);
    void onShowTime(int state);
    void onShowIdCard(int state);
    void onBtnFontSetting();
    void onOldPswChanged();
    void onNewPswChanged();



private:
    Ui::QQueueSystemSetting *ui;
    bool isNewSetting;
    bool isMatchOld;
    bool isMatchNew;
    QFont* timeFont;
    QString tempPsw;
    int  tempId;
};
Q_DECLARE_METATYPE(QQueueSystemSetting)
#endif // QQUEUESYSTEMSETTING_H
