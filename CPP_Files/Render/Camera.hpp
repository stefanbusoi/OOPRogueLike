#pragma once
#include <SFML/Graphics.hpp>

#include "../GameObject.hpp"
#include "../Player.hpp"

class Camera:public GameObject{

    sf::RenderWindow* m_window;
    Player* m_player=nullptr;

protected:
    void print(std::ostream &os) const override;

public:
    friend std::ostream & operator<<(std::ostream &os, const Camera &obj);
    ~Camera() override;
    explicit Camera( const std::string &name="Camera", const sf::Transform &transform=sf::Transform::Identity,GameObject* parent=nullptr);



    sf::Transform& getTransform() ;
    void draw(const sf::Drawable &drawable, const sf::Transform &transform) const;
    [[maybe_unused]]void setTransform(const sf::Transform &transform){m_transform=transform;}
    void update(float deltaT) override;
    float getViewRadius() const;
};

