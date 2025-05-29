#pragma once

#include "BaseGameObject.hpp"
#include "Render/IRenderable.hpp"

class iRendableComp {
public:
  bool operator()(IRenderable *lhs, IRenderable *rhs) const;
};


class gameObjectComp {
public:
  bool operator()(const BaseGameObject *lhs, const BaseGameObject *rhs) const;
};

class ColliderComp {
public:
  bool operator()(const Collider *lhs, const Collider *rhs) const;
};
