#include "Camera.hpp"
#include "Player.hpp"
#include "Game.hpp"


void Player::update(float deltaT)  {
    float SpeedConst=500;

    sf::Vector2f speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space)) {
        speed+=sf::Vector2f({-1.0f,0.0f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
       speed+=sf::Vector2f({-1.0f,0.0f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
        speed+=sf::Vector2f({1.0f,0.0f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
        speed+=sf::Vector2f({0.0f,-1.0f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
        speed+=sf::Vector2f({0.0f,1.0f});
    }
    if (speed.x!=0||speed.y!=0) {
        speed=speed.normalized();
        speed=speed*deltaT*SpeedConst;
    }

    m_transform.translate(speed);


}

Player::~Player() = default;

Player::Player(const Player &other): GameObject(other),
                                     IRenderable(other) {
}

Player::Player(Player &&other) noexcept: GameObject(std::move(other)),
                                         IRenderable(std::move(other)) {
}

Player & Player::operator=(const Player &other) {
    if (this == &other)
        return *this;
    GameObject::operator =(other);
    IRenderable::operator =(other);
    return *this;
}

Player & Player::operator=(Player &&other) noexcept {
    if (this == &other)
        return *this;
    GameObject::operator =(std::move(other));
    IRenderable::operator =(std::move(other));
    return *this;
}

void Player::Render() {
    const Camera& camera=Game::getInstance()->getCamera();
    sf::CircleShape shape(40.f);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(sf::Vector2f(-40,-40));
    sf::Transform transform=this->m_transform;

    camera.draw(shape,transform);
    static sf::Font font("../Minecraft.ttf");

    sf::Text text(font);
    text.setString(m_name);
    text.setPosition(sf::Vector2f(-20,-47));
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(20);

    camera.draw(text,m_transform);
}



Player::Player( const std::string &name, const sf::Transform &transform,GameObject* parent): GameObject(name, transform,parent) {
    m_renderOrder=RenderOrder::Player;
    m_updateOrder=UpdateOrder::Default;

    //this->addCollider();
}

std::ostream & operator<<(std::ostream &os, const Player &obj) {
    return os <<"CLASS Player "<<static_cast<const GameObject &>(obj);
}
