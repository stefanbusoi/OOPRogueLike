#ifndef ICOLIDERABLE_H
#define ICOLIDERABLE_H
#include <vector>

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
        GameObject* gameObject;
        sf::Transform transform;
        [[maybe_unused]] GeometryShape geometryShape;
        [[maybe_unused]] CollisionType collisionType;
        [[maybe_unused]]ColliderMask colliderMask;
    public:
    sf::Transform getGlobalTransform();
    sf::Transform& getLocalTransform();
    void setGameObject(GameObject* obj){gameObject=obj;};
    [[maybe_unused]] GameObject* getGameObject() const {return gameObject;}
    Collider(GeometryShape geometryShape, CollisionType collisionType,ColliderMask mask,sf::Transform transform=sf::Transform::Identity);
};




#endif //ICOLIDERABLE_H
