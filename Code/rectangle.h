#ifndef RECTANGLE_H
#define RECTANGLE_H
#include"rectangleitem.h"
#include"node.h"
class Rectangle:public Node
{
public:
    Rectangle();
    Rectangle(QPointF lc,double wd,double h);
    virtual void SetShape() override;
    virtual int GetType() override;
    ~Rectangle();
};

#endif // RECTANGLE_H
