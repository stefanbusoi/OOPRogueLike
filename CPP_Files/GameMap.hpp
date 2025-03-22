//
// Created by stefa on 3/16/2025.
//

#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <ostream>

#include "GameObject.hpp"
#include "IRenderable.hpp"


class GameMap:public GameObject,public IRenderable{
    friend std::ostream & operator<<(std::ostream &os, const GameMap &obj);

public:
    void Render() override;
    GameMap( const std::string &name="NONNAME", const sf::Transform &transform=sf::Transform::Identity,GameObject* parent=nullptr);

    ~GameMap() override;

    void update(float deltaT) override;

};



#endif //GAMEMAP_H
