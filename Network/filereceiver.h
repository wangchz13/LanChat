#ifndef FILERECEIVER_H
#define FILERECEIVER_H

#include <QObject>
#include <QHostAddress>
#include <QFile>
#include <QTime>
#include <QTcpSocket>

class FileReceiver : public QObject
{
    Q_OBJECT
public:
    explicit FileReceiver(QObject *parent = 0);
    FileReceiver(QHostAddress serverIp, QString savePath);

signals:

public slots:
    void receive();

    void setFileName(QString fileName);

private slots:
    void readyReadSlot();
private:
    QTcpSocket *_tcpClient;
    quint16 _blockSize;
    QHostAddress _hostAddress;
    qint16 _tcpPort;

    qint64 _totalBytes;
    qint64 _bytesReceived;
    qint64 _bytesToReceive;
    qint64 _fileNameSize;
    QString _fileName;
    QFile *_localFile;
    QByteArray _inBlock;

    QTime _time;
};

#endif // FILERECEIVER_H
