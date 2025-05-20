#include "Collider.h"

#include "../Game.hpp"
#include "../GameObject.hpp"
#include "PhysicObject.hpp"
#include "../Utilityies/TransformUtilityies.hpp"
#include "../Exceptions/GameLogicException.hpp"
int Collider::ColliderMatrix[5][5] = {
  {1, 0, 1, 1, 1},
  {0, 0, 1, 1, 0},
  {1, 1, 0, 1, 1},
  {1, 1, 1, 1, 0},
  {1, 0, 1, 0, 0}
};
/*
 * player=0
 * Bullets=1,
 * Map=2,
 * Enemy=3,
 * EnemyBullets=4,
 */

Collider::Collider(ColliderMask mask, GeometryShape shape, const sf::Transform &transform): GameObject("COLLIDER", transform),
                                                                                            m_colliderMask(mask),
                                                                                            m_shape(shape) {
  m_updateOrder = UpdateOrder::Collisions;
}

Collider::~Collider() {
  Game::getInstance()->getColliders().erase(this);
}

void Collider::AddGameObjectToGame() {
  GameObject::AddGameObjectToGame();
  Game::getInstance()->getColliders().insert(this);
}

void Collider::RemoveGameObjectFromGame() {
  GameObject::RemoveGameObjectFromGame();
  Game::getInstance()->getColliders().erase(this);
}


void Collider::update(float deltaTime) {
  (void) deltaTime;
  //I want to copy because there is a chance that inside this for are deleted colliders
  std::set<Collider *, ColliderComp> colliders = Game::getInstance()->getColliders();
  for (const auto &collider: colliders) {
    std::shared_ptr<GameObject> parent1 = this->m_parent.lock();
    std::shared_ptr<GameObject> parent2 = collider->m_parent.lock();

    //If is inside colliders
    if (!Game::getInstance()->getColliders().contains(collider)) {
      continue;
    }
    //if this is inside colliders
    if (!Game::getInstance()->getColliders().contains(this)) {
      break;
    }
    //if the parent is the same don t check collisions
    if (parent2->GetId() == parent1->GetId())
      continue;

    //check if the collision shoud happen;
    if (ColliderMatrix[(int) collider->m_colliderMask][(int) this->m_colliderMask] == 0)
      continue;


    std::shared_ptr<PhysicObject> Physics1 = parent1->GetGameObjectOfType<PhysicObject>();
    if (Physics1 == nullptr)
      continue;
    std::weak_ptr<PhysicObject> Physics2Weak = parent2->GetGameObjectOfType<PhysicObject>();

    auto collisionData = CheckCollision(*this, *collider);

    if (collisionData.collided == true) {
      //If Physics2Weak is expired then the second object is static
      if (Physics2Weak.expired()) {
        sf::Vector2f relativeVelocity = Physics1->getSpeed();

        float velocityAlongNormal = relativeVelocity.dot(collisionData.normal);

        float e = Physics1->getElasticity();

        float invMass1 = 1.0f / Physics1->getMass();

        float j = -(1 + e) * velocityAlongNormal;

        sf::Vector2f impulse = j * collisionData.normal;
        Physics1->setSpeed(Physics1->getSpeed() + invMass1 * impulse);

        parent1->GlobalMoveTransform(-collisionData.normal * collisionData.penetration);
      } else {
        std::shared_ptr<PhysicObject> Physics2 = Physics2Weak.lock();
        float totalWeight = Physics1->getMass() + Physics2->getMass();
        if (totalWeight == 0) totalWeight = 1;

        float move1 = Physics2->getMass() / totalWeight;
        float move2 = Physics1->getMass() / totalWeight;

        sf::Vector2f speed1 = Physics1->getSpeed();
        sf::Vector2f speed2 = Physics2->getSpeed();
        sf::Vector2f relativeVelocity = speed2 - speed1;

        float velocityAlongNormal = relativeVelocity.dot(collisionData.normal);

        float e = std::min(Physics1->getElasticity(), Physics2->getElasticity());

        float invMass1 = 1.0f / Physics1->getMass();
        float invMass2 = 1.0f / Physics2->getMass();

        float j = -(1 + e) * velocityAlongNormal;
        j /= invMass1 + invMass2;

        sf::Vector2f impulse = j * collisionData.normal;
        Physics1->setSpeed(Physics1->getSpeed() - invMass1 * impulse);
        Physics2->setSpeed(Physics2->getSpeed() + invMass2 * impulse);

        parent1->GlobalMoveTransform(-collisionData.normal * collisionData.penetration * move1);
        parent2->GlobalMoveTransform(collisionData.normal * collisionData.penetration * move2);
      }
      if (this->getOnCollide())
        this->getOnCollide()(*this, *collider);
      if (collider->getOnCollide())
        collider->getOnCollide()(*collider, *this);
    } //If collided==true;
  } //For each Game Object
}


std::shared_ptr<GameObject> Collider::clone() const {
  std::shared_ptr<Collider> clone = std::make_shared<Collider>(m_colliderMask, m_shape, m_transform);
  for (std::shared_ptr<GameObject> i: m_children) {
    clone->EmplaceClone(i);
  }
  clone->m_name = m_name;
  clone->m_parent.reset();
  clone->m_updateOrder = m_updateOrder;
  clone->m_onCollide = m_onCollide;
  return clone;
}

