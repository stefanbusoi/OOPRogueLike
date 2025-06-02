//
// Created by stefa on 5/24/2025.
//

#pragma once

#include <memory>

#include "CoreFunctionality/BaseGameObject.hpp"
#include "SFML/Graphics/Transform.hpp"


class Arrow :public BaseGameObject{
    float m_timer{0.0f};
    public:
    Arrow(sf::Transform transform=sf::Transform::Identity);\
    void init() override;
    void update(float deltaT) override;

    void addGameObjectToGame() override;

    std::shared_ptr<BaseGameObject> clone() const override;

    void removeGameObjectFromGame() override;
};
