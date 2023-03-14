#include <QComboBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editelementaction.h"
#include "groupaction.h"
#include "nodeevents.h"
#include "arrow.h"

void MainWindow::textColorChanged()
{
    textAction = qobject_cast<QAction *>(sender());
    auto color = qvariant_cast<QColor>(textAction->data());
    changeTextColor(color);
}

void MainWindow::itemColorChanged()
{
    fillAction = qobject_cast<QAction *>(sender());
    auto color = qvariant_cast<QColor>(fillAction->data());
    changeFillColor(color);
}

void MainWindow::bdColorChanged()
{
    bdAction = qobject_cast<QAction *>(sender());
    auto color = qvariant_cast<QColor>(bdAction->data());
    changeFrameColor(color);
}

void MainWindow::arrowColorChanged()
{
    arrowColorAction = qobject_cast<QAction *>(sender());
    auto color = qvariant_cast<QColor>(arrowColorAction->data());
    changeLineColor(color);
}

void MainWindow::on_addRectangleButton_clicked()
{
    _nextAddedShape = ElementShape::Rectangle;
}

void MainWindow::on_addDiamondButton_clicked()
{
    _nextAddedShape = ElementShape::Diamond;
}

void MainWindow::on_addArrowButton_clicked()
{
    _nextAddedShape = ElementShape::Arrow;
}

void MainWindow::on_addTextButton_clicked()
{
    _nextAddedShape = ElementShape::Text;
}

void MainWindow::on_addSubgraghButton_clicked()
{
    _nextAddedShape = ElementShape::SubGraph;
}

void MainWindow::on_addInputButton_clicked()
{
    _nextAddedShape = ElementShape::Input;
}

void MainWindow::on_addOutputButton_clicked()
{
    _nextAddedShape = ElementShape::Output;
}

void MainWindow::Cut() { NodeEvents::cutElements(); }
void MainWindow::Copy() { NodeEvents::copyElements(); }
void MainWindow::Paste() { Scene::pasteElements(); }
void MainWindow::SelectAll() { NodeEvents::selectAll(); }

void MainWindow::Undo()
{
    auto& undoStack = scene()->undoStack;
    auto& redoStack = scene()->redoStack;
    if (undoStack.size() > 0)
    {
        auto action = undoStack.last();
        undoStack.removeLast();
        action->Undo();
        redoStack.append(action);
        scene()->lastUndoSize = undoStack.size();
    }
}

void MainWindow::Redo()
{
    auto& undoStack = scene()->undoStack;
    auto& redoStack = scene()->redoStack;
    if (undoStack.size() > scene()->lastUndoSize) redoStack.clear();
    if (redoStack.size() > 0)
    {
        auto action = redoStack.last();
        redoStack.removeLast();
        action->Do();
        undoStack.append(action);
        scene()->lastUndoSize = undoStack.size();
    }
}

void MainWindow::clickbdBtn()
{
    auto action = new GroupAction;
    foreach (auto node, *selectedNodes())
    {
        *action << new EditElementAction(node, ElementShape::Rectangle,
                                         ElementProperty::FrameColor,
                                         new QColor(node->GetFrameColor()),
                                         new QColor(bdColor));
    }
    action->Do();
}

void MainWindow::clickFillBtn()
{
    auto action = new GroupAction;
    foreach (auto node, *selectedNodes())
    {
        *action << new EditElementAction(node, ElementShape::Rectangle,
                                         ElementProperty::BackgroundColor,
                                         new QColor(node->GetBackgroundColor()),
                                         new QColor(fillColor));
    }
    action->Do();
}

void MainWindow::clickLineBtn()
{
    auto action = new GroupAction;
    QVector<Arrow*> arrows;
    foreach (auto arrow, *selectedArrows())
    {
        if (arrows.contains(arrow)) continue;
        //arrow->setArrowColor(lineColor);
        foreach (auto arrow, arrow->arrowlist)
        {
            arrows.append(arrow);
        }
        *action << new EditElementAction(arrow, ElementShape::Arrow,
                                         ElementProperty::FrameColor,
                                         new QColor(arrow->getColor()),
                                         new QColor(lineColor));
    }
    action->Do();
}

void MainWindow::clickTextColorButton()
{
    auto action = new GroupAction;
    foreach (auto text, *selectedTexts())
    {
        *action << new EditElementAction(text, ElementShape::Text,
                                         ElementProperty::FontColor,
                                         new QColor(text->get_text_color()),
                                         new QColor(textColor));
    }
    action->Do();
}

void MainWindow::on_addInnerInputButton_clicked()
{
    _nextAddedShape = ElementShape::InnerInput;
}

void MainWindow::on_addInnerOutputButton_clicked()
{
    _nextAddedShape = ElementShape::InnerOutput;
}

void MainWindow::changeFrameColor(QColor color)
{
    if (selectedNodes()->size() > 0)
    {
        auto oldColor = bdColor;
        bdColor = color;
        clickbdBtn();
        bdColor = oldColor;
    }
    else
    {
        bdColor = color;
        auto icon = createColorToolButtonIcon(":/images/bdcolor.png", color);
        bdColorToolBtn->setIcon(icon);
    }
}

