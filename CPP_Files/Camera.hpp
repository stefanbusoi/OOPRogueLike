#pragma once
#include <SFML/Graphics.hpp>

#include "GameObject.hpp"
#include "Player.hpp"

class Camera:public GameObject{

    sf::RenderWindow* m_window;
    Player* m_player=nullptr;
public:
    friend std::ostream & operator<<(std::ostream &os, const Camera &obj);
    ~Camera() override;

    Camera(const Camera &other)
        : GameObject(other),
          m_window(other.m_window),
          m_player(other.m_player) {
    }

    Camera(Camera &&other) noexcept
        : GameObject(std::move(other)),
          m_window(other.m_window),
          m_player(other.m_player) {
    }

    Camera & operator=(const Camera &other) {
        if (this == &other)
            return *this;
        GameObject::operator =(other);
        m_window = other.m_window;
        m_player = other.m_player;
        return *this;
    }

    Camera & operator=(Camera &&other) noexcept {
        if (this == &other)
            return *this;
        GameObject::operator =(std::move(other));
        m_window = other.m_window;
        m_player = other.m_player;
        return *this;
    }

    explicit Camera( const std::string &name="Camera", const sf::Transform &transform=sf::Transform::Identity,GameObject* parent=nullptr);
    sf::Transform& getTransform() ;
    void draw(const sf::Drawable &drawable, const sf::Transform &transform) const;
    [[maybe_unused]]void setTransform(const sf::Transform &transform){m_transform=transform;}
    void update(float deltaT) override;
    float getViewRadius() const;
};

