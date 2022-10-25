#ifndef SHOOTER_ENEMYSPAWNER_HPP
#define SHOOTER_ENEMYSPAWNER_HPP

/**
 * EnemySpawner class
 * This holds the details for spawning an enemy.  Which enemy configuration to spawn, when and where.
 */
class EnemySpawner {
public:
    int configIndex;
    int positionX;
    int spawnTime; // in seconds

    EnemySpawner(int newConfigIndex, int newPositionX, int newSpawnTime) {
      configIndex = newConfigIndex;
      positionX = newPositionX;
      spawnTime = newSpawnTime;
    }
};


#endif //SHOOTER_ENEMYSPAWNER_HPP
