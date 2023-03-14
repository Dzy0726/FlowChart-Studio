#ifndef SHAPE_H
#define SHAPE_H

enum class ElementShape : unsigned char
{
    Unknown,
    Rectangle,
    Diamond,
    Arrow,
    SubGraph,
    Text,
    Input,
    Output,
    Arrownode,
    InnerInput,
    InnerOutput,
};

inline bool isNode(ElementShape shape)
{
    return shape == ElementShape::Input || shape == ElementShape::Output ||
            shape == ElementShape::Diamond || shape == ElementShape::SubGraph ||
            shape == ElementShape::Rectangle || shape == ElementShape::InnerInput ||
            shape == ElementShape::InnerOutput || shape == ElementShape::Arrownode;
}

#endif // SHAPE_H
