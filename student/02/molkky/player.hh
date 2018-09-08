#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

using namespace std;

class Player
{
private:
    string name_;
    int points_;

public:
    Player(string name, int points);
    string get_name() const;
    bool has_won();
    void add_points(int points);
    int get_points();



};

#endif // PLAYER_HH
