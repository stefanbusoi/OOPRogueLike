
#include "Game.hpp"
IRenderable::~IRenderable() {
    Game::getInstance()->getRenderObjects().erase(this);
}
