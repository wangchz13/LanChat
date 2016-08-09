#ifndef CONTACT_H
#define CONTACT_H

#include "baseprofile.h"

#include <QImage>
#include "global.h"

class Contact : public BaseProfile
{
public:
    Contact();
    Contact(QString name, QString data, QImage head=contactHead);
};

#endif // CONTACT_H
