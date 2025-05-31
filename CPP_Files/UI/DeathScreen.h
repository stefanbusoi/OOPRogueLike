//
// Created by fanel012 on 5/31/25.
//
#pragma once
#include "CoreFunctionality/BaseGameObject.hpp"
#include "Render/IRenderable.hpp"
#include "SFML/Graphics/Color.hpp"


class DeathScreen:public IRenderable ,public BaseGameObject{
protected:
    float m_maxValue;
    float m_currentValue;
    sf::Color m_BackGroundColor=sf::Color::Black;
    sf::Color m_mainColor=sf::Color::Red;
    //0-1 based on screen height and width
    float padding=0.01;
    float width=0.25;
    float height=0.05;
    sf::Vector2f m_position=sf::Vector2f(0.375,0.05);

public:
    DeathScreen();

    void AddGameObjectToGame() override;

    void RemoveGameObjectFromGame() override;
    void Render() override;
};
