#ifndef GROUPPROFILE_H
#define GROUPPROFILE_H
#include "baseprofile.h"

#include <QVector>
#include "contactprofile.h"

class GroupProfile : public BaseProfile
{
public:
    GroupProfile();
    GroupProfile(QString groupName, QString groupData, QString foundTime, QImage head = groupHead);

    QString _foundTime;

};

#endif // GROUPPROFILE_H
