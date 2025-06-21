//
// Created by fanel012 on 5/31/25.
#pragma once
#include "CoreFunctionality/BaseGameObject.hpp"
#include "Render/IRenderable.hpp"
#include "Render/RenerableGameObject.hpp"
#include "SFML/Graphics/Color.hpp"


/**
 * a death screen shown after the player death
 */
class DeathScreen:public RendableGameObject{
protected:
    /**
     * how long the player survived
     */
    float m_deadTime;
public:
    DeathScreen();

    void render() override;
};
