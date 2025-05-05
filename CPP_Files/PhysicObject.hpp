//
// Created by stefa on 5/4/2025.
//

#ifndef PHYSICOBJECT_HPP
#define PHYSICOBJECT_HPP
#include "gameObjectComp.hpp"


class PhysicObject:public GameObject {
  sf::Vector2f m_Acceleration;
  sf::Vector2f m_Speed;
  float m_mass;
  float m_friction;

public:
  PhysicObject(float mass, float friction);

  GameObject& Clone() const override;
  void update(float deltaT) override;
  float GetMass() {return m_mass;}
  float GetFriction() {return m_friction;}
  void SetSpeed(sf::Vector2f speed) {m_Speed = speed;}
  void SetAcceleration(sf::Vector2f acceleration) {m_Acceleration = acceleration;}
};



#endif //PHYSICOBJECT_HPP
