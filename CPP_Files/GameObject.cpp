//
// Created by stefa on 3/11/2025.
//

#include "GameObject.hpp"
#include "gameObjectComp.hpp"
#include <iostream>
#include <utility>

#include "Game.hpp"
int GameObject::s_globalId = 0;

GameObject::GameObject(const GameObject &other): m_localId(s_globalId++),
                                                 m_transform(other.m_transform),
                                                 m_children(other.m_children),
                                                 m_name(other.m_name),
                                                 m_parent(other.m_parent),
                                                 m_updateOrder(other.m_updateOrder),
                                                 m_objectColliders(other.m_objectColliders) {

}

GameObject & GameObject::operator=(const GameObject &other) {
    if (other.m_parent!=nullptr) {
        throw std::runtime_error("Can t create a game object with a parent alocated");
    }
    if (other.m_children.size()!=0) {
        throw std::runtime_error("Can t create a game object with a children alocated");
    }
    if (this == &other)
        return *this;
    m_localId = other.m_localId;
    m_transform = other.m_transform;
    m_children = other.m_children;
    m_name = other.m_name;
    m_parent = other.m_parent;
    m_updateOrder = other.m_updateOrder;
    m_objectColliders = other.m_objectColliders;
    return *this;
}
GameObject::GameObject(GameObject &&other) noexcept: m_localId(other.m_localId),
                                                     m_transform(std::move(other.m_transform)),
                                                     m_children(std::move(other.m_children)),
                                                     m_name(std::move(other.m_name)),
                                                     m_parent(other.m_parent),
                                                     m_updateOrder(other.m_updateOrder),
                                                     m_objectColliders(std::move(other.m_objectColliders)) {
    other.m_parent=nullptr;
}
GameObject & GameObject::operator=(GameObject &&other) noexcept {
    if (this == &other)
        return *this;
    m_localId = other.m_localId;
    m_transform = std::move(other.m_transform);
    m_children = std::move(other.m_children);
    m_name = std::move(other.m_name);
    m_parent = other.m_parent;
    m_updateOrder = other.m_updateOrder;
    m_objectColliders = std::move(other.m_objectColliders);
    other.m_parent=nullptr;
    return *this;
}
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
//4star make set parent work corectly
void GameObject::SetParent(GameObject *p_parent) {
    Game* instance=Game::getInstance();
    if (instance->IsInHirarchy(m_parent)&&!instance->IsInHirarchy(p_parent)) {
        AddGameObjectToGame();
    }
    if (!instance->IsInHirarchy(m_parent)&&instance->IsInHirarchy(p_parent)) {
        RemoveGameObjectFromGame();
    }
    m_parent->m_children.erase(this);
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
}

void GameObject::RemoveGameObjectFromGame() {
    Game::getInstance()->getGameObjects().erase(this);
}

sf::Transform GameObject::getGlobalTransform() {
    if (m_parent) {
        sf::Transform localTransform = m_parent->getLocalTransform();
        return localTransform.combine(m_transform);
    }
    return m_transform;
}

void GameObject::AddGameObjectToRenderObjects(IRenderable *game_object) {
    Game::getInstance()->getRenderObjects().insert(game_object);

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
