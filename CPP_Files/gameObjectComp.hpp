#pragma once
#include <ostream>

#include "GameObject.hpp"
#include "Render/IRenderable.hpp"

class iRendableComp {
public:
    bool operator()( IRenderable *lhs,  IRenderable *rhs) const;
};


class gameObjectComp {
    public:
    bool operator()(const GameObject *lhs, const GameObject *rhs) const;

};


