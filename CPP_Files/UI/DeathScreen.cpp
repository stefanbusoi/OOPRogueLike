//
// Created by fanel012 on 5/31/25.
//

#include "DeathScreen.h"

#include <CoreFunctionality/Game.hpp>

#include "Resources.hpp"

DeathScreen::DeathScreen(float maxScore):maxScore(maxScore) {

    m_renderOrder= RenderOrder::UIPostProcessing;
}


void DeathScreen::AddGameObjectToGame() {
    BaseGameObject::AddGameObjectToGame();
    IRenderable::AddToRenderObjects();
}

void DeathScreen::RemoveGameObjectFromGame() {
    BaseGameObject::RemoveGameObjectFromGame();
    IRenderable::RemoveFromRenderObjects();
}

void DeathScreen::Render() {
    auto& renderTexture=Game::getInstance()->getRenderTexture();
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(renderTexture.getSize()));
    rect.setFillColor(sf::Color(0.0f,0.0f,0.0f,126.5f));
    renderTexture.draw(rect);

    sf::Transform tr;
    tr.translate({renderTexture.getSize().x*0.5f,renderTexture.getSize().y*0.3f});

    sf::Text text(Resources::getFont());
    text.setString("YOU DIED");
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(200);
    text.setOrigin(text.getGlobalBounds().size/2.0f);
    renderTexture.draw(text,tr);

    text.setString("Press L to restart");
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(70);
    text.setOrigin(text.getGlobalBounds().size/2.0f);

    tr=sf::Transform::Identity;
    tr.translate({renderTexture.getSize().x*0.5f,renderTexture.getSize().y*0.7f});

    renderTexture.draw(text,tr);
}


