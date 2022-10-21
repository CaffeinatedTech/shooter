#include "engine.hpp"

using namespace sf;

void Engine::update(Time dt) {

  player.update(dt, resolution, levelWidth);

  // Scroll Background
  if (backgroundY < resolution.y) {
    backgroundY -= backgroundSpeed * dt.asMilliseconds();
  }
  else {
    backgroundY = 0;
  }
  backgroundSprite.setTextureRect(IntRect(0, backgroundY, levelWidth, resolution.y));

  // Set MainView position limiting it to the size of the level
  Vector2f newMainViewPos;
  newMainViewPos.x = player.getCenterPosition().x;
  if (newMainViewPos.x - resolution.x / 2 < 0) {
    newMainViewPos.x = resolution.x / 2;
  }
  if (newMainViewPos.x + (resolution.x / 2) > (float) levelWidth) {
    newMainViewPos.x = (float) levelWidth - resolution.x / 2;
  }
  newMainViewPos.y = mainView.getCenter().y;
  mainView.setCenter(newMainViewPos);

  // Player Shooting
  if (player.getShooting()) {
    // Don't shoot too often
    if (player.getShootClock().asMilliseconds() > player.getShootSpeed()) {
      bullets.emplace_back(true, player.getShootPosition(), Bullet::LASER1, false, Vector2f(0.0f, 1.0f));
      player.restartShootClock();
    }
  }

  // Process Bullets
  for (int i = 0; i < bullets.size(); i++) {
    if (bullets[i].getPosition().y < -150) {
      bullets.erase(bullets.begin() + i);
      continue;
    }
    else if (bullets[i].getPosition().y > this->resolution.y + 50) {
      bullets.erase(bullets.begin() + i);
    }

    bullets[i].update(dt, this->resolution, this->resolution.y);
  }

} // END update
