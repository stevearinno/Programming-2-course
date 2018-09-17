#include "square.hh"
#include <cstdlib>
#include <iostream>

Square::Square( int x, int y, bool hasMine, Board* board):
    x_(x), y_(y), hasMine_(hasMine), board_(board) {
    flag_ = 0;
    opened_ = 0;
    printAdj_ = " ";
}

Square::~Square() {}

void Square::print( std::ostream& stream ) {
    printAdj();
    stream << printAdj_;
}

void Square::printAdj() {
    if (!isOpened()){
        if (hasFlag() == 0){
            printAdj_ = ".";
        }
        else{
            printAdj_ = "P";
        }
    }
    else if (isOpened()){
        if (hasMine_ == 0){
            printAdj_ = std::to_string(countAdjacent());
        }
        else if (hasMine_ == 1){
            printAdj_ = "*";
        }
    }
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
            if( x >= 0 && y >= 0 && x < size_board && y < size_board){
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
}

void Square::removeFlag(){
    flag_ = 0;
}

bool Square::isOpened(){
    return opened_;
}

void Square::openSquare(){
    opened_ = 1;
}

bool Square::open(){
    opened_ = 1;

    if (board_->at(y_).at(x_).hasMine_ == 1){
        return 0;
    }
    else{
        checkSurrounding(x_,y_);                        // check the surrounding squares if they also have no surrounding mines
        return 1;
    }
}



void Square::checkSurrounding(int x2, int y2){
    if (board_->at(y2).at(x2).countAdjacent() == 0 ){
        for( int x = (x2-1); x <= x2+1; x++ ) {
                for (int y = (y2 -1);  y <= y2+1; y++){
                    if( x >= 0 && y >= 0 && x < size_board && y < size_board){
                        if(board_->at(y).at(x).hasMine_ == 0 &&  board_->at(y).at(x).flag_ == 0 && board_->at(y).at(x).isOpened() == 0) {                  // take all the coordinates of surrounding mines
                            board_->at(y).at(x).openSquare();
                            checkSurrounding(x,y);
                        }
                    }
                }
        }
    }
}
