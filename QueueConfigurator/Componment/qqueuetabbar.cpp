#include "qqueuetabbar.h"
#include <QGridLayout>


QQueueTabBar::QQueueTabBar(QWidget *parent):
    QTabBar(parent)
{
    auto layout = new QGridLayout(this);
}
