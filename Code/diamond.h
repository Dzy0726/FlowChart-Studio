#ifndef DIAMOND_H
#define DIAMOND_H
#include"diamonditem.h"
#include"node.h"
class Diamond:public Node
{
public:
    Diamond();
    Diamond(QPointF lc,double wd,double h);
    virtual void SetShape() override;
    virtual int GetType() override;
    ~Diamond();
};

#endif // DIAMOND_H
