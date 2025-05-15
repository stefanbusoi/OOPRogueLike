//
// Created by stefa on 5/4/2025.
//

#ifndef FIREARM_HPP
#define FIREARM_HPP
#include <memory>

#include "../GameObject.hpp"


class Firearm:public GameObject {

  std::unique_ptr<GameObject> bulletPrefab;
  float m_speed;
  float m_ang;
  float m_timer;
  float lastShot=0.0f;
  float CurrentTimer=0.0f;

  public:
  void Fire();

  void update(float deltaTime) override;

  Firearm(const std::string& name,sf::Transform transform);
};



#endif //FIREARM_HPP
