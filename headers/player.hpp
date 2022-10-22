#ifndef SHOOTER_PLAYER_HPP
#define SHOOTER_PLAYER_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
private:
    int lives;
    int health;
    int maxHealth;
    int repairDelay;
    int repairAmount;
    unsigned long long int score;

    Sprite playerSprite;

    Vector2f position;
    float speed = 10.0f;
    int shootSpeed = 100; // Milliseconds between shots

    bool leftPressed;
    bool rightPressed;
    bool upPressed;
    bool downPressed;

    float moveXAmount;
    float moveYAmount;

    bool isShooting;

    Clock shootClock;
    Clock repairClock;

public:
    enum DIRECTION { LEFT, RIGHT, UP, DOWN };
    Player();

    Vector2f getPosition();
    void setPosition(Vector2f newPosition);
    Vector2f getCenterPosition();

    void setShooting(bool isShooting);
    bool getShooting();
    int getShootSpeed();
    Vector2f getShootPosition();
    void restartShootClock();
    Time getShootClock();
    Time getRepairClock();
    int getRepairDelay();
    int getRepairAmount();
    bool takeDamage(int damage);
    void repair(int amount);

    void increaseScore(unsigned long long int scoreIncrement);

    void setDirectionPressed(DIRECTION dir, bool pressed, float amount);
    void update(Time dt, Vector2f resolution, int levelWidth);
    Sprite getSprite();

};


#endif //SHOOTER_PLAYER_HPP
