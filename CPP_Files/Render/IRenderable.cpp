
#include "../Game.hpp"

void IRenderable::AddToRenderObjects() {
    Game::getInstance()->getRenderObjects().insert(this);
}
void IRenderable::RemoveFromRenderObjects() {
    Game::getInstance()->getRenderObjects().erase(this);
}
