//
// Created by stefa on 3/11/2025.
//

#include "Game.hpp"

#include "GameMap.hpp"
#include "Player.hpp"
#include "Render/PostProcessingShader.h"
#include <SFML/Graphics.hpp>

#include "PhysicObject.hpp"
#include "UtilityiesFunctions.hpp"
#include "Render/DebugMenu.hpp"
#include "Render/ShapeRenderer.hpp"


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

Game::Game(const sf::VideoMode video_mode, const std::string &Title): GameObject(Title) {
    m_totalTime=0.0f;
    if (s_instance==nullptr) {
        s_instance=this;
    }
    m_window.create(video_mode, Title, sf::State::Fullscreen);
    if (!m_renderTexture.resize(m_window.getSize())) {
        throw std::runtime_error("Failed to resize render texture");
    }
    m_window.setFramerateLimit(144);
     player_=EmplaceGameObject<Player>("Player");
    m_camera=EmplaceGameObject<Camera>("Camera");
    EmplaceGameObject<GameMap>("GameMap");
    EmplaceGameObject<PostProcessingShader>("PostProcessingShader",std::filesystem::path("Shaders/PostProcessingShader.frag"));
    auto debugMenu=EmplaceGameObject<DebugMenu>("DebugMenu");

    sf::Transform transform=sf::Transform::Identity;
    transform.translate({100.0f,100.0f});
    transform.scale({40.0f,40.0f});
    GameObject* game_object=new GameObject("GameObject",transform);
    game_object->EmplaceGameObject<Collider>(CollisionType::Dynamic,ColliderMask::Enemy,GeometryShape::Circle,sf::Transform::Identity);
    game_object->EmplaceGameObject<ShapeRenderer>("CircleRenderer",sf::Transform::Identity, sf::Color(0,255,255), RenderOrder::Player,GeometryShape::Circle);
    game_object->EmplaceGameObject<PhysicObject>(40.0f,0.6f);
    for (auto i=1;i<=4;i++) {
        for (auto j=1;j<=4;j++) {
            auto* x=EmplaceClone(*game_object);
            x->GlobalMoveTransform({i*100.0f,j*100.0f});
         }
    }
   debugMenu->AddPrintList({"ms:{}",&m_precedentFrameTime,Type::FLOAT});
    debugMenu->AddPrintList({"FPS:{}",&fps,Type::FLOAT});
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

void Game::MarkForDeletion(GameObject *p_gameObject) {
    m_ToDelete.push_back(p_gameObject);
}

void Game::exit() {
    for (const auto& gameObject:m_children) {
        delete gameObject;
    }
    m_children.clear();
    m_window.close();
    std::cout << "Fereastra a fost inchisa\n";
}

void Game::handleEvents() {
    while(const std::optional event = getWindow().pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            exit();
        }
        else if (event->is<sf::Event::Resized>()) {
            std::cout << "New width: " << getWindow().getSize().x << '\n'
                      << "New height: " << getWindow().getSize().y << '\n';
        }
        else if (event->is<sf::Event::KeyPressed>()) {
            const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
            if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                exit();
            }
        }else if (event->is<sf::Event::MouseButtonPressed>()) {
            const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>();
            std::cout << "X: " << (keyPressed->position.x)<<",Y: "<<keyPressed->position.y ;
        }
    }
}

void Game::processGameFrame() {
    sf::Time deltaTime = m_clock.getElapsedTime();
    m_totalTime+=deltaTime.asSeconds();
    m_clock.restart();
    handleEvents();
    if (isRunning()) {
        for (const auto& gameObject:m_gameObjects) {
            gameObject->update(deltaTime.asSeconds());
        }
        renderAll();
        m_precedentFrameTime=deltaTime.asSeconds();
        fps=1.0f/deltaTime.asSeconds();
        std::set<GameObject*> m_ToDeleteSet(m_ToDelete.begin(), m_ToDelete.end());
        for (auto* gameObject:m_ToDeleteSet) {
            gameObject->SetParent(nullptr);
            delete gameObject;
        }
        m_ToDelete.clear();
    }

}



