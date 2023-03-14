#include "arrow.h"
#include "nodeitem.h"
//#include "node.h"
#include "graphelement.h"
#include <QPainter>
#include <QPen>
#include <QGraphicsScene>
#include <QtMath>
#include<QMouseEvent>
#include "nodeevents.h"
#include <QMenu>
#include "changeelementaction.h"
#include "mainwindow.h"
#include "diamond.h"
#include "rectangle.h"
#include "arrownode.h"
#include "groupaction.h"
#include "changeelementaction.h"
#include "editelementaction.h"
#include "groupaction.h"

Arrow::Arrow(NodeItem *startItem, NodeItem *endItem,int haveEnd, QGraphicsItem *parent)
    : QGraphicsPathItem(parent), myStartItem(startItem),myEndItem(endItem),HaveEnd(haveEnd)
{
//    apath=new QPainterPath(startItem->pos());
    startItem->GetNode()->ConnectAsSource(this);
    endItem->GetNode()->ConnectAsDestination(this);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    //setType(1);
    //xy[11][11]=1;

}
//! [0]

//! [1]
QRectF Arrow::boundingRect() const
{

     return QRectF(0, 0, 5000, 5000);
}
//////! [1]

//! [2]
//QPainterPath Arrow::shape() const
//{
//    QPainterPath path = QGraphicsItem::shape();
//    path.addPolygon(arrowHead);
//    return path;
//}
QPainterPath Arrow::shape() const
{
    QPainterPath path;
    path.addPath(this->path());
    path.addPolygon(arrowHead);
    return path;
}
//! [2]

//! [3]
void Arrow::updatePosition()
{

//    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    if(list.length()>0){
    list.replace(0,myStartItem->pos());
    list.replace(list.length()-1,myEndItem->pos());
    ischange=true;
    }

//    apath->lineTo(line.dx(),line.dy());
//    setLine(line);
//     update();
}
//! [3]

