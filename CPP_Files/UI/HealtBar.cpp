//
// Created by fanel012 on 5/31/25.
//

#include "HealtBar.h"

#include "CoreFunctionality/Game.hpp"
#include "Entityies/EntityHealth.hpp"
#include "Exceptions/GameLogicException.hpp"
HealtBar::HealtBar():Slider() {

    m_padding=0.01;
    m_width=0.25;
    m_height=0.05;
    m_position=sf::Vector2f(0.375,0.05);

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
