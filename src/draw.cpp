#include "engine.hpp"

void Engine::draw() {
  window.clear(Color::Black);

  window.setView(mainView);

  window.draw(backgroundSprite);
  window.draw(player.getSprite());

  // Draw GUI
  window.setView(window.getDefaultView());
  window.draw(scoreText);

  window.display();

}
