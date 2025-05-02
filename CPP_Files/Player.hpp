#pragma once

#include <ostream>

#include "GameObject.hpp"
#include "Render/IRenderable.hpp"


class Player :public GameObject,public IRenderable{
    void update(float deltaT) override;
    void Render() override;

protected:
    void print(std::ostream &os) const override;

public:
    ~Player() override;
    void AddGameObjectToGame() override;
    void RemoveGameObjectFromGame() override;

    explicit Player( const std::string &name="NONNAME", const sf::Transform &transform=sf::Transform::Identity,GameObject* parent=nullptr);
    Player()=delete;
};


