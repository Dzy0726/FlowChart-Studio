#ifndef INNERINPUTNODE_H
#define INNERINPUTNODE_H
#include "inputnode.h"

class InnerInputNode: public InputNode
{
public:
    InnerInputNode();
    InnerInputNode(QPointF lc,double wd,double h);
    virtual void SetShape() override;
    virtual int GetType() override;
    virtual void Paint(QGraphicsScene *qgs) override;
    virtual void Remove(QGraphicsScene *qgs) override;
    virtual void ChangeZValue(bool isSelected) override;
    virtual void SetFrameColor(const QColor &qc) override;
    virtual void SetThickness(double nt) override;
    virtual void BindToText(QGraphicsScene* qgs) override;
    ~InnerInputNode();
private:
    QGraphicsLineItem* innerLine=new QGraphicsLineItem();
};

#endif // INNERINPUTNODE_H
