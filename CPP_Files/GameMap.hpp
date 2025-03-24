//
// Created by stefa on 3/16/2025.
//

#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <ostream>

#include "GameObject.hpp"
#include "IRenderable.hpp"
#include "SFML/Graphics/Shader.hpp"

class GameMap:public GameObject,public IRenderable{
    sf::Shader m_shader;
public:
    void Render() override;
    explicit GameMap( const std::string &name="NONNAME", const sf::Transform &transform=sf::Transform::Identity,GameObject* parent=nullptr);
    friend std::ostream & operator<<(std::ostream &os, const GameMap &obj);
    ~GameMap() override;
    void update(float deltaT) override;

};



#endif //GAMEMAP_H
