//
// Created by stefa on 3/16/2025.
//

#include "GameMap.hpp"

#include <iostream>

#include "Game.hpp"

void GameMap::Render() {
    Camera &camera=Game::getInstance()->getCamera();
    float dist=camera.getViewRadius()+300;
    sf::RectangleShape rect;
    for (int i=-5;i<5;i++)
    for (int j=-5;j<5;j++) {

        sf::Transform transform=sf::Transform::Identity;
        transform.translate(sf::Vector2f(i,j)*100.0f);
        float squareDist= (transform.transformPoint({0,0})-camera.getTransform().transformPoint({0,0})).length();
        if (squareDist<dist) {
            rect.setSize(sf::Vector2f(100,100));
            rect.setFillColor((i+j)%2==0?sf::Color(50,50,50,255*((dist-squareDist)/dist)):sf::Color(20,20,20,255*((dist-squareDist)/dist)));
            camera.draw(rect,transform);
        }
    }
}

GameMap::GameMap( const std::string &name, const sf::Transform &transform,GameObject* parent):GameObject(name,transform,parent) {
    std::cout<<"Game Map Constructor\n";
    m_renderOrder=RenderOrder::Terrain;
    m_updateOrder=UpdateOrder::Default;
}

GameMap::~GameMap() {
    std::cout<<"GameMap Destructor\n";
}

void GameMap::update(float deltaT) {
    (void)deltaT;
}

std::ostream & operator<<(std::ostream &os, const GameMap &obj) {
    return os<<"CLASS GameMap "<< static_cast<const GameObject &>(obj);
}
