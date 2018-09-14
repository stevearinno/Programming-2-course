#include "square.hh"
#include <cstdlib>
#include <iostream>

Square::Square( int x, int y, bool hasMine, Board* board):
    x_(x), y_(y), hasMine_(hasMine), board_(board) {
    flag_ = 0;
    printAdj_ = " ";
}

Square::~Square() {}

void Square::print( std::ostream& stream ) {
    printAdj();
    stream << printAdj_;
}

void Square::printAdj() {
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
}

void Square::removeFlag(){
    flag_ = 0;
}

bool Square::open(){
    opened_ = 1;

    if (board_->at(y_).at(x_).hasMine_ == 1){
        return 0;
    }
    else{
        //vektorX.clear();
        //vektorY.clear();
        if (board_->at(y_).at(x_).countAdjacent() == 0 ){   // if the square has no mines in the adjacent squares
            checkSurrounding(x_,y_);                        // check the surrounding squares if they also have no surrounding mines
            safeSquare();
            checkZeros(x_,y_);

            for(int x = vektorX2.size()-1; x >= 0; x--){
                for(int y = vektorY2.size()-1; y >= 0; y--){
                    checkSurrounding(vektorX2.at(x),vektorY2.at(y));
                    safeSquare();
                    checkZeros(vektorX2.at(x),vektorY2.at(y));
                }
            }
        }

        return 1;
    }
}

void Square::safeSquare(){                    // opens all surrounding mines of the surrounding squares
    int x2 = 0;
    int y2 = 0;


    for(int y = vektorY.size()-1; y >= 0; --y)
    {
        for(int x = vektorX.size()-1; x >=0; --x)
        {
            x2 = vektorX.at(x);
            y2 = vektorY.at(y);
            // opens all surrounding mines of the surrounding squares
            board_->at(y2).at(x2).opened_ = 1;
        }
    }
}

void Square::checkSurrounding(int x3, int y3){
    vektorX.clear();
    vektorY.clear();
    for( int x = (x3-1); x <= x3+1; x++ ) {
            for (int y = (y3 -1);  y <= y3+1; y++){
                if( x >= 0 && y >= 0 && x < 6 && y < 6){
                    if(board_->at(y).at(x).hasMine_ == 0 &&  board_->at(y).at(x).flag_ == 0) {                  // take all the coordinates of surrounding mines
                       vektorX.push_back(x);
                       vektorY.push_back(y);
                    }
                }
            }
    }
}


void Square::checkZeros(int x4, int y4){
    vektorX2.clear();
    vektorY2.clear();
    for( int x = (x4-1); x <= x4+1; x++ ) {
            for (int y = (y4 -1);  y <= y4+1; y++){
                if( x >= 0 && y >= 0 && x < 6 && y < 6){
                    if(board_->at(y).at(x).countAdjacent() == 0){        // take all the coordinates of surrounding 0s and not opened
                        vektorX2.push_back(x);
                        vektorY2.push_back(y);
                    }
                }
            }
    }
}
