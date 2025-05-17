//
// Created by stefa on 3/11/2025.
//

#include "Game.hpp"

#include "GameMap.hpp"
#include "Player.hpp"
#include "Render/PostProcessingShader.h"
#include <SFML/Graphics.hpp>

#include "EntityHealth.hpp"
#include "Collisions/PhysicObject.hpp"
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

/**
 * Create a window and it initiate the first window
 * @param video_mode The video mode of the window
 * @param Title Title of the window
 */
Game::Game(const sf::VideoMode video_mode, const std::string &Title): GameObject(Title) {
    m_totalTime=0.0f;
    if (s_instance==nullptr) {
        s_instance=this;
    }
    m_window.create(video_mode, Title, sf::State::Fullscreen);
    if (!m_renderTexture.resize(m_window.getSize())) {
        throw std::runtime_error("Failed to resize render texture");
    }
    // m_window.setFramerateLimit(144);
}
void Game::Init() {

    player_=EmplaceGameObject<Player>("Player");
    m_camera=EmplaceGameObject<Camera>("Camera");
    EmplaceGameObject<GameMap>("GameMap");
    EmplaceGameObject<PostProcessingShader>("Pixelate",std::filesystem::path("Shaders/Pixelate.frag"));
    EmplaceGameObject<PostProcessingShader>("PostProcessingShader",std::filesystem::path("Shaders/PostProcessingShader.frag"));
    auto debugMenu=EmplaceGameObject<DebugMenu>("DebugMenu");

    sf::Transform transform=sf::Transform::Identity;
    transform.translate({100.0f,100.0f});
    transform.scale({40.0f,40.0f});
    std::shared_ptr<GameObject> game_object=std::make_shared<GameObject>("GameObject",transform);
    game_object->EmplaceGameObject<Collider>(CollisionType::Dynamic,ColliderMask::Enemy,GeometryShape::Circle,sf::Transform::Identity);
    game_object->EmplaceGameObject<PhysicObject>(40.0f,1.6f,1.0f);
    game_object->EmplaceGameObject<ShapeRenderer>("CircleRenderer",sf::Transform::Identity, sf::Color(0,255,255), RenderOrder::Player,GeometryShape::Circle);
    std::shared_ptr<EntityHealth> entityHealth=game_object->EmplaceGameObject<EntityHealth>(100.0f,100.0f);
    entityHealth->setOnDeath([](EntityHealth* entityHealth) {
        entityHealth->getParent().lock()->SetParent(nullptr);
    });
    for (auto i=1;i<=1;i++) {
        for (auto j=1;j<=1;j++) {
            const auto& x=EmplaceClone(game_object);
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


bool Game::IsActiveInHirarchy(std::weak_ptr<GameObject> p_gameObject) {
    if (p_gameObject.expired()) return false;

    while (!p_gameObject.expired()) {
        if (!p_gameObject.lock()->IsActive()) return false;
        p_gameObject=p_gameObject.lock()->getParent();
    }
    if (p_gameObject.lock().get()==getInstance()) return true;
    return false;
}
bool Game::IsInHirarchy(std::weak_ptr<GameObject> p_gameObject) {

    if (p_gameObject.expired()) return false;

    while (!p_gameObject.lock()->getParent().expired()) {
        p_gameObject=p_gameObject.lock()->getParent();
    }
    if (p_gameObject.lock().get()==getInstance()) return true;
    return false;
}


void Game::MarkForUnactive(std::shared_ptr<GameObject> p_gameObject) {
    if (p_gameObject==nullptr) return;
    m_ToInactive.push_back(p_gameObject);
}

void Game::exit() {
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
            std::cout << "X: " << keyPressed->position.x<<",Y: "<<keyPressed->position.y ;
        }
    }
}

void Game::processGameFrame() {
    sf::Time deltaTime = m_clock.getElapsedTime();
    m_totalTime+=deltaTime.asSeconds();
    m_clock.restart();
    handleEvents();
    if (isRunning()) {
        frameIsRunning=true;
        std::vector<std::weak_ptr<GameObject>> p_gameObjects;
        for (auto gameObject:m_gameObjects) {
            p_gameObjects.push_back(gameObject->weak_from_this());
        }
        for (const auto& gameObject:p_gameObjects) {
            if (!gameObject.expired()) {
                gameObject.lock()->update(deltaTime.asSeconds());
            }
        }
        renderAll();
        m_precedentFrameTime=deltaTime.asSeconds();
        fps=1.0f/deltaTime.asSeconds();
        for (auto gameObject:m_ToInactive) {
            gameObject->RemoveGameObjectFromGame();
        }
        m_ToInactive.clear();
    }
}



