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
    }

  } // END while pollEvent
}
