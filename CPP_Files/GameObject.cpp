//
// Created by stefa on 3/11/2025.
//

#include "GameObject.hpp"
#include "gameObjectComp.hpp"
#include <iostream>
#include <utility>

#include "Game.hpp"
int GameObject::s_globalId = 0;

GameObject::GameObject(std::string name,sf::Transform transform,GameObject *parent): m_localId(s_globalId++),
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
    if (!instance->IsInHirarchy(m_parent)&&instance->IsInHirarchy(p_parent)) {
        AddGameObjectToGame();
    }
    if (instance->IsInHirarchy(m_parent)&&!instance->IsInHirarchy(p_parent)) {
        RemoveGameObjectFromGame();
    }
    if (m_parent!=nullptr) {
        m_parent->m_children.erase(this);
    }
    p_parent->m_children.insert(this);
    m_parent=p_parent;
}




void GameObject::update(float deltaT) {
    (void)deltaT;
    std::cout<<"Start not implemented";
}

sf::Transform & GameObject::getLocalTransform() {
    return m_transform;
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

sf::Transform GameObject::getGlobalTransform() {
    if (m_parent) {
        sf::Transform localTransform = m_parent->getLocalTransform();
        return localTransform.combine(m_transform);
    }
    return m_transform;
}


[[maybe_unused]] void GameObject::addCollider(Collider &collider) {
    collider.setGameObject(this);
    Game::getInstance()->getColliders().insert(&collider);
}

std::ostream & operator<<(std::ostream &os, const GameObject &obj) {
    os<<"Name: "<< obj.m_name
            <<" Id:"<< obj.m_localId
            << " GameObjects:{ ";
    for (const auto x:obj.m_children) {
        os<<x->m_name<<" ";
    }
    os<<"}";
    return os;
}
