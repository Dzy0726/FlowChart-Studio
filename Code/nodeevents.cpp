#include <QMenu>

#include "nodeevents.h"
#include "changeelementaction.h"
#include "mainwindow.h"
#include "groupaction.h"
#include "arrow.h"
#include "subgraphnode.h"
#include "editelementaction.h"


void NodeEvents::contextMenuEvent(Node* node, QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    auto deleteAction = menu.addAction("删除");
    deleteAction->setShortcut(QKeySequence::Delete);
    QAction* subGraphAction;
    QAction* subGraphAction2;
    if (dynamic_cast<SubgraphNode*>(node))
    {
        subGraphAction = menu.addAction("打开子图");
        subGraphAction2 = menu.addAction("创建所有端口");
    }
    auto cutAction = menu.addAction("剪切");
    cutAction->setShortcut(QKeySequence::Cut);
    auto copyAction = menu.addAction("复制");
    copyAction->setShortcut(QKeySequence::Copy);
    auto selectedAction = menu.exec(event->screenPos());
    if (selectedAction == deleteAction)
    {
        deleteElemets();
    }
    else if (selectedAction && selectedAction == subGraphAction)
    {
        auto sgnode = static_cast<SubgraphNode*>(node);
        sgnode->OpenSubGraph();
    }
    else if (selectedAction && selectedAction == subGraphAction2)
    {
        auto sgnode = static_cast<SubgraphNode*>(node);
        sgnode->CreateAllPort();

    }
    else if (selectedAction == copyAction)
    {
        copyElements(node);
    }
    else if (selectedAction == cutAction)
    {
        cutElements(node);
    }
}

void NodeEvents::deleteElemets()
{
    auto action = new GroupAction;
    foreach (auto arrow, *MainWindow::instance()->selectedArrows())
    {
        *action << new ChangeElementAction(arrow, ElementShape::Arrow, false);
    }
    foreach (auto text, *MainWindow::instance()->selectedTexts())
    {
        *action << new ChangeElementAction(text, ElementShape::Text, false);
    }
    foreach (auto node, *MainWindow::instance()->selectedNodes())
    {
        *action << new ChangeElementAction(node, ElementShape::Rectangle, false);
    }
    action->Do();
}
//修改了删除箭头的bug

void NodeEvents::cutElements(Node* node)
{
    auto graph = MainWindow::instance()->cutGraph;
    graph->clear();
    graph->node = node;
    auto action = new GroupAction();
    auto texts = QVector<Text*>();
    foreach (auto node, *MainWindow::instance()->selectedNodes())
    {
        if (!graph->node) graph->node = node;
        graph->addNode(node);
        auto text = node->content;
        if (text)
        {
            texts.append(text);
            graph->addText(text);
            *action << new ChangeElementAction(text, ElementShape::Text, false);
        }
        *action << new ChangeElementAction(node, ElementShape::Rectangle, false);
    }
    foreach (auto text, *MainWindow::instance()->selectedTexts())
    {
        if (texts.contains(text)) continue;
        graph->addText(text);
        *action << new ChangeElementAction(text, ElementShape::Text, false);
    }
    foreach (auto arrow, *MainWindow::instance()->selectedArrows())
    {
        graph->addArrow(arrow);
        *action << new ChangeElementAction(arrow, ElementShape::Arrow, false);
    }
    action->Do();
}

void NodeEvents::copyElements(Node* node)
{
    auto graph = MainWindow::instance()->cutGraph;
    graph->clear();
    graph->node = node;
    auto texts = QVector<Text*>();
    foreach (auto node, *MainWindow::instance()->selectedNodes())
    {
        if (!graph->node) graph->node = node;
        auto text = node->content;
        if (text)
        {
            texts.append(text);
            graph->addText(text);
        }
        graph->addNode(node);
    }
    foreach (auto text, *MainWindow::instance()->selectedTexts())
    {
        if (texts.contains(text)) continue;
        graph->addText(text);
    }
    foreach (auto arrow, *MainWindow::instance()->selectedArrows())
    {
        graph->addArrow(arrow);
    }
}

void NodeEvents::mousePressEvent(Node* node, QGraphicsSceneMouseEvent *event)
{

}

void NodeEvents::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    auto action = new GroupAction;
    auto addTextAction = [action](Text* text)
    {
        *action << new EditElementAction(text, ElementShape::Text,
                                         ElementProperty::Location,
                                         new QPointF(text->lastPosition),
                                         new QPointF(text->get_text_location()));
    };
    auto texts = QVector<Text*>();
    foreach (auto node, *MainWindow::instance()->selectedNodes())
    {
        *action << new EditElementAction(node, ElementShape::Rectangle,
                                        ElementProperty::Location,
                                        new QPointF(node->getNodeItem()->lastLocation),
                                        new QPointF(node->GetLocation()));
        auto text = node->content;
        if (text)
        {
            addTextAction(text);
            text->lastPosition = text->get_text_location();
            texts.append(text);
        }
    }
    foreach (auto text, *MainWindow::instance()->selectedTexts())
    {
        if (texts.contains(text)) continue;
        addTextAction(text);
    }
}

void NodeEvents::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    auto texts = QVector<Text*>();
    foreach (auto node, *MainWindow::instance()->selectedNodes())
    {
        node->SetLocation(node->GetLocation()+event->pos()-event->lastPos());
        Text* text=node->content;
        if(text)
        {
            text->move_text(text->get_text_location()+event->pos()-event->lastPos());
            texts.append(text);
        }
        else{
           QVector<Arrow*> arrows= node->getArrows();
           foreach(Arrow* ar , arrows){
               if(ar->content!=nullptr)
               ar->content->move_text(QPointF((ar->getlist().at(0).x()+ar->getlist().at(1).x())/2,
                                   (ar->getlist().at(0).y()+ar->getlist().at(1).y())/2));
           }

        }
    }
    foreach (auto text, *MainWindow::instance()->selectedTexts())
    {
        if (texts.contains(text)) continue;
        text->move_text((text->get_text_location()+event->pos()-event->lastPos()));
    }
}

void NodeEvents::selectAll()
{
    auto graph = MainWindow::instance()->graph();
    foreach (auto node, graph->getNodes())
    {
        node->getNodeItem()->SetSelected(true);
    }
    foreach (auto arrow, graph->getArrows())
    {
        arrow->setSelected(true);
    }
    foreach (auto text, graph->getTexts())
    {
        text->setSelected(true);
    }
}

void NodeEvents::scaleNodes(Node* node, QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->pos();
    double nw=sqrt(pow(node->GetLocation().x() - pos.x(), 2)),nh=sqrt(pow(node->GetLocation().y() - pos.y(), 2));
    double cw = nw * 2 - node->GetWidth(), ch = nh * 2 - node->GetHeight();
    foreach (auto node, *MainWindow::instance()->selectedNodes())
    {
        auto newW = node->GetWidth() + cw, newH = node->GetHeight() + ch;
        if (newW < 25) newW = 25;
        if (newH < 25) newH = 25;
        node->SetHeight(newH);
        node->SetWidth(newW);
        foreach (auto arrow, node->getArrows())
        {
            arrow->update();
        }
    }
}
