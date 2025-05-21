#include <cmath>
#include "PhysicObject.hpp"

PhysicObject::PhysicObject(float mass, float friction, float elasticity) {
  m_name = "PhysicObject";
  m_mass = mass;
  m_friction = friction;
  m_elasticity = elasticity;
  m_updateOrder = UpdateOrder::PhisicsUpdate;

}

std::shared_ptr<GameObject> PhysicObject::clone() const {
  std::shared_ptr<PhysicObject> clone = std::make_shared<PhysicObject>(m_mass, m_friction, m_elasticity);

  clone->m_Acceleration = m_Acceleration;
  clone->m_Speed = m_Speed;
  for (auto i: m_children) {
    clone->EmplaceClone(i);
  }
  clone->m_transform = m_transform;
  clone->m_name = m_name;
  clone->m_parent.reset();
  clone->m_updateOrder = m_updateOrder;
  return clone;
}

void PhysicObject::update(float deltaT) {
  m_Speed += m_Acceleration * deltaT;
  m_Speed *= std::exp(-m_friction * deltaT);
  m_parent.lock()->GlobalMoveTransform(deltaT * m_Speed);
}
