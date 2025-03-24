#pragma once


#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "IRenderable.hpp"

#include "Collider.h"
#include "UpdateOrder.hpp"
class GameObject {
protected:
    static int s_globalId;
    int m_localId;

public:
    GameObject(const GameObject &other);
    GameObject& operator=(const GameObject &other);
    GameObject(GameObject &&other) noexcept;
    GameObject & operator=(GameObject &&other) noexcept;
protected:
    sf::Transform m_transform;
    std::set<GameObject*> m_children;
    std::string m_name;
    GameObject* m_parent;
    UpdateOrder m_updateOrder;
    std::vector<Collider> m_objectColliders;
public:
    UpdateOrder getUpdateOrder() const {return m_updateOrder;}
    /*Used for Game class only*/
    explicit GameObject(std::string name="NONNAME", sf::Transform transform=sf::Transform::Identity,GameObject* parent=nullptr);
    virtual ~GameObject();

    virtual void update(float deltaT);
    void AddGameObjectToGame(GameObject* gameObject);
    const std::set<GameObject*>& getChildrens() {return m_children;}
    int GetId() const {return m_localId;}
    sf::Transform getGlobalTransform();
    sf::Transform& getLocalTransform();
    [[maybe_unused]] void setName(const std::string& name) {m_name=name;}
    void AddGameObjectToRenderObjects(IRenderable* game_object);
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
