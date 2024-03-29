#ifndef CARDS_HH
#define CARDS_HH

#include <iostream>
#include <memory>

class Cards {

    public:
      // A dynamic structure must have a constructor that initializes
      // the top elem as nullptr.
      Cards();

      // Adds a new card with the given id as the topmost element.
      void add(int id);

      // Prints the content of the data structure with ordinal numbers to the
      // output stream given as a parameter starting from the first element.
      void print(std::ostream& s);

      // Removes the topmost card and returns it as reference parameter number.
      // Returns false, if the data structure is empty, otherwise returns true.
      bool remove(int& id);

      // Reverses the content of the data structure as opposite.
      void reverse();

      // Checks if the stack is empty
      bool is_empty() const;

    private:
      struct Card_data {
        int data;
        std::shared_ptr<Card_data> next;
        std::shared_ptr<Card_data> previous;
      };

      std::shared_ptr<Card_data> top_;
      std::shared_ptr<Card_data> bottom_;
};

#endif // CARDS_HH
