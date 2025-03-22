//
// Created by stefa on 3/12/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <ostream>

#include "GameObject.hpp"
#include "IRenderable.hpp"


class Player :public GameObject,public IRenderable{
    void update(float deltaT) override;
    void Render() override;

public:
    ~Player() override;

    Player(const Player &other);

    Player(Player &&other) noexcept;

    Player & operator=(const Player &other);

    Player & operator=(Player &&other) noexcept;

private:
    friend std::ostream & operator<<(std::ostream &os, const Player &obj);

public:
    Player( const std::string &name="NONNAME", const sf::Transform &transform=sf::Transform::Identity,GameObject* parent=nullptr);
    Player()=delete;
};


#endif //PLAYER_H
