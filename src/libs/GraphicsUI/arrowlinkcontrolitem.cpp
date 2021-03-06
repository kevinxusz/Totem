#include "arrowlinkcontrolitem.h"
#include <QPainterPath>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>


namespace GraphicsUI{
const int AC_WIDTH = 12;
const int AC_HEIGHT = 12;
ArrowLinkControlItem::ArrowLinkControlItem(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    setAcceptHoverEvents(true);
	m_bPressed = false;
    setFlags(ItemSendsScenePositionChanges
             | ItemIgnoresTransformations);
	setCacheMode(DeviceCoordinateCache);
}

QRectF ArrowLinkControlItem::boundingRect() const
{
    return QRectF(-AC_WIDTH*1.0/2,-AC_WIDTH*1.0/2, AC_WIDTH, AC_HEIGHT);
}

void ArrowLinkControlItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QPainterPath path( rect.center() - QPointF(rect.width() / 2, 0));
    path.lineTo( rect.center() - QPointF(0, rect.height() / 2));
    path.lineTo( rect.center() + QPointF(rect.width() / 2, 0));
    path.lineTo( rect.center() + QPointF(0, rect.height() / 2));
    path.closeSubpath();
    painter->setPen(QColor(0, 255, 100));
    painter->setBrush(Qt::yellow);
    painter->drawPath(path);
}

QVariant ArrowLinkControlItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemScenePositionHasChanged && scene())
    {
        emit positionChanged();
    }
	else if (change == ItemSelectedHasChanged)
	{
		QGraphicsItem *pItem = parentItem();
		if(pItem)
			pItem->setFlag(ItemIsMovable, !value.toBool());
	}
    return QGraphicsItem::itemChange(change, value);
}

ArrowLinkControlItem::~ArrowLinkControlItem()
{

}

void ArrowLinkControlItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (!m_bPressed)
		return;

	QPointF pt = event->scenePos();
	QPointF ptItem = pt;
	if (parentItem())
		ptItem = parentItem()->mapFromScene(pt);
	setPos(ptItem);
	event->accept();
}

void ArrowLinkControlItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	grabMouse();
	m_bPressed = true;
}

void ArrowLinkControlItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	ungrabMouse();
	m_bPressed = false;
}

}
