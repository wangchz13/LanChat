#include "facetableview.h"
#include <QPainter>
#include <QHeaderView>
#include <QScrollBar>
#include <QWidget>
#include <QObject>
#include <QMouseEvent>
#include <QStandardItemModel>
#include <QDebug>
#include <QLabel>
#include <QMovie>

FaceTableView::FaceTableView(QWidget *parent)
    :QTableView(parent)
{
    _model = new QStandardItemModel();
    _model->setColumnCount(14);
    _model->setRowCount(8);
    _currentMovie = NULL;
    _currentMovieIndex = -1;
    setModel(_model);
    setWindowFlags(Qt::FramelessWindowHint);
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    for(int i = 0; i < 14; i++) setColumnWidth(i, 30);
    setLineWidth(60);
    setFixedWidth(430);
    setFixedHeight(181);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

//    _delegate = new FaceItemDelegate();
//    setItemDelegate(_delegate);
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 14; j++){
            QMovie *movie = new QMovie(tr(":/source/faces/classic-24/e%1.gif").arg(QString::number(i * 14 + j+100)));
            connect(movie, SIGNAL(finished()), movie, SLOT(start()));
            _movies.push_back(movie);
            QLabel *label = new QLabel;
            label->setFixedSize(30,30);
            label->setContentsMargins(0,0,0,0);
            label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            label->setPixmap(QPixmap(tr(":/source/faces/classic-24/e%1.png").arg(QString::number(i * 14 + j+100))));
            _labels.push_back(label);
            setIndexWidget(_model->index(i,j), label);
        }
    }

}

void FaceTableView::mouseMoveEvent(QMouseEvent *event)
{
    int column = columnAt(event->x());
    int row = columnAt(event->y());
    qDebug() << row << column;
//    int index = row*14+column;
//    if(index == _currentMovieIndex) return;
//    if(index > 105 || index <= 0) return;
//    if(_currentMovieIndex != -1)
//        _movies[_currentMovieIndex]->stop();
//    _movies[index]->start();
//    _currentMovieIndex = index;
}

void FaceTableView::mouseReleaseEvent(QMouseEvent *event)
{
    int column = currentIndex().column();
    int row = currentIndex().row();
    int index = row * 14 + column;
    QString image = tr(":/source/faces/classic-24/e%1.gif").arg(QString::number(index +100));
    emit selected(image);
    close();
}

void FaceTableView::focusOutEvent(QFocusEvent *event)
{
    close();
}

FaceItemDelegate::FaceItemDelegate(QObject *parent)
    :QItemDelegate(parent)
{

}

void FaceItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


    int column = index.column();
    int row = index.row();
    if(row == 7 && column > 4) return;

    int x = 3 + column * 30;
    int y = 3 + row * 30;

    QString faceImage = tr(":/source/faces/classic-24/e%1.png").arg(QString::number(row * 14 + column+100));
    painter->drawImage(x,y,QImage(faceImage));
}
