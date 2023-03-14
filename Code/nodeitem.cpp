#include "nodeitem.h"
#include "nodeevents.h"
#include "node.h"
#include "QKeyEvent"
#include "QDebug"
#include "rectangle.h"
#include <cmath>
#include "mainwindow.h"
#include "groupaction.h"
#include "editelementaction.h"
#include"text.h"
#include"textitem.h"
#include "arrow.h"

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(isFocus)
    {
        isMoved=true;
        if(event->modifiers()==Qt::ShiftModifier&&isResized)
        {
            NodeEvents::scaleNodes(node, event);
        }
        else
        {
            NodeEvents::mouseMoveEvent(event);
            QGraphicsItem::mouseMoveEvent(event);
        }
    }
}

void NodeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
     QGraphicsItem::mouseDoubleClickEvent(event);
     isDoubleClick=true;
     if(this->GetNode()->GetType()!=3)
     {
     node->BindToText(MainWindow::instance()->scene());
     setSelected(false);
     node->content->getTextItem()->SetSelected(true);
     }
}

void NodeItem::keyPressEvent(QKeyEvent *event)
{

}

void NodeItem::keyReleaseEvent(QKeyEvent *event)
{


}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    if(event->button()==Qt::MouseButton::LeftButton)
    {
        isFocus=true;
        lastWidth=node->GetWidth();
        lastHeight=node->GetHeight();
        foreach (auto node, *MainWindow::instance()->selectedNodes())
        {
            auto item = node->getNodeItem();
            item->lastLocation=node->GetLocation();
        }
        if(event->modifiers()==Qt::ShiftModifier)
        {
            isResized=true;
        }
        auto text = GetNode()->content;
        if (text) text->lastPosition = text->get_text_location();
    }
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    isDoubleClick=false;
    if(isFocus)
    {
        if(isMoved)
        {
            if(isResized)
            {
                auto action = new GroupAction;
                foreach (auto node, *MainWindow::instance()->selectedNodes())
                {
                    auto item = node->getNodeItem();
                    if (item->lastWidth == node->GetWidth() && item->lastHeight == node->GetHeight()) continue;
                    *action << new EditElementAction(node, ElementShape::Rectangle,
                                                     ElementProperty::Size,
                                                     new QSizeF(item->lastWidth, item->lastHeight),
                                                     new QSizeF(node->GetWidth(), node->GetHeight()));
                }
            }
            else
            {
                NodeEvents::mouseReleaseEvent(event);
            }
        }
    }
    isMoved=false;
    isFocus=false;
    isResized=false;
}

QVariant NodeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        SetSelected(QGraphicsItem::isSelected());
    }
    return value;
}

void NodeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    NodeEvents::contextMenuEvent(node, event);
}


QPolygonF NodeItem::polygon() const{
    QPolygonF qpf;
    int w=node->GetWidth();
    int h=node->GetHeight();
    Rectangle* ractangle = dynamic_cast<Rectangle*>(node);
    if(ractangle!=nullptr){//表示矩形
        qpf<<QPointF(-w/2,-h/2)<<QPointF(w/2,-h/2)<<QPointF(w/2,h/2)<<QPointF(-w/2,h/2)<<QPointF(-w/2,-h/2);
    }
    else{//2表示菱形
        qpf<<QPointF(-w/2,0)<<QPointF(0,h/2)<<QPointF(w/2,0)<<QPointF(0,-h/2)<<QPointF(-w/2,0);
    }
    return qpf;


}

QPointF NodeItem::pos() {

    return node->GetLocation();
}
int NodeItem::GetWidth(){
    return node->GetWidth();
}
int NodeItem::GetHeight(){
    return node->GetHeight();
}
void NodeItem::RemoveAsSource(Arrow* ar){
    node->DisconnectAsSource(ar);
}
void NodeItem::RemoveAsDestination(Arrow* ar){
    node->DisconnectAsDestination(ar);
}

void NodeItem::SetSelected(bool b)
{
    isSelected=b;
    node->ChangeZValue(b);
    setSelected(b);
    emit Selected(node, QGraphicsItem::isSelected());
}
