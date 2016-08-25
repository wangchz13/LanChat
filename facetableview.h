#ifndef FACETABLEVIEW_H
#define FACETABLEVIEW_H

#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QVector>
#include <QLabel>

class FaceItemDelegate;

class FaceTableView : public QTableView
{
    Q_OBJECT
public:
    FaceTableView(QWidget *parent=0);
    ~FaceTableView(){}

signals:
    void selected(QString image);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void focusOutEvent(QFocusEvent *event);

private:
    FaceItemDelegate *_delegate;
    QStandardItemModel *_model;
    QVector<QMovie *> _movies;
    QVector<QLabel *> _labels;
    QMovie *_currentMovie;
    int _currentMovieIndex;
};

class FaceItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    FaceItemDelegate(QObject *parent=0);
    ~FaceItemDelegate(){}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;


};


#endif // FACETABLEVIEW_H
