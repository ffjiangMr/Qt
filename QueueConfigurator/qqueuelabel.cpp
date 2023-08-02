#include "qqueuelabel.h"
#include <QEvent>
#include <QHoverEvent>
#include <QMouseEvent>
#include <math.h>
#include <QDebug>

QQueueLabel::QQueueLabel(QWidget *parent)
    :QLabel(parent)
{
    this->key_down = false;
    this->zoom = false;
    this->is_on_edge = 0;
    this->installEventFilter(this);
    this->setAttribute(Qt::WA_Hover,true);
}

QQueueLabel::~QQueueLabel()
{
    this->removeEventFilter(this);
}

bool QQueueLabel::eventFilter(QObject *obj, QEvent *e)
{
    bool result = true;
    switch(e -> type())
    {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
        if(this->is_on_edge != EDGENULL)
        {
            widgetEventHandler(e);
        }
        else
        {
            QObject::eventFilter(obj, e);
        }
    case QEvent::HoverMove:
        widgetEventHandler(e);
    default:
        result = QObject::eventFilter(obj, e);
    }
    return result;
}

void QQueueLabel::widgetEventHandler(QEvent *e) {
    switch(e -> type()) {
    case QEvent::HoverMove:
        mouseHoverEventHandler(static_cast<QHoverEvent *>(e));
        break;
    case QEvent::MouseButtonPress:
        mousePressEventHandler(static_cast<QMouseEvent *>(e));
        break;
    case QEvent::MouseButtonRelease:
        mouseReleaseEventHandler(static_cast<QMouseEvent *>(e));
        break;
    default:
        break;
    }
}

void QQueueLabel::mouseHoverEventHandler(QHoverEvent *e) {
    if(!key_down){      //在窗口被拉扯或移动的过程中，停止对鼠标的悬浮监听
        QPoint point(this->x()+e->pos().x(), this->y() + e->pos().y());
        mouseIsOnEdge(point, this->geometry());
        updateCursor();
    }
    else
    {
        current_point = e->pos();
        current_point = this->mapToParent(current_point);
        if(zoom) {
            resizeWidget(current_point);
        }
    }
}

void QQueueLabel::mouseIsOnEdge(const QPoint& point, const QRect& rect) {

    if((abs(rect.x() + rect.width() - point.x()) < 10) && (abs(point.y() - rect.y()) < 10)) {
        is_on_edge = TOPRIGHT; //右上方
    }
    else if((abs(point.x() - rect.x()) < 10) && (abs(point.y() - rect.y()) < 10)) {
        is_on_edge = TOPLEFT; //左上方
    }
    else if((abs(rect.x() + rect.width() - point.x()) < 10) && (abs(rect.y() + rect.height() - point.y()) < 10)) {
        is_on_edge = BOTTOMRIGHT; //右下方
    }
    else if((abs(point.x() - rect.x()) < 10) && (abs(rect.y() + rect.height() - point.y()) < 10)) {
        is_on_edge = BOTTOMLEFT; //左下方
    }
    else if(abs(point.y() - rect.y()) < 10) {
        is_on_edge = TOP; //上边
    }
    else if(abs(rect.x() + rect.width() - point.x()) < 10) {
        is_on_edge = RIGHT; //右边
    }
    else if(abs(rect.y() + rect.height() - point.y()) < 10) {
        is_on_edge = BOTTOM; //下边
    }
    else if(abs(point.x() - rect.x()) < 10) {
        is_on_edge = LEFT; //左边
    }
    else {
        is_on_edge = EDGENULL; //不沾边
    }

    zoom = is_on_edge == EDGENULL ? false : true;
}

void QQueueLabel::updateCursor() {
    switch(is_on_edge) {
    case TOPLEFT:     //左上方
    case BOTTOMRIGHT:     //右下方
        this -> setCursor(Qt::SizeFDiagCursor);   //左上-右下
        break;
    case TOPRIGHT:     //右上方
    case BOTTOMLEFT:     //左下方
        this -> setCursor(Qt::SizeBDiagCursor);   //右上-左下
        break;
    case TOP:     //上边
    case BOTTOM:     //下边
        this -> setCursor(Qt::SizeVerCursor);     //上-下
        break;
    case RIGHT:     //右边
    case LEFT:     //左边
        this -> setCursor(Qt::SizeHorCursor);     //左-右
        break;
    case EDGENULL:
    default:
        this -> setCursor(Qt::ArrowCursor);       //箭头
        break;
    }
}

