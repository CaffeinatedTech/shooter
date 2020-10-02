#include "player.hpp"
#include "textureholder.hpp"

Player::Player() {
  position.x = 500;
  position.y = 900;

  playerSprite.setTexture(TextureHolder::GetTexture("assets/player/sprites/player1.png"));
  playerSprite.setPosition(position);
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
