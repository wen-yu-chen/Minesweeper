#include "Space.h"

Tile::Tile() {
    mineCount = 0;
    isMine = false;
    isClicked = false;
    isFlagged = false;
}

void Tile::setCoordinate(float i, float j) {
    x = j * 32;
    y = i * 32;
}

void Tile::setSprite() {
    flagTexture.loadFromFile("images/flag.png");

    if (!isClicked) {
        tileTexture.loadFromFile("images/tile_hidden.png");
        mineTexture.loadFromFile("images/mine.png");
        numTexture.loadFromFile("images/tile_revealed.png");
    }

    else {

        if (isMine) {
            tileTexture.loadFromFile("images/tile_hidden.png");
            mineTexture.loadFromFile("images/mine.png");
            numTexture.loadFromFile("images/mine.png");
        }

        else {
            tileTexture.loadFromFile("images/tile_revealed.png");
            //mineTexture.loadFromFile("images/tile_revealed.png");

            if (mineCount == 0) {
                numTexture.loadFromFile("images/tile_revealed.png");
            }
            else if (mineCount == 1) {
                numTexture.loadFromFile("images/number_1.png");
            }
            else if (mineCount == 2) {
                numTexture.loadFromFile("images/number_2.png");
            }
            else if (mineCount == 3) {
                numTexture.loadFromFile("images/number_3.png");
            }
            else if (mineCount == 4) {
                numTexture.loadFromFile("images/number_4.png");
            }
            else if (mineCount == 5) {
                numTexture.loadFromFile("images/number_5.png");
            }
            else if (mineCount == 6) {
                numTexture.loadFromFile("images/number_6.png");
            }
            else if (mineCount == 7) {
                numTexture.loadFromFile("images/number_7.png");
            }
            else if (mineCount == 8) {
                numTexture.loadFromFile("images/number_8.png");
            }
        }
    }

    tileSprite.setTexture(tileTexture);
    tileSprite.setPosition(x, y);
    mineSprite.setTexture(mineTexture);
    mineSprite.setPosition(x, y);
    numSprite.setTexture(numTexture);
    numSprite.setPosition(x, y);
    flagSprite.setTexture(flagTexture);
    flagSprite.setPosition(x, y);
}

sf::Sprite Tile::getTileSprite() {
    return tileSprite;
}

sf::Sprite Tile::getMineSprite() {
    return mineSprite;
}

sf::Sprite Tile::getNumSprite() {
    return numSprite;
}

sf::Sprite Tile::getFlagSprite() {
    return flagSprite;
}

void Tile::flag() {
    if (isFlagged) {
        isFlagged = false;
    }

    else {
        isFlagged = true;
    }
}

int Tile::reveal(Tile &t) {
    t.isClicked = true;

    //if no mines adjacent
    if ((t.mineCount == 0) && !(t.isMine)) {
        for (int i = 0; i < t.adjacentTiles.size(); i++) {

            //recursively call reveal() if adjacent tile is not mine
            if ((!t.adjacentTiles[i]->isMine) && (!t.adjacentTiles[i]->isClicked) && (!t.adjacentTiles[i]->isFlagged)) {
                reveal(*t.adjacentTiles[i]);
            }
        }
    }

    t.setSprite();
}