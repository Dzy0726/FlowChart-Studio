#include <QModelIndex>
#include "item.h"
#include "scene.h"
#include "saver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include <QByteArray>
#include <QDebug>
#include <QVariant>
#include<QApplication>
void Saver::AddNewProject(const QString& path)
{

}

void Saver::AddNewFile(const QString& path)
{

}

void Saver::Save(Item* item)
{
    auto index = item->index();
    auto path = item->path();
    auto type = item->itemType();
    if (type == ItemType::File)
    {
        auto graph = item->graph();

        QJsonObject qso;
        QJsonObject gqso;
        gqso.insert("FilePath",path);
        gqso.insert("Name",item->name());
        gqso.insert("Graph",QJsonValue(graph->get_JsonObject()));
        qso.insert("Flie",gqso);

        QJsonDocument doc;
        doc.setObject(qso);
        QFile file(item->path());
        qDebug() << path;
        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug() << "File open failed!";
        }
        else
        {
            qDebug() <<"File open successfully!";
        }
             file.write(doc.toJson(QJsonDocument::Indented));
             file.close();
    }
    else if (type == ItemType::Project)
    {
        auto name = item->name();

        QJsonObject qso;
        QJsonArray FileArray;
        QJsonArray grapharray;
        QJsonObject gqso;
        QJsonObject cgqso;

        gqso.insert("Name",name);
        gqso.insert("Path",path);
        cgqso.insert("GraphId",item->graph()->GetID());
       // cgqso.insert("GraphName",item->graph()->);
        grapharray.append(cgqso);
        gqso.insert("graph",QJsonValue(grapharray));
        FileArray.append(gqso);
        qso.insert("Project",QJsonValue(FileArray));

        QJsonDocument doc;
        doc.setObject(qso);
        QFile file(path);
        qDebug() << path;
        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug() << "File open failed!";
        }
        else
        {
            qDebug() <<"File open successfully!";
        }
             file.write(doc.toJson(QJsonDocument::Indented));
             file.close();
    }
}

void Saver::SaveAs(Item* item, const QString& path)
{

}

Item* Saver::Open(const QString& path)
{
    Item* item;
    if (path.endsWith(".pr"))
    {
        item = new Item(ItemType::Project, path);
    }
    else if (path.endsWith(".gr"))
    {
        item = new Item(ItemType::File, path);
    }
    return item;
}

void Saver::Rename(const QString& oldPath, const QString& newName)
{

}
