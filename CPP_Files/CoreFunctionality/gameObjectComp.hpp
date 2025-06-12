#pragma once

#include "BaseGameObject.hpp"
#include "Render/IRenderable.hpp"

/**
 * Compares the Irenderable based on render order
 */
class iRendableComp {
public:
  bool operator()(IRenderable *lhs, IRenderable *rhs) const;
};


/**
 * compares the game objects based on UpdateOrder
 */
class gameObjectComp {
public:
  bool operator()(const BaseGameObject *lhs, const BaseGameObject *rhs) const;
};

/**
 * compares the collider based on the id
 */
class ColliderComp {
public:
  bool operator()(const Collider *lhs, const Collider *rhs) const;
};
