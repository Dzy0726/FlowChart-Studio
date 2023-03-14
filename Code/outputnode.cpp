#include "outputnode.h"
#include "graph.h"
#include "subgraphnode.h"
#include "inneroutputnode.h"
#include "changeelementaction.h"
#include "elementshape.h"
#include "arrow.h"
OutputNode::OutputNode()
{

}
OutputNode:: OutputNode(QPointF lc,double wd,double h):Node(lc,wd,h)
{


}
OutputNode::~OutputNode()
{
    delete shape;
    delete subShape;
}
void OutputNode::Paint(QGraphicsScene *qgs)
{
    Node::Paint(qgs);
    qgs->addItem(subShape);
    if(GetType()==5)
    {
        if(fatherGraph)
        {
            QMap<int,SubgraphNode*> qm=fatherGraph->getRelatedNodes();
            foreach(auto i,qm)
            {
                InnerOutputNode* ion=new InnerOutputNode(QPointF(i->GetLocation().x()+i->GetWidth(),i->GetLocation().y()-i->GetHeight()),width,height);
                ChangeElementAction* CEA1=new ChangeElementAction(ion,ElementShape::InnerOutput,true,(Scene*)i->GetRelatedQGS());
                Arrow* arr=new Arrow(i->getNodeItem(),ion->getNodeItem(),1);
                CEA1->Do();
                relatedInner.insert(ion->GetID(),ion);
                ChangeElementAction* CEA2=new ChangeElementAction(arr,ElementShape::Arrow,true,(Scene*)i->GetRelatedQGS());
                CEA2->Do();
                ion->BindToText(ion->relatedQGS);
                QString temp="0x";
                temp+= QString::number(GetID(),16);
                ion->content->change_input(temp);
                ion->content->change_content("文本");
            }
        }
    }
}

void OutputNode::Remove(QGraphicsScene *qgs)
{
    Node::Remove(qgs);
    qgs->removeItem(subShape);
    foreach(auto i,relatedInner)
    {
         ChangeElementAction* CEA=new ChangeElementAction(i,ElementShape::InnerOutput,false,(Scene*)i->GetRelatedQGS());
         CEA->Do();
    }
}

void OutputNode::ChangeZValue(bool isSelected)
{
    Node::ChangeZValue(isSelected);
    subShape->setZValue(shape->zValue());
}
void OutputNode::SetShape()
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()+width/2,location.y()-height/2)<<QPointF(location.x(),location.y()-height/2);
    polygon<<QPoint(location.x()-width/2,location.y());
    polygon<<QPointF(location.x(),location.y()+height/2)<<QPointF(location.x()+width/2,location.y()+height/2);
    shape->setPolygon(polygon);
    double k1=0.8,k2=0.6;
    subShape->setRect(location.x()+width/4-k2*width/4,location.y()-k1*height/2,k2*width/2,k1*height);
}
void OutputNode::SetFrameColor(const QColor &qc)
{
    Node::SetFrameColor(qc);
    QPen pen=shape->pen();
    pen.setColor(frameColor);
    subShape->setPen(pen);
}
void OutputNode::SetThickness(double nt)
{
    Node::SetThickness(nt);
    QPen pen=shape->pen();
    pen.setWidthF(nt);
    subShape->setPen(pen);
}
int OutputNode::GetType()
{
    return 5;
}
