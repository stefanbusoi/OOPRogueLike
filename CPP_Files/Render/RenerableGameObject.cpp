//
// Created by stefa on 6/3/2025.
//
//2star: if you have time
#include "RenerableGameObject.hpp"
void RendableGameObject::addGameObjectToGame()  {
  IRenderable::addToRenderObjects();
  BaseGameObject::addGameObjectToGame();
}

RendableGameObject::RendableGameObject(const std::string &name, const sf::Transform &tr, RenderOrder m_renderOrder):
  BaseGameObject(name,tr),
  IRenderable(m_renderOrder) {}

void RendableGameObject::removeGameObjectFromGame()  {
  IRenderable::removeFromRenderObjects();
  BaseGameObject::addGameObjectToGame();
}
