#include "Collider.h"

#include "Game.hpp"
#include "GameObject.hpp"
#include "UtilityiesFunctions.hpp"
#include "Exceptions/GameLogicException.hpp"


 Collider::Collider( CollisionType collisionType,
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
  std::set<Collider*,ColliderComp>& colliders = Game::getInstance()->getColliders();
  for (const auto& collider:colliders) {
    if (collider->GetId()==this->GetId())
      continue;
    auto collisionData=CheckCollision(*this,*collider);
    if (collisionData.collided==true) {
      //5star: solve this code
        auto Obj1=this->m_parent;
        auto Obj2=collider->m_parent;
        Obj1->getLocalTransform().translate(collisionData.normal*collisionData.penetration/2.0f);
        Obj2->getLocalTransform().translate(-collisionData.normal*collisionData.penetration/2.0f);
    }
  }

}
collisionData Collider::ColCircleCircle(const sf::Transform &tr1, const sf::Transform &tr2) {
    sf::Vector2f pos1=Utils::getPosition(tr1);
    sf::Vector2f pos2=Utils::getPosition(tr2);

    sf::Vector2f scale1=Utils::getSize(tr1);
    sf::Vector2f scale2=Utils::getSize(tr2);

    float radius1 = scale1.x;
    float radius2 = scale2.x;

    sf::Vector2f delta = pos2 - pos1;
    float distanceSquared = delta.x * delta.x + delta.y * delta.y;
    float radiusSum = radius1 + radius2;

  collisionData data;
  if (distanceSquared <= radiusSum * radiusSum) {
    float distance = std::sqrt(distanceSquared);
    sf::Vector2f normal = (distance != 0) ? delta / distance : sf::Vector2f(1.f, 0.f); // default normal if overlap perfectly
    float penetration = radiusSum - distance;

    data.collided = true;
    data.normal = normal;
    data.penetration = penetration;
    data.contactPoint = pos1 + normal * (radius1 - penetration * 0.5f);
  } else {
    data.collided = false;
  }
  std::cout << data.collided << std::endl;
  return data;
}

collisionData Collider::ColCircleSquare(const sf::Transform &tr1, const sf::Transform &tr2) {
  sf::Vector2f pos1=Utils::getPosition(tr1);
  sf::Vector2f pos2=Utils::getPosition(tr2);

  sf::Angle ang1=Utils::getAngle(tr1);
  sf::Angle ang2=Utils::getAngle(tr2);

  sf::Vector2f scale1=Utils::getSize(tr1);
  sf::Vector2f scale2=Utils::getSize(tr2);
  throw(GameLogicException("Collider::ColCircleSquare not implemented"));
}

collisionData Collider::ColSqueareSquare(const sf::Transform &tr1, const sf::Transform &tr2) {
  sf::Vector2f pos1=Utils::getPosition(tr1);
  sf::Vector2f pos2=Utils::getPosition(tr2);

  sf::Angle ang1=Utils::getAngle(tr1);
  sf::Angle ang2=Utils::getAngle(tr2);

  sf::Vector2f scale1=Utils::getSize(tr1);
  sf::Vector2f scale2=Utils::getSize(tr2);
  throw(GameLogicException("Collider::ColSqueareSquare not implemented"));
}

collisionData Collider::CheckCollision(const Collider& col1,const Collider& col2) {
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
