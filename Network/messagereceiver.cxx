#include "messagereceiver.h"
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
    qint8 temp;
    in >> temp;
    MessageType type = (MessageType)temp;
    switch (type) {
    case MessageType::login:
        {
            M_Login login;
            in >> login;
            emit newBuddy(login);
            qDebug() << login._userName;
        }
        break;
    case MessageType::message:
        {
            M_Message msg;
            in >> msg;
            emit newMessage(msg);
        }
        break;
    case MessageType::fileRequest:
        {
            M_File request;
            in >> request;
            emit fileRequest(request);
        }
        break;
    case MessageType::refuseFile:
        {
            M_File refuse;
            in >> refuse;
            emit fileRefused(refuse);
        }
        break;
    case MessageType::receiveFile:
        {
            M_File receive;
            in >> receive;
            emit fileReceive(receive);
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
