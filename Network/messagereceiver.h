#ifndef RECEIVEMESSAGE_H
#define RECEIVEMESSAGE_H

#include <QObject>
#include <QUdpSocket>

#include "protocol.h"

class MessageReceiver : public QObject
{
    Q_OBJECT
public:
    explicit MessageReceiver(QObject *parent = 0);

signals:
    void loginReturn(M_FeedBack fb);
    void newMessage(M_Message msg);
    void newBuddy(M_Login login);
    void fileRequest(M_File request);
    void fileRefused(M_File refuse);
    void fileReceive(M_File receive);

public slots:
    void readyReadSlot();

    void listen();

    void msgReturn();

private:
    QByteArray rcvBuffer;
    QUdpSocket *rcvSocket;
};

#endif // RECEIVEMESSAGE_H
