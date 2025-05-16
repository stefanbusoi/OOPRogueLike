#pragma once
#include <functional>

#include "../GameObject.hpp"
#include "SFML/Graphics/Transform.hpp"


enum class CollisionType{
    Dynamic=0,
    Trigger=1,
    Static=2,
};
enum class ColliderMask {
    Player=0,
    Bullets=1,
    Map=2,
    Enemy=3,
};

enum class GeometryShape{
    Square=0,
    Circle=1,
  };

struct collisionData {
    bool collided;
    sf::Vector2f normal;
    sf::Vector2f contactPoint;
    float penetration;
};
class Collider:public GameObject{
        CollisionType m_collisionType;
        ColliderMask m_colliderMask;
        GeometryShape m_shape;
        std::function<void(Collider&,Collider&)> m_onCollide;
        static int ColliderMatrix[4][4];

    public:
        Collider( CollisionType collisionType,ColliderMask mask,GeometryShape shape, const sf::Transform &transform=sf::Transform::Identity);
        ~Collider();
        void AddGameObjectToGame() override;
        void RemoveGameObjectFromGame() override;
        void update(float  deltaT) override;
        GameObject& clone() const override;

        std::function<void(Collider&,Collider&)>& getOnCollide(){return m_onCollide;}

        collisionData CheckCollision(const Collider& col1,const Collider& col2);
        collisionData ColCircleCircle(const sf::Transform & tr1, const sf::Transform & tr2);
        collisionData ColCircleSquare(const sf::Transform & tr1, const sf::Transform & tr2);
        collisionData ColSquareSquare(const sf::Transform & tr1, const sf::Transform & tr2);
};
