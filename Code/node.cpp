#include "node.h"
#include"arrow.h"
#include "mainwindow.h"
#include "changeelementaction.h"

Node::Node(){}
Node::Node(QPointF lc,double w,double h):location(lc),width(w),height(h)
{
}

Node::~Node()
{
    delete content;
}
double Node::GetWidth()
{
    return width;
}

double Node::GetHeight()
{
    return height;
}

QColor Node::GetBackgroundColor()
{
    return backgroundColor;
}

QColor Node::GetFrameColor()
{
    return frameColor;
}
QPointF Node::GetLocation()
{
    return location;
}

void Node::ConnectAsSource(Arrow *ar)
{
    if(isRemoved) return;
    sourceArrows[ar->GetID()]=ar;
}

void Node::ConnectAsDestination(Arrow *ar)
{
    if(isRemoved) return;
    destinationArrows[ar->GetID()]=ar;
}

void Node::DisconnectAsSource(Arrow *ar)
{
    if(isRemoved) return;
    sourceArrows.remove(ar->GetID());
}

void Node::DisconnectAsDestination(Arrow *ar)
{
     if(isRemoved) return;
    destinationArrows.remove(ar->GetID());
}

QVector<Arrow*> Node::getArrows()
{
    QVector<Arrow*> vec;
    foreach (auto arrow, sourceArrows)
    {
        vec.append(arrow);
    }
    foreach (auto arrow, destinationArrows)
    {
        vec.append(arrow);
    }
    return vec;
}

void Node::Paint(QGraphicsScene* qgs)
{
    if(!fatherGraph) fatherGraph=MainWindow::instance()->graph();
    if(!relatedQGS) relatedQGS=qgs;
    SetShape();
    shape->setVisible(true);
    shape->setFlags(QGraphicsItem::ItemIsSelectable);
    SetBackgroundColor(backgroundColor);
    SetFrameColor(frameColor);
    qgs->addItem(shape);
    if(content) qgs->addItem(content);
}

void Node::SetVisibility(bool vis)
{
    shape->setVisible(vis);
}
void Node::SetLocation(const QPointF &qp)
{
    location=qp;
    SetShape();
}

void Node::SetWidth(double wd)
{
    width=wd;
    SetShape();
}

void Node::SetHeight(double h)
{
    height=h;
    SetShape();
}

void Node::SetBackgroundColor(const QColor &qc)
{
    backgroundColor=qc;
    QBrush brush=shape->brush();
    brush.setColor(backgroundColor);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    shape->setBrush(brush);
}

void Node::SetFrameColor(const QColor &qc)
{
    frameColor=qc;
    QPen pen=shape->pen();
    pen.setColor(frameColor);
    shape->setPen(pen);
}

void Node::Remove(QGraphicsScene *qgs)//等待arrow完成后继续修改
{
    isRemoved=true;
    qgs->removeItem(shape);
    if(content) content->delete_text(qgs);
     foreach (auto arrow, sourceArrows)
     {
        arrow->removeArrow();
     }
     foreach (auto arrow, destinationArrows)
     {
         arrow->removeArrow();
     }
     isRemoved=false;
      this->deleteID();
}

void Node::BindToText(QGraphicsScene* qgs)
{
    if(content==nullptr)
    {
        QString temp="0x";
        temp+= QString::number(GetID(),16);
        auto text = new Text(QPointF(location.x()-width/2,location.y()-height/2), this, temp, true);
        text->change_content("文本");
        text->setZValue(shape->zValue());
        auto window = MainWindow::instance();
        text->reset_font(QFont(window->fontFamily, window->fontSize));
        text->reset_color(window->textColor);
        (new ChangeElementAction(text, ElementShape::Text, true))->Do();
        //add by luo yigui
                this->boundTextView=text;
               // this->boundTextView->setParent(this);
    }
}

void Node::SetThickness(double nt)
{
    QPen pen=shape->pen();
    pen.setWidthF(nt);
    shape->setPen(pen);
}

void Node::SetRef(QString s)
{
    if(!content) return;
    content->change_input(s);
}
double Node::GetThickness()
{
    QPen pen=shape->pen();
    return pen.widthF();
}
QVector<Arrow*> Node::getSourceArrows()
{
    QVector<Arrow*> vec;
    foreach (auto arrow, sourceArrows)
    {
        vec.append(arrow);
    }
    return vec;
}

void Node::ChangeZValue(bool isSelected)
{
    if(isSelected) shape->setZValue(100);
    else shape->setZValue(1);
    if(content) content->setZValue(shape->zValue());
}
//将对像转成JSONOBJECT
QJsonObject Node::get_JsonObject()
{
    QJsonObject qso;
    QJsonObject TVqso;
    /*
     QPointF location=QPointF(0.0,0.0);//表示图形中心位置
    double width,height;
    QColor backgroundColor=Qt::white,frameColor=Qt::black;
    NodeItem* shape=new NodeItem(this);
    bool isRemoved=false;*/

    //用上述这些属性构造出一个QJsonObject
    /*
     *        Id:0x123,
              Location_X:123,
              Location_Y:234,
              Height:20,
              Width:40,
              FrameColor:"red",
              BackGroundColor: ,
              FrameLineWidth:6,
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
    qso.insert("Id",GetID());
    qso.insert("Location_X",location.x());
    qso.insert("Location_y",location.y());
    qso.insert("Height",GetHeight());
    qso.insert("Width",GetWidth());
    qso.insert("FrameColor",this->frameColor.name());
    qso.insert("BackGroundColor",this->backgroundColor.name());
    //qso.insert("FrameLineWidth",this->GetID()); //fromelinewidth 还不知道用的是哪个属性，待确定

    //获取TEXTVIEW的属性，转变成TVqso
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

//根据JSON转成成相应的对象
void Node::set_JsonObject(QJsonObject qso)
{

  QString Id = qso.value("Id").toString();
  QString Location_X = qso.value("Location_X").toString();
  QString Location_y = qso.value("Location_y").toString();
  QString Height = qso.value("Height").toString();
  QString Width = qso.value("Width").toString();
  QString FrameColor = qso.value("FrameColor").toString();
  QString BackGroundColor = qso.value("BackGroundColor").toString();

  QJsonObject TVqso = qso.value("TextView").toObject();

  QString TVId = TVqso.value("Id").toString();
  QString TVLocation_X = TVqso.value("Location_X").toString();
  QString TVLocation_y = TVqso.value("Location_y").toString();
  QString TVFontColor = TVqso.value("FontColor").toString();
  QString TVFontSize = TVqso.value("FontSize").toString();

  QJsonObject TVCqso = TVqso.value("TextContent").toObject();

  QString TVCTextDescription = TVCqso.value("TextDescription").toString();
  QString TVCLogicAction = TVCqso.value("LogicAction").toString();


}
