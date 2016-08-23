#ifndef SENDMESSAGE_H
#define SENDMESSAGE_H

#include "protocol.h"
#include <QObject>

class MessageSender : public QObject
{
    Q_OBJECT
public:
    explicit MessageSender(QObject *parent = 0);
    MessageSender(M_Message message);
    MessageSender(M_Login login);

    qint16 port=45454;
signals:
    void newBuddy();
    void newMessage();
    void buddyLeft();

public slots:
    void send(QHostAddress ip=QHostAddress::Broadcast);//默认发送给网关

private:
    QByteArray data;
    MessageType _type;
    M_Message _message;
    M_Login _login;

    QDataStream _buff;
};

#endif // SENDMESSAGE_H