//! [4]
void Arrow::setType(int flag){
    for(Arrow* ar: arrowlist){
    if(flag==1){
    ar->atype=1;
    ar->setPen(QPen(ar->myColor, ar->asize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    }//实线
    else if(flag==2){
    ar->atype=2;
    ar->setPen(QPen(ar->myColor, ar->asize, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));  //标准虚线

    }
    else if(flag==3){
    ar->atype=3;
    ar->setPen(QPen(ar->myColor, ar->asize, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));   //紧凑虚线

    }
    else if(flag==4){
    ar->atype=4;
    ar->setPen(QPen(ar->myColor, ar->asize,Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));  //

    }
    else if(flag==5){
    ar->atype=5;
    ar->setPen(QPen(ar->myColor, ar->asize, Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));   //

    }
    ar->update();
}
}
void Arrow::setSize(int size){
    setPen(QPen(myColor, size,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    this->asize=size;
    setType(atype);
    update();
}

void Arrow::setList(){
//    if (myStartItem->collidesWithItem(myEndItem))
//        return ;
    qreal arrowSize = 20;
    list.clear();

    if(myEndItem->pos()==myStartItem->pos())
    {
        QPointF *pa=new QPointF((myStartItem->pos().x()+myStartItem->GetWidth()), myStartItem->pos().y());
        QPointF *pb=new QPointF((myStartItem->pos().x()+myStartItem->GetWidth()), myStartItem->pos().y()-myStartItem->GetHeight()*3/2);
        QPointF *pc=new QPointF(myStartItem->pos().x(), myStartItem->pos().y()-myStartItem->GetHeight()*3/2);
    //    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
        QLineF centerLine(*pc, myEndItem->pos());
        QPolygonF endPolygon = myEndItem->polygon();
        //得到myEndItem图形所有顶点相对于中点的坐标组
        QPointF p1 = endPolygon.first() + myEndItem->pos();
        //pos()方法得到图形中点相对于窗口左上角的坐标
        //得到myEndItem图形第一个顶点相对于窗口左上角的坐标
        QPointF intersectPoint;
        for (int i = 1; i < endPolygon.count(); ++i) {
            QPointF p2 = endPolygon.at(i) + myEndItem->pos();
            QLineF polyLine = QLineF(p1, p2);
            QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPoint);
            if (intersectType == QLineF::BoundedIntersection)
                break;
            p1 = p2;
        }

        QLineF *ql=new QLineF(intersectPoint,*pc);
    //! [5] //! [6]

        double angle = std::atan2(-ql->dy(), ql->dx());

        QPointF arrowP1 = ql->p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = ql->p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);


    //! [6] //! [7]
        list.insert(0,myStartItem->pos());

        list.insert(1,*pa);
        list.insert(2,*pb);
        list.insert(3,*pc);
        list.insert(4, myEndItem->pos());
        arrowHead.clear();
        arrowHead << ql->p1() << arrowP1 << arrowP2;
        return ;
    }

    if(myStartItem->pos().y()>=myEndItem->pos().y()-myEndItem->GetHeight()/2-arrowSize&&myStartItem->pos().y()<=myEndItem->pos().y()+myEndItem->GetHeight()/2+arrowSize)
    {
        QPointF *pa;
        QPointF *pb;
        if(myStartItem->pos().x()<myEndItem->pos().x()){
        pa=new QPointF(((myEndItem->pos().x()-myEndItem->GetWidth()/2)+(myStartItem->pos().x()+myStartItem->GetWidth()/2))/2, myStartItem->pos().y());
        pb=new QPointF(((myEndItem->pos().x()-myEndItem->GetWidth()/2)+(myStartItem->pos().x()+myStartItem->GetWidth()/2))/2, myEndItem->pos().y());
      }else{
            pa=new QPointF(((myEndItem->pos().x()+myEndItem->GetWidth()/2)+(myStartItem->pos().x()-myStartItem->GetWidth()/2))/2, myStartItem->pos().y());
            pb=new QPointF(((myEndItem->pos().x()+myEndItem->GetWidth()/2)+(myStartItem->pos().x()-myStartItem->GetWidth()/2))/2, myEndItem->pos().y());
        }
    //    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
        QLineF centerLine(*pb, myEndItem->pos());
        QPolygonF endPolygon = myEndItem->polygon();
        //得到myEndItem图形所有顶点相对于中点的坐标组
        QPointF p1 = endPolygon.first() + myEndItem->pos();
        //pos()方法得到图形中点相对于窗口左上角的坐标
        //得到myEndItem图形第一个顶点相对于窗口左上角的坐标
        QPointF intersectPoint;
        for (int i = 1; i < endPolygon.count(); ++i) {
            QPointF p2 = endPolygon.at(i) + myEndItem->pos();
            QLineF polyLine = QLineF(p1, p2);
            QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPoint);
            if (intersectType == QLineF::BoundedIntersection)
                break;
            p1 = p2;
        }

        QLineF *ql=new QLineF(intersectPoint,*pb);
    //! [5] //! [6]

        double angle = std::atan2(-ql->dy(), ql->dx());

        QPointF arrowP1 = ql->p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = ql->p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);


    //! [6] //! [7]
        list.insert(0,myStartItem->pos());

        list.insert(1,*pa);
        list.insert(2,*pb);
        list.insert(3, myEndItem->pos());
        arrowHead.clear();
        arrowHead << ql->p1() << arrowP1 << arrowP2;
        return ;
    }else if(myEndItem->pos().x()>=myStartItem->pos().x()-myStartItem->GetWidth()/2&&myEndItem->pos().x()<=myStartItem->pos().x()+myStartItem->GetWidth()/2)
    {
        QPointF *pa;
        QPointF *pb;
            if(myStartItem->pos().y()<myEndItem->pos().y()){
            pa=new QPointF(myStartItem->pos().x(),((myEndItem->pos().y()-myEndItem->GetHeight()/2)+(myStartItem->pos().y()+myStartItem->GetHeight()/2))/2);
            pb=new QPointF(myEndItem->pos().x(),((myEndItem->pos().y()-myEndItem->GetHeight()/2)+(myStartItem->pos().y()+myStartItem->GetHeight()/2))/2);
          }else{
                pa=new QPointF(myStartItem->pos().x(),((myEndItem->pos().y()+myEndItem->GetHeight()/2)+(myStartItem->pos().y()-myStartItem->GetHeight()/2))/2);
                pb=new QPointF(myEndItem->pos().x(),((myEndItem->pos().y()+myEndItem->GetHeight()/2)+(myStartItem->pos().y()-myStartItem->GetHeight()/2))/2);
            }
    //    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
        QLineF centerLine(*pb, myEndItem->pos());
        QPolygonF endPolygon = myEndItem->polygon();
        //得到myEndItem图形所有顶点相对于中点的坐标组
        QPointF p1 = endPolygon.first() + myEndItem->pos();
        //pos()方法得到图形中点相对于窗口左上角的坐标
        //得到myEndItem图形第一个顶点相对于窗口左上角的坐标
        QPointF intersectPoint;
        for (int i = 1; i < endPolygon.count(); ++i) {
            QPointF p2 = endPolygon.at(i) + myEndItem->pos();
            QLineF polyLine = QLineF(p1, p2);
            QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPoint);
            if (intersectType == QLineF::BoundedIntersection)
                break;
            p1 = p2;
        }

        QLineF *ql=new QLineF(intersectPoint,*pb);
    //! [5] //! [6]

        double angle = std::atan2(-ql->dy(), ql->dx());

        QPointF arrowP1 = ql->p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = ql->p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);


    //! [6] //! [7]
        list.insert(0,myStartItem->pos());

        list.insert(1,*pa);
        list.insert(2,*pb);
        list.insert(3, myEndItem->pos());
        arrowHead.clear();
        arrowHead << ql->p1() << arrowP1 << arrowP2;
        return ;
    }else {//if(myStartItem->pos().y()-100-arrowSize>=myEndItem->pos().y()||myEndItem->pos().y()>=myStartItem->pos().y()+100+arrowSize)
            QPointF *p=new QPointF(myEndItem->pos().x(), myStartItem->pos().y());

        //    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
            QLineF centerLine(*p, myEndItem->pos());
            QPolygonF endPolygon = myEndItem->polygon();
            //得到myEndItem图形所有顶点相对于中点的坐标组
            QPointF p1 = endPolygon.first() + myEndItem->pos();
            //pos()方法得到图形中点相对于窗口左上角的坐标
            //得到myEndItem图形第一个顶点相对于窗口左上角的坐标
            QPointF intersectPoint;
            for (int i = 1; i < endPolygon.count(); ++i) {
                QPointF p2 = endPolygon.at(i) + myEndItem->pos();
                QLineF polyLine = QLineF(p1, p2);
                QLineF::IntersectType intersectType =
                    polyLine.intersect(centerLine, &intersectPoint);
                if (intersectType == QLineF::BoundedIntersection)
                    break;
                p1 = p2;
            }

            QLineF *ql=new QLineF(intersectPoint,*p);
            //setLine(QLineF(intersectPoint, list.at(1)));
        //! [5] //! [6]

            double angle = std::atan2(-ql->dy(), ql->dx());

            QPointF arrowP1 = ql->p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                            cos(angle + M_PI / 3) * arrowSize);
            QPointF arrowP2 = ql->p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                            cos(angle + M_PI - M_PI / 3) * arrowSize);


        //! [6] //! [7]
        list.insert(0,myStartItem->pos());
        list.insert(1, *p);
        list.insert(2, myEndItem->pos());
        arrowHead.clear();
        arrowHead << ql->p1() << arrowP1 << arrowP2;
    }
}


