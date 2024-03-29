#ifndef SHOOTER_BULLET_HPP
#define SHOOTER_BULLET_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet {
private:
    bool isPlayerBullet;
    int bulletType;

    Sprite bulletSprite;
    Vector2f position;
    Vector2f direction;
    float speed;

public:
    enum types {LASER1=1, LASER2};

    Bullet(bool playerFired, Vector2f bulletPosition, int newBulletType, bool atPlayer, Vector2f target);

    bool getIsPlayerBullet();
    int getBulletType();
    Vector2f getPosition();
    void setPosition(Vector2f newPosition);
    Vector2f getDirection();
    float getSpeed();

    void update(Time dt, Vector2f resolution, int levelHeight);

    Sprite getSprite();

};


#endif //SHOOTER_BULLET_HPP
