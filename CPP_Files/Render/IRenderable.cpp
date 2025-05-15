
#include "../Game.hpp"
IRenderable::~IRenderable() {
    if (Game::getInstance()->IsActiveInHirarchy(dynamic_cast<GameObject *>(this))) {
        RemoveFromRenderObjects();
    }
}

void IRenderable::AddToRenderObjects() {
    Game::getInstance()->getRenderObjects().insert(this);
}
void IRenderable::RemoveFromRenderObjects() {
    Game::getInstance()->getRenderObjects().erase(this);
}
