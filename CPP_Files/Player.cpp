#include "Player.hpp"


#include "Game.hpp"
#include "Collisions/PhysicObject.hpp"
#include "Utilityies/TransformUtilityies.hpp"
#include "Render/ShapeRenderer.hpp"
#include "Weapons/Firearm.hpp"


void Player::update(float deltaT)  {
    float SpeedConst=5000;
    sf::Vector2i pos=sf::Mouse::getPosition();
    sf::Vector2f speed;
    if (isKeyPressed(sf::Keyboard::Scancode::A)) {
        speed+=sf::Vector2f({-1.0f,0.0f});
    }
    if (isKeyPressed(sf::Keyboard::Scancode::D)) {
        speed+=sf::Vector2f({1.0f,0.0f});
    }
    if (isKeyPressed(sf::Keyboard::Scancode::W)) {
        speed+=sf::Vector2f({0.0f,-1.0f});
    }
    if (isKeyPressed(sf::Keyboard::Scancode::S)) {
        speed+=sf::Vector2f({0.0f,1.0f});
    }
    if (speed.x!=0||speed.y!=0) {
        speed=speed.normalized();
        speed=speed*SpeedConst;
    }
    pos-={960,540};
    sf::Angle ang=Utils::getAngle(m_transform);
    m_phisicsObject->setAcceleration(speed);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        m_firearm->Fire();
    }
    if (isKeyPressed(sf::Keyboard::Scancode::G)) {
        m_firearm->setActive(false);
    }
    if (isKeyPressed(sf::Keyboard::Scancode::F)) {
        m_firearm->setActive(true);
    }
    m_transform.rotate(sf::radians(atan2f(-pos.x,pos.y)+ang.asRadians()));
    (void)deltaT;

}

void Player::Init() {
    GameObject::Init();
    sf::Transform tr=sf::Transform::Identity;
    tr.scale(sf::Vector2f(40.0f,40.0f));

    EmplaceGameObject<ShapeRenderer>("CircleRenderer",tr, sf::Color(0,255,0), RenderOrder::Player,GeometryShape::Circle);
    EmplaceGameObject<Collider>(ColliderMask::Player,GeometryShape::Circle,tr);

    m_phisicsObject=EmplaceGameObject<PhysicObject>(100.0f,12.f,0.0f);
    m_firearm=EmplaceGameObject<Firearm>("Firearm", sf::Transform::Identity);
}

void Player::print(std::ostream &os) const {
    os<<"CLASS Player:";
    GameObject::print(os);
}


void Player::AddGameObjectToGame() {
    GameObject::AddGameObjectToGame();
 }

void Player::RemoveGameObjectFromGame() {
    GameObject::RemoveGameObjectFromGame();
 }

Player::Player( const std::string &name, const sf::Transform &transform): GameObject(name, transform) {
    m_updateOrder=UpdateOrder::Default;
}

