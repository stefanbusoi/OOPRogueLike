#pragma once

#include <ostream>

#include "GameObject.hpp"
#include "PhysicObject.hpp"
#include "Render/IRenderable.hpp"
#include "Weapons/Firearm.hpp"


class Player :public GameObject{
    void update(float deltaT) override;
    Firearm* m_firearm;
    PhysicObject * m_phisicsObject;

protected:
    void print(std::ostream &os) const override;

public:
    ~Player() override;
    void AddGameObjectToGame() override;
    void RemoveGameObjectFromGame() override;

    explicit Player( const std::string &name="NONNAME", const sf::Transform &transform=sf::Transform::Identity,GameObject* parent=nullptr);
    Player()=delete;
};


