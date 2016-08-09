﻿#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QDataStream>
#include <QString>
#include <QDateTime>
#include <QCryptographicHash>
#include <QHostAddress>

#include "contact.h"
namespace DataProcess {
    QString toMD5(QString &pwd);
    QString creatKey();
    int checkLoginInfo(QString uid, QString pwd);
}

QString getUserName();
QString getComputerName();
QString getIp();

enum MessageType {login,message,myStateChange,contactStateChange,feedBack};
enum StateType {onLine,busy,offLine};
enum ProfileType {contact,group};

class M_Login{
public:
    M_Login(){}
    M_Login(QString userName, QString computerName,QString ipAddress)
        :_userName(userName),
        _computerName(computerName),
        _ipAddress(ipAddress){}
    friend QDataStream &operator <<(QDataStream &out, const M_Login &L){
        out << L._userName << L._computerName << L._ipAddress;
        return out;
    }
    friend QDataStream &operator >>(QDataStream &in, M_Login &L){
        L.clear();
        in >> L._userName >> L._computerName >> L._ipAddress;
        return in;
    }
    void clear(){
        _userName.clear();
        _computerName.clear();
        _ipAddress.clear();
    }

    QString _userName;
    QString _computerName;
    QString _ipAddress;
};

class M_Message{
public:
    M_Message(){}
    M_Message(QString userName, QString data, QString ipAddress, QString time,ProfileType type,QString key=""):
        _userName(userName), _data(data), _ipAddress(ipAddress), _time(time), _type(type){}
    friend QDataStream &operator <<(QDataStream &out, const M_Message &M){
        out << M._userName << M._data << M._ipAddress << M._time << qint8(M._type);
        return out;
    }
    friend QDataStream &operator >>(QDataStream &in, M_Message &M){
        qint8 t;
        in >> M._userName >> M._data >> M._ipAddress >> M._time >> t;
        M._type = (ProfileType)t;
        return in;
    }

    QString _userName;
    QString _data;
    QString _ipAddress;
    QString _key;

    Contact _sender;
    QString _time;
    ProfileType _type;
};

class M_Mystatechange{
public:
    M_Mystatechange(StateType state, QString key) : _state(state), _key(key){}
    friend QDataStream &operator <<(QDataStream &out, const M_Mystatechange &M){
        out << (qint8)M._state << M._key;
        return out;
    }
    friend QDataStream &operator >>(QDataStream &in, M_Mystatechange &M){
        qint8 temp;
        in >> temp >> M._key;
        M._state = (StateType)temp;
        return in;
    }
private:
    StateType _state;
    QString _key;
};

class M_BuddyStateChange{
public:
    M_BuddyStateChange(QString bid, StateType state, QString key)
        : _bid(bid), _state(state), _key(key){}
    friend QDataStream &operator <<(QDataStream &out, const M_BuddyStateChange &B){
        out << B._bid << (qint8)B._state << B._key;
        return out;
    }
    friend QDataStream &operator >>(QDataStream &in, M_BuddyStateChange &B){
        in >>  B._bid;
        qint8 temp;
        in >> temp >> B._key;
        B._state = (StateType)temp;
        return in;
    }
private:
    QString _bid;
    StateType _state;
    QString _key;
};

class M_FeedBack{
public:
    M_FeedBack(int feed, QString key) : _feed(feed), _key(key){}
    M_FeedBack(){}
    friend QDataStream &operator <<(QDataStream &out, const M_FeedBack &F){
        out << F._feed << F._key;
        return out;
    }
    friend QDataStream &operator >>(QDataStream &in, M_FeedBack &F){
        in >> F._feed >> F._key;
        return in;
    }
    qint8 getFeed() const{
        return _feed;
    }
    QString getKey() const{
        return _key;
    }
private:
    qint8 _feed;
    QString _key;
};


#endif // PROTOCOL_H
