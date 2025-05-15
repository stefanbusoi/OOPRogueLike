#include "gameObjectComp.hpp"

#include "Collisions/Collider.h"
#include "Render/IRenderable.hpp"
#include "GameObject.hpp"

bool gameObjectComp::operator()(const GameObject *lhs, const GameObject *rhs) const {
    if (lhs->getUpdateOrder()==rhs->getUpdateOrder()) {
        return lhs->GetId() < rhs->GetId();
    }
    return lhs->getUpdateOrder()<rhs->getUpdateOrder();
}

bool ColliderComp::operator()(const Collider *lhs, const Collider *rhs) const {
    return lhs->GetId()<rhs->GetId();
}



bool iRendableComp::operator()( IRenderable *lhs,  IRenderable *rhs) const {
    if (lhs->getRenderOrder()==rhs->getRenderOrder()) {
        return (dynamic_cast<GameObject*>(lhs)->GetId()) <
               (dynamic_cast<GameObject*>(rhs)->GetId());
    }
    return lhs->getRenderOrder()<rhs->getRenderOrder();
}
