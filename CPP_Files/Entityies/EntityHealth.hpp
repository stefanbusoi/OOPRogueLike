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
  float m_TimeSinceLastAttack = 0.0f;
  float m_ImunityTime = 0.0f;
  bool m_isDead{false};
  GameEvent<EntityHealth *> m_onDeath;
  GameEvent<EntityHealth *> m_onHit;

public:
  EntityHealth(float maxHealh);

  void update(float deltaT) override;

  std::shared_ptr<BaseGameObject> clone() const override;

  float getMaxHealth() const { return m_maxhealth; }
  float getCurrentHealth() const { return m_currentHealth; }

  void setImunityTime(float time);

  void heal(float healValue);

  void dealDamage(float damageValue);

  bool isDead() const { return m_isDead; }

  size_t setOnDeath(const std::function<void(EntityHealth *)> &onDeath);

  size_t setOnHit(const std::function<void(EntityHealth *)> &onDeath);
};
