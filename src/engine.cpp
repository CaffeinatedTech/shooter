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

  backgroundTexture = TextureHolder::GetTexture("assets/backgrounds/sprites/stars.png");
  backgroundTexture.setRepeated(true);
  backgroundSprite.setTexture(backgroundTexture);
  backgroundSprite.setPosition(0,-40);
  backgroundY = 0;
  backgroundSprite.setTextureRect(IntRect(0, backgroundY, levelWidth, resolution.y));
  backgroundSpeed = 0.5f;

  playerHealthBarFrame.setSize(Vector2f(305, 35));
  playerHealthBarFrame.setOutlineColor(Color::Blue);
  playerHealthBarFrame.setOutlineThickness(2.5f);
  playerHealthBarFrame.setFillColor(Color::Transparent);
  playerHealthBarFrame.setPosition(Vector2f(97.5f, 17.5f));
  playerHealthBar.setSize(Vector2f(300, 30));
  playerHealthBar.setFillColor(Color::Green);
  playerHealthBar.setPosition(Vector2f(100, 20));

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

  // Set game state to running
  gameState = STATE::RUNNING;
  previousGameState = gameState;

// TODO - Build the enemy spawner
  // Temporary enemy spawn - need to build a system to read in the enemy files
  enemyConfig thisEnemyConfig;
  thisEnemyConfig.file = "enemy1.png";
  thisEnemyConfig.rotation = 180.f;
  thisEnemyConfig.maxHealth = 15;
  thisEnemyConfig.scorePerHit = 13;
  thisEnemyConfig.scorePerKill = 10000;
  thisEnemyConfig.speed = 5;
  thisEnemyConfig.difficulty = 1;
  thisEnemyConfig.canShoot = true;
  thisEnemyConfig.shootAtPlayer = false;
  thisEnemyConfig.gunPositionOffsetX = 80.f;
  thisEnemyConfig.gunPositionOffsetY = 20.f;
  this->enemies.emplace_back(Vector2f(300.f, 10.f), thisEnemyConfig);
}

void Engine::run() {
  // timing
  Clock clock;
  Time timeSinceLastUpdate = Time::Zero;

  // Main Loop - Runs until the window is closed
  while (window.isOpen()) {
    Time dt = clock.restart();
    // If we are paused, then check for input so we can un-pause and just go to the next loop
    if (this->getGameState() == STATE::PAUSED || this->getGameState() == STATE::GAMEOVER) {
      input();
      draw();
      sleep(milliseconds(5)); // Sleep so we don't peg the CPU
      continue;
    }

    timeSinceLastUpdate += dt;
    runningTime += dt;
    if (this->getGameState() == STATE::INTERMISSION) {
      intermissionRunningTime += dt;
    }

    // Make sure that update is run smoothly if the game is running too fast or slow
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;
      input();
      update(TimePerFrame);
    }

    draw();
  }
}

int Engine::getGameState() {
  return this->gameState;
}

void Engine::setGameState(int newGameState) {
  this->gameState = newGameState;
}

void Engine::togglePause() {
  if (this->getGameState() == STATE::PAUSED) {
    this->setGameState(this->previousGameState);
  }
  else {
    this->previousGameState = this->getGameState();
    this->setGameState(STATE::PAUSED);
  }
}

void Engine::setupFont(Text *textItem, const Font &font, const String &value, int size, Color colour) {
  textItem->setFont(font);
  textItem->setString(value);
  textItem->setCharacterSize(size);
  textItem->setFillColor(colour);
}

