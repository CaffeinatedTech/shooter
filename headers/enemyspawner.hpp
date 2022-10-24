#ifndef SHOOTER_ENEMYSPAWNER_HPP
#define SHOOTER_ENEMYSPAWNER_HPP


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
