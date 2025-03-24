#pragma once
#include <iostream>

#include "RenderOrder.hpp"
class IRenderable {
    protected:
        RenderOrder m_renderOrder;
    public:
        IRenderable()=default;
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



