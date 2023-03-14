#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QToolButton>
#include <QVector>
#include <QStandardItemModel>
#include <QFontComboBox>
#include <QString>
#include "elementshape.h"
#include "action.h"
#include "node.h"
#include "graph.h"
#include "scene.h"
#include <QMap>
#include <QDir>
//*****************************
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QByteArray>//***********************

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Item;

struct item_data
{
    int type;
    QString path;
};
struct tab_data
{

    QString path;
    Item* item;
};

Q_DECLARE_METATYPE(item_data);
Q_DECLARE_METATYPE(tab_data);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static MainWindow* instance() { return _instance; }
    Scene* scene() { return _scene; }
    QList<Scene*> open_scene(){return open_scenes;}
    ElementShape nextAddedShape() const {return _nextAddedShape; }
    void setNextAddedShape(ElementShape shape) { _nextAddedShape = shape; }
    void Doing(Action* action) { scene()->undoStack.append(action); }
    void Discard(Action* action) { if (scene()->undoStack.last() == action) scene()->undoStack.removeLast(); }
    QMap<int, Node*>* selectedNodes() { return &_selectedNodes; }
    QVector<Text*>* selectedTexts() { return &_selectedTexts; }
    QMap<int, Arrow*>* selectedArrows() { return &_selectedArrows; }
    void addNewTab();
    void addNewTab(QString name);
    int index_tab();
    Graph* graph();
    QVector<QString> getChildrenPaths(QStandardItem* item);


    QColor bdColor = Qt::black;
    QColor fillColor = Qt::white;
    QColor lineColor = Qt::black;
    QColor textColor = Qt::black;
    int lineType = 1;
    QString fontFamily = "宋体";
    int fontSize = 12;
    Graph* cutGraph = new Graph;
    int lineWidth = 2;
    int frameWidth = 2;
    QMap<QModelIndex,Scene* > scenes;
    QMap<QGraphicsScene*, Graph*> graphs;
    Ui::MainWindow *ui;

public:
    Ui::MainWindow* getUi() const;

public slots:
    void Undo();
    void Redo();
    void Cut();
    void Copy();
    void Paste();
    void SelectAll();
    void deleteElement();

    void lineTypeChanged(int index);
    void changeFontFamily(QFont font);
    void changeFontSize(QString sizeString);
    void sizeDialog();
    void ok_sizeBtn_clicked();
    void cancel_sizeBtn_clicked();
    void treeItemChanged(QStandardItem* item);
    void changeFrameWidth(QString widthString);
    void changeLineWidth(QString width);

private slots:
    void textColorChanged();
    void textButtonTriggered();

    void itemColorChanged();
    void fillButtonTriggered();

    void bdColorChanged();
    void bdButtonTriggered();

    void arrowColorChanged();
    void arrowColorButtonTriggered();

    void on_addRectangleButton_clicked();
    void on_addDiamondButton_clicked();
    void on_addArrowButton_clicked();
    void on_addTextButton_clicked();

    void removeSubTab(int index);
    void modifyTabText(QStandardItem* item);
    void modifyChildPath(QStandardItem* item);
    void on_addSubgraghButton_clicked();

    void on_addFatherPortButton_clicked();

    void on_addSonPortButton_clicked();

    void onTreeViewMenuRequested(const QPoint &pos);


    //***************************************
     void on_action1_3_triggered();
     //***************************************
    void on_addInnerInputButton_clicked();

    void on_addInnerOutputButton_clicked();

    void on_addInputButton_clicked();

    void on_addOutputButton_clicked();

    void on_tabWidget_tabCloseRequested(int index);

private:
    void changeFrameColor(QColor color);
    void changeFillColor(QColor color);
    void changeLineColor(QColor color);
    void changeTextColor(QColor color);
    void changeFont(QFont font);
    void clickbdBtn();
    void clickFillBtn();
    void clickLineBtn();
    void clickTextColorButton();
    void addNewTab(QStandardItem* currentItem);
    void checkName(QStandardItem *item, bool showMessage = true);
    void closeItem(Item* item);
    void removeItem(Item* item);
    void saveItem(Item* item);


private:

    int rename_index;

    static MainWindow* _instance;

    Scene* _scene = nullptr;

    QList<Scene*> open_scenes;
    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString &image, QColor color);
    QIcon createColorIcon(QColor color);
    QAction *textAction;
    QAction *fillAction;
    QAction *bdAction;
    QAction *arrowColorAction;
    QFontComboBox* fontBtn;
    QComboBox* fontSizeCombo;
    QComboBox* bdSizeCombo;
    QComboBox* arrowSizeCombo;
    QComboBox* nodeSizeCombo_menu;
    QComboBox* arrowSizeCombo_menu;
    QPushButton* ok_sizeBtn;
    QPushButton* cancel_sizeBtn;
    QDialog *dlg;
    QStandardItemModel* model;

    QToolButton* arrowColorToolBtn;
    QToolButton* bdColorToolBtn;
    QToolButton* fontColorToolBtn;
    QToolButton* fillColorToolBtn;

    ElementShape _nextAddedShape;
    QMap<int, Node*> _selectedNodes;
    QMap<int, Arrow*> _selectedArrows;
    QVector<Text*> _selectedTexts;
    Graph* defaultGraph = new Graph();


    QVector<QPair<int,QString>> index_name_subgraph;
};
#endif // MAINWINDOW_H
