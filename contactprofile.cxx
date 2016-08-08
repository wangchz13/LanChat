#include "contactprofile.h"

ContactProfile::ContactProfile()
{

}

ContactProfile::ContactProfile(QString name, QString data, QString ip,QImage head):
    BaseProfile(name, data, head),
    _ipAddress(ip)
{

}
