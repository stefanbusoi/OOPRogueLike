#pragma once
#include <functional>

#include "../GameObject.hpp"
#include "SFML/Graphics/Transform.hpp"


enum class CollisionType{
    Dynamic=1,
    Trigger=2,
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
        void AddGameObjectToGame() override;
        void RemoveGameObjectFromGame() override;
        void update(float  deltaT) override;
        std::function<void(Collider&,Collider&)>& getOnCollide(){return m_onCollide;}
        GameObject& clone() const override;
        collisionData ColCircleCircle(const sf::Transform & Tr1, const sf::Transform & Tr2);

        collisionData ColCircleSquare(const sf::Transform & Tr1, const sf::Transform & Tr2);

        collisionData ColSqueareSquare(const sf::Transform & Tr1, const sf::Transform & Tr2);

        collisionData CheckCollision(const Collider& col1,const Collider& col2);
        Collider( CollisionType collisionType,ColliderMask mask,GeometryShape shape, const sf::Transform &transform=sf::Transform::Identity);
};
