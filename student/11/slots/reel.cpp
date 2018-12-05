/*
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

//    timer = new QTimer(this);
//    timer_value = rand() % 2000 + 1000;
//    timer->start(4);
//    connect(timer, SIGNAL(timeout()), this, SLOT(movingPicture()));
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
        for (int reelElement = 0; reelElement < labels_.size(); reelElement++)
        {
            int random_value = dist(*rng_);
            labels_[reelElement]->setPixmap(fruits_->at(fruitVector[random_value]).
                                            first.scaled(50,50,Qt::KeepAspectRatio));
            saveSymbol(fruitVector[random_value]);
        }
    }

}

void Reel::saveSymbol(std::string symbol)
{
    // for initializing/clearing the vector in each spin
    if (reel_symbols.size() == 4)
        reel_symbols.clear();
    reel_symbols.push_back(symbol);
}

void Reel::movingPicture()
{
    qDebug("test");
    for (int index = 0; index < 4; index++)
    {
        qreal xx = labels_[index]->x();
        qreal yy = labels_[index]->y();
        yy += 1;
        labels_[index]->move(xx,yy);
    }


}

