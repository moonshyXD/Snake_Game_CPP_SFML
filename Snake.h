#ifndef CLION_PROJECTS_SNAKE_H
#define CLION_PROJECTS_SNAKE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>
#include <string>
#include <ctime>

class Snake {
private:
    struct XandY{
        int x;
        int y;
    };
    void init();
    void draw();
    void update();
    bool checkCollision(XandY coordinate);
    bool checkCollisionInSnake(XandY coordinate);
    void endGame();
    void handleEvents();
    void drawSnake(sf::Sprite spriteRevBody);
    void newCoordinates();
    void drawApple(sf::Sprite spriteApple);
    bool checkAppleCollision();

    sf::Clock clock;
    sf::RenderWindow window;
    double deltaTime;
    bool gameOver;
    double fallDelay;
    std::queue<XandY> coordinates;
    int posX;
    int posY;
    int intScore;
    sf::Font font;
    std::string direction;
    std::string pastDirection;
    int snakeLength;
    int appleX;
    int appleY;
    int bodyX;
    int bodyY;
    double minusFallDelay;
public:
    Snake();
    void run();
};


#endif
