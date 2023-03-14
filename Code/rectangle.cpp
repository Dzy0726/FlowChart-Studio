#include "rectangle.h"

Rectangle::Rectangle()
{

}
Rectangle:: Rectangle(QPointF lc,double wd,double h):Node(lc,wd,h)
{


}
Rectangle::~Rectangle()
{
    delete shape;
}


void Rectangle::SetShape()
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
}

int Rectangle::GetType()
{
    return 1;
}

