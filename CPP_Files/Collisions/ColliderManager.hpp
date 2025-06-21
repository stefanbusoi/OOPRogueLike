//
// Created by fanel012 on 5/30/25.
#pragma once
#include "CoreFunctionality/BaseGameObject.hpp"


/**
 * manages all collisions of the game
 */
class ColliderManager : public BaseGameObject{

    public:
    ColliderManager();

    void addGameObjectToGame() override;

    void removeGameObjectFromGame() override;


    void init() override;

    void update(float deltaTime) override;
};