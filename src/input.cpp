#include "engine.hpp"

void Engine::input() {
  Event event;

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

      if (Keyboard::isKeyPressed(Keyboard::Pause) || Keyboard::isKeyPressed(Keyboard::P)) {
        // Make sure we aren't trying to pause the gameover or intro screen
        if (
            this->getGameState() == STATE::INTERMISSION ||
            this->getGameState() == STATE::RUNNING ||
            this->getGameState() == STATE::PAUSED) {
          this->togglePause();
        }
      }

    } // END keyboard input

  } // END while pollEvent
}
