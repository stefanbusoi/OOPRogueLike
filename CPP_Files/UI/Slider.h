#pragma once
#include "../Render/IRenderable.hpp"
#include "CoreFunctionality/BaseGameObject.hpp"
#include "Render/RenerableGameObject.hpp"
#include "SFML/Graphics/Color.hpp"


class Slider:public RendableGameObject{
protected:
    float m_maxValue=0.0f;
    float m_currentValue=0.0f;
    sf::Color m_BackGroundColor=sf::Color::Black;
    sf::Color m_mainColor=sf::Color::Red;

    //0-1 based on screen height and width
    float m_padding=0.01;
    float m_width=0.25;
    float m_height=0.05;
    sf::Vector2f m_position=sf::Vector2f(0.375,0.05);

public:
    Slider();
    explicit Slider(float maxValue);
    void render() override;
};
