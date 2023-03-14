#ifndef ACTION_H
#define ACTION_H

#include <QObject>


class Action : public QObject
{
    Q_OBJECT

public:
    Action();
    virtual ~Action();

    virtual void Do() = 0;
    virtual void Undo() = 0;
};

#endif // ACTION_H
