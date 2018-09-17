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

   // printed ".", "*", "P", or the amount of mines in the adjacent squares
   std::string printAdj_;

   // the status of flag "P" on the particular square
   bool flag_;
   bool hasMine_;
   // checks the safe squares around the target square
   void safeSquare();
   void safeSquare2();

   // checks if there is bomb in certain square and opens it if there is no bomb
   int squareAdj();

   // checks the coordinates of the surrounding squares that will be revealed
   void checkSurrounding(int x3, int y3);

   // checks which string character should be printed
   void printAdj();

   // saves temporary location of the surrounding squares that will be revealed
   std::vector<int> vektorX;
   std::vector<int> vektorY;

   // saves temporary location of zeros that will be revealed at the same time
   std::vector<int> vektorX2;
   std::vector<int> vektorY2;

   // checks zero squares on the surrounding squares
   void checkZeros(int x4, int y4);

   // pointer to the board, where the water drop lies
   Board* board_;
};
#endif // SQUARE_HH
