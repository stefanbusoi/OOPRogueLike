#include "Collider.h"

#include "../Game.hpp"
#include "../GameObject.hpp"
#include "PhysicObject.hpp"
#include "../UtilityiesFunctions.hpp"
int Collider::ColliderMatrix[4][4] = {
  {1,0,1,1},
  {0,0,1,1},
  {1,1,0,1},
  {1,1,1,1}
};
/*
 * player=0
 * Bullets=1,
 * Map=2,
 * Enemy=3,
 */

 Collider::Collider( CollisionType collisionType,
                          ColliderMask mask,GeometryShape shape , const sf::Transform &transform):
      GameObject("COLLIDER",transform),
      m_collisionType(collisionType),
      m_colliderMask(mask),
      m_shape(shape)
    {
    m_updateOrder=UpdateOrder::Collisions;
}

Collider::~Collider() {
   Game::getInstance()->getColliders().erase(this);
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
   (void)deltaTime;
  std::set<Collider*,ColliderComp> colliders = Game::getInstance()->getColliders();
  for (const auto& collider:colliders)
   {
    if (collider->GetId()==this->GetId())
      continue;
    if (ColliderMatrix[(int)collider->m_colliderMask][(int)this->m_colliderMask]==0)
      continue;
    auto collisionData=CheckCollision(*this,*collider);

    if (collisionData.collided==true) {
        auto Obj1=this->m_parent;
        auto Obj2=collider->m_parent;

        auto p1=this->m_parent;
        auto p2=collider->m_parent;

        std::shared_ptr<PhysicObject> Physics1=p1.lock()->GetGameObjectOfType<PhysicObject>();
        std::shared_ptr<PhysicObject> Physics2=p2.lock()->GetGameObjectOfType<PhysicObject>();
/*
      *
            sf::Vector2f relativeVelocity = Physics2->getSpeed() - Physics1->getSpeed();

            float velocityAlongNormal = relativeVelocity.dot( collisionData.normal);

            float e = std::min(Physics1->getElasticity(), Physics2->getElasticity()); // Coefficient of restitution

            float invMass1 = 1.0f / Physics1->getMass();
            float invMass2 = 1.0f / Physics2->getMass();

            float j = -(1 + e) * velocityAlongNormal;
            j /= invMass1 + invMass2;

            sf::Vector2f impulse = j * collisionData.normal;
            Physics1->setSpeed(Physics1->getSpeed() - invMass1 * impulse);
            Physics2->setSpeed(Physics2->getSpeed() + invMass2 * impulse);

 */
      float totalWeight =Physics1->getMass()+Physics2->getMass();
      if (totalWeight==0) totalWeight = 1;//3star: consider an exception

      float move1=Physics2->getMass()/totalWeight;
      float move2=Physics1->getMass()/totalWeight;

      sf::Vector2f speed1=Physics1->getSpeed();
      sf::Vector2f speed2=Physics2->getSpeed();
      sf::Vector2f relativeVelocity = speed2 - speed1;

      float velocityAlongNormal = relativeVelocity.dot( collisionData.normal);

      float e = std::min(Physics1->getElasticity(), Physics2->getElasticity());

      float invMass1 = 1.0f / Physics1->getMass();
      float invMass2 = 1.0f / Physics2->getMass();

      float j = -(1 + e) * velocityAlongNormal;
      j /= invMass1 + invMass2;

      sf::Vector2f impulse = j * collisionData.normal;
      Physics1->setSpeed(Physics1->getSpeed() - invMass1 * impulse);
      Physics2->setSpeed(Physics2->getSpeed() + invMass2 * impulse);

        Obj1.lock()->GlobalMoveTransform(-collisionData.normal*collisionData.penetration*move1);
        Obj2.lock()->GlobalMoveTransform(collisionData.normal*collisionData.penetration*move2);
        if (this->getOnCollide())
          this->getOnCollide()(*this,*collider);
        if (collider->getOnCollide())
          collider->getOnCollide()(*collider,*this);
    }
  }
}


std::shared_ptr<GameObject> Collider::clone() const {
    std::shared_ptr<Collider> clone= std::make_shared<Collider>(m_collisionType,m_colliderMask,m_shape,m_transform);
   for (auto i:m_children) {
     clone->EmplaceClone(i);
   }
   clone->m_name =m_name;
   clone->m_parent.reset();
   clone->m_updateOrder = m_updateOrder;
   clone->m_onCollide=m_onCollide;
   return clone;
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
   /*
   sf::Vector2f pos1=Utils::getPosition(tr1);
   sf::Vector2f pos2=Utils::getPosition(tr2);

   sf::Angle ang1=Utils::getAngle(tr1);
   sf::Angle ang2=Utils::getAngle(tr2);

   sf::Vector2f scale1=Utils::getSize(tr1);
   sf::Vector2f scale2=Utils::getSize(tr2);
*/
   (void)tr1;
   (void)tr2;
   //throw(GameLogicException("Collider::ColCircleSquare not implemented"));
   return collisionData{};
}

collisionData Collider::ColSquareSquare(const sf::Transform &tr1, const sf::Transform &tr2) {
   /*
   sf::Vector2f pos1=Utils::getPosition(tr1);
   sf::Vector2f pos2=Utils::getPosition(tr2);

   sf::Angle ang1=Utils::getAngle(tr1);
   sf::Angle ang2=Utils::getAngle(tr2);

   sf::Vector2f scale1=Utils::getSize(tr1);
   sf::Vector2f scale2=Utils::getSize(tr2);
*/
   (void)tr1;
   (void)tr2;
  //throw(GameLogicException("Collider::ColSqueareSquare not implemented"));
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
      return ColSquareSquare(col1.getGlobalTransform(),col2.getGlobalTransform());
    }
   return collisionData();
}
