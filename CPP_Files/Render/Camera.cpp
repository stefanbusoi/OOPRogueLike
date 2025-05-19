//
// Created by stefa on 3/10/2025.
//

#include "Camera.hpp"


#include "../Game.hpp"
#include "../Utilityies/TransformUtilityies.hpp"
#include "../Exceptions/GameLogicException.hpp"

void Camera::print(std::ostream &os) const {
        os<<"Class Camera";
        GameObject::print(os);
}


Camera::Camera( const std::string &name, const sf::Transform &transform):GameObject(name,transform),m_window(&Game::getInstance()->getWindow()){
        m_player=Game::getInstance()->GetGameObjectOfType<Player>();
        if (m_player.expired())
                throw GameLogicException("Player does not exist");
        m_updateOrder=UpdateOrder::Camera;
}

sf::Transform& Camera::getTransform(){
        return m_transform;
}
void Camera::update([[maybe_unused]]float deltaT) {
        sf::Transform transform=sf::Transform::Identity;
        m_transform=transform.translate(Utils::getPosition(m_player.lock()->getGlobalTransform()));
}


void Camera::draw(const sf::Drawable& drawable, const sf::Transform &transform) const {
        sf::Transform viewTransform=m_transform;
        viewTransform.translate({m_window->getSize().x/-2.0f,m_window->getSize().y/-2.0f});

        sf::Transform finalTransform = viewTransform.getInverse() * transform;
        Game::getInstance()->getRenderTexture().draw(drawable, finalTransform);
}

std::ostream & operator<<(std::ostream &os, const Camera &obj) {

         os<< "CLASS Camera " << static_cast<const GameObject &>(obj);
        return os;
}
