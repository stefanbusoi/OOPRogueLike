//
// Created by stefa on 6/3/2025.
//
#pragma once
//2star: if you have time
#include <CoreFunctionality/BaseGameObject.hpp>
#include "IRenderable.hpp"


class RendableGameObject:public BaseGameObject, public IRenderable{
  void addGameObjectToGame() override;

  void removeGameObjectFromGame() override;
};


