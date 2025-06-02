#pragma once

#include <ostream>
#include "RenderOrder.hpp"

class IRenderable {
protected:
  RenderOrder m_renderOrder = RenderOrder::Default;

public:
  friend std::ostream &operator<<(std::ostream &os, const IRenderable &obj);

  virtual void render() = 0;
  virtual ~IRenderable();
  void addToRenderObjects();

  void removeFromRenderObjects();

  RenderOrder getRenderOrder() const { return m_renderOrder; }
};
