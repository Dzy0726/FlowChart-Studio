#include "innerinputnode.h"
#include "mainwindow.h"
#include "changeelementaction.h"

InnerInputNode::InnerInputNode()
{

}

InnerInputNode::~InnerInputNode()
{
    delete innerLine;
}
InnerInputNode::InnerInputNode(QPointF lc,double wd,double h):InputNode(lc,wd,h) {};
void InnerInputNode::Paint(QGraphicsScene *qgs)
{
    InputNode::Paint(qgs);
    qgs->addItem(innerLine);
}

void InnerInputNode::BindToText(QGraphicsScene *qgs)
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
void InnerInputNode::Remove(QGraphicsScene *qgs)
{
    InputNode::Remove(qgs);
    qgs->removeItem(innerLine);
}

void InnerInputNode::ChangeZValue(bool isSelected)
{
    InputNode::ChangeZValue(isSelected);
    innerLine->setZValue(shape->zValue());
}
void InnerInputNode::SetShape()
{
    InputNode::SetShape();
    double k=0.6;
    innerLine->setLine(location.x()-width/4-k*width/4,location.y()-height/2,location.x()-width/4-k*width/4,location.y()+height/2);
}

void InnerInputNode::SetFrameColor(const QColor &qc)
{
    InputNode::SetFrameColor(qc);
    QPen pen=shape->pen();
    pen.setColor(frameColor);
    innerLine->setPen(pen);
}
void InnerInputNode::SetThickness(double nt)
{
    InputNode::SetThickness(nt);
    QPen pen=shape->pen();
    pen.setWidthF(nt);
    innerLine->setPen(pen);
}
int InnerInputNode::GetType()
{
    return 7;
}