collisionData Collider::ColCircleCircle(const sf::Transform &tr1, const sf::Transform &tr2) {
  sf::Vector2f pos1 = Utils::getPosition(tr1);
  sf::Vector2f pos2 = Utils::getPosition(tr2);

  sf::Vector2f scale1 = Utils::getSize(tr1);
  sf::Vector2f scale2 = Utils::getSize(tr2);

  float radius1 = scale1.x;
  float radius2 = scale2.x;

  sf::Vector2f delta = pos2 - pos1;
  float distanceSquared = delta.lengthSquared();
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

collisionData PointInsideCircle(sf::Vector2f pointPos, sf::Vector2f CirclePos, float radius) {
  collisionData data;
  sf::Vector2f DeltaPos = CirclePos - pointPos;
  if (DeltaPos.lengthSquared() < radius * radius) {
    float distance = DeltaPos.length();
    sf::Vector2f normal = (distance != 0) ? DeltaPos / distance : sf::Vector2f(1.f, 0.f); // default normal if overlap perfectly
    float penetration = radius - distance;
    data.collided = true;
    data.normal = normal.normalized();
    data.penetration = penetration;
    data.contactPoint = pointPos + normal * (radius - penetration * 0.5f);
  } else {
    data.collided = false;
  }


  return data;
}

collisionData CircleInLine(sf::Vector2f pos1, sf::Vector2f pos2, sf::Vector2f CirclePos, float radius) {
  sf::Vector2f deltaPos1 = CirclePos - pos1;
  sf::Vector2f LineDir = pos2 - pos1;

  float a = LineDir.lengthSquared();
  float b = -2.0 * LineDir.dot(deltaPos1);
  float c = deltaPos1.lengthSquared() - radius * radius;
  auto discriminant = b * b - 4 * a * c;
  float dist = -b / (2 * a);
  if (discriminant < 0 || dist < 0 || dist > 1) {
    return collisionData{};
  }
  collisionData data;
  data.collided = true;
  data.contactPoint = pos1 + LineDir * dist;
  data.normal = sf::Vector2f(LineDir.y, -LineDir.x).normalized();
  data.penetration = radius - (data.contactPoint - CirclePos).length();
  return data;
}

collisionData Collider::ColCircleLine(const sf::Transform &tr1, const sf::Transform &tr2) {
  (void)tr1;
  (void)tr2;
  //sf::Vector2f pos1 = Utils::getPosition(tr1);
 // float radius1 = Utils::getSize(tr1).x;

  //sf::Vector2f RelPoint2_1 = tr2.transformPoint({0.0f, 0.0f}) - pos1;
  //sf::Vector2f RelPoint2_2 = tr2.transformPoint({1.0f, 0.0f}) - pos1;
  //sf::Vector2f RelPoint2_3 = tr2.transformPoint({1.0f, 1.0f}) - pos1;
  //sf::Vector2f RelPoint2_4 = tr2.transformPoint({1.0f, 1.0f}) - pos1;
  collisionData data;


  return data;
}

collisionData Collider::ColCircleSquare(const sf::Transform &tr1, const sf::Transform &tr2) {
  sf::Vector2f pos1 = Utils::getPosition(tr1);
  float radius1 = Utils::getSize(tr1).x;

  sf::Vector2f RelPoint2_1 = tr2.transformPoint({-0.5f, -0.5f});
  sf::Vector2f RelPoint2_2 = tr2.transformPoint({0.5f, -0.5f});
  sf::Vector2f RelPoint2_3 = tr2.transformPoint({0.5f, 0.5f});
  sf::Vector2f RelPoint2_4 = tr2.transformPoint({-0.5f, 0.5f});
  collisionData data = PointInsideCircle(pos1, RelPoint2_1, radius1);
  collisionData PointColdata;

  PointColdata = PointInsideCircle(pos1, RelPoint2_2, radius1);
  if (PointColdata.penetration > data.penetration)
    data = PointColdata;

  PointColdata = PointInsideCircle(pos1, RelPoint2_3, radius1);
  if (PointColdata.penetration > data.penetration)
    data = PointColdata;

  PointColdata = PointInsideCircle(pos1, RelPoint2_4, radius1);
  if (PointColdata.penetration > data.penetration)
    data = PointColdata;

  PointColdata = CircleInLine(RelPoint2_2, RelPoint2_1, pos1, radius1);
  if (PointColdata.penetration > data.penetration)
    data = PointColdata;

  PointColdata = CircleInLine(RelPoint2_3, RelPoint2_2, pos1, radius1);
  if (PointColdata.penetration > data.penetration)
    data = PointColdata;

  PointColdata = CircleInLine(RelPoint2_4, RelPoint2_3, pos1, radius1);
  if (PointColdata.penetration > data.penetration)
    data = PointColdata;

  PointColdata = CircleInLine(RelPoint2_1, RelPoint2_4, pos1, radius1);
  if (PointColdata.penetration > data.penetration)
    data = PointColdata;


  return data;
}

collisionData Collider::CheckCollision(const Collider &col1, const Collider &col2) {
  if (col1.m_shape == GeometryShape::Circle && col2.m_shape == GeometryShape::Circle) {
    return ColCircleCircle(col1.getGlobalTransform(), col2.getGlobalTransform());
  }
  if (col1.m_shape == GeometryShape::Circle && col2.m_shape == GeometryShape::Rectangle) {
    return ColCircleSquare(col1.getGlobalTransform(), col2.getGlobalTransform());
  }
  if (col1.m_shape == GeometryShape::Circle && col2.m_shape == GeometryShape::Line) {
    return ColCircleLine(col2.getGlobalTransform(), col1.getGlobalTransform());
  }
  throw GameLogicException("this collision type is not accepted");
}
