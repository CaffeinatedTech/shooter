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

} // END update
