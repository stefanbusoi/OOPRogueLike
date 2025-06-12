//
// Created by stefa on 6/3/2025.
//
//2star: if you have time
#include "RenerableGameObject.hpp"
void RendableGameObject::addGameObjectToGame()  {
  IRenderable::addToRenderObjects();
  BaseGameObject::addGameObjectToGame();
}

void RendableGameObject::removeGameObjectFromGame()  {
  IRenderable::removeFromRenderObjects();
  BaseGameObject::addGameObjectToGame();
}
