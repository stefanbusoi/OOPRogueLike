//
// Created by fanel012 on 5/31/25.
//

#include "DeathScreen.h"

#include <CoreFunctionality/Game.hpp>

#include "Resources.hpp"

DeathScreen::DeathScreen() {
    m_deadTime=Game::getInstance()->getTotalTime();
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

    sf::Transform diedTr;
    diedTr.translate({renderTexture.getSize().x*0.5f,renderTexture.getSize().y*0.3f});

    sf::Text diedText(Resources::getFont());
    diedText.setString("YOU DIED");
    diedText.setFillColor(sf::Color::Red);
    diedText.setCharacterSize(200);
    diedText.setOrigin(diedText.getGlobalBounds().size/2.0f);

    renderTexture.draw(diedText,diedTr);

    sf::Text restartText(Resources::getFont());
    restartText.setString("Press L to restart");
    restartText.setFillColor(sf::Color::White);
    restartText.setCharacterSize(70);
    restartText.setOrigin(restartText.getGlobalBounds().size/2.0f);

    sf::Transform restartTr;
    restartTr.translate({renderTexture.getSize().x*0.5f,renderTexture.getSize().y*0.7f});

    renderTexture.draw(restartText,restartTr);

    sf::Text timerText(Resources::getFont());
    timerText.setString(std::format("{}:{}:{}",(int)m_deadTime/3600,(int)m_deadTime/60-(int)m_deadTime/3600*60,(int)m_deadTime-(int)m_deadTime/60*60));
    timerText.setFillColor(sf::Color::White);
    timerText.setCharacterSize(50);
    timerText.setOrigin(timerText.getGlobalBounds().size/2.0f);

    sf::Transform timerTr;
    timerTr.translate({renderTexture.getSize().x*0.5f,renderTexture.getSize().y*0.5f});

    renderTexture.draw(timerText,timerTr);
}


