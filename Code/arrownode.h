#ifndef ARROWNODE_H
#define ARROWNODE_H
#include"node.h"
#include"arrow.h"
class Arrownode:public Node
{
public:
    Arrownode();
    Arrownode(QPointF lc,double wd,double h);
    virtual void Paint(QGraphicsScene* qgs) override;
    void rePaint(QGraphicsScene* qgs);
    virtual void Remove(QGraphicsScene *qgs) override;
    virtual void SetVisibility(bool vis) override;
    virtual void SetLocation(const QPointF &qp) override;
    virtual void SetFrameColor(const QColor &qc) override;
    virtual void SetBackgroundColor(const QColor &qc) override;
    virtual void SetWidth(double wd) override;
    virtual void SetHeight(double h) override;
    virtual void SetShape() override;
    virtual void BindToText(QGraphicsScene* qgs) override{};
    virtual int GetType() override;
    int selecttext();
    ~Arrownode();
};


#endif // ARROWNODE_H
