#include "engine.hpp"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() {
  // Set up all of the window, textures, sprites, sounds etc.

  resolution.x = 1920;
  resolution.y = 1080;

  levelWidth = 2500;

  window.create(VideoMode(resolution.x, resolution.y), "Shooter", Style::Default);
  window.setFramerateLimit(FPS);
  mainView.setSize(resolution);

  mainFont.loadFromFile("assets/fonts/slant_regular.ttf");

  displayedScore = 0;

  // Score Text
  setupFont(&scoreText, mainFont, std::to_string(displayedScore), 72, Color::Green);
  FloatRect scoreTextBounds = scoreText.getLocalBounds();
  scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 20, 0));

  intermissionTime = 6; // Number of seconds between waves
  runningTime = Time::Zero;
  waveTime = Time::Zero;
  intermissionRunningTime = Time::Zero;
}

void Engine::run() {
  // timing
  Clock clock;
  Time timeSinceLastUpdate = Time::Zero;

  // Main Loop - Runs until the window is closed
  while (window.isOpen()) {
    input();
    // Make sure that update is run smoothly if the game is running too fast or slow
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;
      update(TimePerFrame);
    }

    draw();
  }
}

void Engine::setupFont(Text *textItem, const Font &font, const String &value, int size, Color colour) {
  textItem->setFont(font);
  textItem->setString(value);
  textItem->setCharacterSize(size);
  textItem->setFillColor(colour);
}

