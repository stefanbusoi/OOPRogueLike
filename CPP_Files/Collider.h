#ifndef ICOLIDERABLE_H
#define ICOLIDERABLE_H

//#include "GameObject.hpp"
#include "SFML/Graphics/Transform.hpp"

class GameObject;


enum class CollisionType{
    Dynamic=1,
    Trigger=2,
};
enum class ColliderMask {
    Player=0,
    Map=1,
    Enemy=2,
};
/*
 *5star: make collider work
 *
 */

class Collider/*:public GameObject*/{
        GameObject* m_gameObject;
        sf::Transform m_transform;
        CollisionType m_collisionType;
        ColliderMask m_colliderMask;
    public:
        sf::Transform getGlobalTransform() const;
        sf::Transform& getLocalTransform();
        void setGameObject(GameObject* obj){m_gameObject=obj;};
        GameObject* getGameObject() const {return m_gameObject;}
        Collider( CollisionType collisionType,ColliderMask mask, const sf::Transform &transform=sf::Transform::Identity);
};
#endif //ICOLIDERABLE_H