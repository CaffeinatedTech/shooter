#ifndef SHOOTER_PLAYER_HPP
#define SHOOTER_PLAYER_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
private:
    Sprite playerSprite;

    Vector2f position;
    float speed = 10.0f;

    bool leftPressed;
    bool rightPressed;
    bool upPressed;
    bool downPressed;

    float moveXAmount;
    float moveYAmount;

public:
    enum DIRECTION { LEFT, RIGHT, UP, DOWN };
    Player();

    Vector2f getPosition();
    void setPosition(Vector2f newPosition);
    Vector2f getCenterPosition();

    void setDirectionPressed(DIRECTION dir, bool pressed, float amount);

    void update(Time dt, Vector2f resolution, int levelWidth);

    Sprite getSprite();

};


#endif //SHOOTER_PLAYER_HPP
