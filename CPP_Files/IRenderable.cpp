
#include "Game.hpp"
IRenderable::~IRenderable() {
    if (Game::getInstance()->IsInHirarchy(dynamic_cast<GameObject *>(this))) {
        Game::getInstance()->getRenderObjects().erase(this);
    }
}

void IRenderable::AddToRenderObjects() {
    Game::getInstance()->getRenderObjects().insert(this);
}
void IRenderable::RemoveFromRenderObjects() {
    Game::getInstance()->getRenderObjects().erase(this);
}
