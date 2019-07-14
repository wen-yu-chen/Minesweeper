//#include <SFML/Graphics/Sprite.hpp>
//#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include "Board.h"


Board::Board() {
    gameOn = true;
    victory = false;
    debug = false;
    flagLeft = 50;
    numMine = 50;


    //create tiles
    for (int i = 0; i < 16; i++) {
        tile.push_back(vector<Tile>());

        for (int j = 0; j < 25; j++) {
            tile[i].push_back(Tile());
        }
    }

    int r;//row index
    int c;//column index

    //generate mines
    randomMine(tile, numMine);

    //find neighbors
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {

            //tile at top left corner
           if (i == 0 && j == 0) {
               tile[i][j].adjacentTiles.push_back((&tile[i][j + 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i + 1][j + 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i + 1][j]));
           }

           //top right
           else if (i == 0 && j == 25 - 1) {
               tile[i][j].adjacentTiles.push_back((&tile[i][j - 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i + 1][j - 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i + 1][j]));
           }

           //bottom left
           else if (i == 16 - 1 && j == 0) {
               tile[i][j].adjacentTiles.push_back((&tile[i - 1][j]));
               tile[i][j].adjacentTiles.push_back((&tile[i - 1][j + 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i][j + 1]));
           }

           //bottom right
           else if (i == 16 -  1 && j == 25 - 1) {
               tile[i][j].adjacentTiles.push_back((&tile[i][j - 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i - 1][j - 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i - 1][j]));
           }

           //top edge
           else if (i == 0) {
               tile[i][j].adjacentTiles.push_back((&tile[i][j - 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i][j + 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i + 1][j - 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i + 1][j]));
               tile[i][j].adjacentTiles.push_back((&tile[i + 1][j + 1]));

           }

           //bottom edge
           else if (i == 25 - 1) {
               tile[i][j].adjacentTiles.push_back((&tile[i][j - 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i][j + 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i - 1][j - 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i - 1][j]));
               tile[i][j].adjacentTiles.push_back((&tile[i - 1][j + 1]));
           }

           //left edge
           else if (j == 0) {
               tile[i][j].adjacentTiles.push_back((&tile[i - 1][j]));
               tile[i][j].adjacentTiles.push_back((&tile[i - 1][j + 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i][j + 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i + 1][j + 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i + 1][j]));
           }

           //right edge
           else if (j == 25 - 1) {
               tile[i][j].adjacentTiles.push_back((&tile[i - 1][j]));
               tile[i][j].adjacentTiles.push_back((&tile[i - 1][j - 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i][j - 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i + 1][j - 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i + 1][j]));
           }

           else {
               tile[i][j].adjacentTiles.push_back((&tile[i - 1][j - 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i - 1][j]));
               tile[i][j].adjacentTiles.push_back((&tile[i - 1][j + 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i][j - 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i][j + 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i + 1][j - 1]));
               tile[i][j].adjacentTiles.push_back((&tile[i + 1][j]));
               tile[i][j].adjacentTiles.push_back((&tile[i + 1][j + 1]));
           }
        }
    }

    calculateNeighbor(tile);
    boardCoordinate(tile);
    boardSprite(tile);
}

void Board::randomMine(vector< vector<Tile>> &t, int numMines) {

    int r;//row index
    int c;//column index

    for (int i = 0; i < numMines; i++) {
        mt19937 rng;
        rng.seed(random_device()());
        uniform_int_distribution<mt19937::result_type> x(0, 15);//generate random number from 0 to 15
        uniform_int_distribution<mt19937::result_type> y(0, 24);//same but from 0 to 24

        r = x(rng);
        c = y(rng);

        //mine already exits in this tile
        if (t[r][c].isMine) {
            i--;
        }

        //set mine
        else {
            t[r][c].isMine = true;
        }
    }
}

void Board::calculateNeighbor(vector<vector<Tile>> &t) {

    for (int i = 0; i < 16; i++) {
        for (int j= 0; j < 25; j++) {
            for (int k = 0; k < tile[i][j].adjacentTiles.size(); k++) {

                if (t[i][j].adjacentTiles[k]->isMine) {
                    t[i][j].mineCount++;
                }
            }
        }
    }
}

void Board::boardCoordinate(vector<vector<Tile>> &t) {

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {

            tile[i][j].setCoordinate(i, j);
        }
    }
}

void Board::boardSprite(vector<vector<Tile>> &t) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {

            tile[i][j].setSprite();
        }
    }
}



