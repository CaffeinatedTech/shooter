#include "engine.hpp"

void Engine::input() {
  Event event;
  float playerMoveX = 0.0f;
  float playerMoveY = 0.0f;

  while (window.pollEvent(event)) {
    if (event.type == Event::Closed) {
      window.close();
    }

    // Handle keyboard input
    if (event.type == Event::KeyPressed) {
      // Handle the player quitting
      if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
      }

      // Pause
      if (Keyboard::isKeyPressed(Keyboard::Pause) || Keyboard::isKeyPressed(Keyboard::P)) {
        // Make sure we aren't trying to pause the gameover or intro screen
        if (
            this->getGameState() == STATE::INTERMISSION ||
            this->getGameState() == STATE::RUNNING ||
            this->getGameState() == STATE::PAUSED) {
          this->togglePause();
        }
      }

      // Shooting
      if (Keyboard::isKeyPressed(Keyboard::Space)) {
        if (!player.getShooting()) {
          player.setShooting(true);
        }
      }

    } // END keyboard input

    // Handle Keyboard Release
    if (event.type == Event::KeyReleased) {
      // Stop Shooting
      if (event.key.code == Keyboard::Space) {
        if (player.getShooting()) {
          player.setShooting(false);
        }
      }
    }

    // Player Movement
    if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left)) {
      playerMoveX = 100.0f;
    }

    if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down)) {
      playerMoveY = 100.0f;
    }

    player.setDirectionPressed(
        Player::DIRECTION::RIGHT,
        Keyboard::isKeyPressed(Keyboard::Right),
        playerMoveX);
    player.setDirectionPressed(
        Player::DIRECTION::LEFT,
        Keyboard::isKeyPressed(Keyboard::Left),
        playerMoveX);
    player.setDirectionPressed(
        Player::DIRECTION::UP,
        Keyboard::isKeyPressed(Keyboard::Up),
        playerMoveY);
    player.setDirectionPressed(
        Player::DIRECTION::DOWN,
        Keyboard::isKeyPressed(Keyboard::Down),
        playerMoveY);


  } // END while pollEvent
}
