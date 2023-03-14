#ifndef GRAPH_H
#define GRAPH_H

#include"node.h"
#include"text.h"
#include "elementshape.h"
#include <QFile>
class SubgraphNode;
class Graph:public GraphElement
{
public:
    Graph(){}
    //调用下面这个函数来定义子图，传入要生成子图的节点们
    Graph(QVector<Node*>& v_Node, QVector<Text*>& v_Text, QVector<Graph*>& v_Graph);
    void resizeGraph(); //调整图形在屏幕上的布局
    void MoveSubGraph();//移动子图
    void FoldSubGraph();//折叠
    void unFoldSubGraph();  //展开
    void DeleteSubGraph();  //删除子图，当前子图下所有节点归为父节点

    void addNode(Node* node);
    void removeNode(Node* node);
    Node* searchNode(QPointF point);
    QVector<Node*> searchNodes(Node* node);
    void addText(Text* node);
    void removeText(Text* node);
    Text* searchText(QPointF point);
    QVector<Arrow*> searchArrows(Node* node);
    QVector<Text*> searchTexts(Node* node);
    void addArrow(Arrow* arrow);
    void removeArrow(Arrow* arrow);
    void clear();
    QMap<int, Node*>& getNodes() { return nodes; }
    QMap<int, Arrow*>& getArrows() { return arrows; }
    QVector<Text*>& getTexts() { return texts; }
    QMap<int, SubgraphNode*>& getRelatedNodes(){return relatedNodes;}
    void AddRelatedNode(SubgraphNode* sn);
    void RemoveRelatedNode(SubgraphNode* sn);
    void BindToText(QGraphicsScene *qgs) override {}
    Node* node;
    
    void addNode(Node* node, int index, ElementShape shape);
    QVector<QPair<Node*,ElementShape>> Nodes_ElementShape(int index);
    
    //****************************************************************
        //将对像转成JSONOBJECT
        virtual QJsonObject get_JsonObject() override;
        //根据JSON转成成相应的对象
        virtual void set_JsonObject(QJsonObject qso) override;

        //add by luo yigui
        //save to the json file and set graphFilePath
        int write_to_file(QString path);

        //read the contend from json file and construct the graph
        int read_from_file(QString path);

        QString getPath();
private:
    void SetVisibility(bool set);
    bool isExpended;
    Node* subGraphNode;
    QMap<int, Node*> nodes;
    QMap<int, Arrow*> arrows;
    QVector<Text*> texts;
    QMap<int, Graph*> subGraph;
    QMap<int, SubgraphNode*> relatedNodes;
    struct node_info{
        int node_id;
        Node* p_node = nullptr;
        int index;
        ElementShape shape;
    };
    QVector<node_info> v_node_info;
    //add by luo yigui
        QFile graphFile;
        QString graphFilePath;
};

#endif // GRAPH_H
