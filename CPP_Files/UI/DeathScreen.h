//
// Created by fanel012 on 5/31/25.
//
#pragma once
#include "CoreFunctionality/BaseGameObject.hpp"
#include "Render/IRenderable.hpp"
#include "Render/RenerableGameObject.hpp"
#include "SFML/Graphics/Color.hpp"


class DeathScreen:public RendableGameObject{
protected:
    float m_deadTime;
public:
    DeathScreen();

    void render() override;
};
