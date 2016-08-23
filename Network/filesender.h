#ifndef FILESENDER_H
#define FILESENDER_H

#include <QObject>
#include <QFile>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>

class FileSender : public QObject
{
    Q_OBJECT
public:
    explicit FileSender(QObject *parent = 0);
    FileSender(QString filePath, QHostAddress ipAddress);
signals:

public slots:
    void ready();
    void updateProgress(qint64 numBytes);

    void cancel();

private slots:
    void send();
private:
    qint16 _tcpPort;
    QTcpServer *_tcpServer;
    QString _filePath;
    QString _fileName;
    QFile *_localFile;

    QHostAddress _ipAddress;

    qint64 _totalBytes;
    qint64 _bytesWritten;
    qint64 _bytesToWrite;
    qint64 _payloadSize;
    QByteArray _outBlock;

    QTcpSocket *_clientConnection;
    QTime _time;
};

#endif // FILESENDER_H
