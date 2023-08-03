#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QListWidgetItem>

#include "qqueuedepartmentdefinition.h"
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

private slots:
    void on_pushButton_18_clicked();
    void on_dep_add_btn_clicked();
    void on_dep_rem_btn_clicked();
    void on_dep_clr_btn_clicked();

    void on_dep_list_widget_itemSelectionChanged();

private:
    void init();
    void initDepTab();


    QQueueDepartmentInfo* findDepInfo(const QString &displayName);

private:
    Ui::MainWindow *ui;    
    QString tempDepName;
    QVector<QQueueDepartmentInfo*>* depList;

};
#endif // MAINWINDOW_H
