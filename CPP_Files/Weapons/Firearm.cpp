//
// Created by stefa on 5/4/2025.
//

#include "Firearm.hpp"

#include "../EntityHealth.hpp"
#include "../Game.hpp"
#include "../Render/ShapeRenderer.hpp"
#include "../Utilityies/TransformUtilityies.hpp"

void Firearm::Fire() {
  if (lastShot + m_timer <= CurrentTimer) {
    std::shared_ptr<GameObject> bullet = Game::getInstance()->EmplaceClone(bulletPrefab);
    bullet->GlobalMoveTransform(-Utils::getPosition(bullet->getGlobalTransform()) + Utils::getPosition(getGlobalTransform()));
    lastShot = CurrentTimer;
    bullet->getLocalTransform().rotate(-Utils::getAngle(getGlobalTransform()) + sf::degrees(180.0f));
    for (auto i: bullet->getChildrens()) {
      std::shared_ptr<PhysicObject> x = dynamic_pointer_cast<PhysicObject>(i);
      if (x.get() != nullptr) {
        sf::Vector2f bulletSpeed;
        bulletSpeed = {1000.0f, 0.0f};
        bulletSpeed = bulletSpeed.rotatedBy(-Utils::getAngle(getGlobalTransform()) + sf::degrees(90.0f));
        x->setSpeed(bulletSpeed);
        break;
      }
    }
  }
}

void Firearm::update(float deltaTime) {
  CurrentTimer += deltaTime;
}

Firearm::Firearm(const std::string &name, sf::Transform transform): GameObject(name, transform) {
  lastShot = 0.0f;
  m_timer = 0.4f;
  CurrentTimer = 0.0f;
  sf::Transform BulletTransform;
  BulletTransform.translate({0.0f, -2.f});
  BulletTransform.scale({10.f, 10.f});
  bulletPrefab = std::make_shared<GameObject>("Bullet", BulletTransform);
  sf::Transform BulletTransformHitbox;
  BulletTransformHitbox.scale({0.5f, 0.5f});
  std::shared_ptr<Collider> col = bulletPrefab->EmplaceGameObject<Collider>(
    ColliderMask::Bullets, GeometryShape::Circle, BulletTransformHitbox);
  col->getOnCollide() = [](Collider &ths, Collider &col) {
    auto parent = ths.getParent();

    std::shared_ptr<PhysicObject> ph = ths.getParent().lock()->GetGameObjectOfType<PhysicObject>();
    ph->SetParent(nullptr);

    std::shared_ptr<Collider> cl = ths.getParent().lock()->GetGameObjectOfType<Collider>();
    cl->SetParent(nullptr);

    parent.lock()->SetParent(col.getParent().lock());

    std::shared_ptr<EntityHealth> health = col.getParent().lock()->GetGameObjectOfType<EntityHealth>();
    if (health != nullptr) {
      health->dealDamage(10);
    }
  };
  bulletPrefab->EmplaceGameObject<ShapeRenderer>("CircleRenderer", BulletTransform, "Assets/arrow.png", RenderOrder::Player, GeometryShape::Rectangle);
  bulletPrefab->EmplaceGameObject<PhysicObject>(40.0f, 0.0f, 0.0f);
}

void Firearm::Init() {
  sf::Transform tr = sf::Transform::Identity;

  tr.translate({0.0f, 40.0f})
      .scale({100.f, -130.0f});
  EmplaceGameObject<ShapeRenderer>("CircleRenderer", tr, std::filesystem::path("Assets/bow_arrow.png"), RenderOrder::PostProcessing, GeometryShape::Rectangle);
}
