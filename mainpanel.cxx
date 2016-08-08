#include "mainpanel.h"
#include "ui_mainpanel.h"

MainPanel::MainPanel(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::MainPanel)
{

}

MainPanel::~MainPanel()
{

}

void MainPanel::initSlot()
{
    show();

}
