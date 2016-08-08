#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QWidget>

namespace Ui {
class MainPanel;
}
class MainPanel : public QWidget
{
    Q_OBJECT
signals:

public:
    MainPanel(QWidget *parent = 0);
    ~MainPanel();
public slots:
    void initSlot();

private:
    Ui::MainPanel *ui;
};

#endif // MAINPANEL_H
