//
// Created by stefa on 5/14/2025.
//
#pragma once
#include <functional>

#include "GameObject.hpp"


class EntityHealth:public GameObject {
    float m_maxhealth;
    float m_currentHealth;
    bool m_isDead{false};
    std::function<void()> m_onDeath;
public:
    EntityHealth(float maxHealt,float currentHealt);
    float getMaxHealth() const{return m_maxhealth;}
    float getCurrentHealth() const{return m_currentHealth;}
    bool isDead() const {return m_isDead;}

    void dealDamage(float damageValue);
    void heal(float healValue);
    void setOnDeath(std::function<void()> onDeath);
};
