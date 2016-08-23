/****************************
**
** 类名：ContactProfile
** 作用：存储联系人资料
** 成员： _name, _data, _head, _ipAddress
**
**
** ****************************/
#ifndef CONTACTPROFILE_H
#define CONTACTPROFILE_H
#include "baseprofile.h"

class ContactProfile : public BaseProfile
{
public:
    ContactProfile();
    ContactProfile(QString userName, QString computerName, QString ip, QImage head = contactHead);

    //TODO:在流操作中不要忘了父类成员
    friend QDataStream &operator <<(QDataStream &out, const ContactProfile &C){
        out << C._userName << C._computerName << C._ipAddress;
        return out;
    }
    friend QDataStream &operator >>(QDataStream &in, ContactProfile &C){
        in >> C._userName >> C._computerName >> C._ipAddress;
        return in;
    }

    QString _userName;
    QString _computerName;
    QString _ipAddress;

};

#endif // CONTACTPROFILE_H