void QQueueLabel::resizeWidget(const QPoint& p) {
    min_width = this -> minimumWidth();
    min_height = this -> minimumHeight();

    QRect frame = this -> frameGeometry(); //获取窗口的几何框架

    switch(is_on_edge) {    //根据边框的位置改变窗口的形状
        case TOPLEFT:     //左上方
            temp_point = frame.topLeft();
            if(frame.bottomRight().x() - p.x() > min_width) { temp_point.setX(p.x()); }
            if(frame.bottomRight().y() - p.y() > min_height) { temp_point.setY(p.y()); }
            if(frame.bottomRight().x() - p.x() <= min_width && frame.bottomRight().y() - p.y() <= min_height) {
                temp_point.setX(frame.bottomRight().x() - min_width);
                temp_point.setY(frame.bottomRight().y() - min_height);
            }
            frame.setTopLeft(temp_point);
            break;

        case TOPRIGHT:     //右上方
            temp_point = frame.topRight();
            if(p.x() - frame.bottomLeft().x() > 0) { temp_point.setX(p.x()); }
            if(frame.bottomLeft().y() - p.y() > min_height) { temp_point.setY(p.y()); }
            if(p.x() - frame.bottomLeft().x() <= 0 && frame.bottomLeft().y() - p.y() <= min_height) {
                temp_point.setX(p.x());
                temp_point.setY(frame.bottomLeft().y() - min_height);
            }
            frame.setTopRight(temp_point);
            break;

        case BOTTOMRIGHT:   //右下方
            temp_point = frame.bottomRight();
            if(p.x() - frame.topLeft().x() > 0) { temp_point.setX(p.x()); }
            if(p.y() - frame.topLeft().y() > 0) { temp_point.setY(p.y()); }
            if(p.x() - frame.topLeft().x() <= 0 && p.y() - frame.topLeft().y() <= 0) {
                temp_point.setX(p.x());
                temp_point.setY(p.y());
            }
            frame.setBottomRight(temp_point);
            break;

        case BOTTOMLEFT:    //左下方
            temp_point = frame.bottomLeft();
            if(frame.topRight().x() - p.x() > min_width) { temp_point.setX(p.x()); }
            if(p.y() - frame.topRight().y() > 0) { temp_point.setY(p.y()); }
            if(frame.topRight().x() - p.x() <= min_width && p.y() - frame.topRight().y() <= 0) {
                temp_point.setX(frame.topRight().x() - min_width);
                temp_point.setY(p.y());
            }
            frame.setBottomLeft(temp_point);
            break;

        case TOP:           //上边
            temp_point = frame.topRight();
            if(frame.bottomLeft().y() - p.y() > min_height) { temp_point.setY(p.y()); }
            frame.setTopRight(temp_point);
            break;

        case RIGHT:         //右边
            temp_point = frame.bottomRight();
            if(p.x() - frame.topLeft().x() > 0) { temp_point.setX(p.x()); }
            frame.setBottomRight(temp_point);
            break;

        case BOTTOM:        //下边
            temp_point = frame.bottomLeft();
            if(p.y() - frame.topRight().y() > 0) { temp_point.setY(p.y()); }
            frame.setBottomLeft(temp_point);
            break;

        case LEFT:          //左边

            temp_point = frame.topLeft();
            frame.setX(p.x());
            frame.setWidth(this->x() - p.x() + this->width());
//            if(frame.bottomRight().x() - p.x() > min_width) { temp_point.setX(p.x()); }
//            frame.setTopLeft(temp_point);
            break;

        default:
            break;
    }
    this -> setGeometry(frame);    //给窗口设置新的几何框架
}


void QQueueLabel::mouseMoveEventHandler(QMouseEvent *e) {
    Q_UNUSED(e);

    if(key_down) {
        current_point = e->pos();
        current_point = this->mapToParent(current_point);
        if(zoom) {
            resizeWidget(current_point);
        }
    }
}

void QQueueLabel::mousePressEventHandler(QMouseEvent *e) {
    if((this->is_on_edge != EDGENULL) && (e -> button() == Qt::LeftButton)) {
        key_down = true;
        last_point = e -> pos();
    }
}

void QQueueLabel::mouseReleaseEventHandler(QMouseEvent *e) {
    if(e -> button() == Qt::LeftButton) {
        key_down = false;      //按键松开
    }
}

