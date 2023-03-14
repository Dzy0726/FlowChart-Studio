#include"textitem.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <math.h>
#include <QMenu>
#include<QInputDialog>
#include<QLineEdit>
#include "changeelementaction.h"
#include "mainwindow.h"
#include<QFontDialog>
#include<QColorDialog>

void TextItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

        isFocus=true;
        lastlocation=text->get_text_location();
        QGraphicsItem::mousePressEvent(event);

}

void TextItem::SetSelected(bool b)
{
    isSelected=b;
    text->setSelected(b);
    setSelected(b);
}


void TextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
        QGraphicsItem::mouseReleaseEvent(event);
        if(isFocus){
            if(isMoved){
                emit NewLocation(text,lastlocation);
            }
        }


}


QVariant TextItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        SetSelected(QGraphicsItem::isSelected());
        emit Selected(text, QGraphicsItem::isSelected());
    }
    return value;
}
