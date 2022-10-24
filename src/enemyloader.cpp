//
// Created by adam on 22/10/22.
//

#include "enemyloader.hpp"
#include <iostream>

EnemyLoader::EnemyLoader() {

}

void EnemyLoader::loadEnemyConfigs() {
  pt::ptree tree;

  const filesystem::path configPath = "assets/enemies";

  std::cout << "--=== LOADING ENEMY CONFIGS ===--" << '\n';

  for (const auto& entry : filesystem::directory_iterator(configPath)) {
    if (entry.path().extension() == ".xml") {
      pt::read_xml(entry.path().native(), tree);
      // Make sure the sprite file is present
      if (exists(filesystem::path("assets/enemies/sprites/" + tree.get<string>("enemy.sprite.file")))) {
        std::cout << entry.path().string() << '\n';
        enemyConfig testEnemy;
        testEnemy.file = tree.get<string>("enemy.sprite.file");
        testEnemy.rotation = tree.get<float>("enemy.sprite.rotation");
        testEnemy.maxHealth = tree.get<int>("enemy.stats.maxHealth");
        testEnemy.scorePerHit = tree.get<int>("enemy.stats.scorePerHit");
        testEnemy.scorePerKill = tree.get<int>("enemy.stats.scorePerKill");
        testEnemy.speed = tree.get<float>("enemy.stats.speed");
        testEnemy.difficulty = tree.get<int>("enemy.stats.difficulty");
        testEnemy.canShoot = tree.get<bool>("enemy.abilities.canShoot");
        testEnemy.shootAtPlayer = tree.get<bool>("enemy.abilities.canShoot");
        testEnemy.gunPositionOffsetX = tree.get<float>("enemy.abilities.gunPositionOffsetX");
        testEnemy.gunPositionOffsetY = tree.get<float>("enemy.abilities.gunPositionOffsetY");
        enemyConfigs.emplace_back(testEnemy);

        // Find minimum and maximum difficulties
        if (testEnemy.difficulty > this->maximumDifficulty) { this->maximumDifficulty = testEnemy.difficulty; }
        if (testEnemy.difficulty < this->minimumDifficulty) { this->minimumDifficulty = testEnemy.difficulty; }
      }
      else { // Sprite file is missing
        std::cout << entry.path().string() << " PASSED - missing sprite file" << '\n';
      }
    }
  }

  std::cout << "--=== FOUND " << to_string(enemyConfigs.size()) << " ENEMY CONFIGURATIONS ===--" << '\n';

  // Sort the configurations from easiest to most difficult.
  sort(enemyConfigs.begin(), enemyConfigs.end(), [](enemyConfig &a, enemyConfig &b) {
      return a.difficulty < b.difficulty;
  });

}

vector<enemyConfig> EnemyLoader::getEnemyConfigs() {
  return this->enemyConfigs;
}

int EnemyLoader::getEnemyTypeCount() {
  return static_cast<int>(this->enemyConfigs.size());
}
