#pragma once

#include <iostream>
#include <set>

#include <SFML/Graphics.hpp>

#include "GameObject.hpp"
#include "Camera.hpp"
#include "gameObjectComp.hpp"

class Game :public GameObject{
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    float m_totalTime;
    Camera* m_camera;
    static Game* s_instance;
    void renderAll();
    std::set<Collider*> m_colliders;
    std::set<GameObject*,gameObjectComp> m_gameObjects;
    std::set<IRenderable*,iRendableComp> m_renderableObjects;

public:
    static Game *getInstance();
    Game(sf::VideoMode video_mode, const std::string &Title);
    ~Game() override;
    bool isRunning() const;
    sf::RenderWindow &getWindow() {return m_window;}
    Camera& getCamera() const {return *m_camera;}
    sf::Clock &getClock() {return m_clock;}
    float getTotalTime(){return m_totalTime;}
    void exit();
    float processGameFrame();
    std::set<GameObject*,gameObjectComp>& getGameObjects(){return m_gameObjects;}
    std::set<IRenderable*,iRendableComp>& getRenderOrder(){return m_renderableObjects;};
    std::set<Collider*>& getColliders(){return m_colliders;}
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

};



