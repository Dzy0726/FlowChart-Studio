#include "changeelementaction.h"
#include "mainwindow.h"
#include "text.h"
#include "node.h"
#include "arrow.h"
#include <QDebug>

void onArrowSelected(Arrow* arrow, bool isSelected);

Scene* scene;

ChangeElementAction::ChangeElementAction(void* element, ElementShape shape, bool isCreated, Scene* scene) :
    isCreated(isCreated), shape(shape), element(element)
{
    ::scene = scene;
    if (scene)
    {
        auto lastScene = MainWindow::instance()->scene();
        lastScene->undoStack.removeLast();
        scene->undoStack.append(this);
    }
}

ChangeElementAction::~ChangeElementAction()
{
    ::scene = nullptr;
}

void ChangeElementAction::Do()
{
    auto window = MainWindow::instance();
    auto scene = ::scene ? ::scene : window->scene();
    scene->isChanged = true;
    auto graph = scene->graph;
    if (isNode(shape))
    {
        auto node = static_cast<Node*>(element);
        if (isCreated)
        {
            auto item = node->getNodeItem();
            connect(item, &NodeItem::Selected, this, &ChangeElementAction::onNodeSelected);
            connect(item, &NodeItem::NewLocation, this, &ChangeElementAction::onNodeMoved);
            node->Paint(scene);
            graph->addNode(node);
            graph->addNode(node,MainWindow::instance()->index_tab(),shape);
        }
        else
        {
            auto arrows = node->getArrows();
            foreach (auto arrow, arrows)
            {
                arrow->removeArrow();
                auto action = new ChangeElementAction(arrow, ElementShape::Arrow, false,scene);
                action->Do();
            }
            node->Remove(scene);
            graph->removeNode(node);
            MainWindow::instance()->selectedNodes()->remove(node->GetID());
            disconnect(node->getNodeItem(), &NodeItem::Selected, this, &ChangeElementAction::onNodeSelected);
            node->getNodeItem()->setSelected(false);
        }
    }
    else if (shape == ElementShape::Text)
    {
        auto text = static_cast<Text*>(element);
        if (isCreated)
        {
            auto parent = text->parent;
            if (parent) parent->content = text;
            graph->addText(text);
            text->putup_text(scene);
            connect(text, &Text::Selected, this, &ChangeElementAction::onTextSelected);
            text->build_text(text->get_text_color(), text->get_text_font());
        }
        else
        {
            auto parent = text->parent;
            if (parent) parent->content = nullptr;
            graph->removeText(text);
            window->selectedTexts()->removeAll(text);
            text->delete_text(scene);
            disconnect(text, &Text::Selected, this, &ChangeElementAction::onTextSelected);
            text->setSelected(false);
        }
    }
    else if (shape == ElementShape::Arrow)
    {
        auto arrow = static_cast<Arrow*>(element);
        if (isCreated)
        {
            arrow->myStartItem->GetNode()->ConnectAsSource(arrow);
            arrow->myEndItem->GetNode()->ConnectAsDestination(arrow);
            arrow->setZValue(-100.0);
            arrow->s = onArrowSelected;
            scene->addItem(arrow);
            arrow->updatePosition();
            graph->addArrow(arrow);
        }
        else
        {
            arrow->myStartItem->GetNode()->DisconnectAsSource(arrow);
            arrow->myEndItem->GetNode()->DisconnectAsDestination(arrow);
            graph->removeArrow(arrow);
            scene->removeItem(arrow);
            MainWindow::instance()->selectedArrows()->remove(arrow->GetID());
            arrow->s = nullptr;
            arrow->setSelected(false);
        }
    }
}

void ChangeElementAction::Undo()
{
    ChangeElementAction(element, shape, !isCreated).Do();
}

void ChangeElementAction::onNodeSelected(Node* node, bool isSelected)
{
    auto selectedNodes = MainWindow::instance()->selectedNodes();
    if (isSelected)
    {
        selectedNodes->insert(node->GetID(), node);
    }
    else
    {
        selectedNodes->remove(node->GetID());
    }
}

void ChangeElementAction::onNodeMoved(Node* node, QPointF oldPosition)
{

}

void ChangeElementAction::onTextSelected(Text* text, bool isSelected)
{
    auto selectedTexts = MainWindow::instance()->selectedTexts();
    if (isSelected)
    {
        selectedTexts->append(text);
    }
    else
    {
        selectedTexts->removeAll(text);
        if (text->get_text_all() == "")
        {
            (new ChangeElementAction(text, ElementShape::Text, false))->Do();
        }
    }
}

void onArrowSelected(Arrow* arrow, bool isSelected)
{
    auto selectedArrows = MainWindow::instance()->selectedArrows();
    if (isSelected)
    {
        selectedArrows->insert(arrow->GetID(), arrow);
    }
    else
    {
        selectedArrows->remove(arrow->GetID());
    }
}
