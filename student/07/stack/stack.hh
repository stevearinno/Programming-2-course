#ifndef STACK_HH
#define STACK_HH


class Stack
{
public:
    // Constructor
    Stack();

    // Destructor
    ~Stack();

    // inserts item on the top of stack
    void push(int item);

    // removes the topmost element, i.e. item, from the stack
    // returns true if removing succeeded
    // returns false if the stack is empty
    bool pop(int& item);

    // removes the second topmost element, i.e. item, from the stack
    // returns true if removing succeeded
    // returns false if the stack is empty or contains only a single element
    bool pop_second_top(int& item);

    // prints the elements of the stack from top to bottom
    void print();

private:
    // internal structure of the stack
    struct Stack_item {
       int item;
       Stack_item* next;
    };

    // pointer to the top of the stack
    Stack_item* stack_top_;

    // If you need other operations in implementing the above stack methods,
    // you can declare them here

    // checks if the stack is empty
    bool is_empty() const;
};

#endif // STACK_HH
