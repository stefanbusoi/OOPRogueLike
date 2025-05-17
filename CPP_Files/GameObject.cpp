//
// Created by stefa on 3/11/2025.
//

#include "GameObject.hpp"
#include "gameObjectComp.hpp"
#include <utility>

#include "Game.hpp"
#include "Collisions/Collider.h"
int GameObject::s_globalId = 0;

GameObject::GameObject(std::string name,sf::Transform transform):
    m_transform(transform),
    m_name(std::move(name)) {

}


GameObject::~GameObject() {
    GameObject::RemoveGameObjectFromGame();
    GameObject::SetParent(std::weak_ptr<GameObject>());
    m_children.clear();
}
void GameObject::SetParent(std::weak_ptr<GameObject> p_parent) {
    std::shared_ptr<Game> instance=Game::getInstance();
    if (instance->IsInHirarchy(shared_from_this())&&instance->IsInHirarchy(p_parent)) {
        m_transform=p_parent.lock()->getGlobalTransform().getInverse()*getGlobalTransform();
    }
    if (!instance->IsInHirarchy(shared_from_this())&&instance->IsInHirarchy(p_parent)) {
        AddGameObjectToGame();
    }
    if (instance->IsInHirarchy(shared_from_this())&&!instance->IsInHirarchy(p_parent)) {
        RemoveGameObjectFromGame();
    }
    if (!m_parent.expired()) {
        m_parent.lock()->m_children.erase(shared_from_this());
    }
    if (!p_parent.expired()) {
        p_parent.lock()->m_children.insert(shared_from_this());
    }
    m_parent=p_parent;

}


void GameObject::setActive(bool isActive) {
    if (m_isActive==isActive) return;
    if (isActive) {
        if (Game::getInstance()->IsActiveInHirarchy(getParent())) {
            Game::getInstance()->AddGameObjectToGame();
        }
    }else {
        if (Game::getInstance()->IsActiveInHirarchy(getParent())) {
            Game::getInstance()->MarkForUnactive(shared_from_this());
        }
    }
    m_isActive=isActive;
}


void GameObject::update(float deltaT) {
    (void)deltaT;
    }

  std::shared_ptr<GameObject>  GameObject::clone() const {
    std::shared_ptr<GameObject> clone = std::make_shared<GameObject>();
    for (const std::shared_ptr<GameObject>& i:m_children) {
        clone->EmplaceClone(*i);
    }
    clone->m_transform = m_transform;
    clone->m_name =m_name;
    clone->m_parent.reset();
    clone->m_updateOrder = m_updateOrder;
    return clone;
}


sf::Transform & GameObject::getLocalTransform() {
    return m_transform;
}

void GameObject::MoveTransform(sf::Vector2f movement) {
    m_transform.translate(movement);
}

void GameObject::GlobalMoveTransform(sf::Vector2f movement) {
    sf::Transform transform=sf::Transform::Identity;
    transform.translate(movement);
    m_transform=m_parent.lock()->getGlobalTransform().getInverse()*transform*getGlobalTransform();
}

void GameObject::AddGameObjectToGame() {
    Game::getInstance()->getGameObjects().insert(this);
    for (auto i:getChildrens()) {
        i->AddGameObjectToGame();
    }
}

void GameObject::RemoveGameObjectFromGame() {

    Game::getInstance()->getGameObjects().erase(this);
    for (auto i:getChildrens()) {
        i->RemoveGameObjectFromGame();
    }
}

sf::Transform GameObject::getGlobalTransform() const {
    if (!m_parent.expired()) {
        return m_parent.lock()->getGlobalTransform() * m_transform;
    }
    return m_transform;
}


void GameObject::print(std::ostream& os) const{
    os<<"Name: "<< m_name
            <<" Id:"<< m_localId
            << " GameObjects:{ ";
    for (const auto x:m_children) {
        os<<x->m_name<<" ";
    }
    os<<"}";
}
std::ostream & operator<<(std::ostream &os, const GameObject &obj) {
    obj.print(os);
    return os;
}
