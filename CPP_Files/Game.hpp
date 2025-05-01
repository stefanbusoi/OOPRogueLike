#pragma once
#include <functional>
#include <iostream>
#include <set>

#include <SFML/Graphics.hpp>

#include "GameObject.hpp"
#include "Render/Camera.hpp"
#include "gameObjectComp.hpp"
class Collider;
class Game :public GameObject{
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    float m_totalTime;
    Camera* m_camera;
    sf::RenderTexture m_renderTexture;
    static Game* s_instance;
    void renderAll();
    std::set<Collider*> m_colliders;
    std::set<GameObject*,gameObjectComp> m_gameObjects;
    std::set<IRenderable*,iRendableComp> m_renderableObjects;
    float m_precedentFrameTime;
public:
    static Game *getInstance();

    Game(sf::VideoMode video_mode, const std::string &Title);
    ~Game() override;
    bool isRunning() const;
    sf::RenderWindow &getWindow() {return m_window;}
    sf::RenderTexture &getRenderTexture() {return m_renderTexture;}
    Camera& getCamera() const {return *m_camera;}
   [[maybe_unused]] sf::Clock &getClock() {return m_clock;}
    float getTotalTime(){return m_totalTime;}
    float getPrecedentFrameTime(){return m_precedentFrameTime;}
    bool IsInHirarchy(GameObject *p_gameObject);
    void exit();
    void handleEvents();
    void processGameFrame();
    std::set<GameObject*,gameObjectComp>& getGameObjects(){return m_gameObjects;}
    std::set<IRenderable*,iRendableComp>& getRenderObjects(){return m_renderableObjects;};
    std::set<Collider*>& getColliders(){return m_colliders;}
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

};



