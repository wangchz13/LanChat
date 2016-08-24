#ifndef FILEBUTTON_H
#define FILEBUTTON_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>

#include "protocol.h"

class FileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileWidget(QWidget *parent = 0);
    FileWidget(QString fileName, FileWidgetType type, QWidget *parent=0);

    QPushButton *createButton(QString text, QWidget *parent = 0);

    QString updateInfo(QString info);
signals:

public slots:
    void updateProgressSlot(qint64 totalBytes, qint64 bytesWritten, float speed);
    void succeedSlot(QString fileName);
private:
    QString _title;
    QString _info;

    QLabel *_titleLabel;
    QProgressBar *_progressBar;
    QLabel *_infoLabel;
    QPushButton *_cancelBtn;
    QVBoxLayout *_mainVLayout;
    QHBoxLayout *_bottomHLayout;
};

#endif // FILEBUTTON_H
