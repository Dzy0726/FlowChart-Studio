#include "graph.h"
#include "arrow.h"
#include "subgraphnode.h"
Graph::Graph(QVector<Node*>& v_Node, QVector<Text*>& v_Text, QVector<Graph*>& v_Graph){

}

void Graph::resizeGraph(){

}

void Graph::MoveSubGraph(){

}

void Graph::FoldSubGraph(){
    if (!isExpended)    //若未展开（折叠状态）则不进行折叠
            return;
        //以下遍历map
    foreach(auto node, nodes){
        node->SetVisibility(false);
    }
    foreach(auto arrow, arrows){
        //arrow->SetVisibility(false);
    }
    foreach(auto text, texts){
        text->hide();
    }
    foreach(auto sub, subGraph){
        sub->SetVisibility(false);
    }
    subGraphNode->SetVisibility(true);
    isExpended=false;
}

void Graph::unFoldSubGraph(){
    if (isExpended)    //若已展开则不进行展开
            return;
    //以下遍历map
    foreach(auto node, nodes){
        node->SetVisibility(true);
    }
    foreach(auto arrow, arrows){
        //arrow->SetVisibility(true);
    }
    foreach(auto text, texts){
        text->show();
    }
    foreach(auto sub, subGraph){
        sub->SetVisibility(true);
    }
    subGraphNode->SetVisibility(false);
    isExpended=true;
}

void Graph::DeleteSubGraph(){

}

void Graph::addNode(Node* node)
{
    nodes.insert(node->GetID(), node);
}


void Graph::addNode(Node* node, int index, ElementShape shape){
    node_info n;
    n.node_id=node->GetID();
    n.p_node=node;
    n.index=index;
    n.shape=shape;
    v_node_info.push_back(n);
}

QVector<QPair<Node*,ElementShape>> Graph::Nodes_ElementShape(int index){
    QVector<QPair<Node*,ElementShape>> v;
    foreach(auto n,v_node_info){
        if(n.index == index){
            v.push_back({n.p_node,n.shape});
        }
    }
    return v;
}


void Graph::removeNode(Node* node)
{
    nodes.remove(node->GetID());
}

Node* Graph::searchNode(QPointF point)
{
    foreach (auto node, nodes)
    {
        auto size = QPointF(node->GetWidth(), node->GetHeight());
        QPointF position = node->GetLocation();
        if (point.rx() >= position.rx() - size.rx() && point.ry() >= position.ry() - size.ry() &&
                point.rx() <= position.rx() + size.rx() && point.ry() <= position.ry() + size.ry())
        {
            return node;
        }
    }
    return nullptr;
}

QVector<Node*> Graph::searchNodes(Node* node)
{
    auto size = QPointF(node->GetWidth(), node->GetHeight());
    auto rect = QRectF(node->GetLocation() - size / 2, QSizeF(size.rx(), size.ry()));
    QVector<Node*> vec;
    foreach (auto node, nodes)
    {
        auto sSize = QPointF(node->GetWidth(), node->GetHeight());
        auto point = node->GetLocation() - sSize / 2;
        if (rect.contains(point))
        {
            vec.append(node);
            continue;
        }
        point = node->GetLocation() + QPointF(sSize.rx(), -sSize.ry());
        if (rect.contains(point))
        {
            vec.append(node);
            continue;
        }
        point = node->GetLocation() + QPointF(-sSize.rx(), sSize.ry());
        if (rect.contains(point))
        {
            vec.append(node);
            continue;
        }
        point = node->GetLocation() + sSize / 2;
        if (rect.contains(point))
        {
            vec.append(node);
            continue;
        }
    }
    return vec;
}
QVector<Arrow*> Graph::searchArrows(Node* node)
{

    QVector<Arrow*> vec;
    foreach (auto arrow, arrows)
    {
        if( node->getNodeItem()->contains(arrow->startItem()->pos())||
                node->getNodeItem()->contains(arrow->endItem()->pos())||
                  node->getNodeItem()->contains(
                    QPointF((arrow->endItem()->pos().x()+arrow->endItem()->pos().x())/2
                            ,(arrow->endItem()->pos().y()+arrow->endItem()->pos().y())/2)))
        {
                vec.append(arrow);
                continue;
    }


    }
    return vec;
}
void Graph::addText(Text* text)
{
    texts.append(text);
}

void Graph::removeText(Text* text)
{
    texts.removeAll(text);
}

Text* Graph::searchText(QPointF point)
{
    foreach (auto text, texts)
    {
        auto size = QPointF(text->textWidth(), 0);
        QPointF position = text->get_text_location();
        if (point.rx() >= position.rx() - size.rx() && point.ry() >= position.ry() - size.ry() &&
                point.rx() <= position.rx() + size.rx() && point.ry() <= position.ry() + size.ry())
        {
            return text;
        }
    }
    return nullptr;
}

