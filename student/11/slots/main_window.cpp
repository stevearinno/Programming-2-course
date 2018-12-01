/*
#####################################################################
# TIE-02207 Programming 2: Basics, F2018                            #
# Project4: Slots                                                   #
# Program description: Implements a virtual slots game.             #
# File: main_window.cpp                                             #
# Description: Implements a UI for the game to be playable.         #
# Notes: * This is an exercise program.                             #
#        * Students need to modify this file.                       #
#####################################################################
*/

#include "main_window.hh"
#include <QPixmap>
#include <QString>
#include <chrono>
#include <map>
#include <memory>
#include <random>
#include <utility>
#include <iostream>
#include <QDebug>
#include <QTimer>
#include <QPalette>


// To avoid polluting the global namespace with all kinds of
// names, free functions and global variables / constants are
// usually placed inside a namespace. As we don't have a named
// namespace here, we'll use the anonymous namespace instead.
namespace {

/// \brief Get the fruit symbols and their frequencies.
///
/// \return A map of image names and corresponding images and frequencies.
///
Fruits loadFruits() {
    // Set frequencies for each symbol.
    // * You can freely play around with the values below.
    // * Values are relative to each other, higher == more common.
    // * Names of these fruits (and berries too) have to actually match
    //   images found on the disk. The images must be in the PNG format.
    const std::map<std::string, int> frequencies{
        {"cherries", 56},
        {"strawberry", 50},
        {"orange", 46},
        {"pear", 39},
        {"apple", 35},
        {"bananas", 30},
        {"tomato", 24},
        {"grapes", 15},
        {"eggplant", 5}
    };

    // Define where the images can be found and what kind of images they are.
    // * Here we assume that the build directory is next to Slots directory.
    const std::string directory("../slots/Resources/");
    const std::string extension(".png");

    // Load the images into QPixmaps and bundle them with their frequencies.
    Fruits symbols;
    for (const std::pair<std::string, int>& frequency : frequencies) {
        const std::string filename = directory + frequency.first + extension;
        const QPixmap image(QString::fromStdString(filename));
        symbols[frequency.first] = std::make_pair(image, frequency.second);
    }

    return symbols;
}

}  // namespace


MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent),
    fruits_(loadFruits()) {

    ui_.setupUi(this);
    initUi();

    timer = new QTimer();
}

MainWindow::~MainWindow(){
    delete timer;
}

void MainWindow::reelStopped(const std::string& middle_sym) {

}

void MainWindow::initUi() {
    // Initialize and display current funds etc.
    ui_.moneyLeft->setText("0");
//    timer->start(1000);
//    timer->timeout(ui_.infoLabel->setText("Welcome to Slot Game!"));
//    timer->timeout()
    ui_.infoLabel->setText("Welcome to Slot Game!");



    // Set lock buttons to desired starting state.
    changeLockButton(ui_.lockButton1, false, true);
    changeLockButton(ui_.lockButton2, false, true);
    changeLockButton(ui_.lockButton3, false, true);

    // Create one random number generator for all Reels to use.
    // * The seed value is obtained via the chrono library and
    //   represents the number of seconds since 1.1.1970.
    // * If you need to debug some pesky error, you can temporarily
    //   replace the seed with some literal. See Minesweeper or
    //   Waterdropgame versions 1 and 2.
    const auto time = std::chrono::high_resolution_clock::now();
    const auto seed = time.time_since_epoch().count();
    auto rng = std::make_shared<std::default_random_engine>(seed);
    money_ = 0;

    // Create each Reel with its own specific labels, etc.
    std::vector<QLabel*> reelVec1 = {ui_.slotUp1, ui_.slotMid1, ui_.slotBot1};
    std::vector<QLabel*> reelVec2 = {ui_.slotUp2, ui_.slotMid2, ui_.slotBot2};
    std::vector<QLabel*> reelVec3 = {ui_.slotUp3, ui_.slotMid3, ui_.slotBot3};
    ui_.slotUp1->setPixmap(fruits_.at("cherries").first.scaled(50,50,Qt::KeepAspectRatio));
    ui_.slotUp2->setPixmap(fruits_.at("strawberry").first.scaled(50,50,Qt::KeepAspectRatio));
    ui_.slotUp3->setPixmap(fruits_.at("pear").first.scaled(50,50,Qt::KeepAspectRatio));
    ui_.slotMid1->setPixmap(fruits_.at("cherries").first.scaled(50,50,Qt::KeepAspectRatio));
    ui_.slotMid2->setPixmap(fruits_.at("strawberry").first.scaled(50,50,Qt::KeepAspectRatio));
    ui_.slotMid3->setPixmap(fruits_.at("pear").first.scaled(50,50,Qt::KeepAspectRatio));
    ui_.slotBot1->setPixmap(fruits_.at("cherries").first.scaled(50,50,Qt::KeepAspectRatio));
    ui_.slotBot2->setPixmap(fruits_.at("strawberry").first.scaled(50,50,Qt::KeepAspectRatio));
    ui_.slotBot3->setPixmap(fruits_.at("pear").first.scaled(50,50,Qt::KeepAspectRatio));

    ui_.slotUp1->setAlignment(Qt::AlignCenter);
    ui_.slotUp2->setAlignment(Qt::AlignCenter);
    ui_.slotUp3->setAlignment(Qt::AlignCenter);
    ui_.slotMid1->setAlignment(Qt::AlignCenter);
    ui_.slotMid2->setAlignment(Qt::AlignCenter);
    ui_.slotMid3->setAlignment(Qt::AlignCenter);
    ui_.slotBot1->setAlignment(Qt::AlignCenter);
    ui_.slotBot2->setAlignment(Qt::AlignCenter);
    ui_.slotBot3->setAlignment(Qt::AlignCenter);
    // * Create the Reels yourself, nullptr is just a dummy value here.
    Reel* reel = nullptr;
//    Reel* reel1 = Reel::Reel(reelVec1, ui_.lockButton1, fruits_, rng);
//    Reel* reel2 = Reel::Reel(reelVec2, ui_.lockButton2, fruits_, rng);
//    Reel* reel3 = Reel::Reel(reelVec3, ui_.lockButton3, fruits_, rng);
    connect(reel, &Reel::stopped, this, &MainWindow::reelStopped);
}

