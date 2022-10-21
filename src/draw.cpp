#include "engine.hpp"

void Engine::draw() {
  window.clear(Color::Black);

  window.setView(mainView);

  window.draw(backgroundSprite);
  window.draw(player.getSprite());

  // Draw Bullets
  for (auto& bullet: bullets) {
    window.draw(bullet.getSprite());
  }

  // Draw GUI
  window.setView(window.getDefaultView());
  window.draw(scoreText);

  window.display();

}
