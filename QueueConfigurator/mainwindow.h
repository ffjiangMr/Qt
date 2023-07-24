#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "systemsetttingtab.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init();


private:
    Ui::MainWindow *ui;
    SystemSetttingTab* sysemSettingTab;
};
#endif // MAINWINDOW_H