void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                  QWidget *)
{
    if(!isMoved){
    setList();}
    apath=new QPainterPath(list.at(0));
    QPen myPen = pen();
    myPen.setColor(myColor);
    //调整清晰度---------------------------
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(myPen);
   // painter->setBrush(myColor);
//! [4] //! [5]
    painter->setBrush(Qt::black);
// painter->drawLine(line());
//    for(int i=1;i<=arrownode.length()-1;i++){
//        painter->drawEllipse(arrownode.at(i),4,4);
//    }
    QBrush* brush=new QBrush();
    painter->setBrush(*brush);
    for(int i=1;i<=list.length()-1;i++){
        apath->lineTo(list.at(i));
    }

//    apath->lineTo(list.at(1).x()-list.at(0).x(),0);
//    apath->lineTo(0,list.at(2).y()-list.at(1).y());
//    apath->addPolygon(arrowHead);
    setPath(*apath);
    painter->drawPath(path());
    painter->setPen(QPen(myColor, asize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(myColor);
    if(HaveEnd){
    painter->drawPolygon(arrowHead);}
    if (isSelected()) {
               for(Arrow* ar: arrowlist){
               ar->setSelected(true);
                if(ar->Arrownode!=nullptr){
                    ar->Arrownode->getNodeItem()->SetSelected(true);
                }
                //不需要选定箭头的时候去选定文本框
//                if(ar->content!=nullptr){
//                ar->content->setSelected(true);
//                }
               }
                QBrush* brush=new QBrush();
                painter->setBrush(*brush);
                painter->setPen(QPen(QColor(139,69,19),4, Qt::DashLine));
                QPainterPath Path = path();
                QPainterPath allPath;

//                int max=0;
//                int k=this->arrowlist.length()-1;
//                for(int i=0;i<arrowlist.length();i++){
//                    if(arrowlist[i]->arrowlist.length()>max){
//                        max=arrowlist[i]->arrowlist.length();
//                        k=i;
//                    }
//                }
//                this->arrowlist=arrowlist[k]->arrowlist;
//                if(arrowlist.last()!=this){
//                arrowlist.append(this);}
//                else{arrowlist.replace(arrowlist.length()-1,this);}
//                if(arrowlist.isEmpty()||arrowlist.last()!=this){
//                                arrowlist.append(this);}
//                                else{arrowlist.replace(arrowlist.length()-1,this);}
                if(arrowlist.isEmpty()){
                arrowlist.append(this);}
                for(int i=0;i<arrowlist.length();i++){
                    allPath.addPath(arrowlist[i]->path());
                    QPainterPath myPath=arrowlist[i]->path();
                    painter->drawPath(myPath);
//                    QPainterPath myPathin;
//                    QPainterPath myPathout;
//                    NodeItem *EndItem=arrowlist[i]->myEndItem;
//                    NodeItem *StartItem=arrowlist[i]->myStartItem;
//                    if(EndItem->pos()==StartItem->pos()){
//                    QRectF *rectin=new QRectF
//                   (StartItem->pos().x()+12,StartItem->pos().y()-StartItem->GetHeight()*3/2+12,StartItem->GetWidth()-24,StartItem->GetHeight()*3/2-24);
//                                        myPathin.addRect(*rectin);
//                                        painter->drawPath(myPathin);
//                   QRectF *rectout=new QRectF
//                    (StartItem->pos().x()-12,StartItem->pos().y()-StartItem->GetHeight()*3/2-12,StartItem->GetWidth()+24,StartItem->GetHeight()*3/2+24);
//                                        myPathout.addRect(*rectout);
//                                        painter->drawPath(myPathout);
//                                  }
//                    else if((EndItem->pos().x()<StartItem->pos().x()&&EndItem->pos().y()<StartItem->pos().y())||(EndItem->pos().x()>StartItem->pos().x()&&EndItem->pos().y()>StartItem->pos().y())){
//            //        myPath.translate(0, 4.0);
//                    myPath.translate(12.0, -12.0);
//                    //线向上移动
//                    painter->drawPath(myPath);
//            //        myPath.translate(0,-8.0);
//                    myPath.translate(-24.0, 24.0);
//                    //线向下移动
//                    painter->drawPath(myPath);
//                    }else if((EndItem->pos().x()>StartItem->pos().x()&&EndItem->pos().y()<StartItem->pos().y())||(EndItem->pos().x()<StartItem->pos().x()&&EndItem->pos().y()>StartItem->pos().y())){
//                        //        myPath.translate(0, 4.0);
//                                myPath.translate(-12.0, -12.0);
//                                //线向上移动
//                                painter->drawPath(myPath);
//                        //        myPath.translate(0,-8.0);
//                                myPath.translate(24.0, 24.0);
//                                //线向下移动
//                                painter->drawPath(myPath);
//                    }else{
//                        //        myPath.translate(0, 4.0);
//                                myPath.translate(12.0, -12.0);
//                                //线向上移动
//                                painter->drawPath(myPath);
//                        //        myPath.translate(0,-8.0);
//                                myPath.translate(-24.0, 24.0);
//                                //线向下移动
//                                painter->drawPath(myPath);
//                    }
                //}


            }
}

}


void Arrow::removeArrow()
{
    for(Arrow *ar : arrowlist){
    auto window = MainWindow::instance();
    auto scene = window->scene();
    ar->endItem()->RemoveAsDestination(ar);
    ar->startItem()->RemoveAsSource(ar);
    new ChangeElementAction(ar, ElementShape::Arrow, false);
    scene->removeItem(ar);
    if(content)
         {if(ar->content){
            ar->content->delete_text(scene);
              scene->removeItem(ar->content);
              auto action = new ChangeElementAction(ar->content, ElementShape::Text, false);
                      action->Do();
            }
    }
    if(ar->Arrownode!=nullptr){
        ar->Arrownode->Remove(scene);
    }
    ar->deleteID();
//   endItem()->RemoveAsDestination(this);
//   startItem()->RemoveAsSource(this);
//   new ChangeElementAction(this, ElementShape::Arrow, false);
//   if(content) content->delete_text(scene());
}
}
void Arrow::removemyself()
{
//    for(Arrow *ar : arrowlist){
//    ar->endItem()->RemoveAsDestination(ar);
//    ar->startItem()->RemoveAsSource(ar);
//    new ChangeElementAction(ar, ElementShape::Arrow, false);
//    ar->scene()->removeItem(ar);
//    if(content) ar->content->delete_text(scene());
//    if(ar->Arrownode){
//        ar->Arrownode->Remove(ar->Arrownode->getNodeItem()->scene());
//    }
    auto window = MainWindow::instance();
    auto scene = window->scene();
   endItem()->RemoveAsDestination(this);
   startItem()->RemoveAsSource(this);
   if(content) {
       content->delete_text(scene);
       scene->removeItem(content);
       auto action = new ChangeElementAction(content, ElementShape::Text, false);
               action->Do();
   }
   this->deleteID();
}

//! [1]

//! [2]
//void Arrow::removeArrows()
//{
//    // need a copy here since removeArrow() will
//    // modify the arrows container
//    const auto arrowsCopy = arrows;
//    for (Arrow *arrow : arrowsCopy) {
//        arrow->startItem()->removeArrow(arrow);
//        arrow->endItem()->removeArrow(arrow);
//        scene()->removeItem(arrow);
//        delete arrow;
//    }
//}
//void Arrow::addArrow(Arrow *arrow)
//{
//    arrows.append(arrow);
//}

void Arrow::BindToText(QGraphicsScene* qgs){
    if(content==nullptr){
        QLineF centerLine(myStartItem->pos(), list[1]);
        QPolygonF StartPolygon = myStartItem->polygon();
        //得到myEndItem图形所有顶点相对于中点的坐标组
        QPointF p1 = StartPolygon.first() + myStartItem->pos();
        //pos()方法得到图形中点相对于窗口左上角的坐标
        //得到myEndItem图形第一个顶点相对于窗口左上角的坐标
        QPointF intersectPoint;
        for (int i = 1; i < StartPolygon.count(); ++i) {
            QPointF p2 = StartPolygon.at(i) + myStartItem->pos();
            QLineF polyLine = QLineF(p1, p2);
            QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPoint);
            if (intersectType == QLineF::BoundedIntersection)
                break;
            p1 = p2;
        }
//    content=new Text((QPoint((myStartItem->pos().x()+myEndItem->pos().x())/2,
//                     (myStartItem->pos().y()+myEndItem->pos().y())/2)));
            content=new Text((QPoint((intersectPoint.x()+list[1].x())/2,
                             (intersectPoint.y()+list[1].y())/2)));
    content->putup_text(qgs);
    content->build_text();
    content->change_content("文本");
    auto window = MainWindow::instance();
    content->reset_font(QFont(window->fontFamily, window->fontSize));
    content->reset_color(window->textColor);
    (new ChangeElementAction(content, ElementShape::Text, true))->Do();
    this->boundTextView=content;

    }
};
//void Arrow::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
//    if (!isSelected())
//        return;

//}

void Arrow::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    auto deleteAction = menu.addAction("删除");
    deleteAction->setShortcut(QKeySequence::Delete);
    auto addTextAction = menu.addAction("添加文本框");
    auto cutAction = menu.addAction("剪切");
    cutAction->setShortcut(QKeySequence::Cut);
    auto copyAction = menu.addAction("复制");
    copyAction->setShortcut(QKeySequence::Copy);
    auto selectedAction = menu.exec(event->screenPos());
    if (selectedAction == deleteAction)
    {
        NodeEvents::deleteElemets();
    }
    else if(selectedAction == addTextAction){

             BindToText(MainWindow::instance()->scene());
             setSelected(false);
             content->get_item()->setSelected(true);
    }
    else if (selectedAction == cutAction)
    {
        NodeEvents::cutElements();
    }
    else if (selectedAction == copyAction)
    {
        NodeEvents::copyElements();
    }
}

