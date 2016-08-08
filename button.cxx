#include "button.h"
#include <QDateTime>
Button::Button(QWidget *parent) :
    QPushButton(parent)
{

}

Button::Button(QPixmap *head, QString title, QString *preview, QString time, QWidget *parent)
    :m_head(head), m_title(title), m_preview(preview), m_time(time), m_parent(parent), QPushButton(parent)
{
    setWindowTitle(tr("MessageButton"));
    setParent(parent, Qt::FramelessWindowHint);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setFixedHeight(60);
    setCheckable(true);

//    QAction *quitAction = new QAction(tr("E&xit"), this);
//    quitAction->setShortcut(tr("Ctrl+Q"));
//    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
//    addAction(quitAction);


    QLabel *m_firstLabel = new QLabel;
    m_firstLabel->resize(m_head->width(), m_head->height());
    m_firstLabel->setPixmap(*m_head);
    int side = qMin(m_firstLabel->width(), m_firstLabel->height());
    QRegion maskedRegion(m_firstLabel->width() / 2 - side / 2, m_firstLabel->height() / 2 - side / 2, side,
                         side, QRegion::Ellipse);
    m_firstLabel->setMask(maskedRegion);

    QLabel *m_titleLabel = new QLabel(m_title);
    m_titleLabel->setObjectName(tr("titleLabel"));
    QLabel *m_previewLabel = new QLabel(*m_preview);
    m_previewLabel->setObjectName("previewLabel");

    QLabel *m_timeLabel = new QLabel(m_time);
    m_timeLabel->setObjectName("timeLabel");
    m_counterLabel = new QLabel;
    m_counterLabel->setObjectName("countLabel");
    m_counterLabel->setText("5");

    QHBoxLayout *m_tHLayout = new QHBoxLayout;
    m_tHLayout->addWidget(m_titleLabel);
    m_tHLayout->addStretch();
    m_tHLayout->addWidget(m_timeLabel);

    QHBoxLayout *m_bHLayout = new QHBoxLayout;
    m_bHLayout->addWidget(m_previewLabel);
    m_bHLayout->addStretch();
    m_bHLayout->addWidget(m_counterLabel);

    QVBoxLayout *m_secondVLayout = new QVBoxLayout;
    m_secondVLayout->addLayout(m_tHLayout);
    m_secondVLayout->addLayout(m_bHLayout);

    QHBoxLayout *m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addWidget(m_firstLabel);
    m_mainLayout->addSpacing(5);
    m_mainLayout->addLayout(m_secondVLayout);
}

Button::~Button()
{

}

void Button::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_msgNumber = 0;
    hideCount();
}

void Button::hideCount()
{
    m_counterLabel->hide();
}

void Button::newMessageComing()
{
    if(m_msgNumber == 0)
        m_counterLabel->show();
    m_msgNumber++;
    if(m_msgNumber < 99)
        m_counterLabel->setText(QString::number(m_msgNumber, 10));
    else
        m_counterLabel->setText("99+");
}
