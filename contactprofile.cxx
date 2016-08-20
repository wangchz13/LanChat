#include "contactprofile.h"

ContactProfile::ContactProfile()
{

}

ContactProfile::ContactProfile(QString userName, QString computerName, QString ip, QImage head):
    BaseProfile(userName+"["+computerName+"]", ip, head),
    _ipAddress(ip)
{

}
