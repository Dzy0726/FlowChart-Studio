#include "rectangleitem.h"
#include "nodeevents.h"
#include "node.h"

void RectangleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(isSelected)
    {
        node->SetLocation(event->pos());
    }
}

void RectangleItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void RectangleItem::keyPressEvent(QKeyEvent *event)
{

}

void RectangleItem::keyReleaseEvent(QKeyEvent *event)
{

}


void RectangleItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(contains(event->pos()))
    {
        isSelected=true;
        NodeEvents::mousePressEvent(node, event);
    }


}

void RectangleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(isSelected)
    {
       NodeEvents::mouseReleaseEvent(node, event);
    }
    isSelected=false;
}

void RectangleItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    NodeEvents::contextMenuEvent(node, event);
}
