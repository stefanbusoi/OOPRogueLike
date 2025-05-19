#pragma once
//
// Created by stefa on 5/19/2025.
//

#include "../GameObject.hpp"
#include "../Player.hpp"


class BasicEnemy :public GameObject{

  std::weak_ptr<Player> player;

  public:
  BasicEnemy(std::string name,sf::Transform transform=sf::Transform::Identity);;
  void update(float deltaTime) override;
  void Init() override;

};

