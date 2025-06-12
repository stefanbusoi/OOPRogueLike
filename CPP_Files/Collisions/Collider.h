#pragma once

#include "CoreFunctionality/BaseGameObject.hpp"
#include "SFML/Graphics/Transform.hpp"

#include "Events/GameEvent.hpp"
/**
 * All masks for colliders
 */
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

/**
 * Data about collision between 2 objects
 */
struct collisionData {
  bool collided{false};
  sf::Vector2f normal{1.0f, 0.0f};
  sf::Vector2f contactPoint{0.0f, 0.0f};
  float penetration{0.0f};

  operator bool() const {
    return collided;
  }
};

/**
 * A GameObject witch can colide with other objects, needs an active ColliderManager to work
 */
class Collider : public BaseGameObject {
  GameEvent<Collider&,Collider&> m_onCollide;
  ColliderMask m_colliderMask;
  GeometryShape m_shape;
public:

  static int ColliderMatrix[5][5];
  /**
   *
   * @param mask masks of the collider
   * @param shape shape of the collider
   * @param transform position of the collider
   */
  Collider(ColliderMask mask, GeometryShape shape, const sf::Transform &transform = sf::Transform::Identity);

  ~Collider();

  void addGameObjectToGame() override;

  void removeGameObjectFromGame() override;

  void update(float deltaT) override;

  std::shared_ptr<BaseGameObject> clone() const override;

  /**
   *
   * @return an Game Event witch is triggered when a collision happen, the first paramater is always this object
   */
  GameEvent<Collider &, Collider &> &getOnCollide() { return m_onCollide; }
  /**
   *
   * @return Mask of the collider
   */
  ColliderMask getColliderMask(){return m_colliderMask;}
  /**
   *
   * @param col1 the first collider
   * @param col2 the second collider
   * @return collisionData from the collision of these 2 objects
   */
  static collisionData checkCollision(const Collider &col1, const Collider &col2);

  /**
   *
   * @param tr1 the transfrom of the first object in global space
   * @param tr2 the transform of the second object in global scpae
   * @return colisionData from the collisions of these 2 circles
   */
  static collisionData colCircleCircle(const sf::Transform &tr1, const sf::Transform &tr2);


  /**
   * Important: it dosen t check the ends of the line
   * @param pos1 position of the first point of the line
   * @param pos2 position of the second point of the line
   * @param CirclePos position of the circle
   * @param radius radius of the circle
   * @return collisionData from the collision
   */
  static collisionData CircleInLine(sf::Vector2f pos1, sf::Vector2f pos2, sf::Vector2f CirclePos, float radius);

  /**
    *
    * @param tr1 the transfrom of the circle in global space
    * @param tr2 the transform of the square in global scpae(it can be a rectangle if the scale is not uniform)
    * @return colisionData from the collisions
    */
  static collisionData colCircleSquare(const sf::Transform &tr1, const sf::Transform &tr2);
};
