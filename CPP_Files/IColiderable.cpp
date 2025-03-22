#include "IColiderable.h"
#include "GameObject.hpp"

sf::Transform Collider::getGlobalTransform() {
    if (gameObject) {
        sf::Transform localTransform = gameObject->getLocalTransform();
        return localTransform.combine(transform);
    }
    return transform;
}

sf::Transform & Collider::getLocalTransform() {
    return transform;
}


inline Collider::Collider(GeometryShape geometryShape, CollisionType collisionType,
    ColliderMask mask,sf::Transform transform):geometryShape(geometryShape),collisionType(collisionType),colliderMask(mask),transform(transform)
{}