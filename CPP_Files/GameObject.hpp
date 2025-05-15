#pragma once


#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "Render/IRenderable.hpp"

#include "UpdateOrder.hpp"
#include "Exceptions/GameLogicException.hpp"
#include "SFML/Graphics/Transform.hpp"
class Collider;
class GameObject {
private:
    static int s_globalId;
protected:
    int getGlobalId(){ return s_globalId++; }
    int m_localId;
    virtual void print(std::ostream& os)const;

protected:
    sf::Transform m_transform;
    std::set<GameObject*> m_children;
    std::string m_name;
    GameObject* m_parent{nullptr};
    UpdateOrder m_updateOrder=UpdateOrder::Default;
    bool m_isActive{true};
public:
    virtual void AddGameObjectToGame();
    virtual void RemoveGameObjectFromGame();

    UpdateOrder getUpdateOrder() const {return m_updateOrder;}


    /*Used for Game class only*/
    explicit GameObject(std::string name="NONNAME", sf::Transform transform=sf::Transform::Identity);
    virtual ~GameObject();
    virtual void SetParent(GameObject* p_parent);
    bool IsInGame();
    virtual void update(float deltaT);
    virtual GameObject& clone() const;

    GameObject(const GameObject &other);

    GameObject & operator=(const GameObject &other);

    const std::set<GameObject*>& getChildrens() {return m_children;}
    GameObject* getParent() {return m_parent;}
    int GetId() const {return m_localId;}
    sf::Transform getGlobalTransform() const;
    sf::Transform& getLocalTransform();
    void MoveTransform(sf::Vector2f movement);
    void GlobalMoveTransform(sf::Vector2f movement);
    [[maybe_unused]] void setName(const std::string& name) {m_name=name;}
    void AddGameObjectToRenderObjects(IRenderable* game_object);
    void addCollider(Collider& collider);
    friend std::ostream & operator<<(std::ostream &os, const GameObject &obj);
    void setActive(bool isActive);

    bool IsActive() const {return m_isActive;}
    template <class T=GameObject,class ...ARGS>
    T* EmplaceGameObject(ARGS&&...);

    template <class T=GameObject>
    T* GetGameObjectOfType();

    template <class T=GameObject>
    std::vector<T*> GetGameObjectsOfType();
    GameObject* EmplaceClone(const GameObject& obj);
};


inline GameObject * GameObject::EmplaceClone(const GameObject &obj){
    auto* x=&obj.clone();
    x->SetParent(this);
    m_children.insert(x);
    return x;
}


template <class T, class... ARGS>
T* GameObject::EmplaceGameObject(ARGS&&... args) {
    T* newGameObject = new T(std::forward<ARGS>(args)...);
    newGameObject->SetParent(this);
    m_children.insert(newGameObject);
    return newGameObject;
}

template<class T>
std::vector<T*> GameObject::GetGameObjectsOfType() {
    std::vector<T*> ret;
    for (GameObject* x:m_children) {
        T* gameObject = dynamic_cast<T*>(x);
        if (gameObject) {
            ret.push_back(gameObject);
        }
    }
    return ret;
}

template<class T>
T * GameObject::GetGameObjectOfType() {
    for (GameObject* x:m_children) {
        T* gameObject = dynamic_cast<T*>(x);
        if (gameObject) {
            return gameObject;
        }
    }
    return nullptr;
}