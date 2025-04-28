//
// Created by stefa on 3/11/2025.
//

#include "Game.hpp"

#include "GameMap.hpp"
#include "Player.hpp"
#include "PostProcessingShader.h"
#include <SFML/Graphics.hpp>


Game* Game::s_instance = nullptr;

void Game::renderAll() {
    m_window.display();
    m_window.clear();

    for (const auto& gameObject:m_renderableObjects) {
         gameObject->Render();
    }
    m_renderTexture.display();
    sf::Sprite sprite(m_renderTexture.getTexture());
    m_window.draw(sprite);

}


Game *Game::getInstance() {return s_instance;}

Game::Game(const sf::VideoMode video_mode, const std::string &Title): GameObject(Title){
    m_totalTime=0.0f;
    if (s_instance==nullptr) {
        s_instance=this;
    }
    m_window.create(video_mode, Title, sf::State::Fullscreen);
    if (!m_renderTexture.resize(m_window.getSize())) {
        throw std::runtime_error("Failed to resize render texture");
    }

    AddGameObject<Player>("Player");
    m_camera=AddGameObject<Camera>("Camera");
    AddGameObject<GameMap>("GameMap");
    AddGameObject<PostProcessingShader>("PostProcessingShader");
}

Game::~Game() {
    if (isRunning()) exit();
}

bool Game::isRunning() const {
    return m_window.isOpen();

}

bool Game::IsInHirarchy(GameObject *p_gameObject) {
    if (p_gameObject==nullptr) return false;
    while (p_gameObject->getParent() != nullptr) {
        p_gameObject=p_gameObject->getParent();
    }
    if (p_gameObject==static_cast<GameObject *>(getInstance())) return true;
    return false;
}

void Game::exit() {
    for (const auto& gameObject:m_children) {
        delete gameObject;
    }
    m_children.clear();
    m_window.close();
    std::cout << "Fereastra a fost inchisa\n";
}
float Game::processGameFrame() {
    sf::Time deltaTime = m_clock.getElapsedTime();
    m_totalTime+=deltaTime.asSeconds();
    m_clock.restart();
    for (const auto& gameObject:m_gameObjects) {
        gameObject->update(deltaTime.asSeconds());
    }

    renderAll();
    return  deltaTime.asSeconds();

}



