
#include "BasicEnemy.hpp"


#include "EntityHealth.hpp"
#include "CoreFunctionality/Game.hpp"
#include "Collisions/Collider.h"
#include "Render/ShapeRenderer.hpp"
#include "Utilityies/TransformUtilityies.hpp"

BasicEnemy::BasicEnemy(std::string name, sf::Transform transform):BaseGameObject(name,transform) {}

void BasicEnemy::update(float deltaTime) {
  (void)deltaTime;
  if (physicObject.expired()) {
    physicObject=getGameObjectOfType<PhysicObject>();
  }else {
    if (!player.expired()) {
      sf::Vector2f Dir=Utils::getPosition(getGlobalTransform())-Utils::getPosition(player.lock()->getGlobalTransform());
      physicObject.lock()->setAcceleration(-Dir.normalized()*m_movementSpeed);
    }else {
      physicObject.lock()->setAcceleration({0,0});
    }
  }
}

void BasicEnemy::init() {
    player=Game::getInstance()->getGameObjectOfType<Player>();

    sf::Transform transform= sf::Transform::Identity;
    transform.scale({40.0f, 40.0f});
    emplaceGameObject<Collider>(ColliderMask::Enemy,GeometryShape::Circle, transform)->getOnCollide().subscribe(
      [](Collider& col1,Collider& col2) {
        (void)col1;
         std::weak_ptr<Player> x=std::dynamic_pointer_cast<Player>(col2.getParent().lock());
          if (!x.expired()) {
            x.lock()->getGameObjectOfType<EntityHealth>()->dealDamage(10.0f);
          }
      }
      );
    emplaceGameObject<ShapeRenderer>("ShapeRenderer",transform,sf::Color(230,230,230),RenderOrder::Player,GeometryShape::Circle);
    emplaceGameObject<EntityHealth>(10.0f)->setOnDeath([](EntityHealth* e) {
      e->getParent().lock()->SetParent(nullptr);
    });

    physicObject= emplaceGameObject<PhysicObject>(1.0f,2.0f,0.0f);

}

std::shared_ptr<BaseGameObject> BasicEnemy::clone() const {
  std::shared_ptr<BasicEnemy> clone = std::make_shared<BasicEnemy>(m_name,m_transform);
  for (const std::shared_ptr<BaseGameObject> &i: m_children) {
    clone->emplaceClone(i);
  }
  clone->m_parent.reset();
  clone->m_updateOrder = m_updateOrder;
  clone->m_movementSpeed = m_movementSpeed;
  clone->physicObject=physicObject;
  return clone;
}


