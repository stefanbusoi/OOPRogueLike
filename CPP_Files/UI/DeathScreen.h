//
// Created by fanel012 on 5/31/25.
//
#pragma once
#include "CoreFunctionality/BaseGameObject.hpp"
#include "Render/IRenderable.hpp"
#include "SFML/Graphics/Color.hpp"


class DeathScreen:public IRenderable ,public BaseGameObject{
protected:
    float maxScore=0;
public:
    DeathScreen(float max_score=0);


    void AddGameObjectToGame() override;

    void RemoveGameObjectFromGame() override;
    void Render() override;
};
