#include "Collider.h"

#include "Game.hpp"
#include "GameObject.hpp"
#include "UtilityiesFunctions.hpp"


inline Collider::Collider( CollisionType collisionType,
                           ColliderMask mask,GeometryShape shape ,float weight, const sf::Transform &transform)
    :
      m_transform(transform),
      m_collisionType(collisionType),
      m_colliderMask(mask),
      m_shape(shape),
      m_weight(weight)
    {

    m_updateOrder=UpdateOrder::Collisions;
}
void Collider::AddGameObjectToGame(){
  GameObject::AddGameObjectToGame();
  Game::getInstance()->getColliders().insert(this);
}

void Collider::RemoveGameObjectFromGame(){
  GameObject::RemoveGameObjectFromGame();
  Game::getInstance()->getColliders().erase(this);
}
void Collider::update(float deltaTime) {
  std::set<Collider*>& colliders = Game::getInstance()->getColliders();
  for (const auto& collider:colliders) {
    auto x=CheckCollision(*this,*collider);
  }

}

collisionData Collider::ColCircleCircle(const sf::Transform &tr1, const sf::Transform &tr2) {
    sf::Vector2f pos1=Utils::getPosition(tr1);
    sf::Vector2f pos2=Utils::getPosition(tr2);

    sf::Angle ang1=Utils::getAngle(tr1);
    sf::Angle ang2=Utils::getAngle(tr2);

    sf::Vector2f scale1=Utils::getSize(tr1);
    sf::Vector2f scale2=Utils::getSize(tr2);
}

collisionData Collider::ColCircleSquare(const sf::Transform &tr1, const sf::Transform &tr2) {
  sf::Vector2f pos1=Utils::getPosition(tr1);
  sf::Vector2f pos2=Utils::getPosition(tr2);

  sf::Angle ang1=Utils::getAngle(tr1);
  sf::Angle ang2=Utils::getAngle(tr2);

  sf::Vector2f scale1=Utils::getSize(tr1);
  sf::Vector2f scale2=Utils::getSize(tr2);
}

collisionData Collider::ColSqueareSquare(const sf::Transform &tr1, const sf::Transform &tr2) {
  sf::Vector2f pos1=Utils::getPosition(tr1);
  sf::Vector2f pos2=Utils::getPosition(tr2);

  sf::Angle ang1=Utils::getAngle(tr1);
  sf::Angle ang2=Utils::getAngle(tr2);

  sf::Vector2f scale1=Utils::getSize(tr1);
  sf::Vector2f scale2=Utils::getSize(tr2);
}

collisionData Collider::CheckCollision(Collider col1,Collider col2) {
    if (col1.m_shape==GeometryShape::Circle && col2.m_shape==GeometryShape::Circle) {
        return ColCircleCircle(col1.getGlobalTransform(),col2.getGlobalTransform());
    }
    if (col1.m_shape==GeometryShape::Circle && col2.m_shape==GeometryShape::Square) {
        return ColCircleSquare(col1.getGlobalTransform(),col2.getGlobalTransform());
    }
    if (col1.m_shape==GeometryShape::Square && col2.m_shape==GeometryShape::Circle) {
        return ColCircleSquare(col2.getGlobalTransform(),col1.getGlobalTransform());
    }
    if (col1.m_shape==GeometryShape::Square && col2.m_shape==GeometryShape::Square) {
      return ColSqueareSquare(col1.getGlobalTransform(),col2.getGlobalTransform());
    }
}
