#include "player.hpp"
#include "textureholder.hpp"

Player::Player() {
  lives = 3;
  health = maxHealth = 100;
  repairDelay = 1000; // Milliseconds before starting repair and between each repair tick
  repairAmount = 5; // AMount repaired per tick
  score = 0;

  position.x = 500;
  position.y = 900;

  isShooting = false;

  shootClock.restart();
  repairClock.restart();

  playerSprite.setTexture(TextureHolder::GetTexture("assets/player/sprites/player1.png"));
  playerSprite.setPosition(position);
}

bool Player::getShooting() {
  return this->isShooting;
}

void Player::setShooting(bool isShooting) {
  this->isShooting = isShooting;
  if (!isShooting) {
    this->repairClock.restart();
  }
}

Time Player::getShootClock() {
  return this->shootClock.getElapsedTime();
}

Time Player::getRepairClock() {
  return this->repairClock.getElapsedTime();
}

void Player::restartShootClock() {
  this->shootClock.restart();
}

int Player::getShootSpeed() {
  return this->shootSpeed;
}

Vector2f Player::getShootPosition() {
  Vector2f newShootPosition = this->position;
  return newShootPosition += {this->playerSprite.getLocalBounds().width / 2 - 7, 0};
}

int Player::getRepairDelay() {
  return this->repairDelay;
}

int Player::getRepairAmount() {
  return this->repairAmount;
}

void Player::repair(int amount) {
  this->health += amount;
  if (this->health > this->maxHealth) {
    this->health = this->maxHealth;
  }
  this->repairClock.restart();
}

bool Player::takeDamage(int damage) {
  bool isPlayerDead;
  this->health -= damage;
  if (this->health <= 0) {
    isPlayerDead = true;
    this->health = 0;
  }
  else {
    isPlayerDead = false;
  }
  this->repairClock.restart();
  return isPlayerDead;
}

int Player::getHealth() {
  return this->health;
}

int Player::getMaxHealth() {
  return this->maxHealth;
}

void Player::increaseScore(unsigned long long scoreIncrement) {
  this->score += scoreIncrement;
}

unsigned long long Player::getScore() {
  return this->score;
}

void Player::setScore(unsigned long long newScore) {
  this->score = newScore;
}

Sprite Player::getSprite() {
  return this->playerSprite;
}

Vector2f Player::getPosition() {
  return this->position;
}

void Player::setPosition(Vector2f newPosition) {
  this->position = newPosition;
  this->playerSprite.setPosition(newPosition);
}

Vector2f Player::getCenterPosition() {
  Vector2 centerPos = this->position;
  centerPos.x += this->playerSprite.getLocalBounds().width / 2;
  centerPos.y += this->playerSprite.getLocalBounds().height / 2;
  return centerPos;
}

void Player::setDirectionPressed(DIRECTION dir, bool pressed, float amount) {
  switch (dir) {
    case LEFT:
      leftPressed = pressed;
      moveXAmount = abs(amount);
      break;
    case RIGHT:
      rightPressed = pressed;
      moveXAmount = abs(amount);
      break;
    case UP:
      upPressed = pressed;
      moveYAmount = abs(amount);
      break;
    case DOWN:
      downPressed = pressed;
      moveYAmount = abs(amount);
      break;
  }
}

void Player::update(Time dt, Vector2f resolution, int levelWidth) {

  // Movement
  if (this->rightPressed) {
    this->position.x += speed * (this->moveXAmount / 100);
    if (this->position.x > levelWidth - this->playerSprite.getLocalBounds().width) {
      this->position.x = levelWidth - this->playerSprite.getLocalBounds().width;
    }
  }
  if (this->leftPressed) {
    this->position.x -= speed * (this->moveXAmount / 100);
    if (this->position.x < 0) {
      this->position.x = 0;
    }
  }
  if (this->upPressed) {
    this->position.y -= speed * (this->moveYAmount / 100);
    if (this->position.y < 0) {
      this->position.y = 0;
    }
  }
  if (this->downPressed) {
    this->position.y += speed * (this->moveYAmount / 100);
    if (this->position.y > resolution.y - this->playerSprite.getLocalBounds().height) {
      this->position.y = resolution.y - this->playerSprite.getLocalBounds().height;
    }
  }

  this->setPosition(this->position);
}
