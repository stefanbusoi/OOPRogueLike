#pragma once
#include <iostream>

#include "RenderOrder.hpp"
#include "GameObject.hpp"
class IRenderable {
    protected:
        RenderOrder m_renderOrder;
    public:
        virtual void Render() = 0;
        virtual ~IRenderable();
        RenderOrder getRenderOrder() const {return m_renderOrder;}
};