QVector<Text*> Graph::searchTexts(Node* node)
{
    auto size = QPointF(node->GetWidth(), node->GetHeight());
    auto rect = QRectF(node->GetLocation() - size / 2, QSizeF(size.rx(), size.ry()));
    QVector<Text*> vec;
    foreach (auto text, texts)
    {
        auto sSize = QPointF(text->textWidth(), 0);
        auto point = text->get_text_location() - sSize / 2;
        if (rect.contains(point))
        {
            vec.append(text);
            continue;
        }
        point = text->get_text_location() + QPointF(sSize.rx(), -sSize.ry());
        if (rect.contains(point))
        {
            vec.append(text);
            continue;
        }
        point = text->get_text_location() + QPointF(-sSize.rx(), sSize.ry());
        if (rect.contains(point))
        {
            vec.append(text);
            continue;
        }
        point = text->get_text_location() + sSize / 2;
        if (rect.contains(point))
        {
            vec.append(text);
            continue;
        }
    }
    return vec;
}

void Graph::addArrow(Arrow* arrow)
{
    arrows[arrow->GetID()] = arrow;
}

void Graph::removeArrow(Arrow* arrow)
{
    arrows.remove(arrow->GetID());
}

void Graph::SetVisibility(bool set){

}

void Graph::clear()
{
    nodes.clear();
    texts.clear();
    arrows.clear();
}

void Graph::AddRelatedNode(SubgraphNode *sn)
{
    relatedNodes.insert(sn->GetID(),sn);
}

void Graph::RemoveRelatedNode(SubgraphNode *sn)
{
    relatedNodes.remove(sn->GetID());
}

//将对像转成JSONOBJECT
QJsonObject  Graph::get_JsonObject()
{

    QJsonObject qso;

    /*
File:{
      Name:"aaa",
          Path:"d:/testfile1/aaa",
              */
    qso.insert("Id",this->GetID());
    qso.insert("Path",this->getPath());


    //对于每一种NODE，构建QJSON
    QMap<int,Node*>::iterator iter;
    iter=this->getNodes().begin();
    QJsonArray recArray;
    while (iter!=this->getNodes().end())
     {

        if(iter.value()->GetType()==1) //rectangle
        {
            recArray.append(iter.value()->get_JsonObject());
        }
        iter++;
    }
    if(recArray.size()>0)
    {
        qso.insert("Rectangles",QJsonValue(recArray));
    }

    iter=this->getNodes().begin();
    QJsonArray DiamondArray;
    while (iter!=this->getNodes().end())
     {

        if(iter.value()->GetType()==2) //Diamond
        {
            DiamondArray.append(iter.value()->get_JsonObject());
        }
        iter++;
    }
    if(DiamondArray.size()>0)
    {
        qso.insert("Diamonds",QJsonValue(DiamondArray));
    }

    //for subgraph node
    iter=this->getNodes().begin();
    QJsonArray subgraphArray;
    while (iter!=this->getNodes().end())
     {

        if(iter.value()->GetType()==6) //subgraph
        {
            subgraphArray.append(iter.value()->get_JsonObject());
        }
        iter++;
    }
    if(subgraphArray.size()>0)
    {
        qso.insert("Subgraphs",QJsonValue(subgraphArray));
    }

    //for input node
    iter=this->getNodes().begin();
    QJsonArray inputArray;
    while (iter!=this->getNodes().end())
     {

        if(iter.value()->GetType()==4) //input node
        {
            inputArray.append(iter.value()->get_JsonObject());
        }
        iter++;
    }
    if(inputArray.size()>0)
    {
        qso.insert("Inports",QJsonValue(inputArray));
    }

    //for output node
    iter=this->getNodes().begin();
    QJsonArray outputArray;
    while (iter!=this->getNodes().end())
     {

        if(iter.value()->GetType()==5) //output node
        {
            outputArray.append(iter.value()->get_JsonObject());
        }
        iter++;
    }
    if(outputArray.size()>0)
    {
        qso.insert("Outports",QJsonValue(outputArray));
    }

    //for inner input ports
    iter=this->getNodes().begin();
    QJsonArray iinputArray;
    while (iter!=this->getNodes().end())
     {

        if(iter.value()->GetType()==4) //innerinput node
        {
            iinputArray.append(iter.value()->get_JsonObject());
        }
        iter++;
    }
    if(iinputArray.size()>0)
    {
        qso.insert("InnerInports",QJsonValue(iinputArray));
    }

    //for inner output ports
    iter=this->getNodes().begin();
    QJsonArray ioutputArray;
    while (iter!=this->getNodes().end())
     {

        if(iter.value()->GetType()==5) //inneroutput node  ????
        {
            ioutputArray.append(iter.value()->get_JsonObject());
        }
        iter++;
    }
    if(ioutputArray.size()>0)
    {
        qso.insert("InnerOutports",QJsonValue(ioutputArray));
    }

    //for arrows

    QMap<int,Arrow*>::iterator iter2;
    iter2=this->getArrows().begin();
    QJsonArray arrowArray;
    while(iter2!=getArrows().end())
    {
        if(iter2.value()->getType()==1||2||3)// atype
        {
            arrowArray.append(iter2.value()->get_JsonObject());
        }
        iter2++;
    }
    if(arrowArray.size()>0)
    {
        qso.insert("Arrows",QJsonValue(arrowArray));
    }

    return qso;
}

//根据JSON转成成相应的对象
void  Graph::set_JsonObject(QJsonObject qso)
{

}

QString Graph::getPath()
{
    return this->graphFilePath;
}

//add by luo yigui
//save to the json file and set graphFilePath
int Graph::write_to_file(QString path)
{
    //get the json of this
    graphFilePath=path;
    //save file to path
    return 1;
}

