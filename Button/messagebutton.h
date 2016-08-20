﻿/**************************
**
** 类名：MessageButton
** 父类：BaseButton
** 目的：显示消息，包括群消息和个人消息
**
***************************/
#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include "Button/basebutton.h"
#include "Profile/baseprofile.h"

class MessageButton : public BaseButton
{
public:
    MessageButton(QString title, QString data, QString time, QImage head = defaultHead);
    virtual void mouseDoubleClickEvent(QMouseEvent *e){}
    virtual void mouseReleaseEvent(QMouseEvent *e){}
public slots:
    void refresh();
public:
    QString _time;
    quint16 _count;

    QLabel *_timeLabel;
    QLabel *_countLabel;
    BaseProfile *_profile;
};

#endif // MESSAGEBOX_H