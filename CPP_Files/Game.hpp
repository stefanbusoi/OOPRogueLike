#pragma once

#include <iostream>
#include <set>

#include <SFML/Graphics.hpp>

#include "GameObject.hpp"
#include "Camera.hpp"
#include "gameObjectComp.hpp"

class Game :public GameObject{
    sf::RenderWindow window;
    sf::Clock clock;
    Camera* camera;
    static Game* instance;
    void RenderAll();
    std::set<Collider*> m_colliders;
    std::set<GameObject*,gameObjectComp> gameObjects;
    std::set<IRenderable*,iRendableComp> m_renderableObjects;

public:
    static Game *getInstance();
    Game(sf::VideoMode video_mode, const std::string &Title);
    ~Game() override;
    bool IsRunning() const;
    sf::RenderWindow &getWindow() {return window;}
    Camera& getCamera() const {return *camera;}
    void Exit();
    float ProcessGameFrame();
    std::set<GameObject*,gameObjectComp>& getGameObjects(){return gameObjects;}
    std::set<IRenderable*,iRendableComp>& getRenderOrder(){return m_renderableObjects;};
    std::set<Collider*>& getColliders(){return m_colliders;}
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

};



