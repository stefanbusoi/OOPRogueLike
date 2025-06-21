//
// Created by stefa on 5/30/2025.
#pragma once
#include <CoreFunctionality/BaseGameObject.hpp>

/**
 * Spans an entity after a set timer
 */
class EntitySpawner : public BaseGameObject {
  float m_SpawnTimer;
  float m_Time = 0.0f;
  std::shared_ptr<BaseGameObject> m_Entity;

public:
  /**
   *
   * @param transform where to spawn the entity
   * @param Time after what time
   * @param Entity what entity to spawn
   */
  EntitySpawner(sf::Transform transform, float Time, std::shared_ptr<BaseGameObject> Entity);

  void init() override;

  void update(float deltaT) override;
};
