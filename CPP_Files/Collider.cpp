#include "Collider.h"

#include "Game.hpp"
#include "GameObject.hpp"
#include "PhysicObject.hpp"
#include "UtilityiesFunctions.hpp"
#include "Exceptions/GameLogicException.hpp"


 Collider::Collider( CollisionType collisionType,
                          ColliderMask mask,GeometryShape shape , const sf::Transform &transform)
    :
      GameObject("COLLIDER",transform,nullptr),
      m_collisionType(collisionType),
      m_colliderMask(mask),
      m_shape(shape)
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
  for (const auto& collider:colliders)
   {
    if (collider->GetId()==this->GetId())
      continue;
    auto collisionData=CheckCollision(*this,*collider);

    if (collisionData.collided==true) {
        auto Obj1=this->m_parent;
        auto Obj2=collider->m_parent;

        float mass1=0.0f;
        float mass2=0.0f;
        auto p1=this->m_parent;
        auto p2=collider->m_parent;

        for (auto i:p1->getChildrens()) {
          PhysicObject* x=dynamic_cast<PhysicObject*>(i);
          if (x!=nullptr) {
            mass1=x->GetMass();
            break;
          }
        }
        for (auto i:p2->getChildrens()) {
          PhysicObject* x=dynamic_cast<PhysicObject*>(i);
          if (x!=nullptr) {
            mass2=x->GetMass();
            break;
          }
       }


        float totalWeight = mass1+mass2;
        if (totalWeight==0) totalWeight = 1;//3star: consider an exception

        float move1=mass2/totalWeight;
        float move2=mass1/totalWeight;

        Obj1->GlobalMoveTransform(-collisionData.normal*collisionData.penetration*move1);
        Obj2->GlobalMoveTransform(collisionData.normal*collisionData.penetration*move2);
    }
  }

}


GameObject & Collider::Clone() const {
    Collider* clone= new Collider(m_collisionType,m_colliderMask,m_shape,m_transform);
   for (auto i:m_children) {
     clone->EmplaceClone(*i);
   }
   clone->m_name =m_name;
   clone->m_parent = nullptr;
   clone->m_updateOrder = m_updateOrder;
   return *clone;
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
    data.normal = normal.normalized();
    data.penetration = penetration;
    data.contactPoint = pos1 + normal * (radius1 - penetration * 0.5f);
  } else {
    data.collided = false;
  }
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
   return collisionData{};
}

collisionData Collider::ColSqueareSquare(const sf::Transform &tr1, const sf::Transform &tr2) {
  sf::Vector2f pos1=Utils::getPosition(tr1);
  sf::Vector2f pos2=Utils::getPosition(tr2);

  sf::Angle ang1=Utils::getAngle(tr1);
  sf::Angle ang2=Utils::getAngle(tr2);

  sf::Vector2f scale1=Utils::getSize(tr1);
  sf::Vector2f scale2=Utils::getSize(tr2);
  throw(GameLogicException("Collider::ColSqueareSquare not implemented"));
   return collisionData{};
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
