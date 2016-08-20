#ifndef CONTACTPROFILE_H
#define CONTACTPROFILE_H
#include "baseprofile.h"

class ContactProfile : public BaseProfile
{
public:
    ContactProfile();
    ContactProfile(QString userName, QString computerName, QString ip, QImage head = contactHead);

    QString _ipAddress;

};

#endif // CONTACTPROFILE_H
