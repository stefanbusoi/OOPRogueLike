#pragma once
#include <memory>

#include "CoreFunctionality/BaseGameObject.hpp"


class Firearm : public BaseGameObject {
  std::shared_ptr<BaseGameObject> bulletPrefab;
  float m_speed;
  float m_ang;
  float m_timer;
  float m_lastShot = 0.0f;
  float m_CurrentTimer = 0.0f;

public:
  Firearm(const std::string &name, sf::Transform transform);

  void fire();

  void update(float deltaTime) override;

  void init() override;
};