QVariant Arrow::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        if (s) s(this, QGraphicsItem::isSelected());
    }
    else if(change==QGraphicsItem::ItemPositionChange)
    {
         updatePosition();
         content=nullptr;
         BindToText(MainWindow::instance()->scene());
         setSelected(false);
         content->get_item()->setSelected(true);
    }
    return value;
}

void Arrow::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    auto window = MainWindow::instance();
    auto scene = window->scene();
    auto action = new GroupAction;
     QGraphicsItem::mouseDoubleClickEvent(event);
     isDoubleClick=true;
     auto point = event->scenePos();
     auto arrownode = new class Arrownode(point, 5.0, 5.0);
//     arrownode->SetBackgroundColor(this->getColor());
//     arrownode->SetFrameColor(this->getColor());
     *action << new ChangeElementAction(arrownode, ElementShape::Arrownode, true);
     arrownode->SetFrameColor(getColor());
     arrownode->SetBackgroundColor(getColor());
     auto arrows = myStartItem->GetNode()->getArrows();
//     foreach (auto arrow, arrows)
//     {
//         arrow->removeArrow();
//         //auto action = new ChangeElementAction(arrow, ElementShape::Arrow, false);
//         //MainWindow::instance()->graph->removeArrow(arrow);
//        MainWindow::instance()->scene()->removeItem(arrow);
//     }
//     解决方法：
     QPainterPath p = this->root;
     int type=this->getType();
     Text* content=this->content;
     QColor color=this->myColor;
     int oldid=this->GetID();
     this->removemyself();
     MainWindow::instance()->scene()->removeItem(this);

     //auto arrow1 = new Arrow(myEndItem,myStartItem);
     auto arrow2 = new Arrow(myStartItem,arrownode->getNodeItem(),0);
     auto arrow3 = new Arrow(arrownode->getNodeItem(),myEndItem,1);
