
#include "UI/Slider.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "CoreFunctionality/Game.hpp"



Slider::Slider(): BaseGameObject("Slider", sf::Transform::Identity), m_maxValue(0), m_currentValue(0) {
    m_renderOrder = RenderOrder::UIPreProcessing;
    m_updateOrder = UpdateOrder::UI;
}

Slider::Slider(float maxValue):Slider(){
    m_maxValue = maxValue;
    m_currentValue = maxValue;
}

void Slider::AddGameObjectToGame() {
    BaseGameObject::AddGameObjectToGame();
    IRenderable::AddToRenderObjects();
}
void Slider::RemoveGameObjectFromGame() {
    BaseGameObject::RemoveGameObjectFromGame();
    IRenderable::RemoveFromRenderObjects();

}

void Slider::Render() {
    std::shared_ptr<Game> x = Game::getInstance();
    sf::RenderTarget &renderTexture = x->getRenderTexture();


    sf::Vector2u size = renderTexture.getSize();
    sf::RectangleShape BackGroundShape;
    BackGroundShape.setFillColor(m_BackGroundColor);
    BackGroundShape.setSize(sf::Vector2f(size.x*width, size.y*height));

    sf::RectangleShape ContendShape;
    ContendShape.setFillColor(m_mainColor);
    ContendShape.setSize(sf::Vector2f((size.x)*(width-2*padding)*(m_currentValue/m_maxValue), (size.y)*(height-2*padding)));
    sf::Transform tr;
    tr.translate({m_position.x*size.x, m_position.y*size.y});
    renderTexture.draw(BackGroundShape,tr);
    tr.translate({padding*size.x,padding*size.y});
    renderTexture.draw(ContendShape,tr);
}
