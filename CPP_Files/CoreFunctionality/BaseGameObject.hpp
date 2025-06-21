#pragma once
#include <memory>
#include <set>
#include <string>
#include <vector>
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

  /**
   *
   * @return get a clone of the current object
   */
  virtual std::shared_ptr<BaseGameObject> clone() const;

  BaseGameObject(const BaseGameObject &other) = delete;
  BaseGameObject &operator=(const BaseGameObject &other) = delete;

  /**
   * Add the game object to the game
   */
  virtual void addGameObjectToGame();

  /**
   * Removes the game object from the game
   */
  virtual void removeGameObjectFromGame();

  /**
   *
   * @return Returns the update priority of this game object
   */
  UpdateOrder getUpdateOrder() const { return m_updateOrder; }


  /**
   *
   * @param name name of the game object
   * @param transform position of the game object relative to it s parent
   */
  explicit BaseGameObject(std::string name = "NONNAME", const sf::Transform &transform = sf::Transform::Identity);

  /**
   * initialise the game object, you can t use emplaceGameObject or emplaceClone inside constructors
   */
  virtual void init();

  /**
   * Updates the game object each frame
   * @param deltaT the interval of time between this update and the precedent update
   */
  virtual void update(float deltaT);

  virtual ~BaseGameObject();

  /**
    * set the parent of the game object, also adds the game object to the render and update queue if the parent is an active object
    * @param p_parent
    */
   void SetParent(const std::shared_ptr<BaseGameObject> &p_parent);

  /**
   *
   * @return the parent of this game object or nullptr if is the root of current game object
   */
  std::weak_ptr<BaseGameObject> getParent() { return m_parent; }

  int getId() const { return m_localId; }
  void setTransform(const sf::Transform &transform) { m_transform = transform; }

  /**
   *
   * @return returns the transform relative to the global space
   */
  sf::Transform getGlobalTransform() const;

  /**
   *
   * @return returns the transform relative to the parent
   */
  sf::Transform &getLocalTransform();



  /**
   *
   * @param movement move the game object on the map relative to world space
   */
  void globalMoveTransform(sf::Vector2f movement);


  /**
   *
   * @param isActive set if this object is active or not
   */
  void setActive(bool isActive);


  /**
   *
   * @return if this object is active
   */
  bool isActive() const { return m_isActive; }

  /**
   *
   * @return all childrens of the current object
   */
  const std::set<std::shared_ptr<BaseGameObject> > &getChildrens() { return m_children; }

  /**
   * Constructs a game object and inserts it in the childrens
   * @tparam T type of the game objects
   * @tparam ARGS constructor paramaters
   * @return a shared pointer to that game object
   */
  template<class T=BaseGameObject, class... ARGS>
  std::shared_ptr<T> emplaceGameObject(ARGS &&...);

  /**
   *
   * @tparam T type of the game object
   * @return the first apearence of that type of GameObject or nullptr if are none
   */
  template<class T=BaseGameObject>
  std::shared_ptr<T> getGameObjectOfType();


  /**
   *
   * @param obj the object to be cloned
   * @param tr where to be placed based on parent position
   * @return a shared_ptr to it s clone
   */
  std::shared_ptr<BaseGameObject> emplaceClone(const std::shared_ptr<BaseGameObject> &obj,const sf::Transform& tr=sf::Transform::Identity);

  friend std::ostream &operator<<(std::ostream &os, const BaseGameObject &obj);
};


inline std::shared_ptr<BaseGameObject> BaseGameObject::emplaceClone(const std::shared_ptr<BaseGameObject> &obj,const sf::Transform& tr) {
  std::shared_ptr<BaseGameObject> x = obj->clone();
  x->setTransform(tr*x->getLocalTransform());
  x->SetParent(shared_from_this());
  m_children.insert(x);
  return x;
}


template<class T, class... ARGS>
std::shared_ptr<T> BaseGameObject::emplaceGameObject(ARGS &&... args) {
  std::shared_ptr<T> newGameObject = std::make_shared<T>(std::forward<ARGS>(args)...);
  m_children.insert(newGameObject);
  newGameObject->init();
  newGameObject->SetParent(shared_from_this());
  return newGameObject;
}



template<class T>
std::shared_ptr<T> BaseGameObject::getGameObjectOfType() {
  for (const std::shared_ptr<BaseGameObject> &x: m_children) {
    if (auto gameObject = std::dynamic_pointer_cast<T>(x)) {
      return gameObject;
    }
  }
  return nullptr;
}
