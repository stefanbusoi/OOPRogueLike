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
class GameObject : public std::enable_shared_from_this<GameObject> {
  static int s_globalId;
  const int m_localId{generateId()};
  static int generateId() { return s_globalId++; }

protected:
  sf::Transform m_transform;
  std::string m_name;

  std::set<std::shared_ptr<GameObject> > m_children;
  std::weak_ptr<GameObject> m_parent;
  UpdateOrder m_updateOrder = UpdateOrder::Default;

  bool m_isActive{true};

  virtual void print(std::ostream &os) const;

public:
  virtual std::shared_ptr<GameObject> clone() const;

  GameObject(const GameObject &other) = delete;

  GameObject &operator=(const GameObject &other) = delete;

  virtual void AddGameObjectToGame();

  virtual void RemoveGameObjectFromGame();

  UpdateOrder getUpdateOrder() const { return m_updateOrder; }


  explicit GameObject(std::string name = "NONNAME", sf::Transform transform = sf::Transform::Identity);

  virtual void Init();

  virtual void update(float deltaT);

  virtual ~GameObject();

  virtual void SetParent(const std::shared_ptr<GameObject> &p_parent);

  std::weak_ptr<GameObject> getParent() { return m_parent; }

  int GetId() const { return m_localId; }
  void setName(const std::string &name) { m_name = name; }
  std::string getName() const { return m_name; }


  sf::Transform getGlobalTransform() const;

  sf::Transform &getLocalTransform();

  void MoveTransform(sf::Vector2f movement);

  void GlobalMoveTransform(sf::Vector2f movement);

  void AddGameObjectToRenderObjects(IRenderable *game_object);

  void setActive(bool isActive);

  bool IsInGame();

  bool IsActive() const { return m_isActive; }

  const std::set<std::shared_ptr<GameObject> > &getChildrens() { return m_children; }

  template<class T=GameObject, class... ARGS>
  std::shared_ptr<T> EmplaceGameObject(ARGS &&...);

  template<class T=GameObject>
  std::shared_ptr<T> GetGameObjectOfType();

  template<class T=GameObject>
  std::vector<T *> GetGameObjectsOfType();

  std::shared_ptr<GameObject> EmplaceClone(std::shared_ptr<GameObject> obj);

  friend std::ostream &operator<<(std::ostream &os, const GameObject &obj);
};


inline std::shared_ptr<GameObject> GameObject::EmplaceClone(std::shared_ptr<GameObject> obj) {
  std::shared_ptr<GameObject> x = obj->clone();
  x->SetParent(shared_from_this());
  m_children.insert(x);
  return x;
}


template<class T, class... ARGS>
std::shared_ptr<T> GameObject::EmplaceGameObject(ARGS &&... args) {
  std::shared_ptr<T> newGameObject = std::make_shared<T>(std::forward<ARGS>(args)...);
  m_children.insert(newGameObject);
  newGameObject->Init();
  newGameObject->SetParent(shared_from_this());
  return newGameObject;
}

template<class T>
std::vector<T *> GameObject::GetGameObjectsOfType() {
  std::vector<T *> ret;
  for (std::shared_ptr<GameObject> x: m_children) {
    if (auto gameObject = std::dynamic_pointer_cast<T *>(x)) {
      ret.push_back(gameObject);
    }
  }
  return ret;
}

template<class T>
std::shared_ptr<T> GameObject::GetGameObjectOfType() {
  for (const std::shared_ptr<GameObject> &x: m_children) {
    if (auto gameObject = std::dynamic_pointer_cast<T>(x)) {
      return gameObject;
    }
  }
  return nullptr;
}
