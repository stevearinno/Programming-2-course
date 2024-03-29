#include <iostream>
#include <memory>
#include "cards.hh"

using namespace std;

Cards::Cards(): top_( nullptr ), bottom_( nullptr ) {
}


void Cards::add(int id) {
    if (is_empty()){
        std::shared_ptr<Card_data> new_card
                = std::make_shared<Card_data>(Card_data{id, nullptr,nullptr});
        top_ = new_card;
        bottom_ = new_card;
    }
    else{
        std::shared_ptr<Card_data> new_card
                = std::make_shared<Card_data>(Card_data{id, top_, nullptr});
        top_ -> previous = new_card;
        top_ = new_card;
    }

}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id)
{
    if (is_empty()){
        return false;
    }
    else{
        id = top_ -> data;
        top_ = top_ -> next;
        top_ -> previous = nullptr;

        return true;
    }

}

void Cards::reverse()
{
    if (!is_empty()){
        std::shared_ptr<Card_data> to_be_reversed = bottom_;
        bottom_ = top_;
        top_ = to_be_reversed;

        bottom_ -> next = nullptr;

        while( to_be_reversed != 0 ){
            to_be_reversed -> next = to_be_reversed -> previous;
            to_be_reversed = to_be_reversed -> next;
        }
        top_ -> previous = nullptr;
    }

}

bool Cards::is_empty() const
{
    if (top_ == nullptr){
        return true;
    }
    else{
        return false;
    }
}



// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file reverse.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in reverse.cpp
