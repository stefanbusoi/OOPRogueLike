//
// Created by stefa on 3/11/2025.
//

#include "GameObject.hpp"

#include <iostream>
#include <utility>

#include "Game.hpp"
int GameObject::GLOBAL_ID = 0;
GameObject::GameObject(std::string name,sf::Transform transform,GameObject *parent):
    LOCAL_ID(GLOBAL_ID++),
    m_transform(transform),
    m_name(std::move(name)),
    m_parent(parent)
   {}





GameObject::~GameObject() {
    if (m_parent!=nullptr) {
        Game::getInstance()->getGameObjects().erase(this);
    }for ( GameObject* x:m_children) {
        delete x;
    }
}



void GameObject::update(float deltaT) {
    (void)deltaT;
    std::cout<<"Start not implemented";
}

sf::Transform & GameObject::getLocalTransform() {
    return m_transform;
}

void GameObject::AddGameObjectToGame(GameObject *gameObject) {
    Game::getInstance()->getGameObjects().insert(gameObject);


}

sf::Transform GameObject::getGlobalTransform() {
    if (m_parent) {
        sf::Transform localTransform = m_parent->getLocalTransform();
        return localTransform.combine(m_transform);
    }
    return m_transform;
}

void GameObject::AddGameObjectToRenderObjects(IRenderable *game_object) {
    Game::getInstance()->getRenderOrder().insert(game_object);

}

void GameObject::addCollider(Collider &collider) {
    collider.setGameObject(this);
    Game::getInstance()->getColliders().insert(&collider);
}

std::ostream & operator<<(std::ostream &os, const GameObject &obj) {
    os<<"Name: "<< obj.m_name
            <<" Id:"<< obj.LOCAL_ID
            << " GameObjects:{ ";
    for (auto x:obj.m_children) {
        os<<x->m_name<<" ";
    }
    os<<"}";
    return os;
}
