#include "contactprofile.h"

ContactProfile::ContactProfile()
{

}

ContactProfile::ContactProfile(QString userName, QString computerName, QString ip, QImage head):
    BaseProfile(userName+"["+computerName+"]", ip, head),
    _userName(userName),
    _computerName(computerName),
    _ipAddress(ip)
{
    _fullName = _userName + "[" + _computerName + "]";
}
