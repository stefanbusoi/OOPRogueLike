#include "gameObjectComp.hpp"
#include "IRenderable.hpp"
#include "GameObject.hpp"

bool gameObjectComp::operator()(const GameObject *lhs, const GameObject *rhs) const {
    if (lhs->getUpdateOrder()==rhs->getUpdateOrder()) {
        return lhs->GetId() < rhs->GetId();
    }
    return lhs->getUpdateOrder()<rhs->getUpdateOrder();
}

bool iRendableComp::operator()(const IRenderable *lhs, const IRenderable *rhs) const {
    if (lhs->getRenderOrder()==rhs->getRenderOrder()) {
        //TODO: Make this work return dynamic_cast<GameObject*>(lhs)->GetId()<dynamic_cast<GameObject*>(rhs)->GetId();
        return lhs<rhs;
    }
    return lhs->getRenderOrder()<rhs->getRenderOrder();
}
