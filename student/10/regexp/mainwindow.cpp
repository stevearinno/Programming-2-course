#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QRegExp>
#include <iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_returnPressed()
{

    QString fullIsbn = ui->lineEdit->text();
    int size = fullIsbn.size();
    QString output = "No match";

//    qDebug() << fullIsbn;

    QRegExp rx("^[01]+[-]+(\\d{2,7})+[-]+(\\d{1,6})+[-]+[\\d|X|x]$");

    if ((rx.indexIn(fullIsbn) != -1) && (size == 13))
    {
        fullIsbn.replace("-", "");
        int sumDigits = 0;
        int i = 0;
        while (i < 9)
        {
            sumDigits += (fullIsbn.mid(i,1).toInt() * (10 - i));
            i++;
        }
        QString lastDigit = fullIsbn.mid(9,1);
        int lastNumber = 0;
        if (lastDigit == "X" || lastDigit == "x")
        {
            lastNumber = 10;
        }
        else
        {
            lastNumber = lastDigit.toInt();
        }
        if ((sumDigits + lastNumber)%11 == 0)
        {
            output = "Match";
        }
    }

    ui->textBrowser->setText(output);

}
