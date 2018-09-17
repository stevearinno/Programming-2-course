#ifndef SQUARE_HH
#define SQUARE_HH

#include <vector>
#include <iostream>
#include <vector>

const int size_board = 6;

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

   // the status of square if it has ever been opened or not
   bool opened_;

   // returns the status if the square is opened or not
   bool isOpened();

   // opens the square
   void openSquare();

   // printed ".", "*", "P", or the amount of mines in the adjacent squares
   std::string printAdj_;

   // the status of flag "P" on the particular square
   bool flag_;

   // the status of the square if it has mine or not
   bool hasMine_;

   // checks if the square has mine or not
   void hasMine();

   // checks if there is bomb in certain square and opens it if there is no bomb
   int squareAdj();

   // checks the coordinates of the surrounding squares that will be revealed
   void checkSurrounding(int x2, int y2);

   // checks which string character should be printed
   void printAdj();

   // pointer to the board, where the water drop lies
   Board* board_;
};
#endif // SQUARE_HH
