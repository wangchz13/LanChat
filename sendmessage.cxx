#include "sendmessage.h"
#include <QUdpSocket>

#include <QDebug>
using namespace DataProcess;
MessageSender::MessageSender(QObject *parent) : QObject(parent)
{

}

MessageSender::MessageSender(M_Login login)
    : _login(login)
{
    _type = MessageType::login;
}

MessageSender::MessageSender(M_Message message)
    : _message(message)
{
    _type = MessageType::message;
}


void MessageSender::send()
{
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_6);
    out  << (qint8)_type;
    switch (_type) {
    case MessageType::login:
        out << _login;
    case MessageType::message:
        out << _message;
    default:
        break;
    }

    QUdpSocket socket;
    socket.writeDatagram(data.data(), data.size(), QHostAddress::Broadcast, port);
}
