#include "widget.h"
#include "./ui_widget.h"
#include <QTabBar>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->hide();
}

Widget::~Widget()
{
    delete ui;
}
