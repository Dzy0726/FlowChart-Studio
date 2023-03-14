#ifndef DELETEELEMENTACTION_H
#define DELETEELEMENTACTION_H

#include <QPointF>

#include "action.h"
#include "node.h"
#include "elementshape.h"


class DeleteElementAction : public Action
{
    Q_OBJECT
public:
    DeleteElementAction(Node* node, bool isAdded = true);

    void Do() override;
    void Undo() override;

private:
    Node* node;
    ElementShape shape;
    QSizeF size;
    QPointF point;
};

#endif // DELETEELEMENTACTION_H
