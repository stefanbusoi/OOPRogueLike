
#include "BasicEnemy.hpp"
#include "../Collisions/Collider.h"
#include "../Render/ShapeRenderer.hpp"

BasicEnemy::BasicEnemy(std::string name, sf::Transform transform):GameObject(name,transform) {

  }

void BasicEnemy::update(float deltaTime) {
  GameObject::update(deltaTime);
}

void BasicEnemy::Init() {
    sf::Transform transform= sf::Transform::Identity;
    transform.scale({40.0f, 40.0f});
    EmplaceGameObject<Collider>(ColliderMask::Enemy,GeometryShape::Circle, transform);
    EmplaceGameObject<ShapeRenderer>("ShapeRenderer",transform,sf::Color(230,230,230),RenderOrder::Player,GeometryShape::Circle);

  }


