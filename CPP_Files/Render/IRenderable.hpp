#pragma once

#include <ostream>
#include "RenderOrder.hpp"

class IRenderable {
protected:
  RenderOrder m_renderOrder;

public:
  friend std::ostream &operator<<(std::ostream &os, const IRenderable &obj);
  IRenderable( RenderOrder renderOrder);
  virtual void render() = 0;
  virtual ~IRenderable();
  void addToRenderObjects();

  void removeFromRenderObjects();

  RenderOrder getRenderOrder() const { return m_renderOrder; }
};
