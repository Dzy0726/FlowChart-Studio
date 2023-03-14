
#ifndef GRAPHELEMENT_H
#define GRAPHELEMENT_H
#include<QStyle>
#include<QGraphicsLineItem>
#include<text.h>
#include"QGraphicsScene"
//class GraphElement
//{
//public:
//    GraphElement();
//};

class GraphElement //图形元素
{
      public:
          GraphElement();
          ~GraphElement(){};
          int GetID();
          virtual void BindToText(QGraphicsScene* qgs)=0;
          int father;//一个流程图的父流程图的ID，暂定
          int Id;//单个文件内唯一,文件内可能存在若干图形，不同图形ID不同
          QString sId;//16进制字符串的ID
          void setsId(){this->sId=getIdNum(this->Id);}
          QString getsId(){return this->sId;}
          bool changesId(QString str);//用户手动修改图形元素的ID值
          int graphId;//一个流程图的Id，一个图形可以通过该ID知道它是属于那个流程图的
          //1 2 3 4 5 ...
          //1 1 0 1 0 ...
          //创建一个位示图，表示流程图编号分配，每次合并就往编号小的合，然后大的置0，删除图形元素时，判定是否他单独构成一个流程图，如果是就之0
          Text* content=nullptr; //文本内容
          void setId();
          void deleteID();//删除ID
          QString getIdNum(int num);
          int CStringHexToInt(QString str);
          bool isRepeat(QString str);
          int chagearrowID(int oldid);

          //将对像转成JSONOBJECT
          virtual QJsonObject get_JsonObject()=0;
          //根据JSON转成成相应的对象
          virtual void set_JsonObject(QJsonObject qso)=0;

private:
//          static int maxid;
};
#endif // GRAPHELEMENT_H
