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

    QString getIP();
    QString getUserName();
    qint16 port=45454;
signals:
    void newBuddy();
    void newMessage();
    void buddyLeft();

public slots:
    void send();

private:
    QByteArray data;
    MessageType _type;
    M_Message _message;
    M_Login _login;
};

#endif // SENDMESSAGE_H
