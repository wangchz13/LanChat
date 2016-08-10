#include "messagebutton.h"
//#include "chatform.h"

//#include <QTime>
//#include <QPainter>
//#include <QPen>
//#include <QBrush>
//#include <QPalette>
//#include <QtWidgets>
//#include <QPixmap>

//MessageButton::MessageButton()
//{

//}

//MessageButton::MessageButton(QString title, QString context, QString time, QPixmap *head, QWidget *parent)
//    : _title(title), _context(context), _time(time),  _parent(parent)
//{
//    if(head)
//        _head = head;
//    initMessageButton();
//}

////MessageButton::MessageButton(QString userName, QString computerName, QString ipAddress)
////    :_title(userName + "-" + computerName), _context(ipAddress)
////{

////}

//MessageButton::~MessageButton()
//{
//    delete _head;

//    delete _firstLabel;
//    delete _titleLabel;
//    delete _previewLabel;
//    delete _timeLabel;
//    delete _counterLabel;

//    delete _tHLayout;
//    delete _bHLayout;
//    delete _secondVLayout;
//    delete _mainLayout;
//}

//void MessageButton::mouseDoubleClickEvent(QMouseEvent *event)
//{
//    ChatForm *chat = new ChatForm(_title, _context, _head);
//    chat->show();
//    _msgNumber = 0;
//    hideCounter();
//}

//void MessageButton::mouseReleaseEvent(QMouseEvent *event)
//{

//}

//void MessageButton::setMenu(QMenu *menu)
//{

//}

//void MessageButton::initMessageButton()
//{
//    setWindowTitle(tr("MessageButton"));
//    setParent(0, Qt::FramelessWindowHint);
//    setContextMenuPolicy(Qt::ActionsContextMenu);
//    setFixedHeight(60);
//    setCheckable(true);

//    QAction *quitAction = new QAction(tr("E&xit"), this);
//    quitAction->setShortcut(tr("Ctrl+Q"));
//    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
//    addAction(quitAction);


//    _firstLabel = new QLabel;
//    if(_head){//有头像
//        _firstLabel->resize(_head->width(), _head->height());
//        _firstLabel->setPixmap(*_head);
//        int side = qMin(_firstLabel->width(), _firstLabel->height());
//        QRegion maskedRegion(_firstLabel->width() / 2 - side / 2, _firstLabel->height() / 2 - side / 2, side, side, QRegion::Ellipse);
//        _firstLabel->setMask(maskedRegion);
//    }

//    _titleLabel = new QLabel(_title);
//    _titleLabel->setObjectName(tr("titleLabel"));
//    _previewLabel = new QLabel(_context);
//    _previewLabel->setObjectName("previewLabel");

//    _timeLabel = new QLabel(_time);
//    _timeLabel->setObjectName("timeLabel");
//    _counterLabel = new QLabel;
//    _counterLabel->setObjectName("countLabel");

//    _tHLayout = new QHBoxLayout;
//    _tHLayout->addWidget(_titleLabel);
//    _tHLayout->addStretch();
//    _tHLayout->addWidget(_timeLabel);

//    _bHLayout = new QHBoxLayout;
//    _bHLayout->addWidget(_previewLabel);
//    _bHLayout->addStretch();
//    _bHLayout->addWidget(_counterLabel);

//    _secondVLayout = new QVBoxLayout;
//    _secondVLayout->addLayout(_tHLayout);
//    _secondVLayout->addLayout(_bHLayout);

//    _mainLayout = new QHBoxLayout(this);
//    _mainLayout->addWidget(_firstLabel);
//    _mainLayout->addSpacing(5);
//    _mainLayout->addLayout(_secondVLayout);
//}


//void MessageButton::hideCounter()
//{
//    _counterLabel->hide();
//}
////新消息，注意调用此槽前m_preview已刷新
//void MessageButton::newMessageComing()
//{
//    _counterLabel->show();
//    _msgNumber++;
//    qDebug() << _msgNumber << "end";
//    if(_msgNumber < 99)
//        _counterLabel->setText(QString::number(_msgNumber, 10));
//    else
//        _counterLabel->setText("99+");
//    _previewLabel->setText(_context);
//    qDebug() << _context;
//}


MessageButton::MessageButton(QString title, QString data, QString time, QImage head):
    BaseButton(title, data, head),
    _time(time),
    _count(0)
{
    //调用者应该有一句MessageButton.profile = new contact...

    _timeLabel = new QLabel(_time);
    _countLabel = new QLabel;

    _titleHLayout->addStretch();
    _titleHLayout->addWidget(_timeLabel);

    _dataHLayout->addStretch();
    _dataHLayout->addWidget(_countLabel);
}

void MessageButton::refresh()
{
    _countLabel->show();
    _count++;
    if(_count < 99)
        _countLabel->setText(QString::number(_count, 10));
    else
        _countLabel->setText("99+");
    _dataLabel->setText(_data);
}
