#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <qpalette.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette palGreen = palette();
    QPalette palBlue = palette();
    palGreen.setColor(QPalette::Background, Qt::green);
    palBlue.setColor(QPalette::Background, Qt::blue);
    //ui->lcdNumberMin->setFrameStyle(QFrame::Box | QFrame::Raised);
    ui->lcdNumberSec->setAutoFillBackground(true);
    ui->lcdNumberMin->setAutoFillBackground(true);

    ui->lcdNumberSec->setPalette(palGreen);
    ui->lcdNumberMin->setPalette(palBlue);
    //ui->lcdNumberSec->setPalette(Qt::green);
}

MainWindow::~MainWindow()
{
    delete ui;
}
