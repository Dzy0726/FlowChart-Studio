#include "diamond.h"
#include "QGraphicsItem"
#include "QFont"
Diamond::Diamond()
{

}
Diamond:: Diamond(QPointF lc,double wd,double h):Node(lc,wd,h)
{


}
Diamond::~Diamond()
{
    delete shape;
}

void Diamond::SetShape()
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y())<<QPointF(location.x(),location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y())<<QPointF(location.x(),location.y()+height/2);
    shape->setPolygon(polygon);
}

int Diamond::GetType()
{
    return 2;
}
