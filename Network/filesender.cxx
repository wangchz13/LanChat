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
    _ipAddress = ipAddress;
    _payloadSize = 64*1024;
    _totalBytes = 0;
    _bytesWritten = 0;
    _bytesToWrite = 0;

    _tcpServer = new QTcpServer(this);
    connect(_tcpServer,SIGNAL(newConnection()), this, SLOT(sendFile()));

}

void FileSender::send()
{
    MessageSender request(M_FileRequest(myProfile, _fileName));
    request.send(_ipAddress);
}

void FileSender::updateProgress(qint64 numBytes)
{

}

void FileSender::sendFile()
{
    _clientConnection = _tcpServer->nextPendingConnection();
    connect(_clientConnection, SIGNAL(bytesWritten(qint64)), this, SLOT(updateProgress(qint64)));
    _localFile = new QFile(_filePath);
    if(!_localFile->open(QFile::ReadOnly)){
        //TODO:emit something
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
}
