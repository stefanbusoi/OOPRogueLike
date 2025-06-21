//
// Created by fanel012 on 5/31/25.

#include "CoreFunctionality/BaseGameObject.hpp"


/**
 * spawn enemy at fixed interval with speed based on game time
 */
class EnemySpawnerManager : public BaseGameObject {
  float spawnTimer = 0.8;
  float Timer = 0.0;

public:
  EnemySpawnerManager(): BaseGameObject("EntitySpawner", sf::Transform::Identity) {}

  void update(float deltaT) override;
};
