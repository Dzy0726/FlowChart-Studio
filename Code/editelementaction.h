#ifndef EDITELEMENTACTION_H
#define EDITELEMENTACTION_H

#include "action.h"
#include "elementshape.h"
#include "elementProperty.h"


class EditElementAction : public Action
{
public:
    EditElementAction(void* element, ElementShape shape, ElementProperty property, void* from, void* to);
    ~EditElementAction();

    void Do() override;
    void Undo() override;
private:
    ElementShape shape;
    ElementProperty property;
    void* from;
    void* to;
    void* element;
};

#endif // EDITELEMENTACTION_H
