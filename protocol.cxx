#include "protocol.h"

#include <QtNetwork>
#include <QDesktopServices>

QString DataProcess::toMD5(QString &pwd){
    QString md5;
    md5 = QCryptographicHash::hash(pwd.toLocal8Bit(), QCryptographicHash::Md5).toHex();
    return md5;
}
QString DataProcess::creatKey(){
    QString key;
    qint64 t = QDateTime::currentMSecsSinceEpoch();
    key = QString::number(t,10) + QString().sprintf("%d", &t);
    return key;
}
int DataProcess::checkLoginInfo(QString uid, QString pwd){
    if(uid.isEmpty())
        return 1;
    if(pwd.isEmpty())
        return 2;
    QRegExp rx("^[a-z0-9_-]{3,16}$");
    if(!rx.exactMatch(uid))
        return 3;
    if(!rx.exactMatch(pwd))
        return 4;
    return 0;
}

QString getComputerName()
{
    return QHostInfo::localHostName();
}

QString getUserName()
{
    QString name = "我的电脑";
    return name;
}

QString getIp()
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the fiirst non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).toString().contains("192.168.1")) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    qDebug() << ipAddress;
    return ipAddress;
}

