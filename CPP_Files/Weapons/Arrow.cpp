//
// Created by stefa on 5/24/2025.
//

#include "Arrow.hpp"
#include "Collisions/Collider.h"
#include "Collisions/PhysicObject.hpp"
#include "Entityies/EntityHealth.hpp"
#include "Render/ShapeRenderer.hpp"


Arrow::Arrow(sf::Transform transform):BaseGameObject("Arrow",transform) {


}

void Arrow::Init() {
  sf::Transform BulletTransform;
  BulletTransform.translate({0.0f, 4.f});
  BulletTransform.scale({100.f, 100.f});
  sf::Transform BulletTransformHitbox;
  BulletTransformHitbox.scale({0.5f, 0.5f});
  std::shared_ptr<Collider> col = EmplaceGameObject<Collider>(
    ColliderMask::Bullets, GeometryShape::Circle, BulletTransformHitbox);
  col->getOnCollide().subscribe ([](Collider &ths, Collider &col) {
    auto parent = ths.getParent();

    std::shared_ptr<PhysicObject> ph = ths.getParent().lock()->GetGameObjectOfType<PhysicObject>();
    ph->SetParent(nullptr);

    std::shared_ptr<Collider> cl = ths.getParent().lock()->GetGameObjectOfType<Collider>();
    cl->SetParent(nullptr);

    parent.lock()->SetParent(col.getParent().lock());
    auto p2=col.getParent().lock()->GetGameObjectOfType<PhysicObject>();
    if (p2!=nullptr) {
      p2->setSpeed((p2->getSpeed()*p2->getMass()+ph->getSpeed()*ph->getMass())/(p2->getMass()+ph->getMass()));
    }
    std::shared_ptr<EntityHealth> health = col.getParent().lock()->GetGameObjectOfType<EntityHealth>();
    if (health != nullptr) {
      health->dealDamage(10);
    }
  });
  EmplaceGameObject<ShapeRenderer>("CircleRenderer", BulletTransform, "Assets/arrow.png", RenderOrder::Player, GeometryShape::Rectangle);
  EmplaceGameObject<PhysicObject>(100.0f, 0.0f, 0.0f);
}

void Arrow::update(float deltaT) {
  timer += deltaT;
  if (timer>30.0f) {
    SetParent(nullptr);
  }

}
void Arrow::AddGameObjectToGame() {
  BaseGameObject::AddGameObjectToGame();
}

std::shared_ptr<BaseGameObject> Arrow::clone() const {
  std::shared_ptr<Arrow> clone = std::make_shared<Arrow>();
  for (const std::shared_ptr<BaseGameObject> &i: m_children) {
    clone->EmplaceClone(i);
  }
  clone->m_transform = m_transform;
  clone->m_name = m_name;
  clone->m_parent.reset();
  clone->m_updateOrder = m_updateOrder;
  return clone;
}

void Arrow::RemoveGameObjectFromGame() {
  BaseGameObject::RemoveGameObjectFromGame();
}


