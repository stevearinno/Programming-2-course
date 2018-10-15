#include "stack.hh"
#include <iostream>


// Implement stack operations here
Stack::Stack():stack_top_(nullptr){

}

Stack::~Stack(){
    while (!is_empty()){
        Stack_item* item_to_be_released = stack_top_;
        stack_top_ = stack_top_ -> next;

        delete item_to_be_released;
    }
}

void Stack::push(int item){
    Stack_item* new_item = new Stack_item{item, nullptr};

    if (is_empty()){
        stack_top_ = new_item;
    }
    else {
        new_item -> next = stack_top_;
        stack_top_ = new_item;
    }
}

bool Stack::pop(int &item){

    if (is_empty()){
        return false;
    }
    else{
        // ************ useless variable
        item = stack_top_ -> item;
        Stack_item* item_to_be_deleted = stack_top_;
        stack_top_ = item_to_be_deleted -> next;

        delete item_to_be_deleted;

        return true;
    }
}

bool Stack::pop_second_top(int &item){
    if (is_empty()|| stack_top_ -> next == nullptr){
        return false;
    }
    else{
        Stack_item* item_to_be_removed = stack_top_ -> next;

        // ************ useless variable
        item = item_to_be_removed -> item;

        stack_top_ -> next = item_to_be_removed -> next;
        delete item_to_be_removed;

        return true;
    }

}

void Stack::print(){
    Stack_item* item_to_be_printed = stack_top_;

    std::cout << "Stack elements from top to bottom: ";
    while (item_to_be_printed != nullptr){
        std::cout << item_to_be_printed -> item << " ";
        item_to_be_printed = item_to_be_printed -> next;
    }
    std::cout << std::endl;
}

bool Stack::is_empty() const{
    if (stack_top_ == nullptr){
        return true;
    }
    else{
        return false;
    }
}




