#pragma once

#include <ostream>

#include "CoreFunctionality/BaseGameObject.hpp"
#include "Collisions/PhysicObject.hpp"
#include "Weapons/Firearm.hpp"


class Player : public BaseGameObject {
  void update(float deltaT) override;

  std::shared_ptr<Firearm> m_firearm;
  std::shared_ptr<PhysicObject> m_phisicsObject;

protected:
  void print(std::ostream &os) const override;

public:
  void init() override;

  void addGameObjectToGame() override;

  void removeGameObjectFromGame() override;

  explicit Player(const std::string &name = "NONNAME", const sf::Transform &transform = sf::Transform::Identity);

  Player() = delete;
};