//     arrownode->ConnectAsSource(arrow3);
//     arrownode->ConnectAsDestination(arrow2);
     myStartItem->GetNode()->ConnectAsDestination(arrow2);

     arrow2->setArrowColor(color);
     arrow3->setArrowColor(color);
     if(content!=nullptr){
     arrow2->content=content;
     //arrow3->content=content;
     //arrownode->content=content;
     //给arrownode的content赋值
     arrow2->content->putup_text(scene);
     arrow2->content->build_text();
     }
//     if(arrow2->content!=nullptr){
//     arrow2->content->move_text(QPointF((arrow2->list.at(0).x()+arrow2->list.at(1).x())/2,
//             (arrow2->list.at(0).y()+arrow2->list.at(1).y())/2));}
     arrownode->deleteID();
          arrow2->deleteID();
          arrow2->Id=oldid;
          arrow2->chagearrowID(oldid);
          arrow3->deleteID();
          arrow3->Id=oldid;
          arrow3->chagearrowID(oldid);
     arrow2->arrowlist.append(this->arrowlist);
     arrow3->arrowlist.append(this->arrowlist);
     arrow2->arrowlist.removeOne(this);
     arrow3->arrowlist.removeOne(this);
     arrow2->arrowlist.append(arrow3);
     arrow2->arrowlist.append(arrow2);
     arrow3->arrowlist.append(arrow2);
     arrow3->arrowlist.append(arrow3);
     for(int i=0;i<arrow2->arrowlist.length()-1;i++){
         arrow2->arrowlist[i]->arrowlist=arrow2->arrowlist;
//         arrow2->arrowlist[i]->Arrownode=arrownode;
     }
     if(arrow2->endItem()->GetWidth()<=5){
         arrow2->Arrownode=dynamic_cast<class Arrownode*>(arrow2->endItem()->GetNode());
     }
     if(arrow3->endItem()->GetWidth()<=5){
         arrow3->Arrownode=dynamic_cast<class Arrownode*>(arrow3->endItem()->GetNode());
     }
     arrow2->setType(getType());
     arrow3->setType(getType());
     //修改属性要建立在arrowlist之后
     if(myEndItem->GetWidth()>5){
     arrow3->HaveEnd=1;}
     else{
     arrow3->HaveEnd=0;}
     //思考，我们加入箭头构造的判定条件如果满足就不生成黑色三角形
     *action << new ChangeElementAction(arrow2, ElementShape::Arrow, true);
     *action << new ChangeElementAction(arrow3, ElementShape::Arrow, true);
     *action << new ChangeElementAction(this, ElementShape::Arrow, false);
     action->Do();
     this->update();
}
void Arrow::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
   /* if(event->button()==Qt::MouseButton::LeftButton)
    {
        if(isDoubleClick){
            isMoved=true;
            QPointF pos = event->pos();
            qreal arrowSize = 20;
//            list.clear();
            if((myStartItem->pos().x()==myEndItem->pos().x()&&myStartItem->pos().y()!=myEndItem->pos().y())
                    ||(myStartItem->pos().y()==myEndItem->pos().y()&&myStartItem->pos().x()!=myEndItem->pos().x())){

                if (event->scenePos().x() == myStartItem->pos().x() && event->scenePos().x() == myEndItem->pos().x()){
                list.insert(1,pos);}

            }//1直线
            else if((myStartItem->pos().y()>=myEndItem->pos().y()-myEndItem->GetHeight()/2-arrowSize&&myStartItem->pos().y()<=myEndItem->pos().y()+myEndItem->GetHeight()/2+arrowSize)
                    ||(myEndItem->pos().x()>=myStartItem->pos().x()-myStartItem->GetWidth()/2&&myEndItem->pos().x()<=myStartItem->pos().x()+myStartItem->GetWidth()/2)){

              if(event->scenePos().y() == myStartItem->pos().y()){
              list.insert(1,pos);}

              if (event->scenePos().y() == myStartItem->pos().y()&& event->scenePos().x() == myEndItem->pos().x()){
              list.replace(1,pos);}

              else{
              list.insert(2,pos);}
            }//2折
            else if((myStartItem->pos().y()<myEndItem->pos().y()-myEndItem->GetHeight()/2-arrowSize||myStartItem->pos().y()>myEndItem->pos().y()+myEndItem->GetHeight()/2+arrowSize)
                    &&(myEndItem->pos().x()<myStartItem->pos().x()-myStartItem->GetWidth()/2||myEndItem->pos().x()>myStartItem->pos().x()+myStartItem->GetWidth()/2)){

                if (event->scenePos().x() == myStartItem->pos().x()|| event->scenePos().y() == myStartItem->pos().y()){
                list.insert(1,pos);}

                if (event->scenePos().x()==list.at(1).x()&& event->scenePos().y()== list.at(1).y()){
                list.replace(1,pos);}

                if (event->scenePos().x() == (myEndItem->pos().x() + myStartItem->pos().x()) / 2||event->scenePos().y() == ((myEndItem->pos().y() + myStartItem->pos().y()) / 2)){
                list.insert(2,pos);}

                if (event->scenePos().x() == list.at(2).x() && event->scenePos().y() == list.at(2).y()){
                list.replace(2,pos);}
                if (event->scenePos().x() == myEndItem->pos().x()|| event->scenePos().y() == myEndItem->pos().y()){
                list.insert(3,pos);}
            }//3折
        }

    }*/
}
void Arrow::mousePressEvent(QGraphicsSceneMouseEvent *event){
     isFocus=true;
}

