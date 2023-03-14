#ifndef RECSHAPE_H
#define RECSHAPE_H
#include "QGraphicsItem"

class RecShape:public QGraphicsRectItem
{
public:
    RecShape();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // RECSHAPE_H
