#include <vec2.hpp>
#include "bullet.hpp"
#include "textureholder.hpp"

Bullet::Bullet(bool playerFired, sf::Vector2f bulletPosition, int newBulletType, bool atPlayer, sf::Vector2f target) {
  this->isPlayerBullet = playerFired;
  this->bulletType = newBulletType;
  this->position.x = bulletPosition.x;
  this->position.y = bulletPosition.y;
  this->direction = Vector2f(0.0f, -1.0f);

  switch (this->bulletType) {
    case LASER1:
      this->bulletSprite.setTexture(TextureHolder::GetTexture("assets/other/sprites/laser_red01.png"));
      this->bulletSprite.setPosition(this->position);
      this->speed = 10.0f;
      break;
    case LASER2:
      this->bulletSprite.setTexture(TextureHolder::GetTexture("assets/other/sprites/M484BulletCollection2.png"));
      this->bulletSprite.setTextureRect({271, 107, 11, 11});
      this->bulletSprite.setPosition(this->position);
      this->speed = 10.0f;
      break;
    default:
      break;
  }
}

int Bullet::getBulletType() {
  return this->bulletType;
}

bool Bullet::getIsPlayerBullet() {
  return this->isPlayerBullet;
}

float Bullet::getSpeed() {
  return this->speed;
}

Vector2f Bullet::getPosition() {
  return this->position;
}

void Bullet::setPosition(sf::Vector2f newPosition) {
  this->position = newPosition;
  this->bulletSprite.setPosition(newPosition);
}

Vector2f Bullet::getDirection() {
  return this->direction;
}

Sprite Bullet::getSprite() {
  return this->bulletSprite;
}

void Bullet::update(sf::Time dt, sf::Vector2f resolution, int levelHeight) {
  Vector2f newPosition = this->position;
  newPosition += this->getDirection() * this->getSpeed();
  this->setPosition(newPosition);
}

