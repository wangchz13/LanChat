#ifndef BASEPROFILE_H
#define BASEPROFILE_H
#include "global.h"
#include <QImage>

class BaseProfile
{
public:
    BaseProfile();
    BaseProfile(QString name, QString data, QImage head = contactHead)
        :_name(name),_data(data),_head(head){}

    QString _name;
    QString _data;
    QImage _head;
};

#endif // BASEPROFILE_H
