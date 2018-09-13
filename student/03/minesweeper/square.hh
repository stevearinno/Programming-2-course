#ifndef SQUARE_HH
#define SQUARE_HH

#include <vector>
#include <iostream>


class Square;
using Board = std::vector< std::vector< Square > >;

class Square {
 public:

   // location and amount of water as parameters to constructor
   //Square( int x, int y, bool hasMine, Board* board, bool opened = 0, std::string printAdj =" ", std::string adj = " ", bool flag = 0);
    Square( int x, int y, bool hasMine, Board* board);

   ~Square();

   // prints the square to the given stream
   void print( std::ostream& );

   // counts how many mines in the adjacent squares
   int countAdjacent();

   // checks if all the mines are revealed
   bool isReady();

   // checks if the square has flag
   bool hasFlag();

   // adds flag to the square
   void addFlag();

   // removes flag from the square
   void removeFlag();

   // opens all the squares and if it is mine (0), it means game over
   bool open();

 private:

   // adds water to each direction and disappears
   void pop();

   // checks if the square revealed/opened already
   bool checkOpened();

   // location and the number of mines on the adjacent squares
   int x_;
   int y_;
   bool opened_;
   std::string printAdj_;
   std::string adj_;
   bool flag_;
   bool hasMine_;
   // checks the safe squares around the target square
   void safeSquare();

   // checks if there is bomb in certain square
   int squareAdj();


   // pointer to the board, where the water drop lies
   Board* board_;
};
#endif // SQUARE_HH