void Arrow::setArrowColor(const QColor &color)
{
    myColor = color;
    for(Arrow* ar: arrowlist){
    ar->myColor=color;
    auto brush = Arrow::brush();
    brush.setColor(color);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    ar->setBrush(brush);
    if(ar->Arrownode!=nullptr){
        ar->Arrownode->SetFrameColor(color);
        ar->Arrownode->SetBackgroundColor(color);
    }}
}

//*******************
QJsonObject Arrow::get_JsonObject()
{ /*
   Arrow
        id:
        scrld:
        Dstld:
        PathPoints:{
                   x:
                   y:
                   }
        LineColor:
        LineWidth:
        LineType:#1实线 2虚线 3点线
        startPoint:{
                    x:
                    y:
                    }
        endPoint:{
                   x:
                   y:
                 }
        TextView:{
                 Id:0x567,
                 Width:30,
                 Height:15,
                 FontColor:"red",
                 FontType:"宋体"
                 FontSize:"8"
                 TextContent:{
                              TextDescription:"begin",
                              LogicAction:“(A AND B) AND (NOT C) ”
                             }
  */
    QJsonObject qso;
    QJsonObject startpointobj;
    QJsonObject endpointobj;
    QJsonObject TVqso;

    startpointobj.insert("x",myStartItem->pos().x());
    startpointobj.insert("y",myStartItem->pos().y());
    endpointobj.insert("x",myEndItem->pos().x());
    endpointobj.insert("y",myEndItem->pos().y());

    qso.insert("id",GetID());
    qso.insert("Linetype",getType());
    qso.insert("Color",this->myColor.name());
    qso.insert("size",getSize());
    qso.insert("startPoint",startpointobj);
    qso.insert("endPoint",endpointobj);
    qso.insert("HaveEnd",getHaveEnd());
        //QList<QJsonObject> PathPoints;
        QJsonArray PathPoints;
        for(int i=1;i<list.length()-1;i++)
        {
            QJsonObject xy;
            xy.insert("x",list[i].x());
            xy.insert("y",list[i].y());
            PathPoints.append(xy);

        }
        qso.insert("PathPoints",PathPoints);//PathPoints
    /*
        QJsonObject Arrownode;
        Node*arrownode=getArrowNode();
        if (arrownode!=nullptr)
         {
         Arrownode.insert("x",arrownode->GetLocation().x());
         Arrownode.insert("y",arrownode->GetLocation().y());
         qso.insert("Arrownode",Arrownode);
        }//ArrowNode

    */
         if(this->boundTextView!=nullptr)
        {

            TVqso.insert("Id",boundTextView->getId());
            TVqso.insert("Location_X",boundTextView->x());
            TVqso.insert("Location_y",boundTextView->y());
            TVqso.insert("FontColor",boundTextView->get_text_color().name());
            TVqso.insert("FontSize",boundTextView->get_text_font().toString());

            QJsonObject TVCqso;
            TVCqso.insert("TextDescription",boundTextView->get_text_content());
            TVCqso.insert("LogicAction",boundTextView->get_text_logic());

            TVqso.insert("TextContent",QJsonValue(TVCqso));

            qso.insert("TextView",QJsonValue(TVqso));
        }

    return qso;

}
void Arrow::set_JsonObject(QJsonObject qso)
{

}
