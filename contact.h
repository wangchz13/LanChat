#ifndef CONTACT_H
#define CONTACT_H
#include "global.h"
#include <QImage>

class Contact
{
public:
    Contact();
    Contact(QString name, QString data, QImage head = contactHead);
    QString _name;
    QString _data;
    QImage _head;
};

#endif // CONTACT_H
