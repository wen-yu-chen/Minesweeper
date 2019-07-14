#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");


    sf::Texture t;
    t.loadFromFile("images/test_1.png");
    sf::Texture t2;
    t2.loadFromFile("images/test_2.png");
    sf::Texture debug;
    debug.loadFromFile("images/debug.png");
    sf::Texture happy;
    happy.loadFromFile("images/face_happy.png");
    sf::Texture lose;
    lose.loadFromFile("images/face_lose.png");
    sf::Texture win;
    win.loadFromFile("images/face_win.png");
    sf::Texture digit;
    digit.loadFromFile("images/digits.png");


    //test sprite
    sf::Sprite s(t);
    s.setPosition(560,512);
    sf::Sprite s2(t2);
    s2.setPosition(624,512);

    //debug sprite
    sf::Sprite d(debug);
    d.setPosition(496, 512);

    //face sprite
    sf::Sprite sm(happy);
    sm.setPosition(368, 512);
    sf::Sprite sm2(lose);
    sm2.setPosition(368, 512);
    sf::Sprite sm3(win);
    sm3.setPosition(368, 512);

    //digit sprite
    sf::Sprite n0(digit);
    n0.setPosition(0, 512);
    n0.setTextureRect(sf::IntRect(0, 0, 21, 32));
    sf::Sprite n1(digit);
    n1.setPosition(21, 512);
    sf::Sprite n2(digit);
    n2.setPosition(42, 512);

    Board myBoard;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {

            if (event.mouseButton.button == sf::Mouse::Left) {

                myBoard.boardReveal(event.mouseButton.x, event.mouseButton.y, 0);//0 indicates left click

            }

            else if (event.mouseButton.button == sf::Mouse::Right) {

                myBoard.boardReveal(event.mouseButton.x, event.mouseButton.y, 1);//1 indicates right click
            }
        }

        window.clear();

        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 25; j++) {

                if (!myBoard.tile[i][j].isClicked) {

                    if (myBoard.debug) {
                        if (myBoard.tile[i][j].isMine) {
                            window.draw(myBoard.tile[i][j].getTileSprite());
                            window.draw(myBoard.tile[i][j].getMineSprite());
                        }
                        else {
                            if (myBoard.tile[i][j].isFlagged) {
                                window.draw(myBoard.tile[i][j].getTileSprite());
                                window.draw(myBoard.tile[i][j].getFlagSprite());
                            }

                            else {
                                window.draw(myBoard.tile[i][j].getTileSprite());
                            }

                        }
                    }
                    else {
                        if (myBoard.tile[i][j].isFlagged) {
                            window.draw(myBoard.tile[i][j].getTileSprite());
                            window.draw(myBoard.tile[i][j].getFlagSprite());
                        }
                        else {
                            window.draw(myBoard.tile[i][j].getTileSprite());
                        }

                    }
                }

                else {
                    if (myBoard.tile[i][j].isMine) {
                        window.draw(myBoard.tile[i][j].getTileSprite());
                        window.draw(myBoard.tile[i][j].getMineSprite());
                    } else {
                        window.draw(myBoard.tile[i][j].getTileSprite());
                        window.draw(myBoard.tile[i][j].getNumSprite());
                    }
                }
            }
        }

        myBoard.tileRevealed();

        window.draw(n0);
        window.draw(myBoard.calculateDigit(0, n1));
        window.draw(myBoard.calculateDigit(1, n2));

        if (myBoard.gameOn) {
            window.draw(sm);
        }

        else  {
            if (!myBoard.victory) {
                window.draw(sm2);
            }

            else {
                window.draw(sm3);
            }
        }
        window.draw(d);
        window.draw(s);
        window.draw(s2);

        window.display();
    }

    return 0;
}