#include "cards.hh"

using namespace std;

// TODO: Implement the methods here

Cards::Cards(): top_(nullptr), bottom_(nullptr){

}

Cards::~Cards(){
    while (top_ != nullptr){
        Card_data* card_to_be_released = top_;
        top_ = top_ -> next;

        delete card_to_be_released;
    }
}

void Cards::add(int id){
    Card_data* new_card = new Card_data{id, nullptr};

    if (top_ == nullptr){
        top_ = new_card;
        bottom_ = new_card;
    }
    else {
        new_card -> next = top_;
        top_ = new_card;
    }
}

bool Cards::remove(int& id){
    if ( is_empty() ) {
       return false;
    }

    Card_data* card_to_be_removed = top_;

    id = card_to_be_removed -> data;

    if ( top_ == bottom_ ) {
       top_ = nullptr;
       bottom_ = nullptr;
    } else {
       top_ = top_->next;
    }

    delete card_to_be_removed;

    return true;
}

bool Cards::is_empty() const {
   if ( top_ == nullptr ) {
      return true;
   } else {
      return false;
   }
}

void Cards::print_from_top_to_bottom(std::ostream& s){
    Card_data* card_to_be_printed = top_;
    int running_number = 1;

    while ( card_to_be_printed != nullptr ) {
       s << running_number << ": " << card_to_be_printed->data << std::endl;
       ++running_number;
       card_to_be_printed = card_to_be_printed->next;
    }

}

bool Cards::bottom_to_top(){
    if ( is_empty() || top_ == bottom_) {
       return false;
    }

    Card_data* card_to_be_moved = bottom_;
    Card_data* card_to_be_bottom = top_;

    // Finds the card before the bottom and turns it to bottom_
    while ( card_to_be_bottom != nullptr ) {
        if (card_to_be_bottom -> next == card_to_be_moved){
            bottom_ = card_to_be_bottom;
        }
        card_to_be_bottom = card_to_be_bottom -> next;
    }

    bottom_ -> next = nullptr;
    // Set the next location of the of the bottom card to point to the top card
    card_to_be_moved -> next = top_;
    // Changes the location of the bottom card to be the top
    top_ = card_to_be_moved;

    return true;
}

bool Cards::top_to_bottom(){
    if ( is_empty() || top_ == bottom_ ) {
       return false;
    }

    bottom_ -> next = top_;
    bottom_ = top_;
    top_ = bottom_ -> next;
    bottom_ -> next = nullptr;


    return true;
}


void Cards::print_from_bottom_to_top(std::ostream& s){
    int i = 1;
    s<< i<<": "<< bottom_->data <<endl;
    i++;
    recursive_print(bottom_, s,i);
}

int Cards::recursive_print(Card_data* top, std::ostream& s, int& i){
    Card_data* card_to_be_checked = top_;
    while (card_to_be_checked -> next != top){
        card_to_be_checked = card_to_be_checked -> next;
        if(top == top_) {
            return 0;
        }
    }
    top = card_to_be_checked;
    s << i<<": "<<top->data<<endl;
    i++;
    return recursive_print( top, s, i);
}

/*
void Cards::print_from_bottom_to_top(std::ostream& s){
    int running_number = 1;
    Card_data* card_to_be_printed = bottom_;
    s << running_number << ": " << card_to_be_printed << std::endl;

    int printed_value = recursive_print(card_to_be_printed) -> data;

    while ( printed_value != top_ -> data ) {
       s << running_number << ": " << printed_value << std::endl;
       ++running_number;
       Card_data* current_card = recursive_print(card_to_be_printed);
       printed_value = current_card -> data;
    }

    if ( printed_value == top_ -> data ){
        s << running_number << ": " << printed_value << std::endl;
    }
}

Cards::Card_data* Cards::recursive_print(Card_data* top){

    Card_data* next_card = top;
    Card_data* current_card = top_;

    while ( current_card != nullptr ) {
        if (current_card -> next == next_card){
            //return current_card -> data;
            return current_card;
        }
        current_card = current_card -> next;
    }
    return nullptr;
}

*/
