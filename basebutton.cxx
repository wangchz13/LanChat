#include "basebutton.h"

BaseButton::BaseButton(QPushButton *parent) : QPushButton(parent)
{

}

BaseButton::BaseButton(QString title, QString data, QImage head):
    _title(title),
    _data(data),
    _head(head)
{
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setCheckable(true);
    setFixedHeight(60);

    _titleLabel = new QLabel(_title);//设置标题
    _titleLabel->setObjectName(tr("titleLabel"));
    _dataLabel = new QLabel(_data);//设置数据
    _titleLabel->setObjectName(tr("dataLabel"));
    _headLabel = new QLabel;//设置头像
    _headLabel->setFixedSize(40, 40);
    _headLabel->setPixmap(QPixmap::fromImage(_head));

    _titleHLayout = new QHBoxLayout;
    _titleHLayout->addWidget(_titleLabel);//没必要加弹簧，后代会加上
    _dataHLayout = new QHBoxLayout;
    _dataHLayout->addWidget(_dataLabel);

    _combineVLayout = new QVBoxLayout;
    _combineVLayout->addLayout(_titleHLayout);
    _combineVLayout->addLayout(_dataHLayout);

    _mainHLayout = new QHBoxLayout(this);
    _mainHLayout->addWidget(_headLabel);
    _mainHLayout->addSpacing(5);
    _mainHLayout->addLayout(_combineVLayout);
}

BaseButton::~BaseButton()
{
    delete _headLabel;
    delete _titleLabel;
    delete _dataLabel;
}
