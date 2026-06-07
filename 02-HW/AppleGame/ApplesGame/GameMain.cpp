#include <SFML/Graphics.hpp>

#include <SFML/Window/Keyboard.hpp>

#include <SFML/Audio.hpp>

#include <iostream>

#include <cmath>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float PLAYER_SPEED = 100.f;
const float PLAYER_SIZE = 20.f;
const float PLAYER_ACCELERATION = 3.f;
const int NUM_APPLES = 20;
const float APPLE_RADIUS = 10.f;
const float GAME_OVER_TIME = 2.f;
const int NUM_STONES = 5;
const float STONES_SIZE = 20.f;

int main() {
    int seed = (int)time(nullptr);
    srand(seed);

    //Инициализация времени
    sf::Clock clock;

    //Инициализация Game Over и Restart
    sf::Font font;
    font.loadFromFile("Resources/Fonts/Roboto-Regular.ttf");
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(250.f, 250.f);

    sf::Text restartText;
    restartText.setFont(font);
    restartText.setString("Restart...");
    restartText.setCharacterSize(30);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(260.f, 320.f);

    //Инициализация экрана и игрока
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apple Game");
    sf::RectangleShape playerShape;
    float playerX = SCREEN_WIDTH / 2.f;
    float playerY = SCREEN_HEIGHT / 2.f;
    playerShape.setPosition(playerX, playerY);
    float playerSpeed = PLAYER_SPEED;
    int playerDirection = 0;
    playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
    playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
    playerShape.setFillColor(sf::Color::Cyan);

    //Инициализация камней
    sf::RectangleShape stones[NUM_STONES];
    float stonesX[NUM_STONES];
    float stonesY[NUM_STONES];

    for (int i = 0; i < NUM_STONES; ++i) {

        float stoneX = STONES_SIZE + rand() / (float)RAND_MAX * (SCREEN_WIDTH - STONES_SIZE * 2);
        float stoneY = STONES_SIZE + rand() / (float)RAND_MAX * (SCREEN_HEIGHT - STONES_SIZE * 2);
        float deltaX = std::abs(playerShape.getPosition().x - stoneX);
        float deltaY = std::abs(playerShape.getPosition().y - stoneY);

        while (deltaX < PLAYER_SIZE / 2 + STONES_SIZE / 2 && deltaY < PLAYER_SIZE / 2 + STONES_SIZE / 2) {
            stoneX = STONES_SIZE + rand() / (float)RAND_MAX * (SCREEN_WIDTH - STONES_SIZE * 2);
            stoneY = STONES_SIZE + rand() / (float)RAND_MAX * (SCREEN_HEIGHT - STONES_SIZE * 2);
            deltaX = std::abs(playerShape.getPosition().x - stoneX);
            deltaY = std::abs(playerShape.getPosition().y - stoneY);
        }

        stonesX[i] = stoneX;
        stonesY[i] = stoneY;
        stones[i].setSize(sf::Vector2f(STONES_SIZE, STONES_SIZE));
        stones[i].setFillColor(sf::Color::Magenta);
        stones[i].setOrigin(STONES_SIZE / 2.f, STONES_SIZE / 2.f);
        stones[i].setPosition(stoneX, stoneY);
    }

    //Инициализация яблок
    sf::CircleShape apples[NUM_APPLES];
    float applesX[NUM_APPLES];
    float applesY[NUM_APPLES];

    for (int i = 0; i < NUM_APPLES; ++i) {

        bool isBadPosition = true;

        while (isBadPosition) {
            float appleX = APPLE_RADIUS + rand() / (float)RAND_MAX * (SCREEN_WIDTH - APPLE_RADIUS * 2);
            float appleY = APPLE_RADIUS + rand() / (float)RAND_MAX * (SCREEN_HEIGHT - APPLE_RADIUS * 2);
            isBadPosition = false;

            for (int j = 0; j < NUM_STONES; ++j) {
                float deltaX = std::abs(appleX - stonesX[j]);
                float deltaY = std::abs(appleY - stonesY[j]);

                if (deltaX < APPLE_RADIUS + STONES_SIZE / 2 && deltaY < APPLE_RADIUS + STONES_SIZE / 2) {
                    isBadPosition = true;
                }
            }

            applesX[i] = appleX;
            applesY[i] = appleY;
        }

        apples[i].setRadius(APPLE_RADIUS);
        apples[i].setFillColor(sf::Color::Red);
        apples[i].setOrigin(APPLE_RADIUS, APPLE_RADIUS);
        apples[i].setPosition(applesX[i], applesY[i]);

    }

    int eatenApples = 0;
    float lastTime = clock.getElapsedTime().asSeconds();
    bool gameOver = false;
    float gameOverTimer = 0.f;

    while (window.isOpen()) {
        float currentTime = clock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (gameOver == true) {
            gameOverTimer += deltaTime;
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (gameOver == false) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                playerDirection = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                playerDirection = 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                playerDirection = 2;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                playerDirection = 3;
            }

            if (playerDirection == 0) {
                playerY -= playerSpeed * deltaTime;
            }
            if (playerDirection == 1) {
                playerX += playerSpeed * deltaTime;
            }
            if (playerDirection == 2) {
                playerY += playerSpeed * deltaTime;
            }
            if (playerDirection == 3) {
                playerX -= playerSpeed * deltaTime;
            }

        }

        bool hasCollisionPlayerWithScreenBorder = (
            playerX + PLAYER_SIZE / 2.f >= SCREEN_WIDTH || playerX - PLAYER_SIZE / 2.f <= 0 ||
            playerY + PLAYER_SIZE / 2.f >= SCREEN_HEIGHT || playerY - PLAYER_SIZE / 2.f <= 0
            );

        if (!gameOver && hasCollisionPlayerWithScreenBorder) {
            gameOver = true;
        }

        if (gameOverTimer > GAME_OVER_TIME) {
            playerX = SCREEN_WIDTH / 2.f;
            playerY = SCREEN_HEIGHT / 2.f;
            playerShape.setPosition(playerX, playerY);
            playerSpeed = PLAYER_SPEED;
            eatenApples = 0;
            playerDirection = 0;

            for (int i = 0; i < NUM_STONES; ++i) {
                float stoneX = STONES_SIZE + rand() / (float)RAND_MAX * (SCREEN_WIDTH - STONES_SIZE * 2);
                float stoneY = STONES_SIZE + rand() / (float)RAND_MAX * (SCREEN_HEIGHT - STONES_SIZE * 2);
                float deltaX = std::abs(playerShape.getPosition().x - stoneX);
                float deltaY = std::abs(playerShape.getPosition().y - stoneY);

                while (deltaX < PLAYER_SIZE / 2 + STONES_SIZE / 2 && deltaY < PLAYER_SIZE / 2 + STONES_SIZE / 2) {
                    stoneX = STONES_SIZE + rand() / (float)RAND_MAX * (SCREEN_WIDTH - STONES_SIZE * 2);
                    stoneY = STONES_SIZE + rand() / (float)RAND_MAX * (SCREEN_HEIGHT - STONES_SIZE * 2);
                    deltaX = std::abs(playerShape.getPosition().x - stoneX);
                    deltaY = std::abs(playerShape.getPosition().y - stoneY);
                }
                stonesX[i] = stoneX;
                stonesY[i] = stoneY;
                stones[i].setPosition(stoneX, stoneY);
            }

            for (int i = 0; i < NUM_APPLES; ++i) {
                bool isBadPosition = true;

                while (isBadPosition) {
                    float appleX = APPLE_RADIUS + rand() / (float)RAND_MAX * (SCREEN_WIDTH - APPLE_RADIUS * 2);
                    float appleY = APPLE_RADIUS + rand() / (float)RAND_MAX * (SCREEN_HEIGHT - APPLE_RADIUS * 2);
                    isBadPosition = false;

                    for (int j = 0; j < NUM_STONES; ++j) {
                        float deltaX = std::abs(appleX - stonesX[j]);
                        float deltaY = std::abs(appleY - stonesY[j]);

                        if (deltaX < APPLE_RADIUS + STONES_SIZE / 2 && deltaY < APPLE_RADIUS + STONES_SIZE / 2) {
                            isBadPosition = true;
                        }

                    }

                    if (isBadPosition == false) {
                        applesX[i] = appleX;
                        applesY[i] = appleY;
                        apples[i].setPosition(appleX, appleY);
                    }
                }
            }

            gameOver = false;
            gameOverTimer = 0.f;
        }

        if (gameOver == false) {
            for (int i = 0; i < NUM_APPLES; ++i) {

                float deltaX = std::abs(playerX - applesX[i]);
                float deltaY = std::abs(playerY - applesY[i]);
                bool isBadPosition = true;

                if (deltaX < (PLAYER_SIZE / 2.f + APPLE_RADIUS) && deltaY < (PLAYER_SIZE / 2.f + APPLE_RADIUS)) {
                    while (isBadPosition) {
                        float appleX = APPLE_RADIUS + rand() / (float)RAND_MAX * (SCREEN_WIDTH - APPLE_RADIUS * 2);
                        float appleY = APPLE_RADIUS + rand() / (float)RAND_MAX * (SCREEN_HEIGHT - APPLE_RADIUS * 2);
                        isBadPosition = false;

                        for (int j = 0; j < NUM_STONES; ++j) {
                            float deltaX = std::abs(appleX - stonesX[j]);
                            float deltaY = std::abs(appleY - stonesY[j]);

                            if (deltaX < APPLE_RADIUS + STONES_SIZE / 2 && deltaY < APPLE_RADIUS + STONES_SIZE / 2) {
                                isBadPosition = true;
                            }
                        }

                        if (isBadPosition == false) {
                            applesX[i] = appleX;
                            applesY[i] = appleY;
                        }

                    }
                    apples[i].setPosition(applesX[i], applesY[i]);
                    ++eatenApples;
                    playerSpeed += PLAYER_ACCELERATION;
                }
            }

            for (int i = 0; i < NUM_STONES; ++i) {
                float deltaX = std::abs(playerX - stonesX[i]);
                float deltaY = std::abs(playerY - stonesY[i]);

                if (deltaX < (PLAYER_SIZE / 2.f + STONES_SIZE / 2.f) && deltaY < (PLAYER_SIZE / 2.f + STONES_SIZE / 2.f)) {
                    gameOver = true;
                }
            }
        }

        window.clear();

        if (gameOver == false) {
            playerShape.setPosition(playerX, playerY);

            for (int i = 0; i < NUM_APPLES; ++i) {
                window.draw(apples[i]);
            }

            for (int i = 0; i < NUM_STONES; ++i) {
                window.draw(stones[i]);
            }
            window.draw(playerShape);
        }
        else {
            window.draw(gameOverText);
            window.draw(restartText);
        }
        window.display();
    }
    return 0;
}