#include "Snake.h"

Snake::Snake() : window(sf::VideoMode(1024, 768), "Snake Game") {
    deltaTime = 0;
    gameOver = false;
    fallDelay = 0.5f;
    posX = 5;
    posY = 1;
    intScore = 0;
    direction = "down";
    snakeLength = 2;
    appleX = 5;
    appleY = 7;
    pastDirection = "none";
    bodyX = posX;
    bodyY = posY - 1;
    minusFallDelay = 0.1f;

    XandY startBody = {bodyX, bodyY};
    coordinates.push(startBody);
}

void Snake::endGame() {
    window.clear(sf::Color::Black);

    sf::Text gameOv;
    gameOv.setFont(font);
    gameOv.setCharacterSize(50);
    gameOv.setFillColor(sf::Color::Red);
    gameOv.setPosition(325, 250);
    gameOv.setString("GAME OVER!");

    sf::Text urScore;
    urScore.setFont(font);
    urScore.setCharacterSize(30);
    urScore.setFillColor(sf::Color::Red);
    urScore.setStyle(sf::Text::Bold);
    urScore.setPosition(375, 350);
    urScore.setString("YOUR SCORE: ");

    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(30);
    score.setFillColor(sf::Color::Red);
    score.setStyle(sf::Text::Bold);
    score.setPosition(485, 400);
    std::string str_score = std::to_string(intScore);
    score.setString(str_score);

    sf::Text restart;
    restart.setFont(font);
    restart.setCharacterSize(30);
    restart.setFillColor(sf::Color::Red);
    restart.setStyle(sf::Text::Bold);
    restart.setPosition(350, 700);
    restart.setString("Press R to restart");


    window.draw(gameOv);
    window.draw(urScore);
    window.draw(score);
    window.draw(restart);

}

bool Snake::checkCollisionInSnake(XandY coordinate) {
    std::queue<XandY> temp = coordinates;
    while (!temp.empty()) {
        if (coordinate.x == temp.front().x && coordinate.y == temp.front().y) {
            gameOver = true;
            return true;
        }
        temp.pop();
    }
    return false;
}

bool Snake::checkAppleCollision() {
    std::queue<XandY> temp = coordinates;
    while (!temp.empty()) {
        if (temp.front().x == appleX && temp.front().y == appleY) {
            return true;
        }
        temp.pop();
    }
    return false;
}

bool Snake::checkCollision(XandY coordinate) {
    int x = coordinate.x;
    int y = coordinate.y;

    if (appleX == x && appleY == y) {
        appleY = std::rand() % 15;
        appleX = std::rand() % 15;
        intScore++;
        return true;
    } else if (x < 0 || y < 0 || x > 15 || y > 15 || checkCollisionInSnake(coordinate)) {
        gameOver = true;
        return true;
    }
    return false;
}

void Snake::init() {
    std::srand(std::time(0));
    window.setFramerateLimit(144);

    if (!font.loadFromFile("/Snake_Game/gameFiles/arial_bold.ttf"))
        throw ("COULD NOT LOAD FONT!");
}

void Snake::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                if (pastDirection != "down") {
                    direction = "up";
                }
            }
            if (event.key.code == sf::Keyboard::Left) {
                if (pastDirection != "right") {
                    direction = "left";
                }
            }
            if (event.key.code == sf::Keyboard::Right) {
                if (pastDirection != "left") {
                    direction = "right";
                }
            }
            if (event.key.code == sf::Keyboard::Down) {
                if (pastDirection != "up") {
                    direction = "down";
                }
            }
            if (event.key.code == sf::Keyboard::R && gameOver) {
                gameOver = false;
                fallDelay = 0.5f;
                posX = 5;
                posY = 1;
                intScore = 0;
                direction = "down";
                snakeLength = 2;
                appleX = 5;
                appleY = 7;
                pastDirection = "none";
                bodyX = posX;
                bodyY = posY - 1;
                minusFallDelay = 0.1f;
                XandY startBody = {bodyX, bodyY};
                coordinates.push(startBody);
                run();
            }
        }
    }
}

