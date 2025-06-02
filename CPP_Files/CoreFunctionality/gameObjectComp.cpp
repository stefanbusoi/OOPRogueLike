#include "gameObjectComp.hpp"

#include "Collisions/Collider.h"
#include "Render/IRenderable.hpp"
#include "BaseGameObject.hpp"

bool gameObjectComp::operator()(const BaseGameObject *lhs, const BaseGameObject *rhs) const {
  if (lhs->getUpdateOrder() == rhs->getUpdateOrder()) {
    return lhs->getId() < rhs->getId();
  }
  return lhs->getUpdateOrder() < rhs->getUpdateOrder();
}

bool ColliderComp::operator()(const Collider *lhs, const Collider *rhs) const {
  return lhs->getId() < rhs->getId();
}


bool iRendableComp::operator()(IRenderable *lhs, IRenderable *rhs) const {
  if (lhs->getRenderOrder() == rhs->getRenderOrder()) {
    if (dynamic_cast<BaseGameObject *>(lhs) != nullptr && dynamic_cast<BaseGameObject *>(rhs) != nullptr) {
      return dynamic_cast<BaseGameObject *>(lhs)->getId() <
             dynamic_cast<BaseGameObject *>(rhs)->getId();
    }
    if (dynamic_cast<BaseGameObject *>(lhs) != nullptr)
      return true;
    return false;
  }
  return lhs->getRenderOrder() < rhs->getRenderOrder();
}