void MainWindow::changeFillColor(QColor color)
{
    if (selectedNodes()->size() > 0)
    {
        auto oldColor = fillColor;
        fillColor = color;
        clickFillBtn();
        fillColor = oldColor;
    }
    else
    {
        fillColor = color;
        auto icon = createColorToolButtonIcon(":/images/floodfill.png", color);
        fillColorToolBtn->setIcon(icon);
    }
}

void MainWindow::changeLineColor(QColor color)
{
    if (selectedArrows()->size() > 0)
    {
        auto oldColor = lineColor;
        lineColor = color;
        clickLineBtn();
        lineColor = oldColor;
    }
    else
    {
        lineColor = color;
        auto icon = createColorToolButtonIcon(":/images/arrowcolor.png", color);
        arrowColorToolBtn->setIcon(icon);
    }
}

void MainWindow::changeTextColor(QColor color)
{
    if (selectedTexts()->size() > 0)
    {
        auto oldColor = textColor;
        textColor = color;
        clickTextColorButton();
        textColor = oldColor;
    }
    else
    {
        textColor = color;
        auto icon = createColorToolButtonIcon(":/images/textpointer.png", color);
        fontColorToolBtn->setIcon(icon);
    }
}

void MainWindow::textButtonTriggered() {}
void MainWindow::fillButtonTriggered() {}
void MainWindow::bdButtonTriggered() {}
void MainWindow::arrowColorButtonTriggered() {}

void MainWindow::lineTypeChanged(int index)
{
    auto type = index + 1;
    if (type == 3) type++;
    ui->arrowComboBox->setCurrentIndex(index);
    if (selectedArrows()->size() > 0)
    {
        auto lastIndex = lineType - 1;
        if (lastIndex == 3) lastIndex--;
        ui->arrowComboBox->setCurrentIndex(lastIndex);
        auto action = new GroupAction;
        foreach (auto arrow, *selectedArrows())
        {
            *action << new EditElementAction(arrow, ElementShape::Arrow,
                                             ElementProperty::ArrowKind,
                                             new int(arrow->getType()),
                                             new int(type));
        }
        action->Do();
    }
    else
    {
        lineType = type;
    }
}

void MainWindow::changeFontFamily(QFont font)
{
    auto family = font.family();
    if (selectedTexts()->size() > 0)
    {
        fontBtn->setCurrentText(fontFamily);
        auto action = new GroupAction;
        foreach (auto text, *selectedTexts())
        {
            *action << new EditElementAction(text, ElementShape::Text,
                                             ElementProperty::Font,
                                             new QFont(text->get_text_font()),
                                             new QFont(family, fontSize));
        }
        action->Do();
    }
    else
    {
        fontFamily = family;
    }
}

void MainWindow::changeFontSize(QString sizeString)
{
    auto size = sizeString.toInt();
    if (selectedTexts()->size() > 0)
    {
        auto action = new GroupAction;
        fontSizeCombo->setCurrentText(QString::number(fontSize));
        foreach (auto text, *selectedTexts())
        {
            *action << new EditElementAction(text, ElementShape::Text,
                                             ElementProperty::Font,
                                             new QFont(text->get_text_font()),
                                             new QFont(fontFamily, size));
        }
        action->Do();
    }
    else
    {
        fontSize = size;
    }
}

void MainWindow::changeFont(QFont font)
{
    if (selectedTexts()->size() > 0)
    {
        auto action = new GroupAction;
        foreach (auto text, *selectedTexts())
        {
            *action << new EditElementAction(text, ElementShape::Text,
                                             ElementProperty::Font,
                                             new QFont(text->get_text_font()),
                                             new QFont(font));
        }
        action->Do();
    }
    else
    {
        fontSize = font.pointSize();
        fontFamily = font.family();
        fontSizeCombo->setCurrentText(QString::number(fontSize));
        fontBtn->setCurrentFont(font);
    }
}

void MainWindow::changeLineWidth(QString widthString)
{
    auto width = widthString.toInt();
    if (selectedArrows()->empty())
    {
        lineWidth = width;
    }
    else
    {
        auto action = new GroupAction;
        arrowSizeCombo->setCurrentText(QString::number(lineWidth));
        foreach (auto arrow, *selectedArrows())
        {
            *action << new EditElementAction(arrow, ElementShape::Arrow,
                                             ElementProperty::ArrowWidth,
                                             new int(arrow->getSize()),
                                             new int(width));
        }
        action->Do();
    }
}

void MainWindow::changeFrameWidth(QString widthString)
{
    auto width = widthString.toInt();
    if (selectedNodes()->empty())
    {
        frameWidth = width;
    }
    else
    {
        auto action = new GroupAction;
        bdSizeCombo->setCurrentText(QString::number(frameWidth));
        foreach (auto node, *selectedNodes())
        {
            *action << new EditElementAction(node, ElementShape::Rectangle,
                                             ElementProperty::FrameWidth,
                                             new int(node->GetThickness()),
                                             new int(width));
        }
        action->Do();
    }
}

void MainWindow::deleteElement()
{
    NodeEvents::deleteElemets();
}

void MainWindow::on_addSonPortButton_clicked() {}
void MainWindow::on_addFatherPortButton_clicked() {}