void MainWindow::on_addMoneyButton_clicked()
{
    QString moneyAdded = ui_.moneyLine->text();
    float moneyAmount = moneyAdded.toFloat();

    if (moneyAmount > 0)
    {
        money_ += moneyAmount;
        ui_.moneyLeft->setText(QString::number(money_));
        ui_.infoLabel->setText("Money Added!");
    }
    else
    {
        ui_.infoLabel->setText("Please insert your money!");
    }
}

void MainWindow::on_lockButton1_clicked()
{
    QPushButton* button = ui_.lockButton1;
    if (isLocked(button))
    {
        changeLockButton(button, false);
    }
    else
    {
        changeLockButton(button, true);
    }
}

void MainWindow::on_lockButton2_clicked()
{
    QPushButton* button = ui_.lockButton2;
    if (isLocked(button))
    {
        changeLockButton(button, false);
    }
    else
    {
        changeLockButton(button, true);
    }
}

void MainWindow::on_lockButton3_clicked()
{
    QPushButton* button = ui_.lockButton3;
    if (isLocked(button))
    {
        changeLockButton(button, false);
    }
    else
    {
        changeLockButton(button, true);
    }
}

void MainWindow::changeLockButton(QPushButton* button, bool lockReel, bool isFirstRun)
{
    QString buttonNo = "";
    if (!isFirstRun)
    {
        if (button == ui_.lockButton1)
            buttonNo = "1";
        else if (button == ui_.lockButton2)
            buttonNo = "2";
        else
            buttonNo = "3";
    }

    QPalette pal = button->palette();
    button->setAutoFillBackground(true);
    if (lockReel)
    {
        pal.setColor(QPalette::Button, QColor(Qt::red));

        button->setText("UNLOCK");
        if(!isFirstRun)
            ui_.infoLabel->setText("Reel " + buttonNo + " is LOCKED");
    }
    else
    {
        pal.setColor(QPalette::Button, QColor(Qt::green));
        button->setText("LOCK");
        if(!isFirstRun)
            ui_.infoLabel->setText("Reel " + buttonNo + " is UNLOCKED");
    }
    button->setPalette(pal);
    button->update();
}

bool MainWindow::isLocked(QPushButton *button)
{
    if (button->text() == "LOCK")
        return false;
    else
        return true;

}

void MainWindow::on_releaseButton_clicked()
{
    changeLockButton(ui_.lockButton1, false);
    changeLockButton(ui_.lockButton2, false);
    changeLockButton(ui_.lockButton3, false);
    ui_.infoLabel->setText("All reels are UNLOCKED!");
}


