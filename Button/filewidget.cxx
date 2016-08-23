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
    _titleLabel->setFont(QFont("微软雅黑",8));
    _progressBar = new QProgressBar();
    _progressBar->setFixedHeight(5);
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

//    setFixedHeight(65);
}

QPushButton *FileWidget::createButton(QString text, QWidget *parent)
{
    QPushButton *button = new QPushButton(text,parent);

    button->setFlat(true);
    button->setStyleSheet("background: transparent;color: rgb(0, 0, 255);");
    button->setCursor(Qt::PointingHandCursor);
    button->setStyle(QStyleFactory::create("Windows"));
    qDebug() << text.size();
    button->setFixedWidth(text.size()*20);
    return button;
}
