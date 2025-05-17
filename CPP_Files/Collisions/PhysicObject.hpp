//
// Created by stefa on 5/4/2025.
//

#ifndef PHYSICOBJECT_HPP
#define PHYSICOBJECT_HPP
#include "../gameObjectComp.hpp"


class PhysicObject:public GameObject {
  sf::Vector2f m_Acceleration;
  sf::Vector2f m_Speed;
  float m_mass;
  float m_friction;
  float m_elasticity;

public:
  PhysicObject(float mass, float friction,float elasticity);

  std::shared_ptr<GameObject> clone() const override;
  void update(float deltaT) override;
  float getMass() {return m_mass;}
  float getFriction() {return m_friction;}
  float getElasticity(){return m_elasticity;}
  sf::Vector2f getSpeed() {return m_Speed;}
  void setSpeed(sf::Vector2f speed) {m_Speed = speed;}
  void setAcceleration(sf::Vector2f acceleration) {m_Acceleration = acceleration;}
};



#endif //PHYSICOBJECT_HPP
