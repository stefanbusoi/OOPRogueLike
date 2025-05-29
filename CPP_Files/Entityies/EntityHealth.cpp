//
// Created by stefa on 5/14/2025.
//

#include "EntityHealth.hpp"

EntityHealth::EntityHealth(float maxHealt): m_maxhealth(maxHealt),
                                                                m_currentHealth(maxHealt) {
}

std::shared_ptr<BaseGameObject> EntityHealth::clone() const {
  std::shared_ptr<EntityHealth> clone = std::make_shared<EntityHealth>(m_maxhealth);
  clone->m_currentHealth = m_currentHealth;
  clone->m_isDead = m_isDead;
  clone->m_onDeath = m_onDeath;
  for (auto i: m_children) {
    clone->EmplaceClone(i);
  }
  clone->m_transform = m_transform;
  clone->m_name = m_name;
  clone->m_parent.reset();
  clone->m_updateOrder = m_updateOrder;
  return clone;
}

void EntityHealth::dealDamage(float damageValue) {
  m_currentHealth -= damageValue;
  if (m_currentHealth <= 0) {
    m_isDead = true;
    m_onDeath.CallFunction(this);
  }
}

void EntityHealth::heal(float healValue) {
  m_currentHealth = std::min(m_currentHealth + healValue, m_maxhealth);
}
size_t EntityHealth::setOnDeath(const std::function<void(EntityHealth *)> &onDeath) {
  return m_onDeath.subscribe(onDeath);
}
