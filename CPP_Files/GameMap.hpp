//
// Created by stefa on 3/16/2025.
//

#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <ostream>

#include "GameObject.hpp"
#include "Render/IRenderable.hpp"
#include "SFML/Graphics/Shader.hpp"

class GameMap:public GameObject,public IRenderable{
    sf::Shader m_shader;

protected:
    void print(std::ostream &os) const override;

public:
    void Render() override;
    explicit GameMap( const std::string &name="NONNAME", const sf::Transform &transform=sf::Transform::Identity);
    void update(float deltaT) override;

    void AddGameObjectToGame() override;

    void RemoveGameObjectFromGame() override;
};



#endif //GAMEMAP_H
