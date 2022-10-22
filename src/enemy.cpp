//
// Created by adam on 22/10/22.
//

#include "enemy.hpp"
#include "textureholder.hpp"
#include "bullet.hpp"

Enemy::Enemy(Vector2f startPosition, enemyConfig config) {
  this->position = startPosition;
  this->isShooting = false;
  this->isDead = false;
  this->shootSpeed = 800;

  this->enemySprite.setTexture(TextureHolder::GetTexture("assets/enemies/sprites/" + config.file));
  this->enemySprite.rotate(config.rotation);
  this->health = config.maxHealth;
  this->speed = config.speed;
  this->scorePerHit = config.scorePerHit;
  this->scorePerKill = config.scorePerKill;
  this->canShoot = config.canShoot;
  this->shootAtPlayer = config.shootAtPlayer;
  this->gunPosition = Vector2f(config.gunPositionOffsetX, config.gunPositionOffsetY);
}

Sprite Enemy::getSprite() {
  return this->enemySprite;
}

Vector2f Enemy::getPosition() {
  return this->position;
}

void Enemy::setPosition(Vector2f newPosition) {
  this->position = newPosition;
  this->enemySprite.setPosition(newPosition);
}

Vector2f Enemy::getCenter() {
  Rect<float> thisSpriteRect = this->enemySprite.getGlobalBounds();
  return {thisSpriteRect.left + thisSpriteRect.width / 2,
                  thisSpriteRect.top + thisSpriteRect.height / 2};
}

unsigned long long int Enemy::getScorePerHit() {
  return this->scorePerHit;
}

unsigned long long int Enemy::getScorePerKill() {
  return this->scorePerKill;
}

bool Enemy::getDead() {
  return this->isDead;
}

bool Enemy::getCanShoot() {
  return this->canShoot;
}

bool Enemy::getShootAtPlayer() {
  return this->shootAtPlayer;
}

int Enemy::getShootSpeed() {
  return this->shootSpeed;
}

Time Enemy::getShootClock() {
  return this->shootClock.getElapsedTime();
}

void Enemy::restartShootClock() {
  this->shootClock.restart();
}

Vector2f Enemy::getShootPosition() {
  Vector2f newShootPosition = this->position;
  newShootPosition.x -= this->gunPosition.x;
  newShootPosition.y -= this->gunPosition.y;
  return newShootPosition;
}

unsigned long long Enemy::takeDamage(int damage) {
  unsigned long long int score = 0;
  this->health -= damage;
  this->isDead = this->health <= 0;
  score += this->scorePerHit * damage;
  if (this->isDead) {
    score += this->scorePerKill;
  }
  return score;
}

void Enemy::update(Time dt, Vector2f resolution) {
  Vector2f newPosition = this->position;
  newPosition.y += this->speed;
  this->setPosition(newPosition);
}
