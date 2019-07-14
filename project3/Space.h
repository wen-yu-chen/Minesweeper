//#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

using namespace std;

class Tile {
public:
    unsigned int mineCount;//number of mines adjacent to this tile
    bool isMine;
    bool isClicked;
    bool isFlagged;
    float x;//x coordinate of image
    float y;//y coordinate of image

    vector<Tile*> adjacentTiles;

    sf::Sprite tileSprite;
    sf::Sprite mineSprite;
    sf::Texture tileTexture;
    sf::Texture mineTexture;
    sf::Texture numTexture;
    sf::Sprite numSprite;
    sf::Texture flagTexture;
    sf::Sprite flagSprite;

    Tile();
    void setCoordinate(float i, float j);//set x and y
    void setSprite();
    sf::Sprite getTileSprite();
    sf::Sprite getMineSprite();
    sf::Sprite getNumSprite();
    sf::Sprite getFlagSprite();
    void flag();
    int reveal(Tile &t);
};