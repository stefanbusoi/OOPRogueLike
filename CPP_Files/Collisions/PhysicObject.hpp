#pragma once
#include "../gameObjectComp.hpp"


class PhysicObject : public GameObject {
  sf::Vector2f m_Acceleration;
  sf::Vector2f m_Speed;
  float m_mass{0.0f};
  float m_friction{0.0f};
  float m_elasticity{0.0f};

public:
  PhysicObject(float mass, float friction, float elasticity);

  std::shared_ptr<GameObject> clone() const override;

  void update(float deltaT) override;

  float getMass() { return m_mass; }
  void setMass(float mass) { m_mass = mass; }

  float getFriction() { return m_friction; }
  void setFriction(float friction) { m_friction = friction; }

  float getElasticity() { return m_elasticity; }
  void setElasticity(float elasticity);

  sf::Vector2f getSpeed() { return m_Speed; }
  void setSpeed(sf::Vector2f speed) { m_Speed = speed; }

  sf::Vector2f getAcceleration() { return m_Acceleration; }
  void setAcceleration(sf::Vector2f acceleration) { m_Acceleration = acceleration; }
};
