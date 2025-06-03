#pragma once
#include <functional>
#include <iostream>
#include <set>

#include <SFML/Graphics.hpp>

#include "CoreFunctionality/BaseGameObject.hpp"
#include "Render/Camera.hpp"
#include "CoreFunctionality/gameObjectComp.hpp"
class Collider;

/**
 * This is the base class of the game
 * Manages the global state of the game and manages all objects
 */
class Game : public BaseGameObject {
  sf::RenderWindow m_window;
  sf::Clock m_clock;
  float m_totalTime{0.0f};
  float m_precedentFrameTime{0.0f};
  float fps{0.0f};
  std::weak_ptr<Camera> m_camera;
  sf::RenderTexture m_renderTexture;
  static std::weak_ptr<Game> s_instance;
  std::weak_ptr<Player> player_;

  std::set<Collider *, ColliderComp> m_colliders;
  std::set<BaseGameObject *, gameObjectComp> m_gameObjects;
  std::set<IRenderable *, iRendableComp> m_renderableObjects;

  int m_nrColliders = 0;
  int m_nrGameObjects = 0;
  int m_nrIrenderable = 0;

  bool frameIsRunning = false;

  Game(sf::VideoMode video_mode, const std::string &Title);

  void renderAll();
  void handleEvents();
public:

  /**
   *
   * @return the instance of the game, it can only be called if an instance already exists
   */
  static std::shared_ptr<Game> getInstance();
  /**
   * This can be only called once
   * @param video_mode VideoMode of the game Window
   * @param Title Title of the Game
   * @return an instance of the game
   */
  static std::shared_ptr<Game> getInstance(sf::VideoMode video_mode, const std::string &Title);

  void init() override;
  ~Game() override;
  bool isRunning() const;

  void addGameObjectToGame() override;

  void removeGameObjectFromGame() override;

  /**
   *
   * @param p_gameObject
   * @return checks if p_gameObject is active in Game hirarchy, if any node between Game and p_gameObject is inactive it returns false
   */
  bool isActiveInHirarchy(std::weak_ptr<BaseGameObject> p_gameObject);

  sf::RenderWindow &getWindow() { return m_window; }
  sf::RenderTexture &getRenderTexture() { return m_renderTexture; }
  std::weak_ptr<Camera> getCamera() const { return m_camera; }
  /**
   *
   * @return Total time from the game start
   */
  float getTotalTime() { return m_totalTime; }
  /**
   *
   * @return Time passesd since the last frame
   */
  float getPrecedentFrameTime() { return m_precedentFrameTime; }

  /**
   *
   * @param p_gameObject
   * @return Check if p_gameObject is inside Hirarchy
   */
  bool isInHirarchy(std::weak_ptr<BaseGameObject> p_gameObject);


  /**
   * Close the gameWindow and clear all objects
   */
  void exit();

  /**
   * Restarts Total game time and reinitialise all objects
   */
  void restartGame();

  /**
   * Shoud only be called once every frame
   * @return Calculate the delta time of the current frame
   */
  sf::Time calculateDeltaTime();

  /**
   * Proces one frame of the game
   */
  void processGameFrame();

  /**
   * 
   * @return Returns all active GameObjects
   */
  std::set<BaseGameObject *, gameObjectComp> &getGameObjects() { return m_gameObjects; }
  /**
   * 
   * @return Returns a set of all active Renerable objects
   */
  std::set<IRenderable *, iRendableComp> &getRenderObjects() { return m_renderableObjects; };
  /**
   * 
   * @return Returns a set of all active colliders
   */
  std::set<Collider *, ColliderComp> &getColliders() { return m_colliders; }

  Game(const Game &) = delete;

  Game &operator=(const Game &) = delete;
};
