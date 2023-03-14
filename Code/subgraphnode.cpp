#include "subgraphnode.h"
#include "inputnode.h"
#include "innerinputnode.h"
#include "arrow.h"
#include "changeelementaction.h"
#include "subgraphnode.h"
#include "outputnode.h"
#include "inneroutputnode.h"
#include <math.h>

SubgraphNode::SubgraphNode()
{
     subShape.resize(2);
     subShape[0]=new QGraphicsLineItem();
     subShape[1]=new QGraphicsLineItem();
}
SubgraphNode:: SubgraphNode(QPointF lc,double wd,double h):Node(lc,wd,h)
{
    subShape.resize(2);
    subShape[0]=new QGraphicsLineItem();
    subShape[1]=new QGraphicsLineItem();
}
SubgraphNode:: SubgraphNode(QPointF lc,double wd):Node(lc,wd,wd)
{
    subShape.resize(2);
    subShape[0]=new QGraphicsLineItem();
    subShape[1]=new QGraphicsLineItem();
}
SubgraphNode::~SubgraphNode()
{
    delete shape;
    delete subShape[0];
    delete subShape[1];
}

void SubgraphNode::Paint(QGraphicsScene *qgs)
{
    Node::Paint(qgs);
    if(relatedGraph) relatedGraph->AddRelatedNode(this);
    qgs->addItem(subShape[0]);
    qgs->addItem(subShape[1]);
}

void SubgraphNode::SetShape()
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
    double k=0.8;
    subShape[0]->setLine(location.x(),location.y()-k*height/2,location.x(),location.y()+k*height/2);
    subShape[1]->setLine(location.x()-k*width/2,location.y(),location.x()+k*width/2,location.y());
}

void SubgraphNode::Remove(QGraphicsScene *qgs)
{
    Node::Remove(qgs);
    qgs->removeItem(subShape[0]);
    qgs->removeItem(subShape[1]);
    if(relatedGraph)relatedGraph->RemoveRelatedNode(this);
}
void SubgraphNode::ChangeZValue(bool isSelected)
{
    Node::ChangeZValue(isSelected);
    subShape[0]->setZValue(shape->zValue());
    subShape[1]->setZValue(shape->zValue());
}

void SubgraphNode::SetFrameColor(const QColor &qc)
{
    Node::SetFrameColor(qc);
    QPen pen=shape->pen();
    pen.setColor(frameColor);
    subShape[0]->setPen(pen);
    subShape[1]->setPen(pen);
}
int SubgraphNode::GetType()
{
    return 6;
}

void SubgraphNode::SetThickness(double nt)
{
    Node::SetThickness(nt);
    QPen pen=shape->pen();
    pen.setWidthF(nt);
    subShape[0]->setPen(pen);
    subShape[1]->setPen(pen);
}
void SubgraphNode::OpenSubGraph()
{
    
    BindToText(MainWindow::instance()->scene());
    point_w->addNewTab(content->get_text_content());
    relatedGraph=MainWindow::instance()->graph();
    if(relatedGraph) relatedGraph->AddRelatedNode(this);
    QVector<QPair<Node*,ElementShape>> v =
            MainWindow::instance()->graph()->Nodes_ElementShape(point_w->index_tab());
    foreach(auto n,v){
        if(n.second==ElementShape::Input){
            //画输入节点
        }
        if(n.second==ElementShape::Output){
            //画输出节点
        }
    }
}

void SubgraphNode::CreateAllPort()
{
   if(!relatedGraph) return;
   foreach(auto n, relatedGraph->getNodes())
   {
       if(n->GetType()==4)
       {
           InputNode* in=dynamic_cast<InputNode*>(n);
           InnerInputNode* iin=new InnerInputNode(QPointF(GetLocation().x()-GetWidth(),GetLocation().y()-GetHeight()),n->GetWidth(),n->GetHeight());
           ChangeElementAction* CEA1=new ChangeElementAction(iin,ElementShape::InnerInput,true,(Scene*)GetRelatedQGS());
           Arrow* arr=new Arrow(iin->getNodeItem(),getNodeItem(),1);
           CEA1->Do();
           in->relatedInner.insert(iin->GetID(),iin);
           ChangeElementAction* CEA2=new ChangeElementAction(arr,ElementShape::Arrow,true,(Scene*)GetRelatedQGS());
           CEA2->Do();
           iin->BindToText(iin->GetRelatedQGS());
           QString temp="0x";
           temp+= QString::number(n->GetID(),16);
           iin->content->change_input(temp);
           iin->content->change_content("文本");
       }
       if(n->GetType()==5)
       {
           OutputNode* on=dynamic_cast<OutputNode*>(n);
           InnerOutputNode* ion=new InnerOutputNode(QPointF(GetLocation().x()+GetWidth(),GetLocation().y()-GetHeight()),n->GetWidth(),n->GetHeight());
           ChangeElementAction* CEA1=new ChangeElementAction(ion,ElementShape::InnerOutput,true,(Scene*)GetRelatedQGS());
           Arrow* arr=new Arrow(ion->getNodeItem(),getNodeItem(),1);
           CEA1->Do();
           on->relatedInner.insert(ion->GetID(),ion);
           ChangeElementAction* CEA2=new ChangeElementAction(arr,ElementShape::Arrow,true,(Scene*)GetRelatedQGS());
           CEA2->Do();
           ion->BindToText(ion->GetRelatedQGS());
           QString temp="0x";
           temp+= QString::number(n->GetID(),16);
           ion->content->change_input(temp);
           ion->content->change_content("文本");
       }
   }
}
