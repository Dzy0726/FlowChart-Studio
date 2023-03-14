#ifndef DIAMONDITEM_H
#define DIAMONDITEM_H

#include <QGraphicsItem>

#include "node.h"

class DiamondItem:public QGraphicsPolygonItem
{
public:
    DiamondItem(Node* node) : node(node) {}

protected:

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
private:
    bool isSelected=false;
    Node* node;
};

#endif // DIAMONDITEM_H
