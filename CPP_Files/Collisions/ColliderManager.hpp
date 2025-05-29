//
// Created by fanel012 on 5/30/25.
//
#pragma once
#include "CoreFunctionality/BaseGameObject.hpp"


class ColliderManager : public BaseGameObject{

    public:
    ColliderManager();

    void AddGameObjectToGame() override;

    void RemoveGameObjectFromGame() override;

    ~ColliderManager() override;

    void Init() override;

    void update(float deltaTime) override;
};