#include "Network/filereceiver.h"

#include <QDataStream>

FileReceiver::FileReceiver(QObject *parent) : QObject(parent)
{

}

FileReceiver::FileReceiver(QHostAddress serverIp, QString savePath)
{
    _totalBytes = 0;
    _bytesReceived = 0;
    _fileNameSize = 0;
    _hostAddress = serverIp;
    _tcpClient = new QTcpSocket(this);
    _tcpPort = 6666;
    _fileName = savePath;
    connect(_tcpClient, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));
}

void FileReceiver::receive()
{
    _blockSize = 0;
    _tcpClient->abort();
    _tcpClient->connectToHost(_hostAddress, _tcpPort);
    _time.start();
}

void FileReceiver::newConnect()
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
    float useTime = _time.elapsed();

    if(_bytesReceived <= sizeof(qint64)*2){
        if(_tcpClient->bytesAvailable()>=sizeof(qint64)*2 && _fileNameSize ==0){
            in >> _totalBytes >> _fileNameSize;
            _bytesReceived += sizeof(qint64)*2;
        }
        if(_tcpClient->bytesAvailable() >= _fileNameSize && _fileNameSize != 0){
            in >> _fileName;
            _bytesReceived += _fileNameSize;
            if(!_localFile->open(QFile::WriteOnly)){
                qDebug() << "无法读取文件" << endl;
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
        double speed = _bytesReceived / useTime;

        if(_bytesReceived == _totalBytes){
            _localFile->close();
            _tcpClient->close();
            qDebug() << "文件接收完毕";
        }
    }

}

void FileReceiver::setFileName(QString fileName)
{
    _localFile = new QFile(fileName);
}
