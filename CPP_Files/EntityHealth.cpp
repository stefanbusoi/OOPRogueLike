
//
// Created by stefa on 5/14/2025.
//

#include "EntityHealth.hpp"

EntityHealth::EntityHealth(float maxHealt, float currentHealt):
  m_maxhealth(maxHealt),
  m_currentHealth(currentHealt) {
}

void EntityHealth::dealDamage(float damageValue) {
  m_currentHealth -= damageValue;
  if (m_currentHealth <= 0) {
    m_isDead = true;
    if (m_onDeath)
      m_onDeath();
  }
}

void EntityHealth::heal(float healValue) {
  m_currentHealth=std::min(m_currentHealth+healValue,m_maxhealth);
}

void EntityHealth::setOnDeath(std::function<void()> onDeath) {
  m_onDeath=onDeath;
}
