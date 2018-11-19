#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <qpalette.h>
#include <QTimer>
#include <QString>
#include <string>
#include <QLocale>

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
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateLcd()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::on_startButton_clicked()
{

    min = 0;
    sec = 1;
    timer->start(1000);

}

void MainWindow::updateLcd()
{
    ui->lcdNumberSec->display(sec);
    ui->lcdNumberMin->display(min);
    sec += 1;
    if (sec == 60)
    {
        min += 1;
        sec = 0;
    }
}


void MainWindow::on_resetButton_clicked()
{

    min = 0;
    sec = 0;
    ui->lcdNumberSec->display(sec);
    ui->lcdNumberMin->display(min);
    timer->stop();
}
