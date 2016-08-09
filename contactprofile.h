#ifndef CONTACTPROFILE_H
#define CONTACTPROFILE_H
#include "baseprofile.h"

class ContactProfile : public BaseProfile
{
public:
    ContactProfile();
    ContactProfile(QString name, QString data, QString ip, QImage head = contactHead);

    QString _ipAddress;

};

#endif // CONTACTPROFILE_H
