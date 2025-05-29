#pragma once

#include "CoreFunctionality/BaseGameObject.hpp"
#include "SFML/Graphics/Transform.hpp"

#include "Events/GameEvent.hpp"
enum class ColliderMask {
  Player = 0,
  Bullets = 1,
  Map = 2,
  Enemy = 3,
  EnemyBullets = 4
};

enum class GeometryShape {
  Rectangle = 0,
  Circle = 1,
  Line = 2,
};

struct collisionData {
  bool collided{false};
  sf::Vector2f normal{1.0f, 0.0f};
  sf::Vector2f contactPoint{0.0f, 0.0f};
  float penetration{0.0f};

  operator bool() const {
    return collided;
  }
};

class Collider : public BaseGameObject {


public:
  ColliderMask m_colliderMask;
  GeometryShape m_shape;
  GameEvent<Collider&,Collider&> m_onCollide;
  static int ColliderMatrix[5][5];
  Collider(ColliderMask mask, GeometryShape shape, const sf::Transform &transform = sf::Transform::Identity);

  ~Collider();

  void AddGameObjectToGame() override;

  void RemoveGameObjectFromGame() override;

  void update(float deltaT) override;

  std::shared_ptr<BaseGameObject> clone() const override;

  GameEvent<Collider &, Collider &> &getOnCollide() { return m_onCollide; }

  static collisionData CheckCollision(const Collider &col1, const Collider &col2);

  static collisionData ColCircleCircle(const sf::Transform &tr1, const sf::Transform &tr2);

  static collisionData ColCircleLine(const sf::Transform &tr1, const sf::Transform &tr2);

  static collisionData ColCircleSquare(const sf::Transform &tr1, const sf::Transform &tr2);
};
