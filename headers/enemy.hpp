#ifndef SHOOTER_ENEMY_HPP
#define SHOOTER_ENEMY_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

struct enemyConfig {
    std::string file;
    float rotation;
    int maxHealth;
    unsigned long long int scorePerHit;
    unsigned long long int scorePerKill;
    float speed;
    int difficulty;
    bool canShoot;
    bool shootAtPlayer;
    float gunPositionOffsetX;
    float gunPositionOffsetY;
};

class Enemy {
private:
    int enemyType;
    int health;
    float speed;
    unsigned long long int scorePerHit;
    unsigned long long int scorePerKill;

    Sprite enemySprite;
    Vector2f position;

    bool canShoot;
    int bulletType;
    bool shootAtPlayer;
    int shootSpeed;
    int firstShotDelay;
    Vector2f gunPosition;

    bool isShooting;
    bool isDead;

    Clock shootClock;

public:
    Enemy(Vector2f startPosition, enemyConfig config);

    Sprite getSprite();
    Vector2f getPosition();
    void setPosition(Vector2f newPosition);
    Vector2f getCenter();

    unsigned long long int getScorePerHit();
    unsigned long long int getScorePerKill();
    unsigned long long int takeDamage(int damage);

    bool getCanShoot();
    bool getShootAtPlayer();
    int getShootSpeed();
    Time getShootClock();
    void restartShootClock();
    Vector2f getShootPosition();


    bool getDead();

    void update(Time dt, Vector2f resolution);

};


#endif //SHOOTER_ENEMY_HPP
