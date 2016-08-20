#include "groupprofile.h"

GroupProfile::GroupProfile()
{

}

GroupProfile::GroupProfile(QString name, QString data, QString time,QImage head):
    BaseProfile(name, data, head),
    _foundTime(time)
{
    _contactVec.clear();
}
