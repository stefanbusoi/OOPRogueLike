#pragma once
#include <memory>

#include "CoreFunctionality/BaseGameObject.hpp"


class Firearm : public BaseGameObject {
  std::shared_ptr<BaseGameObject> bulletPrefab;
  float m_speed;
  float m_ang;
  float m_timer;
  float lastShot = 0.0f;
  float CurrentTimer = 0.0f;

public:
  Firearm(const std::string &name, sf::Transform transform);

  void Fire();

  void update(float deltaTime) override;

  void Init() override;
};
