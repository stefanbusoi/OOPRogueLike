#pragma once

#include <ostream>
#include "RenderOrder.hpp"

/**
 * The base component of all renerable objects
 */
class IRenderable {
protected:
  /**
   * used to order the objects in the order in which they must be rendered
   */
  RenderOrder m_renderOrder;

public:
  friend std::ostream &operator<<(std::ostream &os, const IRenderable &obj);
  /**
   * 
   * @param renderOrder when to render the object
   */
  IRenderable( RenderOrder renderOrder);
  virtual void render() = 0;
  virtual ~IRenderable();
  /**
   * add an object to render list
   */
  void addToRenderObjects();

  /**
   * remove the object from the render list
   */
  void removeFromRenderObjects();

  /**
   * 
   * @return get the order in witch the objects shoud be rendered
   */
  RenderOrder getRenderOrder() const { return m_renderOrder; }
};
