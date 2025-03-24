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
                default:
                    return os;
            }
        }

        IRenderable() {
            m_renderOrder = RenderOrder::Default;
        }
        IRenderable(const IRenderable &other)
            : m_renderOrder(other.m_renderOrder) {
        }
        IRenderable(IRenderable &&other) noexcept
            : m_renderOrder(other.m_renderOrder) {
        }
        IRenderable & operator=(const IRenderable &other) {
            if (this == &other)
                return *this;
            m_renderOrder = other.m_renderOrder;
            return *this;
        }
        IRenderable & operator=(IRenderable &&other) noexcept {
            if (this == &other)
                return *this;
            m_renderOrder = other.m_renderOrder;
            return *this;
        }

        virtual void Render() = 0;
        virtual ~IRenderable();
        RenderOrder getRenderOrder() const {return m_renderOrder;}
};



