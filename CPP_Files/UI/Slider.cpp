
#include "UI/Slider.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "CoreFunctionality/Game.hpp"



Slider::Slider()
    :BaseGameObject("Slider", sf::Transform::Identity),
    IRenderable(RenderOrder::UIPreProcessing)
{
    m_updateOrder = UpdateOrder::UI;
}

Slider::Slider(float maxValue):Slider(){
    m_maxValue = maxValue;
    m_currentValue = maxValue;
}

void Slider::addGameObjectToGame() {
    BaseGameObject::addGameObjectToGame();
    IRenderable::addToRenderObjects();
}
void Slider::removeGameObjectFromGame() {
    BaseGameObject::removeGameObjectFromGame();
    IRenderable::removeFromRenderObjects();

}

void Slider::render() {
    std::shared_ptr<Game> x = Game::getInstance();
    sf::RenderTarget &renderTexture = x->getRenderTexture();


    sf::Vector2u size = renderTexture.getSize();
    sf::RectangleShape BackGroundShape;
    BackGroundShape.setFillColor(m_BackGroundColor);
    BackGroundShape.setSize(sf::Vector2f(size.x*m_width, size.y*m_height));

    sf::RectangleShape ContendShape;
    ContendShape.setFillColor(m_mainColor);
    ContendShape.setSize(sf::Vector2f((size.x)*(m_width-2*m_padding)*(m_currentValue/m_maxValue), (size.y)*(m_height-2*m_padding)));
    sf::Transform tr;
    tr.translate({m_position.x*size.x, m_position.y*size.y});
    renderTexture.draw(BackGroundShape,tr);
    tr.translate({m_padding*size.x,m_padding*size.y});
    renderTexture.draw(ContendShape,tr);
}
