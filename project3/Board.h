#include "Space.h"

using namespace std;

class Board {
public:
    bool gameOn;
    bool victory;
    bool debug;
    int flagLeft;
    int numMine;

    vector< vector<Tile>> tile;

    Board();
    void randomMine(vector< vector<Tile>> &t, int numMines);
    void calculateNeighbor(vector< vector<Tile>> &t);
    void boardCoordinate(vector< vector<Tile>> &t);
    void boardSprite(vector< vector<Tile>> &t);
    void boardReveal(float a, float b, int n);
    void restart();
    void test(int z);
    sf::Sprite calculateDigit(int q, sf::Sprite &s);//int i determines if caculating n1 or n2
    void tileRevealed();
};