#ifndef GROUP_H
#define GROUP_H
#include "global.h"
#include <QImage>

class Group
{
public:
    Group();
    Group(QString name, QString data, QImage head = groupHead);

    QString _groupName;
    QString _data;
    QImage _head;
};

#endif // GROUP_H
