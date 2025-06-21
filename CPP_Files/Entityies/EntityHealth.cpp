
#include "EntityHealth.hpp"

EntityHealth::EntityHealth(float maxHealt): m_maxhealth(maxHealt),
                                                                m_currentHealth(maxHealt) {
}

void EntityHealth::update(float deltaT) {
  m_TimeSinceLastAttack+= deltaT;
}

std::shared_ptr<BaseGameObject> EntityHealth::clone() const {
  std::shared_ptr<EntityHealth> clone = std::make_shared<EntityHealth>(m_maxhealth);
  clone->m_currentHealth = m_currentHealth;
  clone->m_isDead = m_isDead;
  clone->m_onDeath = m_onDeath;
  for (auto i: m_children) {
    clone->emplaceClone(i);
  }
  clone->m_transform = m_transform;
  clone->m_name = m_name;
  clone->m_parent.reset();
  clone->m_updateOrder = m_updateOrder;
  return clone;
}

void EntityHealth::dealDamage(float damageValue) {
  if (m_ImunityTime<m_TimeSinceLastAttack) {
    m_TimeSinceLastAttack=0.0f;
    m_currentHealth -= damageValue;
    m_onHit.callFunction(this);
    if (m_currentHealth <= 0) {
      m_isDead = true;
      m_onDeath.callFunction(this);
    }
  }
}

void EntityHealth::setImunityTime(float time) {
  m_ImunityTime = time;
}
  
size_t EntityHealth::setOnDeath(const std::function<void(EntityHealth *)> &onDeath) {
  return m_onDeath.subscribe(onDeath);
}

size_t EntityHealth::setOnHit(const std::function<void(EntityHealth *)> &onHit) {
  return m_onHit.subscribe(onHit);
}
