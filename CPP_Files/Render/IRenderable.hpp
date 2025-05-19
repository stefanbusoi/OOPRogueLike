#pragma once

#include <ostream>
#include <memory>
#include "RenderOrder.hpp"
class IRenderable {
protected:
    RenderOrder m_renderOrder=RenderOrder::Default;

public:
    friend std::ostream & operator<<(std::ostream &os, const IRenderable &obj);
    virtual void Render() = 0;
    void AddToRenderObjects();
    void RemoveFromRenderObjects();
    RenderOrder getRenderOrder() const {return m_renderOrder;}

};
