#include "inneroutputnode.h"
#include "mainwindow.h"
#include "changeelementaction.h"

InnerOutputNode::InnerOutputNode()
{

}

InnerOutputNode::~InnerOutputNode()
{
    delete innerLine;
}
InnerOutputNode::InnerOutputNode(QPointF lc,double wd,double h):OutputNode(lc,wd,h) {};
void InnerOutputNode::Paint(QGraphicsScene *qgs)
{
    OutputNode::Paint(qgs);
    qgs->addItem(innerLine);
}
void InnerOutputNode::BindToText(QGraphicsScene *qgs)
{
    if(content==nullptr)
    {
        QString temp="0x";
        temp+= QString::number(GetID(),16);
        auto text = new Text(QPointF(location.x()-width/2,location.y()-height/2), this, temp, true);
        text->change_input("");
        text->change_content("文本");
        text->setZValue(shape->zValue());
        auto window = MainWindow::instance();
        text->reset_font(QFont(window->fontFamily, window->fontSize));
        text->reset_color(window->textColor);
        (new ChangeElementAction(text, ElementShape::Text, true,(Scene*)qgs))->Do();
        //add by luo yigui
                this->boundTextView=text;
               // this->boundTextView->setParent(this);
    }
}
void InnerOutputNode::Remove(QGraphicsScene *qgs)
{
    OutputNode::Remove(qgs);
    qgs->removeItem(innerLine);
}

void InnerOutputNode::ChangeZValue(bool isSelected)
{
    OutputNode::ChangeZValue(isSelected);
    innerLine->setZValue(shape->zValue());
}
void InnerOutputNode::SetShape()
{
    OutputNode::SetShape();
    double k=0.6;
    innerLine->setLine(location.x()+width/4+k*width/4,location.y()-height/2,location.x()+width/4+k*width/4,location.y()+height/2);
}

void InnerOutputNode::SetFrameColor(const QColor &qc)
{
    OutputNode::SetFrameColor(qc);
    QPen pen=shape->pen();
    pen.setColor(frameColor);
    innerLine->setPen(pen);
}
void InnerOutputNode::SetThickness(double nt)
{
    OutputNode::SetThickness(nt);
    QPen pen=shape->pen();
    pen.setWidthF(nt);
    innerLine->setPen(pen);
}
int InnerOutputNode::GetType()
{
    return 8;
}
