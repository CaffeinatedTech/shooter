#include <random>
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

  // Setup Text objects
  setupFont(&scoreText, mainFont, std::to_string(displayedScore), 72, Color::Green);
  FloatRect scoreTextBounds = scoreText.getLocalBounds();
  scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 20, 0));

  setupFont(&intermissionWaveLabel, mainFont, "Waves Completed: ", 72, Color::Blue);
  FloatRect intermissionWaveLabelBounds = intermissionWaveLabel.getLocalBounds();
  intermissionWaveLabel.setPosition(Vector2f((resolution.x / 2 - intermissionWaveLabelBounds.width) + 200, 600));

  setupFont(&intermissionWaveValue, mainFont, "9", 72, Color::Green);
  intermissionWaveValue.setPosition(Vector2f(resolution.x / 2 + 250, 600));

  setupFont(&intermissionTimer, mainFont, "Next Wave: 9", 120, Color::Yellow);
  FloatRect intermissionTimerBounds = intermissionTimer.getLocalBounds();
  intermissionTimer.setPosition(Vector2f(resolution.x / 2 - intermissionTimerBounds.width / 2, 300));

  setupFont(&intermissionWaveKillsLabel, mainFont, "Last Wave Kills: ", 72, Color::Blue);
  FloatRect intermissionWaveKillsLabelBounds = intermissionWaveKillsLabel.getLocalBounds();
  intermissionWaveKillsLabel.setPosition(Vector2f((resolution.x / 2 - intermissionWaveKillsLabelBounds.width) + 200, 680));

  setupFont(&intermissionWaveKillsValue, mainFont, "9", 72, Color::Green);
  intermissionWaveKillsValue.setPosition(Vector2f(resolution.x / 2 + 250, 680));

  setupFont(&intermissionWaveScoreLabel, mainFont, "Last Wave Score: ", 72, Color::Blue);
  FloatRect intermissionWaveScoreLabelBounds = intermissionWaveScoreLabel.getLocalBounds();
  intermissionWaveScoreLabel.setPosition(Vector2f((resolution.x / 2 - intermissionWaveScoreLabelBounds.width) + 200, 760));

  setupFont(&intermissionWaveScoreValue, mainFont, "9", 72, Color::Green);
  intermissionWaveScoreValue.setPosition(Vector2f(resolution.x / 2 + 250, 760));

  intermissionTime = 6; // Number of seconds between waves
  runningTime = Time::Zero;
  waveTime = Time::Zero;
  intermissionRunningTime = Time::Zero;

  // Set game state to running
  gameState = STATE::RUNNING;
  previousGameState = gameState;
  waveRunning = true;
  waveNumber = 1;
  waveKills = 0;
  waveScore = 0;

  enemyLoader.loadEnemyConfigs();
  enemyWeightsReset();
  enemyList = generateNextWave(waveNumber);

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
    if (waveRunning) {
      waveTime += dt;
    }
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

void Engine::enemyWeightsReset() {
  this->enemyWeights.clear();
  int weightToDistribute = 100;
  for (int i = 0; i < enemyLoader.getEnemyTypeCount(); i++) {
    this->enemyWeights.push_back(weightToDistribute);
    weightToDistribute = 0;
  }
}

vector<EnemySpawner> Engine::generateNextWave(int newWaveNumber) {
  vector<EnemySpawner> newEnemyList;

  // Update enemy weights
  if (newWaveNumber > 1) {
    for (int e = enemyLoader.getEnemyTypeCount() - 1; e >= 0; e--) {
      if (e > 0) {
        if (enemyWeights[e - 1] >= 10 - (e+1)) {
          enemyWeights[e - 1] -= 10 - (e+1);
          enemyWeights[e] += 10 - (e+1);
        }
      }
    }
  }

  // Generate an enemy list
  srand ((unsigned) time(nullptr));
  int randomXPos;
  int spawnTime = 0;
  int enemyToSpawn = 1;
  random_device rd;
  mt19937 gen(rd());
  discrete_distribution<int> d (enemyWeights.begin(), enemyWeights.end());
  for (int i = 0; i < 12; i ++) {
    randomXPos = rand() % (levelWidth - 200) + 100;
    spawnTime += rand() % (3000) + 1;
    enemyToSpawn = d(gen);
    newEnemyList.emplace_back(enemyToSpawn, randomXPos, spawnTime);
  }
  return newEnemyList;
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

