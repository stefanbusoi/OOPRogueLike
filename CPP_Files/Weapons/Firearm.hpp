#pragma once
#include <memory>

#include "CoreFunctionality/BaseGameObject.hpp"


/**
 * projectile weapon used by the player
 */
class Firearm : public BaseGameObject {
  std::shared_ptr<BaseGameObject> bulletPrefab;
  float m_speed=20.0f;
  float m_ang=0.0f;
  float m_timer=0.0f;
  float m_lastShot = 0.0f;
  float m_CurrentTimer = 0.0f;

public:
  Firearm(const std::string &name, sf::Transform transform);

  void fire();

  void update(float deltaTime) override;

  void init() override;
};
