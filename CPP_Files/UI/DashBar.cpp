//
// Created by fanel012 on 5/31/25.
//

#include "DashBar.hpp"

#include "CoreFunctionality/Game.hpp"
#include "Entityies/EntityHealth.hpp"
#include "Exceptions/GameLogicException.hpp"

void DashBar::update(float deltaT) {
  (void) deltaT;
  if (!player.expired()) {
    m_currentValue=player.lock()->getDashTotalCooldown()-player.lock()->getDashCurrentCooldown();
  }else {
    player=Game::getInstance()->getGameObjectOfType<Player>();
  }
}

void DashBar::render() {
  if (m_currentValue!=m_maxValue)
    Slider::render();
}

DashBar::DashBar():Slider() {

  m_padding=0.01;
  m_width=0.25;
  m_height=0.03;
  m_position=sf::Vector2f(0.375,0.09);
  m_mainColor=sf::Color(200,200,255);
   player=Game::getInstance()->getGameObjectOfType<Player>();
  if (player.expired()) {
    throw GameLogicException("DashBar must be added after player");
  }
  m_maxValue=player.lock()->getDashTotalCooldown();



}
