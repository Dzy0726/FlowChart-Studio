#include "diamonditem.h"
#include "nodeevents.h"


void DiamondItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(isSelected)
    {
        node->SetLocation(event->pos());
    }
}



void DiamondItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}



void DiamondItem::keyPressEvent(QKeyEvent *event)
{

}

void DiamondItem::keyReleaseEvent(QKeyEvent *event)
{

}


void DiamondItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(contains(event->pos()))
    {
        isSelected=true;
        NodeEvents::mousePressEvent(node, event);
    }
}

void DiamondItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(isSelected)
    {
       NodeEvents::mouseReleaseEvent(node, event);
    }
    isSelected=false;
}

void DiamondItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    NodeEvents::contextMenuEvent(node, event);
}
