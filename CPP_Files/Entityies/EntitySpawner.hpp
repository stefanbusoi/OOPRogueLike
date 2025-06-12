//
// Created by stefa on 5/30/2025.
//
#pragma once
#include <CoreFunctionality/BaseGameObject.hpp>

class EntitySpawner : public BaseGameObject {
  float m_SpawnTimer;
  float m_Time = 0.0f;
  std::shared_ptr<BaseGameObject> m_Entity;

public:
  EntitySpawner(sf::Transform transform, float Time, std::shared_ptr<BaseGameObject> Entity);

  void init() override;

  void update(float deltaT) override;
};
