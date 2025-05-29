//
// Created by stefa on 5/14/2025.
//
#pragma once
#include <functional>

#include "Events/GameEvent.hpp"
#include "CoreFunctionality/BaseGameObject.hpp"


class EntityHealth : public BaseGameObject {
  float m_maxhealth;
  float m_currentHealth;
  bool m_isDead{false};
  GameEvent<EntityHealth*> m_onDeath;
public:
  EntityHealth(float maxHealh);

  std::shared_ptr<BaseGameObject> clone() const override;

  float getMaxHealth() const { return m_maxhealth; }
  float getCurrentHealth() const { return m_currentHealth; }

  void heal(float healValue);

  void dealDamage(float damageValue);

  bool isDead() const { return m_isDead; }

  size_t setOnDeath(const std::function<void(EntityHealth *)> &onDeath);
};
