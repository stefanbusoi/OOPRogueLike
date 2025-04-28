#include "Collider.h"
#include "GameObject.hpp"

sf::Transform Collider::getGlobalTransform() const {
    if (m_gameObject) {
        sf::Transform localTransform = m_gameObject->getLocalTransform();
        return localTransform.combine(m_transform);
    }
    return m_transform;
}

sf::Transform & Collider::getLocalTransform() {
    return m_transform;
}


inline Collider::Collider( CollisionType collisionType,
    ColliderMask mask, const sf::Transform &transform)
    : m_gameObject(nullptr),
      m_transform(transform),
      m_collisionType(collisionType),
      m_colliderMask(mask) {
}
