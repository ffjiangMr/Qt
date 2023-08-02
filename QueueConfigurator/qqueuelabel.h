#ifndef QQUEUELABEL_H
#define QQUEUELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>

class QQueueLabel : public QLabel
{
    Q_OBJECT

    enum {
        EDGENULL = 0,
        TOPLEFT,
        TOPRIGHT,
        BOTTOMRIGHT,
        BOTTOMLEFT,
        TOP,
        RIGHT,
        BOTTOM,
        LEFT
    };
public:
    QQueueLabel(QWidget *parent = nullptr);
    ~QQueueLabel();

    inline bool IsZoom()
    {
        return this->zoom;
    }

private:
    bool key_down;
    bool zoom;
    int is_on_edge;
    int left;
    int top;
    int right;
    int bottom;
    int min_width;
    int min_height;
    QPoint last_point;
    QPoint current_point;
    QPoint point;
    QPoint temp_point;

   // QWidget *widget;

    void updateCursor();
    void mouseIsOnEdge(const QPoint &point, const QRect &rect);
    void resizeWidget(const QPoint &p);
    void widgetEventHandler(QEvent *e);
    void mouseHoverEventHandler(QHoverEvent *e);
    void mouseMoveEventHandler(QMouseEvent *e);
    void mousePressEventHandler(QMouseEvent *e);
    void mouseReleaseEventHandler(QMouseEvent *e);

protected:
    bool eventFilter(QObject *obj, QEvent *e) override;

};

#endif // QQUEUELABEL_H