void Snake::drawSnake(sf::Sprite spriteRevBody) {
    std::queue<XandY> temp = coordinates;
    while (!temp.empty()) {
        int x = temp.front().x;
        int y = temp.front().y;
        spriteRevBody.setPosition(x * 51.2, y * 51.2);
        window.draw(spriteRevBody);
        temp.pop();
    }
    sf::Texture head;
    if (direction == "down") {
        if (!head.loadFromFile("/Snake_Game/gameFiles/headDown.png")) {
            throw EXIT_FAILURE;
        }
    } else if (direction == "up") {
        if (!head.loadFromFile("/Snake_Game/gameFiles/headUp.png")) {
            throw EXIT_FAILURE;
        }
    } else if (direction == "left") {
        if (!head.loadFromFile("/Snake_Game/gameFiles/headLeft.png")) {
            throw EXIT_FAILURE;
        }
    } else if (direction == "right") {
        if (!head.loadFromFile("/Snake_Game/gameFiles/headRight.png")) {
            throw EXIT_FAILURE;
        }
    }
    sf::Sprite spriteHead;
    spriteHead.setTexture(head);

    spriteHead.setPosition(posX * 51.2, posY * 51.2);
    window.draw(spriteHead);
}

void Snake::newCoordinates() {
    XandY nextTail = {bodyX, bodyY};
    coordinates.pop();
    coordinates.push(nextTail);
}

void Snake::drawApple(sf::Sprite spriteApple) {
    spriteApple.setPosition(appleX * 51.2, appleY * 51.2);
    window.draw(spriteApple);
}

void Snake::update() {
    deltaTime = clock.restart().asSeconds();
    fallDelay -= deltaTime;
    if (fallDelay <= 0) {
        XandY head = {posX, posY};
        if (!checkCollision(head)) {
            if (direction == "down") {
                bodyY = posY;
                bodyX = posX;
                posY++;
            } else if (direction == "up") {
                bodyY = posY;
                bodyX = posX;
                posY--;
            } else if (direction == "right") {
                bodyY = posY;
                bodyX = posX;
                posX++;
            } else if (direction == "left") {
                bodyY = posY;
                bodyX = posX;
                posX--;
            }
            newCoordinates();
        } else {
            XandY nextTail = {coordinates.back().x, coordinates.back().y};
            coordinates.push(nextTail);
            int pastAppleX = appleX;
            int pastAppleY = appleY;
            while (appleX != pastAppleX || appleY != pastAppleY) {
                appleY = std::rand() % 15;
                appleX = std::rand() % 15;
            }
            bool appleCol = checkAppleCollision();
            while (appleCol) {
                appleY = std::rand() % 15;
                appleX = std::rand() % 15;
                appleCol = checkAppleCollision();
            }
            if (minusFallDelay <= 0.5f) {
                minusFallDelay += 0.005;
            }
        }
        fallDelay = 0.5f - minusFallDelay;
        pastDirection = direction;
    }
}

void Snake::draw() {
    window.clear(sf::Color::Black);

    sf::RectangleShape square(sf::Vector2f(51.2, 51.2));
    square.setFillColor(sf::Color::Transparent);
    square.setOutlineThickness(1);
    square.setOutlineColor(sf::Color::White);

    for (int i = 0; i < 768; i += 51.2) {
        for (int j = 0; j < 760; j += 51.2) {
            square.setPosition(i, j);
            window.draw(square);
        }
    }

    sf::Text yourScore;
    yourScore.setFont(font);
    yourScore.setCharacterSize(20);
    yourScore.setFillColor(sf::Color::Red);
    yourScore.setPosition(848, 50);
    yourScore.setString("YOUR SCORE: ");
    window.draw(yourScore);

    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(25);
    score.setFillColor(sf::Color::Red);
    score.setPosition(912, 85);
    std::string strScore = std::to_string(intScore);
    score.setString(strScore);
    window.draw(score);

    sf::Texture head;
    if (!head.loadFromFile("/Snake_Game/gameFiles/headDown.png")) {
        throw EXIT_FAILURE;
    }
    sf::Texture body;
    if (!body.loadFromFile("/Snake_Game/gameFiles/snakeBody.png")) {
        throw EXIT_FAILURE;
    }
    sf::Texture revBody;
    if (!revBody.loadFromFile("/Snake_Game/gameFiles/snakeRevBody.png")) {
        throw EXIT_FAILURE;
    }
    sf::Texture apple;
    if (!apple.loadFromFile("/Snake_Game/gameFiles/apple.png")) {
        throw EXIT_FAILURE;
    }

    sf::Sprite spriteHead;
    spriteHead.setTexture(head);

    sf::Sprite spriteBody;
    spriteBody.setTexture(body);

    sf::Sprite spriteRevBody;
    spriteRevBody.setTexture(revBody);

    sf::Sprite spriteApple;
    spriteApple.setTexture(apple);

    drawSnake(spriteRevBody);
    drawApple(spriteApple);

    if (gameOver) {
        while (!coordinates.empty()) {
            coordinates.pop();
        }
        endGame();
    }

    window.display();
}

void Snake::run() {
    init();
    while (window.isOpen()) {
        update();
        handleEvents();
        draw();
    }
}

