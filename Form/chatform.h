﻿/*******************************************
**
** 类名：ChatForm
** 父类：QWidget
** 作用：聊天界面，包括
**
** ****************************************/
#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>
#include <QVector>
#include <QImage>

#include "global.h"
#include "protocol.h"

class QLabel;
class QVBoxLayout;
class QTextBrowser;

namespace Ui {
class ChatForm;
}

class ChatForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatForm(QWidget *parent = 0);
    ChatForm(QString title, QString context, QImage head, ProfileType type, QWidget *parent=0);
    ~ChatForm();
    void initForm();

    operator ==(const ChatForm &rhs){
        return this->_title == rhs._title && this->_type == rhs._type;
    }

    void newMessageComing(M_Message msg);
private slots:
    void on_sendMsgButton_clicked();

private:
    Ui::ChatForm *ui;

    QString _title;
    QString _data;
    QImage _head;

    ProfileType _type;
};

#endif // CHATFORM_H