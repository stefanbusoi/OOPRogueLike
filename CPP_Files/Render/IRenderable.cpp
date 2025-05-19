
#include "../Game.hpp"

void IRenderable::AddToRenderObjects() {
    Game::getInstance()->getRenderObjects().insert(this);
}
void IRenderable::RemoveFromRenderObjects() {
    Game::getInstance()->getRenderObjects().erase(this);
}
inline std::ostream & operator<<(std::ostream &os, const IRenderable &obj) {
    os << "IRenderable: m_renderOrder: ";
    switch (obj.m_renderOrder) {
        case RenderOrder::Default:
            return os << "Default";
        case RenderOrder::Player:
            return os << "Player";
        case RenderOrder::Terrain:
            return os << "Terrain";
        case RenderOrder::PostProcessing:
            return os << "PostProcessing";
        case RenderOrder::PlayerWeapons:
            return os << "PlayerWeapons";
        case RenderOrder::UIPreProcessing:
            return os << "UIPreProcessing";
        case RenderOrder::UIPostProcessing:
            return os << "UIPostProcessing";
        default:
            return os;
    }
}