void Board::boardReveal(float a, float b, int n) {
    bool complete = false;

    //restart
    if ((n == 0) && (a >= 368) && (a < 432) && (b >= 512) && (b < 576)) {
        restart();
        complete = true;
    }

    //test1
    else if ((n == 0) && (a >= 560) && (a < 624) && (b >= 512) && (b < 576)) {
        test(1);

        complete = true;
    }

    //test2
    else if ((n == 0) && (a >= 624) && (a < 688) && (b >= 512) && (b < 576)) {
        test(2);

        complete = true;
    }


    if (gameOn) {

        //debug mode
        if ((n == 0) && (a >= 496) && (a < 560) && (b >= 512) && (b < 576)) {
            debug = true;

            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 25; j++) {

                    if (tile[i][j].isMine && tile[i][j].isFlagged) {
                        tile[i][j].isFlagged = false;
                        flagLeft++;
                    }

                }
            }

            complete = true;
        }

        //blank space
        else if (b >= 512) {
            complete = true;

        }

        //tile
        while (!complete) {
            for (int i = 0; i < tile.size(); i++) {
                for (int j = 0; j < tile[0].size(); j++) {

                    //n == 0 indicates left click
                    if ((n == 0) && (tile[i][j].x <= a) && (a < (tile[i][j].x + 32)) && (tile[i][j].y <= b) &&
                        (b < (tile[i][j].y + 32))) {

                        //game over
                        if (tile[i][j].isMine) {
                            gameOn = false;
                            debug = true;
                        }

                        else {
                            //if tile is not flagged, reveal it
                            if (!tile[i][j].isFlagged) {
                                tile[i][j].reveal(tile[i][j]);
                            }
                        }

                        complete = true;
                    }

                    //n == 1 indicates right click
                    else if ((n == 1) && (tile[i][j].x <= a) && (a < (tile[i][j].x + 32)) && (tile[i][j].y <= b) &&
                               (b < (tile[i][j].y + 32))) {

                        if (flagLeft > 0) {
                            tile[i][j].flag();

                            if (tile[i][j].isFlagged) {
                                flagLeft--;
                            }

                            else {
                                flagLeft++;
                            }
                        }

                        //no flags left
                        else {

                            //remove flag
                            if (tile[i][j].isFlagged) {
                                tile[i][j].flag();
                                flagLeft++;
                            }
                        }

                        complete = true;
                    }
                }
            }
        }
    }
}

void Board::restart() {
    gameOn = true;
    victory = false;
    debug = false;
    flagLeft = 50;
    numMine = 50;

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {

            tile[i][j].isMine = false;
            tile[i][j].isClicked = false;
            tile[i][j].isFlagged = false;
            tile[i][j].mineCount = 0;
        }
    }

    randomMine(tile, 50);
    calculateNeighbor(tile);
    boardSprite(tile);
}

void Board::test(int z) {
    restart();
    numMine = 0;

    ifstream f;
    int myArray[400];
    int n = 0;//array index
    char c;

    if (z == 1) {
        f.open("boards/testboard.brd");
    }

    else {
        f.open("boards/testboard2.brd");
    }

    //read data from file
    while (!f.eof()) {
        f >> c;

        myArray[n] = c - '0';
        n++;
    }

    n = 0;

    //generate mines
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            tile[i][j].mineCount = 0;

            if (myArray[n] == 1) {
                tile[i][j].isMine = true;
                numMine++;
            }
            else {
                tile[i][j].isMine = false;
            }

            n++;
        }
    }

    calculateNeighbor(tile);
    boardSprite(tile);
}

sf::Sprite Board::calculateDigit(int q, sf::Sprite &s) {
    int num;

    //caculate second bit digit
    if (q == 0) {
        num = flagLeft / 10;
    }

    //calculate third bit digit
    else {
        num = flagLeft % 10;
    }

    switch (num) {
        case 0:
            s.setTextureRect(sf::IntRect(0, 0, 21, 32));

            break;

        case 1:
            s.setTextureRect(sf::IntRect(21, 0, 21, 32));

            break;

        case 2:
            s.setTextureRect(sf::IntRect(42, 0, 21, 32));

            break;

        case 3:
            s.setTextureRect(sf::IntRect(63, 0, 21, 32));

            break;

        case 4:
            s.setTextureRect(sf::IntRect(84, 0, 21, 32));

            break;

        case 5:
            s.setTextureRect(sf::IntRect(105, 0, 21, 32));

            break;

        case 6:
            s.setTextureRect(sf::IntRect(126, 0, 21, 32));

            break;

        case 7:
            s.setTextureRect(sf::IntRect(147, 0, 21, 32));

            break;

        case 8:
            s.setTextureRect(sf::IntRect(168, 0, 21, 32));

            break;

        case 9:
            s.setTextureRect(sf::IntRect(189, 0, 21, 32));

            break;

        default:
            break;
    }

    return s;
}

void Board::tileRevealed() {
    int count = 0;

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            if (tile[i][j].isClicked) {
                count++;
            }
        }
    }

    //victory
    if (count == 400 - numMine) {
        gameOn = false;
        victory = true;
    }
}