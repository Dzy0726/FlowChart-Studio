
#ifndef NEWARROW_H
#define NEWARROW_H
#include "graphelement.h"
#include "node.h"
#include "diamond.h"
#include <QPainter>
#include <QPen>
#include <QtMath>
#include<QMouseEvent>
class NodeItem;
class Arrow: public QGraphicsPathItem,public GraphElement
{

public:
    QPainterPath root;
    bool ischange=false;
    QList<Arrow*> arrowlist;
    enum { Type = UserType + 4 };

    Arrow(NodeItem *startItem, NodeItem *endItem,int haveEnd,
          QGraphicsItem *parent = nullptr);

    int type() const override { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void setArrowColor(const QColor &color);
    QColor getColor() { return myColor; }
    int getType() { return atype; }
    void setType(int flag);
    void setSize(int size);
    int getSize() {return asize;}
    void setId(int size);
    void setList();
    NodeItem *startItem() const { return myStartItem; }
    NodeItem *endItem() const { return myEndItem; }
    void removeArrow();
    void removemyself();
    void updatePosition();
    Text* getcontent(){return content;}
    virtual void BindToText(QGraphicsScene* qgs) override;
    NodeItem *myStartItem;
    NodeItem *myEndItem;
    int getHaveEnd() {return HaveEnd;}
    QList<QPointF> getlist(){return list;}
    using Selected = void (*)(Arrow* n,bool b);
    Selected s;
     Node*  getArrowNode(){return Arrownode;}

    //将对像转成JSONOBJECT
        virtual QJsonObject get_JsonObject() override;
        //根据JSON转成成相应的对象
        virtual void set_JsonObject(QJsonObject qso) override;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    Text *boundTextView=nullptr;
private:

    QPolygonF arrowHead;
    QList<QLineF> lines;
    QColor myColor = Qt::black;
    int id=1;
    int atype=1;
    int asize=2;
    QList<QPointF> list;// 箭头结点
    QPainterPath *apath;//箭头路径
//    QList<QPointF> arrownode;//箭头结点
    bool isDoubleClick=false;
    bool isFocus=false;
    bool isMoved=false;
    Node *Arrownode=nullptr;
    int HaveEnd;

};

#endif // NEWARROW_H
