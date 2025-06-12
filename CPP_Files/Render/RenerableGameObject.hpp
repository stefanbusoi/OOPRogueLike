//
// Created by stefa on 6/3/2025.
//
#pragma once
//2star: if you have time
#include <CoreFunctionality/BaseGameObject.hpp>
#include "IRenderable.hpp"


class RendableGameObject:public BaseGameObject, public IRenderable{
public:
  void addGameObjectToGame() override;
  RendableGameObject(const std::string& name,const sf::Transform& tr,RenderOrder m_renderOrder );
  void removeGameObjectFromGame() override;
};


