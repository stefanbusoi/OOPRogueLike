//
// Created by stefa on 3/11/2025.
//

#include "BaseGameObject.hpp"
#include "gameObjectComp.hpp"
#include <utility>

#include "Game.hpp"
#include "Collisions/Collider.h"
int BaseGameObject::s_globalId = 0;

BaseGameObject::BaseGameObject(std::string name, sf::Transform transform): m_transform(transform),
                                                                   m_name(std::move(name)) {
}

void BaseGameObject::init() {
}


BaseGameObject::~BaseGameObject() {
  //Only Game shoud ever have m_localID==0
  if (m_localId!=0) {
    removeGameObjectFromGame();
  }
};

void BaseGameObject::SetParent(const std::shared_ptr<BaseGameObject> &p_parent) {
  std::shared_ptr<Game>instance = Game::getInstance();
  if (instance->isInHirarchy(weak_from_this()) && instance->isInHirarchy(p_parent)) {
    m_transform = p_parent->getGlobalTransform().getInverse() * getGlobalTransform();
    p_parent->m_children.insert(shared_from_this());
    m_parent.lock()->m_children.erase(shared_from_this());
  }
  if (!instance->isInHirarchy(weak_from_this()) && instance->isInHirarchy(p_parent)) {
    addGameObjectToGame();
    p_parent->m_children.insert(weak_from_this().lock());
  }
  if (instance->isInHirarchy(weak_from_this()) && !instance->isInHirarchy(p_parent)) {
    removeGameObjectFromGame();
    m_parent.lock()->m_children.erase(weak_from_this().lock());
  }
  m_parent = p_parent;
}


void BaseGameObject::setActive(bool isActive) {
  if (m_isActive == isActive) return;
  if (isActive) {
    if (Game::getInstance()->isActiveInHirarchy(getParent())) {
      this->addGameObjectToGame();
    }
  } else {
    if (Game::getInstance()->isActiveInHirarchy(getParent())) {
      this->removeGameObjectFromGame();
    }
  }
  m_isActive = isActive;
}


void BaseGameObject::update(float deltaT) {
  (void) deltaT;
}
std::shared_ptr<BaseGameObject> BaseGameObject::clone() const {
  std::shared_ptr<BaseGameObject> clone = std::make_shared<BaseGameObject>();
  for (const std::shared_ptr<BaseGameObject> &i: m_children) {
    clone->emplaceClone(i);
  }
  clone->m_transform = m_transform;
  clone->m_name = m_name;
  clone->m_parent.reset();
  clone->m_updateOrder = m_updateOrder;
  return clone;
}


sf::Transform &BaseGameObject::getLocalTransform() {
  return m_transform;
}

void BaseGameObject::MoveTransform(sf::Vector2f movement) {
  m_transform.translate(movement);
}

void BaseGameObject::globalMoveTransform(sf::Vector2f movement) {
  sf::Transform transform = sf::Transform::Identity;
  transform.translate(movement);
  m_transform = getGlobalTransform().getInverse()*getLocalTransform() * transform * getGlobalTransform();
}

void BaseGameObject::addGameObjectToGame() {
  Game::getInstance()->getGameObjects().insert(this);
  for (auto i: getChildrens()) {
    i->addGameObjectToGame();
  }
}

void BaseGameObject::removeGameObjectFromGame() {
  Game::getInstance()->getGameObjects().erase(this);
  for (auto i: getChildrens()) {
    i->removeGameObjectFromGame();
  }
}

sf::Transform BaseGameObject::getGlobalTransform() const {
  if (!m_parent.expired()) {
    return m_parent.lock()->getGlobalTransform() * m_transform;
  }
  return m_transform;
}


void BaseGameObject::print(std::ostream &os) const {
  os << "Name: " << m_name
      << " Id:" << m_localId
      << " GameObjects:{ ";
  for (const auto &x: m_children) {
    os << x->m_name << " ";
  }
  os << "}";
}

std::ostream &operator<<(std::ostream &os, const BaseGameObject &obj) {
  obj.print(os);
  return os;
}
