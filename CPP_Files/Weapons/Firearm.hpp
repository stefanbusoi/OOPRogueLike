//
// Created by stefa on 5/4/2025.
//

#ifndef FIREARM_HPP
#define FIREARM_HPP
#include <memory>

#include "../GameObject.hpp"


class Firearm:public GameObject {

  std::shared_ptr<GameObject> bulletPrefab;
  float m_speed;
  float m_ang;
  float m_timer;
  float lastShot=0.0f;
  float CurrentTimer=0.0f;

  public:

  Firearm(const std::string& name,sf::Transform transform);

  void Fire();
  void update(float deltaTime) override;
  void Init() override;

};



#endif //FIREARM_HPP
