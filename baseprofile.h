/*************************************************
 *
 * 类名：BaseProfile
 * 父类：无
 * 作用：作为群资料和个人资料的公共部分，只包含标题（名称）、备注、头像
 *
 * ***********************************************/
#ifndef BASEPROFILE_H
#define BASEPROFILE_H
#include "global.h"
#include <QImage>
#include <QString>

class BaseProfile
{
public:
    BaseProfile();
    BaseProfile(QString name, QString data, QImage head=defaultHead)
        :_name(name),_data(data),_head(head){}

public:
    QString _name;
    QString _data;
    QImage _head;
};

#endif // BASEPROFILE_H
