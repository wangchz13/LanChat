#include "receivemessage.h"
#include "protocol.h"

#include <QDataStream>
#include <QByteArray>

MessageReceiver::MessageReceiver(QObject *parent) : QObject(parent)
{
    rcvSocket = new QUdpSocket(this);
    rcvSocket->bind(45454,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
}

void MessageReceiver::readyReadSlot()
{
    qDebug() << "new message coming!";
    rcvBuffer.resize(rcvSocket->pendingDatagramSize());
    rcvSocket->readDatagram(rcvBuffer.data(), rcvBuffer.size());
    QDataStream in(&rcvBuffer, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_6);
    MessageType type;
    qint8 temp;
    in >> temp;
    type = (MessageType)temp;
    switch (type) {
    case MessageType::Login:
        {
            M_Login login;
            in >> login;
            emit newBuddy(login);
            qDebug() << login._userName;
        }
        break;
    case MessageType::Message:
        {
            M_Message msg;
            in >> msg;
            emit newMessage(msg);
        }
        break;
    default:
        break;
    }

}

void MessageReceiver::msgReturn()
{


}

void MessageReceiver::listen()
{
    connect(rcvSocket, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));
}
