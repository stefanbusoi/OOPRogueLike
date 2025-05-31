
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
    physicObject=GetGameObjectOfType<PhysicObject>();
  }else {
    if (!player.expired()) {
      sf::Vector2f Dir=Utils::getPosition(getGlobalTransform())-Utils::getPosition(player.lock()->getGlobalTransform());
      physicObject.lock()->setAcceleration(-Dir.normalized()*m_movementSpeed);
    }else {
      physicObject.lock()->setAcceleration({0,0});
    }
  }
}

void BasicEnemy::Init() {
    player=Game::getInstance()->GetGameObjectOfType<Player>();

    sf::Transform transform= sf::Transform::Identity;
    transform.scale({40.0f, 40.0f});
    EmplaceGameObject<Collider>(ColliderMask::Enemy,GeometryShape::Circle, transform)->getOnCollide().subscribe(
      [](Collider& col1,Collider& col2) {
        (void)col1;
         std::weak_ptr<Player> x=std::dynamic_pointer_cast<Player>(col2.getParent().lock());
          if (!x.expired()) {
            x.lock()->GetGameObjectOfType<EntityHealth>()->dealDamage(10.0f);
          }
      }
      );
    EmplaceGameObject<ShapeRenderer>("ShapeRenderer",transform,sf::Color(230,230,230),RenderOrder::Player,GeometryShape::Circle);
    EmplaceGameObject<EntityHealth>(10.0f)->setOnDeath([](EntityHealth* e) {
      e->getParent().lock()->SetParent(nullptr);
    });

    physicObject= EmplaceGameObject<PhysicObject>(1.0f,2.0f,0.0f);

}

std::shared_ptr<BaseGameObject> BasicEnemy::clone() const {
  std::shared_ptr<BasicEnemy> clone = std::make_shared<BasicEnemy>(m_name,m_transform);
  for (const std::shared_ptr<BaseGameObject> &i: m_children) {
    clone->EmplaceClone(i);
  }
  clone->m_parent.reset();
  clone->m_updateOrder = m_updateOrder;
  clone->m_movementSpeed = m_movementSpeed;
  clone->physicObject=physicObject;
  return clone;
}


