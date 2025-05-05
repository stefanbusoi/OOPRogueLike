//
// Created by stefa on 3/11/2025.
//

#include "GameObject.hpp"
#include "gameObjectComp.hpp"
#include <iostream>
#include <utility>

#include "Game.hpp"
#include "Collider.h"
#include "Exceptions/GameLogicException.hpp"
int GameObject::s_globalId = 0;

GameObject::GameObject(std::string name,sf::Transform transform,GameObject *parent): m_localId(getGlobalId()),
    m_transform(transform),
    m_name(std::move(name)),
    m_parent(parent),
    m_updateOrder(UpdateOrder::Default) {
}


GameObject::~GameObject() {

    if (m_parent!=nullptr) {
        Game::getInstance()->getGameObjects().erase(this);
    }for ( GameObject* x:m_children) {
        delete x;
    }
}
void GameObject::SetParent(GameObject *p_parent) {
    Game* instance=Game::getInstance();
    if (instance->IsInHirarchy(m_parent)&&instance->IsInHirarchy(p_parent)) {
        m_transform=p_parent->getGlobalTransform().getInverse()*getGlobalTransform();
    }
    if (!instance->IsInHirarchy(m_parent)&&instance->IsInHirarchy(p_parent)) {
        AddGameObjectToGame();
    }
    if (instance->IsInHirarchy(m_parent)&&!instance->IsInHirarchy(p_parent)) {
        RemoveGameObjectFromGame();
    }
    if (m_parent!=nullptr) {
        m_parent->m_children.erase(this);
    }
    if (p_parent!=nullptr) {
        p_parent->m_children.insert(this);
    }
    m_parent=p_parent;

}




void GameObject::update(float deltaT) {
    (void)deltaT;
}

GameObject & GameObject::Clone() const {
    GameObject* clone =new GameObject();
    for (auto i:m_children) {
        clone->EmplaceClone(*i);
    }
    clone->m_transform = m_transform;
    clone->m_name =m_name;
    clone->m_parent = nullptr;
    clone->m_updateOrder = m_updateOrder;
    return *clone;
}

GameObject::GameObject(const GameObject &other){
    *this=other.Clone();
}

GameObject & GameObject::operator=(const GameObject &other) {

    if (this == &other)
        return *this;
    m_localId = other.m_localId;
    m_transform = other.m_transform;
    m_children = other.m_children;
    m_name = other.m_name;
    m_parent = other.m_parent;
    m_updateOrder = other.m_updateOrder;
    return *this;
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
    m_transform=m_parent->getGlobalTransform().getInverse()*transform*getGlobalTransform();
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
    if (m_parent) {
        return m_parent->getGlobalTransform() * m_transform;
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
