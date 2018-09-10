#include "player.hh"


void Player::add_points(int points1){
    points_ += points1;
    if (points_ > 50){
        points_ = 25;
    }
}

bool Player::has_won(){
    if (points_ == 50){
        return 1;
    }
    else{
        return 0;
    }
}

int Player::get_points(){
    return points_;
}
