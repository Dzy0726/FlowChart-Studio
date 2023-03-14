#ifndef INNEROUTPUTNODE_H
#define INNEROUTPUTNODE_H
#include "outputnode.h"

class InnerOutputNode:public OutputNode
{
public:
    InnerOutputNode();
    InnerOutputNode(QPointF lc,double wd,double h);
    virtual void SetShape() override;
    virtual int GetType() override;
    virtual void Paint(QGraphicsScene *qgs) override;
    virtual void Remove(QGraphicsScene *qgs) override;
    virtual void ChangeZValue(bool isSelected) override;
    virtual void SetFrameColor(const QColor &qc) override;
    virtual void SetThickness(double nt) override;
    virtual void BindToText(QGraphicsScene* qgs) override;
    ~InnerOutputNode();
private:
    QGraphicsLineItem* innerLine=new QGraphicsLineItem();
};

#endif // INNEROUTPUTNODE_H
