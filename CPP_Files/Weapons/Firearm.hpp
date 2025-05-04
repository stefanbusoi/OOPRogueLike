//
// Created by stefa on 5/4/2025.
//

#ifndef FIREARM_HPP
#define FIREARM_HPP
#include "../GameObject.hpp"


class Firearm:public GameObject {

  GameObject* bullet;
  public:
  void Fire() {

  }
  Firearm(const std::string& name,sf::Transform transform);
};



#endif //FIREARM_HPP
