#ifndef ELEMENTEVENTS_H
#define ELEMENTEVENTS_H

#include <QObject>

class ElementEvents : public QObject
{
    Q_OBJECT

public slots:
    static void onSelected(void* element, bool isSelected);
};

#endif // ELEMENTEVENTS_H
