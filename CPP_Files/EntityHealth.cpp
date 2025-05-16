
//
// Created by stefa on 5/14/2025.
//

#include "EntityHealth.hpp"

EntityHealth::EntityHealth(float maxHealt, float currentHealt):
  m_maxhealth(maxHealt),
  m_currentHealth(currentHealt) {
}

GameObject & EntityHealth::clone() const {
  EntityHealth* clone=new EntityHealth(m_maxhealth,m_currentHealth);
  clone->m_isDead=m_isDead;
  clone->m_onDeath=m_onDeath;
  for (auto i:m_children) {
    clone->EmplaceClone(*i);
  }
  clone->m_transform = m_transform;
  clone->m_name =m_name;
  clone->m_parent = nullptr;
  clone->m_updateOrder = m_updateOrder;
  return *clone;
}

void EntityHealth::dealDamage(float damageValue) {
  m_currentHealth -= damageValue;
  if (m_currentHealth <= 0) {
    m_isDead = true;
    if (m_onDeath)
      m_onDeath(this);
  }
}

void EntityHealth::heal(float healValue) {
  m_currentHealth=std::min(m_currentHealth+healValue,m_maxhealth);
}

void EntityHealth::setOnDeath(const std::function<void(EntityHealth*)> &onDeath) {
  m_onDeath=onDeath;
}
