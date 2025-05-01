#include "Render/Camera.hpp"
#include "Player.hpp"

#include <cmath>
#include <math.h>

#include "Game.hpp"
#include "UtilityiesFunctions.hpp"


Player::~Player() = default;

void Player::update(float deltaT)  {
    float SpeedConst=500;
    sf::Vector2i pos=sf::Mouse::getPosition();
    sf::Vector2f speed;
    if (isKeyPressed(sf::Keyboard::Scancode::A)) {
        speed+=sf::Vector2f({-1.0f,0.0f});
    }
    if (isKeyPressed(sf::Keyboard::Scancode::D)) {
        speed+=sf::Vector2f({1.0f,0.0f});
    }
    if (isKeyPressed(sf::Keyboard::Scancode::W)) {
        speed+=sf::Vector2f({0.0f,1.0f});
    }
    if (isKeyPressed(sf::Keyboard::Scancode::S)) {
        speed+=sf::Vector2f({0.0f,-1.0f});
    }
    if (speed.x!=0||speed.y!=0) {
        speed=speed.normalized();
        speed=speed*deltaT*SpeedConst;
    }
    pos-={960,540};
    sf::Angle ang=Utils::getAngle(m_transform);
     speed= speed.rotatedBy(ang);
    m_transform.rotate(sf::radians(atan2f(-pos.x,pos.y)+ang.asRadians()));
    m_transform.translate(speed);
}
void Player::Render() {
    const Camera& camera=Game::getInstance()->getCamera();
    sf::Transform transform=m_transform;

    sf::CircleShape shape(40.f);
    shape.setOrigin({40, 40});
    shape.setFillColor(sf::Color(100, 250, 50));
    camera.draw(shape,transform);

    sf::RectangleShape rect({10.0f,40.0f});
    rect.setOrigin({5, 0});

    rect.setFillColor(sf::Color(0, 0, 0));
    camera.draw(rect,transform);

}


void Player::AddGameObjectToGame() {
    GameObject::AddGameObjectToGame();
    IRenderable::AddToRenderObjects();
}

void Player::RemoveGameObjectFromGame() {
    GameObject::RemoveGameObjectFromGame();
    IRenderable::RemoveFromRenderObjects();
}

Player::Player( const std::string &name, const sf::Transform &transform,GameObject* parent): GameObject(name, transform,parent) {
    m_renderOrder=RenderOrder::Player;
    m_updateOrder=UpdateOrder::Default;

    //this->addCollider();
}

std::ostream & operator<<(std::ostream &os, const Player &obj) {
    return os <<"CLASS Player "<<static_cast<const GameObject &>(obj);
}
