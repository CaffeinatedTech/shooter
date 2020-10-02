#include "engine.hpp"

void Engine::draw() {
  window.clear(Color::Black);

  window.setView(mainView);

  window.display();

}
