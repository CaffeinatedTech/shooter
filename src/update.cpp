#include "engine.hpp"
#include <sstream>
#include <iostream>
#include <cmath>

using namespace sf;

void Engine::update(Time dt) {

  player.update(dt, resolution, levelWidth);

  // Scroll Background
  if (backgroundY < resolution.y) {
    backgroundY -= backgroundSpeed * dt.asMilliseconds();
  }
  else {
    backgroundY = 0;
  }
  backgroundSprite.setTextureRect(IntRect(0, backgroundY, levelWidth, resolution.y));

  // Set MainView position limiting it to the size of the level
  Vector2f newMainViewPos;
  newMainViewPos.x = player.getCenterPosition().x;
  if (newMainViewPos.x - resolution.x / 2 < 0) {
    newMainViewPos.x = resolution.x / 2;
  }
  if (newMainViewPos.x + (resolution.x / 2) > (float) levelWidth) {
    newMainViewPos.x = (float) levelWidth - resolution.x / 2;
  }
  newMainViewPos.y = mainView.getCenter().y;
  mainView.setCenter(newMainViewPos);

  // Player Shooting
  if (player.getShooting()) {
    // Don't shoot too often
    if (player.getShootClock().asMilliseconds() > player.getShootSpeed()) {
      bullets.emplace_back(true, player.getShootPosition(), Bullet::LASER1, false, Vector2f(0.0f, 1.0f));
      player.restartShootClock();
    }
  }

  // Check if player ship colliding with enemy
  for (int e = 0; e < enemies.size(); e++) {
    if (player.getSprite().getGlobalBounds().intersects(enemies[e].getSprite().getGlobalBounds())) {
      // Player hit an enemy
      bool playerIsDead = player.takeDamage(20); // Magic number, some enemies should be big enough to kill the player outright.

      // Destroy the enemy and increment the score - you did get a kill after all.
      long long unsigned int thisCollisionScore = enemies[e].getScorePerKill();
      player.increaseScore(thisCollisionScore);
      waveScore += thisCollisionScore;
      waveKills++;
      enemies.erase(enemies.begin() + e);
      if (playerIsDead) {
        setGameState(GAMEOVER);
      }
      continue;
    }
  }

  // Process Bullets
  for (int i = 0; i < bullets.size(); i++) {
    if (bullets[i].getPosition().y < -150) {
      bullets.erase(bullets.begin() + i);
      continue;
    }
    else if (bullets[i].getPosition().y > this->resolution.y + 50) {
      bullets.erase(bullets.begin() + i);
    }

    bullets[i].update(dt, this->resolution, this->resolution.y);

    // Check for collisions
    // Player Bullets
    if (bullets[i].getIsPlayerBullet()) {
      for (int e = 0; e < enemies.size(); e++) {
        if (bullets[i].getSprite().getGlobalBounds().intersects(enemies[e].getSprite().getGlobalBounds())) {
          // Bullet hit enemy
          long long unsigned int thisHitScore = enemies[e].takeDamage(5);
          player.increaseScore(thisHitScore);
          waveScore += thisHitScore;
          bullets.erase(bullets.begin() + i);
          if (enemies[e].getDead()) {
            waveKills++;
            enemies.erase(enemies.begin() + e);
          }
          continue;
        }
      }
    }
    else { // Enemy Bullet
      if (bullets[i].getSprite().getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {
        bool playerIsDead = player.takeDamage(20); // Magic number, some bullet types should do more damage
        if (playerIsDead) {
          setGameState(GAMEOVER);
        }
        bullets.erase(bullets.begin() + i);
      }
    }
  }

  // Process Enemies
  for (int i = 0; i < enemies.size(); i++) {
    enemies[i].update(dt, this->resolution);
    // Enemy shooting
    bool allowShoot = false;
    if (enemies[i].getCanShoot()) {
      if (enemies[i].getShootClock().asMilliseconds() > enemies[i].getShootSpeed()) {
        allowShoot = true;
      }
    }
    if (allowShoot) {
      bullets.emplace_back(Bullet(false, enemies[i].getShootPosition(), Bullet::LASER1, enemies[i].getShootAtPlayer(), player.getCenterPosition()));
      enemies[i].restartShootClock();
    }

    // Check if enemy is below the screen, and delete it
    if (enemies[i].getPosition().y > resolution.y + 150) {
      enemies.erase(enemies.begin() + i);
    }
  }

  // Update score text
  if (displayedScore != player.getScore()) {
    displayedScore = player.getScore();
    scoreText.setString(to_string(displayedScore));
    FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 20, 0));
  }

  // Check if Enemy Spawn list is empty, and there are no more enemies on the level - player has reached the end of the wave.
  if (enemyList.empty() && enemies.empty()) {
    waveNumber ++;
    waveTime = Time::Zero;
    enemyList = generateNextWave(waveNumber);

    // TODO - add intermission and trigger it here.
  }

  // Process Enemy Spawn List
  if (waveRunning) {
    for (int i = 0; i < enemyList.size(); i++) {
      if (waveTime.asMilliseconds() >= enemyList[i].spawnTime) {
        enemies.emplace_back(Vector2f(static_cast<float>(enemyList[i].positionX), -100), enemyLoader.getEnemyConfigs()[enemyList[i].configIndex]);
        enemyList.erase(enemyList.begin() + i);
      }
      else {
        // There must not be any enemies with spawn times less than or equal to the running time.
        // So don't bother iterating the rest of the list.
        break;
      }
    }
  }

  // Update player health bar
  float newPlayerHealthBarWidth = (player.getHealth() / 100.f) * 300.f;
  if (newPlayerHealthBarWidth < 0) { newPlayerHealthBarWidth - 0.f; }
  playerHealthBar.setSize(Vector2f(newPlayerHealthBarWidth, playerHealthBar.getSize().y));

  stringstream ss;
  for (auto& conf: enemyList) {
    ss << enemyLoader.getEnemyConfigs()[conf.configIndex].difficulty << ", ";
  }
  ss << " | ";
  ss << "Enemy Weights: " << enemyWeights[0] << "," << enemyWeights[1] << "," << enemyWeights[2] << " | Enemies: " << enemies.size() << " | ";
  ss << bullets.size();

  cout << ss.str() << " bullets" << " | SCORE:  " << player.getScore() << " | HEALTH: " << player.getHealth() << " | " << endl;

} // END update
