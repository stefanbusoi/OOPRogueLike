//
// Created by stefa on 3/10/2025.
//

#include "Camera.hpp"

#include <cmath>

#include "Game.hpp"

Camera::~Camera() {
}

Camera::Camera( const std::string &name, const sf::Transform &transform,GameObject* parent):GameObject(name,transform,parent),m_window(&Game::getInstance()->getWindow()) {
        for (const auto& player:Game::getInstance()->getChildrens()) {
                m_player=dynamic_cast<Player*>(player);
                if (m_player!=nullptr)
                        break;
        }
        m_updateOrder=UpdateOrder::Camera;
}

sf::Transform& Camera::getTransform(){
        return m_transform;
}
void Camera::update([[maybe_unused]]float deltaT) {
m_transform=m_player->getGlobalTransform();
}

float Camera::getViewRadius() const {return sf::Vector2f({m_window->getSize().x/-2.0f,m_window->getSize().y/-2.0f}).length()/2.0f;}

void Camera::draw(const sf::Drawable& drawable, const sf::Transform &transform) const {
        sf::Transform tr=m_transform;
        tr.translate({m_window->getSize().x/-2.0f,m_window->getSize().y/-2.0f});
        m_window->draw(drawable,tr.getInverse()*transform);
}

std::ostream & operator<<(std::ostream &os, const Camera &obj) {
        return os<< "CLASS Camera " << static_cast<const GameObject &>(obj);
}
