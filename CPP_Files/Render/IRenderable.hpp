#pragma once

#include <ostream>

#include "RenderOrder.hpp"
class IRenderable {
    protected:
        RenderOrder m_renderOrder;
    public:
        friend std::ostream & operator<<(std::ostream &os, const IRenderable &obj) {
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

        IRenderable();


        virtual void Render() = 0;
        virtual ~IRenderable();
        void AddToRenderObjects();
        void RemoveFromRenderObjects();
        RenderOrder getRenderOrder() const {return m_renderOrder;}
};
