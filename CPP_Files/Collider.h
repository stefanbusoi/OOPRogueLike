#ifndef ICOLIDERABLE_H
#define ICOLIDERABLE_H

#include "GameObject.hpp"
#include "SFML/Graphics/Transform.hpp"


enum class CollisionType{
    Dynamic=1,
    Trigger=2,
};
enum class ColliderMask {
    Player=0,
    Map=1,
    Enemy=2,
};
enum class GeometryShape{
    Square=0,
    Circle=1,
  };
/*
 *5star: make collider work
 *
 */
struct collisionData {
    int x;
};
class Collider:public GameObject{
        sf::Transform m_transform;
        CollisionType m_collisionType;
        ColliderMask m_colliderMask;
        GeometryShape m_shape;
        float m_weight;

    public:
        void AddGameObjectToGame() override;
        void RemoveGameObjectFromGame() override;
        void update(float  deltaT) override;

        collisionData ColCircleCircle(const sf::Transform & Tr1, const sf::Transform & Tr2);

        collisionData ColCircleSquare(const sf::Transform & Tr1, const sf::Transform & Tr2);

        collisionData ColSqueareSquare(const sf::Transform & Tr1, const sf::Transform & Tr2);

        collisionData CheckCollision(Collider col1,Collider col2);
        Collider( CollisionType collisionType,ColliderMask mask,GeometryShape shape,float weight, const sf::Transform &transform=sf::Transform::Identity);
};
#endif //ICOLIDERABLE_H