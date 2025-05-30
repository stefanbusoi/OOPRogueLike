#pragma once
//
// Created by stefa on 5/19/2025.
//

#include "CoreFunctionality/BaseGameObject.hpp"
#include "Player.hpp"


class BasicEnemy :public BaseGameObject{

  std::weak_ptr<Player> player;
  std::weak_ptr<PhysicObject> physicObject;
  float movementSpeed=500.0f;
  public:
  BasicEnemy(std::string name,sf::Transform transform=sf::Transform::Identity);
  void update(float deltaTime) override;
  void Init() override;

  std::shared_ptr<BaseGameObject> clone() const override;
};

