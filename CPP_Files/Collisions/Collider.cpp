#include "Collider.h"

#include "CoreFunctionality/Game.hpp"
#include "CoreFunctionality/BaseGameObject.hpp"
#include "PhysicObject.hpp"
#include "Utilityies/TransformUtilityies.hpp"
#include "Exceptions/GameLogicException.hpp"
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

Collider::Collider(ColliderMask mask, GeometryShape shape, const sf::Transform &transform): BaseGameObject("COLLIDER", transform),
                                                                                            m_colliderMask(mask),
                                                                                            m_shape(shape) {
  m_updateOrder = UpdateOrder::Collisions;
}

Collider::~Collider() {
  Game::getInstance()->getColliders().erase(this);
}

void Collider::addGameObjectToGame() {
  BaseGameObject::addGameObjectToGame();
  Game::getInstance()->getColliders().insert(this);
}

void Collider::removeGameObjectFromGame() {
  BaseGameObject::removeGameObjectFromGame();
  Game::getInstance()->getColliders().erase(this);
}


void Collider::update(float deltaTime) {
  (void) deltaTime;
}


std::shared_ptr<BaseGameObject> Collider::clone() const {
  std::shared_ptr<Collider> clone = std::make_shared<Collider>(m_colliderMask, m_shape, m_transform);
  for (std::shared_ptr<BaseGameObject> i: m_children) {
    clone->emplaceClone(i);
  }
  clone->m_name = m_name;
  clone->m_parent.reset();
  clone->m_updateOrder = m_updateOrder;
  clone->m_onCollide = m_onCollide;
  return clone;
}

collisionData Collider::colCircleCircle(const sf::Transform &tr1, const sf::Transform &tr2) {
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

collisionData Collider::CircleInLine(sf::Vector2f pos1, sf::Vector2f pos2, sf::Vector2f CirclePos, float radius) {
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


collisionData Collider::colCircleSquare(const sf::Transform &tr1, const sf::Transform &tr2) {
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
collisionData Collider::checkCollision(const Collider &col1, const Collider &col2) {
  if (col1.m_shape == GeometryShape::Circle && col2.m_shape == GeometryShape::Circle) {
    return colCircleCircle(col1.getGlobalTransform(), col2.getGlobalTransform());
  }
  if (col1.m_shape == GeometryShape::Circle && col2.m_shape == GeometryShape::Rectangle) {
    return colCircleSquare(col1.getGlobalTransform(), col2.getGlobalTransform());
  }
  throw GameLogicException("this collision type is not accepted");
}
