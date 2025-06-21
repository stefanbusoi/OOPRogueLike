//
// Created by fanel012 on 5/31/25.
//

#include "HealthBar.h"

#include "CoreFunctionality/Game.hpp"
#include "Entityies/EntityHealth.hpp"
#include "Exceptions/GameLogicException.hpp"
HealthBar::HealthBar():Slider() {

    m_padding=0.01f;
    m_width=0.25f;
    m_height=0.05f;
    m_position=sf::Vector2f(0.375f,0.05f);

    auto player=Game::getInstance()->getGameObjectOfType<Player>();
    if (player==nullptr) {
        throw GameLogicException("HealtBar must be added after player");
    }
    auto PlayerHealth=player->getGameObjectOfType<EntityHealth>();
    m_maxValue=PlayerHealth->getMaxHealth();
    m_currentValue=PlayerHealth->getCurrentHealth();
    PlayerHealth->setOnHit([this](EntityHealth* health) {
        m_currentValue=health->getCurrentHealth();
    });

}
