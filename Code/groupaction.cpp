#include "groupaction.h"
#include "mainwindow.h"
#include <QDebug>

GroupAction::GroupAction()
{
    qDebug() << "GroupAction" ;
}

GroupAction& GroupAction::operator<<(Action* action)
{
    auto window = MainWindow::instance();
    window->Discard(action);
    actions.append(action);
    return *this;
}

void GroupAction::Do()
{
    foreach (auto action, actions)
    {
        action->Do();
    }
}

void GroupAction::Undo()
{
    for (auto i = actions.size() - 1; i >= 0; i--)
    {
        actions[i]->Undo();
    }
}
