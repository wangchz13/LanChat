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
    MessageSender(M_FileRequest request, MessageType type = MessageType::fileRequest);

    qint16 port=45454;
signals:
    void newBuddy();
    void newMessage();
    void buddyLeft();

public slots:
    void send(QHostAddress ip=QHostAddress::Broadcast);//默认发送给网关

private:
    QByteArray _data;
    MessageType _type;
};

#endif // SENDMESSAGE_H
