#pragma once

#include <ostream>

#include "CoreFunctionality/BaseGameObject.hpp"
#include "Collisions/PhysicObject.hpp"
#include "Weapons/Firearm.hpp"


class Player : public BaseGameObject {
  float m_DashCooldown = 1.0f;
  float m_CurrentCooldown = 0.0f;

  void update(float deltaT) override;

  std::shared_ptr<Firearm> m_firearm;
  std::shared_ptr<PhysicObject> m_phisicsObject;

protected:
  void print(std::ostream &os) const override;

public:
  float getDashCurrentCooldown() const { return m_CurrentCooldown; }
  float getDashTotalCooldown() const { return m_DashCooldown; }

  void init() override;

  void addGameObjectToGame() override;

  void PlayerMovement(float deltaT);

  void removeGameObjectFromGame() override;

  explicit Player(const std::string &name = "NONNAME", const sf::Transform &transform = sf::Transform::Identity);

  Player() = delete;
};
