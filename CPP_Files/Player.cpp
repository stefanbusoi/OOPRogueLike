#include "Render/Camera.hpp"
#include "Player.hpp"

#include <cmath>
#include <math.h>

#include "Game.hpp"
#include "PhysicObject.hpp"
#include "UtilityiesFunctions.hpp"
#include "Render/ShapeRenderer.hpp"
#include "Weapons/Firearm.hpp"

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
    m_phisicsObject->SetAcceleration(speed);
    m_transform.rotate(sf::radians(atan2f(-pos.x,pos.y)+ang.asRadians()));

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

Player::Player( const std::string &name, const sf::Transform &transform,GameObject* parent): GameObject(name, transform,parent) {
    m_updateOrder=UpdateOrder::Default;
    sf::Transform tr=sf::Transform::Identity;
    tr.scale(sf::Vector2f(40.0f,40.0f));
    EmplaceGameObject<ShapeRenderer>("CircleRenderer",tr, sf::Color(0,255,0), RenderOrder::Player,GeometryShape::Circle);
    sf::Transform tr2=sf::Transform::Identity;
    tr2.scale(sf::Vector2f(40.0f,40.0f));
    EmplaceGameObject<Collider>(CollisionType::Dynamic,ColliderMask::Player,GeometryShape::Circle,tr2);
    m_phisicsObject=EmplaceGameObject<PhysicObject>(100.0f,1.f);
    m_firearm=EmplaceGameObject<Firearm>("Firearm", sf::Transform::Identity);
}

