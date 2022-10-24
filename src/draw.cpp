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

  // Draw Enemies
  for (auto& enemy: enemies) {
    window.draw(enemy.getSprite());
  }

  // Draw GUI
  window.setView(window.getDefaultView());
  window.draw(scoreText);
  window.draw(playerHealthBarFrame);
  window.draw(playerHealthBar);

  if (gameState == STATE::INTERMISSION) {
    window.draw(intermissionTimer);
    window.draw(intermissionWaveLabel);
    window.draw(intermissionWaveValue);
    window.draw(intermissionWaveKillsLabel);
    window.draw(intermissionWaveKillsValue);
    window.draw(intermissionWaveScoreLabel);
    window.draw(intermissionWaveScoreValue);
  }

  window.display();

}
