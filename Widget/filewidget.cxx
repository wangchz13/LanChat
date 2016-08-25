#include "filewidget.h"

#include <QStyleFactory>

FileWidget::FileWidget(QWidget *parent) : QWidget(parent)
{

}

FileWidget::FileWidget(QString fileName, FileWidgetType type, QWidget *parent):
    QWidget(parent)
{
    _title = fileName;
    _titleLabel = new QLabel(_title);
    _titleLabel->setFont(QFont("微软雅黑",9));
    _progressBar = new QProgressBar();
    _progressBar->setFixedHeight(10);
    _infoLabel = new QLabel("info");

    _bottomHLayout = new QHBoxLayout;
    _bottomHLayout->addWidget(_infoLabel);
    _bottomHLayout->addStretch();

    _cancelBtn = createButton("取消");
    _bottomHLayout->addWidget(_cancelBtn);
    _mainVLayout = new QVBoxLayout(this);
    _mainVLayout->addWidget(_titleLabel);
    _mainVLayout->addWidget(_progressBar);
    _mainVLayout->addLayout(_bottomHLayout);

    if(type == FileWidgetType::sender)
        _infoLabel->setText("等待对方接收...");
    else
        _infoLabel->setText("正在接收...");

//    setFixedHeight(65);
}

QPushButton *FileWidget::createButton(QString text, QWidget *parent)
{
    QPushButton *button = new QPushButton(text,parent);

    button->setFlat(true);
    button->setStyleSheet("background: transparent;color: rgb(0, 0, 255);");
    button->setCursor(Qt::PointingHandCursor);
    button->setStyle(QStyleFactory::create("Windows"));
    button->setFixedWidth(text.size()*20);
    return button;
}

QString FileWidget::updateInfo(QString info)
{
    _infoLabel->setText(info);
}


void FileWidget::updateProgressSlot(qint64 totalBytes, qint64 bytesWritten, float speed)
{
    _progressBar->setMaximum(totalBytes);
    _progressBar->setValue(bytesWritten);
    _infoLabel->setText(tr("%1 MB/s").arg(speed*1000/(1024*1024),0,'f',2));
}

void FileWidget::succeedSlot(QString fileName)
{
    deleteLater();
}
