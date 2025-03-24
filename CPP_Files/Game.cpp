//
// Created by stefa on 3/11/2025.
//

#include "Game.hpp"

#include "GameMap.hpp"
#include "Player.hpp"
#include "PostProcessingShader.h"


Game* Game::s_instance = nullptr;

void Game::renderAll() {
    m_window.display();
    m_window.clear();
    for (const auto& gameObject:m_renderableObjects) {
         gameObject->Render();
    }

}


Game *Game::getInstance() {return s_instance;}

Game::Game(const sf::VideoMode video_mode, const std::string &Title): GameObject(Title){
    m_totalTime=0.0f;
    if (s_instance==nullptr) {
        s_instance=this;
    }
    m_window.create(video_mode, Title, sf::State::Fullscreen);
    Player player("Player");
    AddGameObject<Player>(std::move(player));
    Camera camera;
    m_camera=AddGameObject<Camera>(std::move(camera));
    AddGameObject<GameMap>("GameMap");
}

Game::~Game() {
    if (isRunning()) exit();
    for (const auto& gameObject:m_children) {
        delete gameObject;
    }
    m_children.clear();
}

bool Game::isRunning() const {
    return m_window.isOpen();

}

void Game::exit() {
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



