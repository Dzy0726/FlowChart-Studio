#ifndef TEXT_H
#define TEXT_H


#include <QMainWindow>
#include<QString>
#include<QFont>
#include<QGraphicsRectItem>
#include<QGraphicsScene>
#include <QGraphicsTextItem>
#include<QColor>
#include<QGraphicsItem>
#include <QGraphicsScene>
#include<textitem.h>
#include<textdialog.h>
#include<textdialog2.h>
#include<textdialog3.h>
class Node;

class TextItem;
class Text : public QGraphicsTextItem{
Q_OBJECT
public:
    Text(QPointF primary_location,Node* parent = 0,QString parentID = NULL,bool IDchanged=false);//由节点生成
    //Text(QPointF position1, QPointF position2,QGraphicsItem* parent = 0);//由图生成（鼠标位置决定大小）
    ~Text();
    void build_text(QColor c=Qt::black, QFont f=QFont());//初始化并在界面中显示
    void putup_text(QGraphicsScene* scene);
    void delete_text(QGraphicsScene* scene);
    void delete_char(int begin, int end);//参数：待删除字符位置
    void add_char(int position, QString str);//增加字符位置，增加的字符
    void reset_font(QFont new_font);//新字体
    void reset_color(QColor new_color);
   // Text(Text old_t, QPointF primary_location, double primary_width, double primary_height,QGraphicsItem* parent = 0);//附着于新的节点
    void move_text(QPointF new_location);//参数：新的坐标位置
   // void resize_text(double d_width, double d_height);//参数：表示宽和高的位移
    void change_content(QString new_c);

    QString get_text_logic(); //add by luo yigui
    QFont get_text_font();
    QString get_text_content();
    QString get_text_all();
    QPointF get_text_location();
    QColor get_text_color();
    Text* get_item();
    TextItem* getTextItem() const { return shape; }
    Node* parent = nullptr;
    QPointF lastPosition;
    QString getId() { return ID; }
    QString getInput(){return Input;}
    void change_input(QString inputID);
    void change_ID(QString ID_);
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:

    QPointF location;
    QString content;
    QFont font;
    QColor color;
    QString logic=NULL;
    QString all=NULL;
    TextItem* shape=new TextItem(this);
    QString ID;
    bool IDchange=false;
    QString Input;
    bool isInput=false;

signals:
    void Selected(Text*t,bool b);
};



#endif 
