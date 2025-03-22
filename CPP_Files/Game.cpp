//
// Created by stefa on 3/11/2025.
//

#include "Game.hpp"

#include "GameMap.hpp"
#include "Player.hpp"


Game* Game::instance = nullptr;

void Game::RenderAll() {
    window.display();
    window.clear();
    for (const auto& gameObject:m_renderableObjects) {
         gameObject->Render();
    }

}


Game *Game::getInstance() {return instance;}

Game::Game(const sf::VideoMode video_mode, const std::string &Title): GameObject(Title){
    std::cout<<"Game Constructor";
    if (instance==nullptr) {
        instance=this;
    }
    window.create(video_mode, Title, sf::State::Fullscreen);
    Player player("Player");
    AddGameObject<Player>(std::move(player));
    Camera cAmera;
    camera=AddGameObject<Camera>(std::move(cAmera));
    AddGameObject<GameMap>("GameMap");
}

Game::~Game() {
    std::cout<<"Game Destructor";
    if (IsRunning()) Exit();
    for (const auto& gameObject:m_children) {
        delete gameObject;
    }
    m_children.clear();
}

bool Game::IsRunning() const {
    return window.isOpen();

}

void Game::Exit() {
    window.close();
    std::cout << "Fereastra a fost inchisa\n";
}
float Game::ProcessGameFrame() {
    sf::Time deltaTime = clock.getElapsedTime();
    clock.restart();
    for (const auto& gameObject:gameObjects) {
        gameObject->update(deltaTime.asSeconds());
    }
    RenderAll();
    return  deltaTime.asSeconds();

}



