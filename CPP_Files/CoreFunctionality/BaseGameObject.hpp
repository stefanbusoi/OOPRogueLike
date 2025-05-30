#pragma once
#include <memory>
#include <set>
#include <string>
#include <vector>
#include "Render/IRenderable.hpp"
#include "UpdateOrder.hpp"
#include "SFML/Graphics/Transform.hpp"
class Collider;

/**
 * GameObject is the base Class for all Objects
 *
 */
class BaseGameObject : public std::enable_shared_from_this<BaseGameObject> {
  static int s_globalId;
  const int m_localId{generateId()};
  static int generateId() { return s_globalId++; }

protected:
  sf::Transform m_transform;
  std::string m_name;

  std::set<std::shared_ptr<BaseGameObject> > m_children;
  std::weak_ptr<BaseGameObject> m_parent;
  UpdateOrder m_updateOrder = UpdateOrder::Default;

  bool m_isActive{true};

  virtual void print(std::ostream &os) const;

public:
  virtual std::shared_ptr<BaseGameObject> clone() const;

  BaseGameObject(const BaseGameObject &other) = delete;

  BaseGameObject &operator=(const BaseGameObject &other) = delete;

  virtual void AddGameObjectToGame();

  virtual void RemoveGameObjectFromGame();

  UpdateOrder getUpdateOrder() const { return m_updateOrder; }


  explicit BaseGameObject(std::string name = "NONNAME", sf::Transform transform = sf::Transform::Identity);

  virtual void Init();

  virtual void update(float deltaT);

  virtual ~BaseGameObject();

   void SetParent(const std::shared_ptr<BaseGameObject> &p_parent);

  std::weak_ptr<BaseGameObject> getParent() { return m_parent; }

  int GetId() const { return m_localId; }
  void setName(const std::string &name) { m_name = name; }
  std::string getName() const { return m_name; }
  void setTransform(const sf::Transform &transform) { m_transform = transform; }

  sf::Transform getGlobalTransform() const;

  sf::Transform &getLocalTransform();

  void MoveTransform(sf::Vector2f movement);

  void GlobalMoveTransform(sf::Vector2f movement);

  void AddGameObjectToRenderObjects(IRenderable *game_object);

  void setActive(bool isActive);

  bool IsInGame();

  bool IsActive() const { return m_isActive; }

  const std::set<std::shared_ptr<BaseGameObject> > &getChildrens() { return m_children; }

  template<class T=BaseGameObject, class... ARGS>
  std::shared_ptr<T> EmplaceGameObject(ARGS &&...);

  template<class T=BaseGameObject>
  std::shared_ptr<T> GetGameObjectOfType();

  template<class T=BaseGameObject>
  std::vector<T *> GetGameObjectsOfType();

  std::shared_ptr<BaseGameObject> EmplaceClone(std::shared_ptr<BaseGameObject> obj,const sf::Transform& tr=sf::Transform::Identity);

  friend std::ostream &operator<<(std::ostream &os, const BaseGameObject &obj);
};


inline std::shared_ptr<BaseGameObject> BaseGameObject::EmplaceClone(std::shared_ptr<BaseGameObject> obj,const sf::Transform& tr) {
  std::shared_ptr<BaseGameObject> x = obj->clone();
  x->setTransform(tr*x->getLocalTransform());
  x->SetParent(shared_from_this());
  m_children.insert(x);
  return x;
}


template<class T, class... ARGS>
std::shared_ptr<T> BaseGameObject::EmplaceGameObject(ARGS &&... args) {
  std::shared_ptr<T> newGameObject = std::make_shared<T>(std::forward<ARGS>(args)...);
  m_children.insert(newGameObject);
  newGameObject->Init();
  newGameObject->SetParent(shared_from_this());
  return newGameObject;
}

template<class T>
std::vector<T*> BaseGameObject::GetGameObjectsOfType() {
  std::vector<T*> ret;
  for (std::shared_ptr<BaseGameObject> x: m_children) {
    if (auto gameObject = std::dynamic_pointer_cast<T *>(x)) {
      ret.push_back(gameObject);
    }
  }
  return ret;
}

template<class T>
std::shared_ptr<T> BaseGameObject::GetGameObjectOfType() {
  for (const std::shared_ptr<BaseGameObject> &x: m_children) {
    if (auto gameObject = std::dynamic_pointer_cast<T>(x)) {
      return gameObject;
    }
  }
  return nullptr;
}
