#ifndef SUBGRAPHNODE_H
#define SUBGRAPHNODE_H
#include "node.h"
#include "QGraphicsLineItem"

#include"inputnode.h"
#include"outputnode.h"
#include "mainwindow.h"

extern MainWindow* point_w;
class Graph;
class SubgraphNode:public Node
{
public:
    SubgraphNode();
    SubgraphNode(QPointF lc,double wd,double h);
    SubgraphNode(QPointF lc,double wd);
    virtual void SetShape() override;
    virtual int GetType() override;
    virtual void Paint(QGraphicsScene *qgs) override;
    virtual void Remove(QGraphicsScene *qgs) override;
    virtual void ChangeZValue(bool isSelected) override;
    virtual void SetFrameColor(const QColor &qc) override;
    virtual void SetThickness(double nt) override;
    ~SubgraphNode();
    
    void OpenSubGraph();
    void CreateAllPort();
    
protected:
    QVector<QGraphicsLineItem*> subShape;
    Graph* relatedGraph=nullptr;
};

#endif // SUBGRAPHNODE_H
