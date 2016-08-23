#include "groupprofile.h"

GroupProfile::GroupProfile()
{

}

GroupProfile::GroupProfile(QString groupName, QString groupData, QString foundTime, QImage head):
    BaseProfile(groupName, groupData, head),
    _foundTime(foundTime)
{

}
