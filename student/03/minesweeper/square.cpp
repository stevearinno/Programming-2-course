#include "square.hh"
#include <cstdlib>
#include <iostream>

//Square::Square( int x, int y, bool hasMine, Board* board, bool opened, std::string printAdj, std::string adj, bool flag):
//    x_(x), y_(y), hasMine_(hasMine), board_(board), opened_(opened), printAdj_(printAdj), adj_(adj), flag_(flag) {}
Square::Square( int x, int y, bool hasMine, Board* board):
    x_(x), y_(y), hasMine_(hasMine), board_(board) {
    flag_ = 0;
    printAdj_ = " ";
}

Square::~Square() {}

void Square::print( std::ostream& stream ) {
    if (opened_ == 0){
        if (hasFlag() == 0){
            printAdj_ = ".";
        }
        else{
            printAdj_ = "P";
        }
    }
    else if (opened_ == 1){
        if (hasMine_ == 0){
            printAdj_ = std::to_string(countAdjacent());
        }
        else if (hasMine_ == 1){
            printAdj_ = "*";
        }
    }
    stream << printAdj_;
}

int Square::countAdjacent(){
    int adjcount_ = 0;
    if (board_->at(y_).at(x_).hasMine_ == 1){
            adjcount_ = -1;
    }
            else{
            adjcount_ = 0;
}

        for( int x = (x_-1); x <= x_+1; x++ ) {
        for (int y = (y_ -1);  y <= y_+1; y++){
            if( x >= 0 && y >= 0 && x < 6 && y < 6){
                if( board_->at(y).at(x).hasMine_ == 1) {
                   adjcount_ += 1;
                }
            }
        }
    }
    return adjcount_;
}

bool Square::isReady(){
    if (hasMine_ == 1 && hasFlag() == 1){
        return 1;
    }
    else if (hasMine_ == 0 && hasFlag() == 0){
        return 1;
    }
    else{
        return 0;
    }
}

bool Square::hasFlag(){
    return flag_;
}

void Square::addFlag(){
    flag_ = 1;
    //return flag_;
}

void Square::removeFlag(){
    flag_ = 0;
    //return flag_;
}

bool Square::open(){
    opened_ = 1;
    if (board_->at(y_).at(x_).hasMine_ == 1){
        return 0;
    }
    else{
        safeSquare();
        return 1;
    }
}

void Square::safeSquare(){
    // opens all safe squares to the left of the target
    int x = x_-1;
    int y = y_;
    while(x >=0 && y >= 0 && board_->at(y).at(x).hasMine_ == 0 &&  board_->at(y).at(x).flag_ == 0){
        board_->at(y).at(x).opened_ = 1;
        x -= 1;
    }

    // opens all safe squares to the right of the target square
    x = x_+1;
    y = y_;
    while(x < 6 && y >= 0 && board_->at(y).at(x).hasMine_ == 0 &&  board_->at(y).at(x).flag_ == 0){
        board_->at(y).at(x).opened_ = 1;
        x += 1;
    }

    // opens all safe squares to the down of the target square
    x = x_;
    y = y_-1;
    while(x < 6 && y >= 0 && board_->at(y).at(x).hasMine_ == 0 &&  board_->at(y).at(x).flag_ == 0){
        board_->at(y).at(x).opened_ = 1;
        y -= 1;
    }

    // opens all safe squares to the up of the target square
    x = x_;
    y = y_+1;
    while(x < 6 && y < 6 && board_->at(y).at(x).hasMine_ == 0 &&  board_->at(y).at(x).flag_ == 0){
        board_->at(y).at(x).opened_ = 1;
        y += 1;
    }
}

