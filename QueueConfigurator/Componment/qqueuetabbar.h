#ifndef QQUEUETABBAR_H
#define QQUEUETABBAR_H

#include <QObject>
#include <QWidget>
#include <QTabBar>

class QQueueTabBar : public QTabBar
{
    Q_OBJECT
public:
    QQueueTabBar(QWidget *parent = nullptr);
};

#endif // QQUEUETABBAR_H
