//
// Created by stefa on 6/3/2025.
#pragma once
#include <CoreFunctionality/BaseGameObject.hpp>
#include "IRenderable.hpp"


/**
 * game objects that are renderable to the screen
 */
class RendableGameObject:public BaseGameObject, public IRenderable{
public:
  void addGameObjectToGame() override;
  RendableGameObject(const std::string& name,const sf::Transform& tr,RenderOrder m_renderOrder );
  void removeGameObjectFromGame() override;
};


