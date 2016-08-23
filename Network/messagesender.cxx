#include "messagesender.h"
#include <QUdpSocket>
#include <QDataStream>

#include <QDebug>
using namespace DataProcess;
MessageSender::MessageSender(QObject *parent) : QObject(parent)
{

}

MessageSender::MessageSender(M_Login login)
{
    _type = MessageType::login;
    QDataStream out(&_data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_6);
    out << (qint8)_type;
    out << login;
}

MessageSender::MessageSender(M_File request, MessageType type)
{
    _type = type;
    QDataStream out(&_data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_6);
    out << (qint8)_type;
    out << request;
}

MessageSender::MessageSender(M_Message message)
{
    _type = MessageType::message;
    QDataStream out(&_data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_6);
    out << (qint8)_type;
    out << message;
}


void MessageSender::send(QHostAddress ip)
{
    QUdpSocket socket;
    socket.writeDatagram(_data.data(), _data.size(), ip, port);
}
