
#include "Game.hpp"
#include "Render/GameMapRenderer.hpp"
#include "Entityies/Player.hpp"
#include "Render/PostProcessingShader.h"
#include <SFML/Graphics.hpp>

#include "Entityies/EntitySpawner.hpp"
#include "Entityies/EntityHealth.hpp"
#include "Entityies/BasicEnemy.hpp"
#include "Exceptions/GameLogicException.hpp"
#include "Utilityies/TransformUtilityies.hpp"
#include "UI/DebugMenu.hpp"
#include "Render/ShapeRenderer.hpp"
#include "Collisions/ColliderManager.hpp"
#include "Entityies/EnemySpawnerManager.h"
#include "UI/HealtBar.h"
std::weak_ptr<Game> Game::s_instance = std::weak_ptr<Game>();

void Game::renderAll() {
  m_window.display();
  m_window.clear();
  for (const auto &gameObject: m_renderableObjects) { gameObject->render(); }
  m_renderTexture.display();
  sf::Sprite sprite(m_renderTexture.getTexture());
  m_window.draw(sprite);
}
std::shared_ptr<Game> Game::getInstance(const sf::VideoMode video_mode, const std::string &Title) {
  if (!s_instance.expired())  {
    throw GameLogicException("paramaterised getInstance should be called only once");
  }
  auto instance = std::shared_ptr<Game>(new Game(video_mode, Title));
  s_instance=instance;
  return instance;
}

std::shared_ptr<Game> Game::getInstance() {
  if (s_instance.expired()) {
    throw GameLogicException("paramaterised get instance is not called, please call Game::getInstance(sf::VideoMode video_mode,std::string Title)");
  }
  return s_instance.lock();
}

Game::Game(const sf::VideoMode video_mode, const std::string &Title): BaseGameObject(Title) {
    m_window.create(video_mode, Title, sf::State::Windowed);
  if (!m_renderTexture.resize(m_window.getSize())) {
    throw std::runtime_error("Failed to resize render texture");
  }
}

void Game::init() {
  m_totalTime=0.0f;
  sf::Transform playerPos=sf::Transform::Identity;
  playerPos.translate({-200,800});
  emplaceGameObject<ColliderManager>();
  emplaceGameObject<GameMapRenderer>("GameMap");
  emplaceGameObject<PostProcessingShader>("Pixelate", std::filesystem::path("Shaders/Pixelate.frag"));
  emplaceGameObject<PostProcessingShader>("PostProcessingShader", std::filesystem::path("Shaders/PostProcessingShader.frag"));
  emplaceGameObject<EnemySpawnerManager>();
  player_ = emplaceGameObject<Player>("Player",playerPos);
  m_camera = emplaceGameObject<Camera>("Camera");
  emplaceGameObject<HealtBar>();

  sf::Transform transform = sf::Transform::Identity;
  transform.scale({40.0f, 40.0f});
  auto game_object = std::make_shared<BaseGameObject>("GameObject", transform);
  game_object->emplaceGameObject<Collider>(ColliderMask::Enemy, GeometryShape::Rectangle, sf::Transform::Identity);
  game_object->emplaceGameObject<ShapeRenderer>("CircleRenderer", sf::Transform::Identity, sf::Color(0, 255, 255), RenderOrder::Player, GeometryShape::Rectangle);
  for (auto i = -3; i <= 3; i++) {
    for (auto j = -3; j <= 3; j++) {
      if (abs(i)==3||abs(j)==3) {
        const auto x = emplaceClone(game_object);
        x->getLocalTransform().scale({ 25.0f, 25.0f}).rotate(sf::radians(cos(i) * 12 + sin(j)*20));
        x->globalMoveTransform({i * 900.0f, j * 900.0f});
      }
    }
  }
  std::shared_ptr<BasicEnemy> enemy=std::make_shared<BasicEnemy>("Enemy");
  enemy->setMovementSpeed(500.0f);
  for (auto i =- 2; i <= 2; i++) {
    for (auto j = -2; j <= 2; j++) {
      sf::Transform tr;
      tr.translate({-i * 800.0f, -j * 800.0f});
      emplaceGameObject<EntitySpawner>(tr,3,enemy);
    }
  }
  auto debugMenu = emplaceGameObject<DebugMenu>("DebugMenu");
  debugMenu->AddPrintList("ms:{}", &m_precedentFrameTime, Type::FLOAT);
  debugMenu->AddPrintList("FPS:{}", &fps, Type::FLOAT);
  debugMenu->AddPrintList("NrGameObj:{}", &m_nrGameObjects, Type::INT);
  debugMenu->AddPrintList("NrRenderObj:{}", &m_nrIrenderable, Type::INT);
  debugMenu->AddPrintList("NrColliders:{}", &m_nrColliders, Type::INT);
}

Game::~Game() { if (isRunning()) exit(); }
bool Game::isRunning() const { return m_window.isOpen(); }

void Game::addGameObjectToGame() {
}

void Game::removeGameObjectFromGame() {
}

bool Game::isActiveInHirarchy(std::weak_ptr<BaseGameObject> p_gameObject) {
  if (p_gameObject.expired()) return false;
  while (!p_gameObject.lock()->getParent().expired()) {
    if (!p_gameObject.lock()->isActive()) return false;
    p_gameObject = p_gameObject.lock()->getParent();
  }
  if (p_gameObject.lock() == getInstance()) return true;
  return false;
}

bool Game::isInHirarchy(std::weak_ptr<BaseGameObject> p_gameObject) {
  if (p_gameObject.expired()) return false;
  while (!p_gameObject.lock()->getParent().expired()) {
    p_gameObject = p_gameObject.lock()->getParent();
  }
  if (p_gameObject.lock() == getInstance()) return true;
  return false;
}

void Game::exit() {
  m_children.clear();
  m_window.close();
  std::cout << "Fereastra a fost inchisa\n";
}
void Game::restartGame() {
  m_children.clear();
  init();
}
sf::Time Game::calculateDeltaTime() {
  sf::Time deltaTime = m_clock.getElapsedTime();
  m_clock.restart();
  m_totalTime += deltaTime.asSeconds();
  m_precedentFrameTime = deltaTime.asSeconds();
  fps = 1.0f / deltaTime.asSeconds();
  return deltaTime;
}

void Game::handleEvents() {
  while (const std::optional event = getWindow().pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      exit();
    } else if (event->is<sf::Event::KeyPressed>()) {
      const auto *keyPressed = event->getIf<sf::Event::KeyPressed>();
      if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
        exit();
      }
      if (keyPressed->scancode==sf::Keyboard::Scancode::L) {
        restartGame();
      }
    }
  }
}



void Game::processGameFrame() {
  sf::Time deltaTime = calculateDeltaTime();

  m_nrColliders = m_colliders.size();
  m_nrIrenderable = m_renderableObjects.size();
  m_nrGameObjects = m_gameObjects.size();

  handleEvents();

  if (isRunning()) {
    frameIsRunning = true;
    std::vector<std::weak_ptr<BaseGameObject> > p_gameObjects;
    for (auto gameObject: m_gameObjects) {
      p_gameObjects.push_back(gameObject->weak_from_this());
    }
    for (const auto &gameObject: p_gameObjects) {
      if (!gameObject.expired()) {
        gameObject.lock()->update(deltaTime.asSeconds());
      }
    }

    renderAll();

  }
}
