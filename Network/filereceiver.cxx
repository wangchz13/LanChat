#include "Network/filereceiver.h"

#include <QDataStream>

FileReceiver::FileReceiver(QObject *parent) : QObject(parent)
{

}

FileReceiver::FileReceiver(QHostAddress serverIp, QString savePath)
{
    _speed = 0;
    _totalBytes = 0;
    _bytesReceived = 0;
    _fileNameSize = 0;
    _hostAddress = serverIp;
    _tcpPort = 6666;
    _localFile = new QFile(savePath);

    _tcpClient = new QTcpSocket(this);
    connect(_tcpClient, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));
}

void FileReceiver::receive()
{
    _blockSize = 0;
    _tcpClient->abort();
    _tcpClient->connectToHost(_hostAddress, _tcpPort);
    _time.start();
}

void FileReceiver::readyReadSlot()
{
    QDataStream in(_tcpClient);
    in.setVersion(QDataStream::Qt_5_7);


    if(_bytesReceived <= sizeof(qint64)*2){
        if(_tcpClient->bytesAvailable()>=sizeof(qint64)*2 && _fileNameSize ==0){
            in >> _totalBytes >> _fileNameSize;
            _bytesReceived += sizeof(qint64)*2;
        }
        if(_tcpClient->bytesAvailable() >= _fileNameSize && _fileNameSize != 0){
            in >> _fileName;
            _bytesReceived += _fileNameSize;
            if(!_localFile->open(QFile::WriteOnly)){
                return;
            }
        }else
            return;
    }
    if(_bytesReceived < _totalBytes){
        _bytesReceived += _tcpClient->bytesAvailable();
        _inBlock = _tcpClient->readAll();
        _localFile->write(_inBlock);
        _inBlock.resize(0);
        qDebug() << "总共：" << _totalBytes << " " << "已接受：" << _bytesReceived;

    }
    float useTime = _time.elapsed();
    _speed = _bytesReceived / useTime;
    emit updateProgress(_totalBytes, _bytesReceived, _speed);
    if(_bytesReceived == _totalBytes){
        _localFile->close();
        _tcpClient->close();
        emit succeed(_fileName);
    }
}

void FileReceiver::setFileName(QString fileName)
{
    _localFile = new QFile(fileName);
}
