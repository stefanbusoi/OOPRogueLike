#pragma once
#include <functional>
#include <iostream>
#include <set>

#include <SFML/Graphics.hpp>

#include "GameObject.hpp"
#include "Render/Camera.hpp"
#include "gameObjectComp.hpp"
class Collider;

class Game : public GameObject {
  sf::RenderWindow m_window;
  sf::Clock m_clock;
  float m_totalTime;
  float m_precedentFrameTime;
  float fps;
  std::weak_ptr<Camera> m_camera;
  sf::RenderTexture m_renderTexture;
  static Game *s_instance;
  std::weak_ptr<Player> player_;
  std::vector<std::shared_ptr<GameObject> > m_ToInactive;

  std::set<Collider *, ColliderComp> m_colliders;
  std::set<GameObject *, gameObjectComp> m_gameObjects;
  std::set<IRenderable *, iRendableComp> m_renderableObjects;

  int m_nrColliders = 0;
  int m_nrGameObjects = 0;
  int m_nrIrenderable = 0;

  bool frameIsRunning = false;

  void renderAll();

  void handleEvents();

public:
  static Game *getInstance();

  Game(sf::VideoMode video_mode, const std::string &Title);

  void Init() override;

  ~Game() override;

  bool isRunning() const;

  bool IsActiveInHirarchy(std::weak_ptr<GameObject> p_gameObject);

  sf::RenderWindow &getWindow() { return m_window; }
  sf::RenderTexture &getRenderTexture() { return m_renderTexture; }
  std::weak_ptr<Camera> getCamera() const { return m_camera; }
  float getTotalTime() { return m_totalTime; }
  float getPrecedentFrameTime() { return m_precedentFrameTime; }

  bool IsInHirarchy(std::weak_ptr<GameObject> p_gameObject);

  void MarkForUnactive(std::shared_ptr<GameObject> p_gameObject);

  void exit();

  sf::Time CalculateDeltaTime();

  void processGameFrame();

  std::set<GameObject *, gameObjectComp> &getGameObjects() { return m_gameObjects; }
  std::set<IRenderable *, iRendableComp> &getRenderObjects() { return m_renderableObjects; };
  std::set<Collider *, ColliderComp> &getColliders() { return m_colliders; }

  Game(const Game &) = delete;

  Game &operator=(const Game &) = delete;
};
