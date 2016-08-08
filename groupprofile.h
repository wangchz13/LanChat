#ifndef GROUPPROFILE_H
#define GROUPPROFILE_H
#include "baseprofile.h"

#include <QVector>
#include "contactprofile.h"

class GroupProfile : BaseProfile
{
public:
    GroupProfile();
    GroupProfile(QString name, QString data, QString time, QImage head = groupHead);

    QString _foundTime;
    QVector<QString> _contactVec;
};

#endif // GROUPPROFILE_H
