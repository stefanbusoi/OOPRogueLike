//
// Created by stefa on 3/10/2025.
//

#include "Camera.hpp"


#include "../Game.hpp"
#include "../UtilityiesFunctions.hpp"
#include "../Exceptions/GameLogicException.hpp"

void Camera::print(std::ostream &os) const {
        os<<"Class Camera";
        GameObject::print(os);
}

Camera::~Camera() {
}

Camera::Camera( const std::string &name, const sf::Transform &transform,GameObject* parent):GameObject(name,transform,parent),m_window(&Game::getInstance()->getWindow()) {
        for (const auto& player:Game::getInstance()->getChildrens()) {
                m_player=dynamic_cast<Player*>(player);
                if (m_player!=nullptr)
                        break;
        }
        if (m_player==nullptr)
                throw GameLogicException("Player does not exist");
        m_updateOrder=UpdateOrder::Camera;
}

sf::Transform& Camera::getTransform(){
        return m_transform;
}
void Camera::update([[maybe_unused]]float deltaT) {
        sf::Transform transform=sf::Transform::Identity;
        m_transform=transform.translate(Utils::getPosition(m_player->getGlobalTransform()));
}

[[maybe_unused]] float Camera::getViewRadius() const {return sf::Vector2f({m_window->getSize().x/-2.0f,m_window->getSize().y/-2.0f}).length()/2.0f;}

void Camera::draw(const sf::Drawable& drawable, const sf::Transform &transform) const {
        sf::Transform viewTransform=m_transform;
        viewTransform.translate({m_window->getSize().x/-2.0f,m_window->getSize().y/-2.0f});

        sf::Transform finalTransform = viewTransform.getInverse() * transform;
        Game::getInstance()->getRenderTexture().draw(drawable, finalTransform);
}

std::ostream & operator<<(std::ostream &os, const Camera &obj) {
        os<<"test";
         os<< "CLASS Camera " << static_cast<const GameObject &>(obj);
        return os;
}
