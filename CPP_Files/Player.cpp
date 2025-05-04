#include "Render/Camera.hpp"
#include "Player.hpp"

#include <cmath>
#include <math.h>

#include "Game.hpp"
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
        speed=speed*deltaT*SpeedConst;
    }
    pos-={960,540};
    sf::Angle ang=Utils::getAngle(m_transform);
    GlobalMoveTransform(speed);
    m_transform.rotate(sf::radians(atan2f(-pos.x,pos.y)+ang.asRadians()));

}
void Player::Render() {
    const Camera& camera=Game::getInstance()->getCamera();
    sf::Transform transform=getGlobalTransform();

    sf::RectangleShape rect({10.0f,40.0f});
    rect.setOrigin({5, 0});

    rect.setFillColor(sf::Color(0, 0, 0));
    camera.draw(rect,transform);

}

void Player::print(std::ostream &os) const {
    os<<"CLASS Player:";
    GameObject::print(os);
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
    m_renderOrder=RenderOrder::PlayerWeapons;
    m_updateOrder=UpdateOrder::Default;
    sf::Transform tr=sf::Transform::Identity;
    tr.scale(sf::Vector2f(40.0f,40.0f));
    EmplaceGameObject<ShapeRenderer>("CircleRenderer",tr, sf::Color(0,255,0), RenderOrder::Player,GeometryShape::Circle);
    sf::Transform tr2=sf::Transform::Identity;
    tr2.scale(sf::Vector2f(40.0f,40.0f));
    EmplaceGameObject<Collider>(CollisionType::Dynamic,ColliderMask::Player,GeometryShape::Circle,112.0f,tr2);
    m_firearm=EmplaceGameObject<Firearm>("Firearm", sf::Transform::Identity);
}

