/************************************************
**
** 类名：BaseButton
** 父类：QPushButton
** 作用：作为所有button的抽象基类，提供标题，头像，消息预览（或备注）等基础数据成员，以及设置Layout
**
** **********************************************/
#ifndef BASEBUTTON_H
#define BASEBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QPixmap>
#include <QImage>
#include "global.h"
class BaseButton : public QPushButton
{
    Q_OBJECT
public:
    explicit BaseButton(QPushButton *parent = 0);
    BaseButton(QString title, QString data, QImage head =defaultHead);
    virtual ~BaseButton();

    virtual void mouseDoubleClickEvent(QMouseEvent *e)=0;
    virtual void mouseReleaseEvent(QMouseEvent *e)=0;

    bool operator ==(const BaseButton &rhs){
        return this->_title == rhs._title;
    }

signals:

public slots:

public:
    QString _title;
    QString _data;
    QImage _head;

    QLabel *_titleLabel;
    QLabel *_dataLabel;
    QLabel *_headLabel;

    QHBoxLayout *_titleHLayout;//标题横向布局
    QHBoxLayout *_dataHLayout;//内容横向布局
    QVBoxLayout *_combineVLayout;//合并的竖布局
    QHBoxLayout *_mainHLayout;//主布局
};

#endif // BASEBUTTON_H
