#include "staritem.h"
#include <QtGui>
#include <QGraphicsSceneMouseEvent>

StarItem::StarItem(QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
    ,m_color(Qt::black)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    init_animation();
}

void StarItem::animate_move(QPointF p, int msec)
{
    pos_animate->stop();
    pos_animate->setDuration(msec);
    pos_animate->setEasingCurve(QEasingCurve::InQuad);
    pos_animate->setStartValue(this->pos());
    pos_animate->setEndValue(p);
    pos_animate->start();
}

void StarItem::animate_delete(int msec)
{
    delete_animate->setDuration(msec);
    pos_animate->setEasingCurve(QEasingCurve::InQuad);
    delete_animate->setStartValue(this->rect());
    delete_animate->setEndValue(QRectF(0, 0, 0, 0));
    delete_animate->start();
}

void StarItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::black);
    painter->setBrush(QBrush(m_color));
    painter->drawPolygon(getDrawPolygon());
}

void StarItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    Q_EMIT clicked();
}


void StarItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{

}

void StarItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
//    if (delete_animate->state() != QAbstractAnimation::Running)
//        Q_EMIT clicked();
}

QPolygonF StarItem::getDrawPolygon() const
{
    const qreal width = rect().width();
    const qreal height = rect().height();

    QPointF p1(0, 0);
    QPointF p2(0.5*width, 0.25*height);
    QPointF p3(width, 0);
    QPointF p4(0.75*width, 0.5*height);
    QPointF p5(width, height);
    QPointF p6(0.5*width, 0.75*height);
    QPointF p7(0, height);
    QPointF p8(0.25*width, 0.5*height);

    QPolygonF polygon;
    polygon.append(p1);
    polygon.append(p2);
    polygon.append(p3);
    polygon.append(p4);
    polygon.append(p5);
    polygon.append(p6);
    polygon.append(p7);
    polygon.append(p8);

    return polygon;
}

void StarItem::init_animation()
{
    pos_animate = new QPropertyAnimation(this, "pos", this);
    pos_animate->setEasingCurve(QEasingCurve::InQuad);

    delete_animate = new QPropertyAnimation(this, "rect", this);
    delete_animate->setEasingCurve(QEasingCurve::InQuad);

    connect(delete_animate, &QPropertyAnimation::finished, this, &StarItem::deleteLater);
}
