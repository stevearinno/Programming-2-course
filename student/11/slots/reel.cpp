﻿/*
#####################################################################
# TIE-02207 Programming 2: Basics, F2018                            #
# Project4: Slots                                                   #
# Program description: Implements a virtual slots game.             #
# File: reel.cpp                                                    #
# Description: Draws random fruits for labels to display.           #
# Notes: * This is an exercise program.                             #
#        * Students need to modify this file.                       #
#####################################################################
*/

#include "reel.hh"


Reel::Reel(const std::vector<QLabel*>& labels,
           const QPushButton* lock_button,
           const Fruits* fruits,
           std::shared_ptr<std::default_random_engine> rng):
    labels_(labels), lock_button_(lock_button), fruits_(fruits), rng_(rng)
{
    // Connect all signals & slots you need here.
    setPictures();

}

void Reel::setPictures()
{
    if (lock_button_->text() == "LOCK")
    {
        // Setup the weights (in this case linearly weighted)
        std::vector<std::string> fruitVector;
        std::vector<int> weights;

        auto fruitIterator = fruits_->begin();
        for(;fruitIterator!=fruits_->end(); fruitIterator++)
        {
            fruitVector.push_back(fruitIterator->first);
            weights.push_back((fruitIterator->second).second);
        }

        std::discrete_distribution<int> dist(weights.begin(), weights.end());
        for (int reelElement = 0; reelElement < 3; reelElement++)
        {
            int random_value = dist(*rng_);
            labels_[reelElement]->setPixmap(fruits_->at(fruitVector[random_value]).first.scaled(50,50,Qt::KeepAspectRatio));
//            if (reelElement == 1)
//            {
                checkMiddleSymbol(fruitVector[random_value]);
//            }
        }
    }

}

void Reel::checkMiddleSymbol(std::string symbol)
{
    if (all_middle_symbols.size() == 3)
        all_middle_symbols.clear();
    all_middle_symbols.push_back(symbol);
}

//void Reel::checkMiddleSymbol()
//{
//    if (all_middle_symbols[0] == all_middle_symbols[1] == all_middle_symbols[2])
//    {
//        MainWindow::money_ += ui_.spinBox->value();
//        ui_.moneyLeft->setText(QString::number(MainWindow::money_));
//    }

//}
