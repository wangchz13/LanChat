#ifndef CONTACT_H
#define CONTACT_H

#include "baseprofile.h"

#include <QImage>
#include "global.h"

class Contact : BaseProfile
{
public:
    Contact();
    Contact(QString name, QString data, QImage head);
};

#endif // CONTACT_H
