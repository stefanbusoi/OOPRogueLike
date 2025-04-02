#ifndef ICOLIDERABLE_H
#define ICOLIDERABLE_H

#include "SFML/Graphics/Transform.hpp"

class GameObject;

enum class GeometryShape{
    Square=0,
    Circle=1,
};
enum class CollisionType{
    Static=0,
    Dynamic=1,
    Trigger=2,
};
enum class ColliderMask {
    Player=0,
    Map=1,
    Enemy=2,
};

class Collider{
        GameObject* m_gameObject;
        sf::Transform m_transform;
        [[maybe_unused]] GeometryShape m_geometryShape;
        [[maybe_unused]] CollisionType m_collisionType;
        [[maybe_unused]]ColliderMask m_colliderMask;
    public:
        sf::Transform getGlobalTransform() const;
        sf::Transform& getLocalTransform();
        void setGameObject(GameObject* obj){m_gameObject=obj;};
        [[maybe_unused]] GameObject* getGameObject() const {return m_gameObject;}
        Collider(GeometryShape geometryShape, CollisionType collisionType,ColliderMask mask, const sf::Transform &transform=sf::Transform::Identity);
};
#endif //ICOLIDERABLE_H