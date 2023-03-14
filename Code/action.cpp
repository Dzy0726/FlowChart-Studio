#include "action.h"
#include "mainwindow.h"


Action::Action()
{
    MainWindow::instance()->Doing(this);
}

Action::~Action()
{
    MainWindow::instance()->Discard(this);
}
