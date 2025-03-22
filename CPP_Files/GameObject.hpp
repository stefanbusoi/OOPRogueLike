#pragma once


#include <ostream>
#include <set>
#include <string>
#include <vector>


#include "IColiderable.h"
#include "IRenderable.hpp"
#include "UpdateOrder.hpp"
#include "SFML/Graphics/Transform.hpp"
class GameObject {
protected:
    static int GLOBAL_ID;
    int LOCAL_ID;

public:
    GameObject(const GameObject &other)
        : LOCAL_ID(GLOBAL_ID++),
          m_transform(other.m_transform),
          m_children(other.m_children),
          m_name(other.m_name),
          m_parent(other.m_parent),
          m_updateOrder(other.m_updateOrder),
          objectColliders(other.objectColliders) {

    }
    GameObject& operator=(const GameObject &other) {
        if (other.m_parent!=nullptr) {
            throw std::runtime_error("Can t create a game object with a parent alocated");
        }
        if (other.m_children.size()!=0) {
            throw std::runtime_error("Can t create a game object with a children alocated");
        }
        if (this == &other)
            return *this;
        LOCAL_ID = other.LOCAL_ID;
        m_transform = other.m_transform;
        m_children = other.m_children;
        m_name = other.m_name;
        m_parent = other.m_parent;
        m_updateOrder = other.m_updateOrder;
        objectColliders = other.objectColliders;
        return *this;
    }

    GameObject(GameObject &&other) noexcept
        : LOCAL_ID(other.LOCAL_ID),
          m_transform(std::move(other.m_transform)),
          m_children(std::move(other.m_children)),
          m_name(std::move(other.m_name)),
          m_parent(other.m_parent),
          m_updateOrder(other.m_updateOrder),
          objectColliders(std::move(other.objectColliders)) {
        other.m_parent=nullptr;
    }



    GameObject & operator=(GameObject &&other) noexcept {
        if (this == &other)
            return *this;
        LOCAL_ID = other.LOCAL_ID;
        m_transform = std::move(other.m_transform);
        m_children = std::move(other.m_children);
        m_name = std::move(other.m_name);
        m_parent = other.m_parent;
        m_updateOrder = other.m_updateOrder;
        objectColliders = std::move(other.objectColliders);
        other.m_parent=nullptr;
        return *this;
    }

protected:
    sf::Transform m_transform;
    std::set<GameObject*> m_children;
    std::string m_name;
    GameObject* m_parent;
    UpdateOrder m_updateOrder;
    std::vector<Collider> objectColliders;
public:
    UpdateOrder getUpdateOrder() const {return m_updateOrder;}
    /*Used for Game class only*/
    GameObject(std::string name="NONNAME", sf::Transform transform=sf::Transform::Identity,GameObject* parent=nullptr);
    virtual ~GameObject();

    virtual void update(float deltaT);
    void AddGameObjectToGame(GameObject* gameObject);
    std::set<GameObject*> getChildrens() {return m_children;}
    int GetId() const {return LOCAL_ID;}
    sf::Transform getGlobalTransform();
    sf::Transform& getLocalTransform();
    void setName(const std::string& name) {m_name=name;}
    void AddGameObjectToRenderObjects(IRenderable * game_object);
    void addCollider(Collider& collider);
    friend std::ostream & operator<<(std::ostream &os, const GameObject &obj);
    template <class T=GameObject>
    T* AddGameObject(std::string name="NONAME", sf::Transform transform=sf::Transform::Identity);

    template <class T=GameObject>
    T* AddGameObject(T&& temp);

};

template<class T>
T* GameObject::AddGameObject(std::string name, sf::Transform transform) {
    T* newGameObject = new T(name,transform,this);
    auto* renderableComponent = dynamic_cast<IRenderable *>(newGameObject);
    if (renderableComponent) {
        AddGameObjectToRenderObjects(renderableComponent);
    }

    m_children.insert(newGameObject);
    AddGameObjectToGame(dynamic_cast<GameObject*>(newGameObject));
    return newGameObject;
}

template<class T>
T* GameObject:: AddGameObject(T&& temp){
    if (temp.m_parent!=nullptr) {
        throw std::runtime_error("Can t add a game object already alocated");
    }
    if (temp.m_children.size()!=0) {
        throw std::runtime_error("Can t add a game object with childs");
    }
    T* newGameObject = new T(std::move(temp));
    newGameObject->m_parent = this;
    auto* renderableComponent = dynamic_cast<IRenderable *>(newGameObject);
    if (renderableComponent) {
        AddGameObjectToRenderObjects(renderableComponent);
    }
    m_children.insert(newGameObject);
    AddGameObjectToGame(dynamic_cast<GameObject*>(newGameObject));


    return newGameObject;
}
