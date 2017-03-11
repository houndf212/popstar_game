#ifndef STARITEM_H
#define STARITEM_H
#include <QtCore>
#include <QGraphicsItem>
#include "pos.h"

class StarItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(QRectF rect READ rect WRITE setRect)
public:
    Q_SIGNAL void clicked();
public:
    StarItem(QGraphicsItem *parent = 0);
    void animate_move(QPointF p, int msec);
    void animate_delete(int msec);
    QColor color() const { return m_color; }
    void setColor(QColor color) { m_color = color; }

    Pos original_pos() const { return m_original_pos; }
    void set_original_pos(Pos p) { m_original_pos = p; }

    Pos current_pos() const { return m_current_pos; }
    void set_current_pos(Pos p) { m_current_pos = p; }
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    // The mouse press event decides which item should become the mouse grabber (see QGraphicsScene::mouseGrabberItem()).
    // If you do not reimplement this function, the press event will propagate to any topmost item beneath this item,
    // and no other mouse events will be delivered to this item.
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) override;
private:
    QPolygonF getDrawPolygon() const;
    void init_animation();
private:
    Pos m_original_pos; // locate in board pos
    Pos m_current_pos;
    QColor m_color;
    QPropertyAnimation* pos_animate;
    QPropertyAnimation* delete_animate;
};

#endif // STARITEM_H
