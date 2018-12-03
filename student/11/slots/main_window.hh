﻿/*
#####################################################################
# TIE-02207 Programming 2: Basics, F2018                            #
# Project4: Slots                                                   #
# Program description: Implements a virtual slots game.             #
# File: main_window.h                                               #
# Description: Implements a UI for the game to be playable.         #
# Notes: * This is an exercise program.                             #
#        * Students need to modify this file.                       #
#####################################################################
*/

#ifndef SLOTS_MAINWINDOW_H
#define SLOTS_MAINWINDOW_H

#include "reel.hh"
#include "ui_main_window.h"
#include <QMainWindow>
#include <string>
#include <QTimer>


/// \class MainWindow
/// \brief Implements the main window which is used to interact with the game.
///
/// MainWindow owns all the widgets used to display the game to the player
/// and to play the game. MainWindow contains the whole game, no other windows
/// are used.
///
class MainWindow: public QMainWindow {
    Q_OBJECT

public:

    /// \brief Construct a new MainWindow.
    ///
    /// \param[in] parent Points to this MainWindow's parent widget.
    ///
    explicit MainWindow(QWidget* parent = nullptr);

    ~MainWindow();



private slots:

    /// \brief Check if the round is over and prepare for the next round.
    ///
    /// Should get called when a Reel has decided on which fruits to display.
    ///
    /// \param[in] middle_sym Name of the fruit symbol on the middle lane.
    ///
    void reelStopped(const std::string& middle_sym);

    void on_add_money_button_clicked();

    void lockButton();

    void on_release_button_clicked();

    void on_spin_button_clicked();

    void on_spin_box_valueChanged(int arg1);

private:

    /// \brief Initialize the Reels, buttons, etc. so the game can be played.
    ///
    void initUi();
    // locks and unlocks reel
    void changeLockButton(QPushButton* button, bool lockReel, bool isFirstRun=false);
    // checks if the reel is locked
    bool isLocked(QPushButton* button);

    const Fruits fruits_;       ///< The game symbols and their rarities.
    Ui::MainWindowClass ui_;    ///< (Black) Qt magic handling the UI.
    float money_;                // amount of money that the player has
    QTimer* timer;              // the timer for looping welcome text
    std::vector<QLabel*> reelVec1;
    std::vector<QLabel*> reelVec2;
    std::vector<QLabel*> reelVec3;
    Reel* reel1;
    Reel* reel2;
    Reel* reel3;

};  // class MainWindow


#endif  // SLOTS_MAINWINDOW_H
