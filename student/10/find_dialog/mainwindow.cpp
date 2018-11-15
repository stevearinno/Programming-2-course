#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QString>
#include <fstream>
#include <string>
//#include<bits/stdc++.h>

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

//void MainWindow::on_fileLineEdit_editingFinished()
//{
////    QString inputString = ui->fileLineEdit->text();
////    qDebug() << inputString;
////    ui->textBrowser->setText("not found");

////    QString fileInput = ui->fileLineEdit->text();
////    std::string filename = fileInput.toUtf8().constData();
////    QString output = "";
////    std::ifstream file_object(filename);
////    if ( not file_object )
////    {
////        output = "File not found";
////    }
////    else
////    {
////        output = "File found";
////    }
////    ui->textBrowser->setText(output);

//}


void MainWindow::on_findPushButton_clicked()
{
    QString wordSearch = ui->keyLineEdit->text();
    QString fileInput = ui->fileLineEdit->text();
    std::string keySearch = wordSearch.toUtf8().constData();
    std::string filename = fileInput.toUtf8().constData();
    std::ifstream file_object(filename);
    QString output = "";
    std::string line;

    // if matchCheckBox is unchecked, make the word to search lowercase
    if ( !(ui->matchCheckBox->isChecked()) )
    {
        std::transform(keySearch.begin(), keySearch.end(), keySearch.begin(), ::tolower);
    }

    if ( not file_object )
    {
        output = "File not found";
    }
    else
    {
        if ( keySearch == "" )
        {
            output = "File found";
        }
        else
        {
            while ( getline(file_object, line) )
            {
                if ( !(ui->matchCheckBox->isChecked()) )
                {
                    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
                }

                // if the word is not found
                if( line.find(keySearch) == std::string::npos )
                {
                    output = "Word not found" ;
                }
                else
                {
                    output = "Word found" ;
                    break;
                }
            }
        }
    }

    ui->textBrowser->setText(output);
}
