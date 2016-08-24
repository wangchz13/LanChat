#include "Network/filesender.h"

#include <QDataStream>
#include <QTime>

#include "Network/messagesender.h"

FileSender::FileSender(QObject *parent) : QObject(parent)
{

}

FileSender::FileSender(QString filePath, QHostAddress ipAddress)
{
    _tcpPort = 6666;
    _filePath = filePath;
    _fileName = filePath.right(filePath.size() - filePath.lastIndexOf('/')-1);
    _ipAddress = ipAddress;
    _payloadSize = 64*1024;
    _totalBytes = 0;
    _bytesWritten = 0;
    _bytesToWrite = 0;
    _speed = 0;
    _tcpServer = new QTcpServer(this);
    connect(_tcpServer, SIGNAL(newConnection()), this, SLOT(send()));
}

void FileSender::ready()
{
    if(!_tcpServer->listen(QHostAddress(myIpAddress), _tcpPort)){
        deleteLater();
    }
    MessageSender request(M_File(myProfile, _fileName));
    request.send(_ipAddress);
}

void FileSender::bytesWrittenSlot(qint64 numBytes)
{
    _bytesWritten += numBytes;
    emit updateProgress(_totalBytes, _bytesWritten, _speed);
    if(_bytesToWrite > 0){
        _outBlock = _localFile->read(qMin(_bytesToWrite, _payloadSize));
        _bytesToWrite -= _clientConnection->write(_outBlock);
        _outBlock.resize(0);
        qDebug() << _totalBytes << _bytesWritten;
    }else
        _localFile->close();
    float useTime = _time.elapsed();
    _speed = _bytesWritten / useTime;
    if(_bytesWritten == _totalBytes){
        _localFile->close();
        _tcpServer->close();
        emit succeed(_fileName);
    }
}

void FileSender::send()
{
    _clientConnection = _tcpServer->nextPendingConnection();
    connect(_clientConnection, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWrittenSlot(qint64)));
    _localFile = new QFile(_filePath);
    if(!_localFile->open(QFile::ReadOnly)){
        return;
    }
    _totalBytes = _localFile->size();
    QDataStream sendOut(&_outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_7);
    _time.start();
    QString currentFile = _filePath.right(_filePath.size()
                                          - _filePath.lastIndexOf('/') - 1);
    sendOut << qint64(0) << qint64(0) << currentFile;
    _totalBytes += _outBlock.size();
    sendOut.device()->seek(0);
    sendOut << _totalBytes << qint64(_outBlock.size() - sizeof(qint64)*2);
    _bytesToWrite = _totalBytes - _clientConnection->write(_outBlock);
    _outBlock.resize(0);
}

void FileSender::cancel()
{
    _tcpServer->close();
    deleteLater();
}
