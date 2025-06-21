//
// Created by stefa on 5/14/2025.
#pragma once
#include <functional>

#include "Events/GameEvent.hpp"
#include "CoreFunctionality/BaseGameObject.hpp"


/**
 * Manages the Health of an entity
 */
class EntityHealth : public BaseGameObject {
  float m_maxhealth;
  float m_currentHealth;
  float m_TimeSinceLastAttack = 0.0f;
  float m_ImunityTime = 0.0f;
  bool m_isDead{false};
  GameEvent<EntityHealth *> m_onDeath;
  GameEvent<EntityHealth *> m_onHit;

public:
  /**
   *
   * @param maxHealh max healt of the entity
   */
  explicit EntityHealth(float maxHealh);

  void update(float deltaT) override;

  std::shared_ptr<BaseGameObject> clone() const override;

  float getMaxHealth() const { return m_maxhealth; }
  float getCurrentHealth() const { return m_currentHealth; }

  void setImunityTime(float time);


  void dealDamage(float damageValue);

  /**
   *
   * @param onDeath what to do when the entity get at 0 hp
   * @return an index used to remove from OnDeath
   */
  size_t setOnDeath(const std::function<void(EntityHealth *)> &onDeath);

  /**
   *
   * @param onHit what to do when the entity takes damage
   * @return and index used to remove from OnHit
   */
  size_t setOnHit(const std::function<void(EntityHealth *)> &onHit);
};
