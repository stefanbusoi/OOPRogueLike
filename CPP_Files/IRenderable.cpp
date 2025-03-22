//
// Created by stefa on 3/20/2025.
//
#include "Game.hpp"
IRenderable::~IRenderable() {
    Game::getInstance()->getRenderOrder().erase(this);
}
