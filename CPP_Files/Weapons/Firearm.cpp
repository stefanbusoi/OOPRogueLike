//
// Created by stefa on 5/4/2025.
//

#include "Firearm.hpp"

#include "Arrow.hpp"
#include "CoreFunctionality/Game.hpp"
#include "Render/ShapeRenderer.hpp"
#include "Utilityies/TransformUtilityies.hpp"

void Firearm::fire() {
  if (isActive()) {
    if (m_lastShot + m_timer <= m_CurrentTimer) {
      std::shared_ptr<BaseGameObject> bullet = Game::getInstance()->emplaceClone(bulletPrefab);
      bullet->globalMoveTransform(-Utils::getPosition(bullet->getGlobalTransform()) + Utils::getPosition(getGlobalTransform()));
      m_lastShot = m_CurrentTimer;
      bullet->getLocalTransform().rotate(-Utils::getAngle(getGlobalTransform()) + sf::degrees(180.0f));
      std::weak_ptr<PhysicObject> x=bullet->getGameObjectOfType<PhysicObject>();
      if (!x.expired()) {
        sf::Vector2f bulletSpeed;
        bulletSpeed = {1000.0f, 0.0f};
        bulletSpeed = bulletSpeed.rotatedBy(-Utils::getAngle(getGlobalTransform()) + sf::degrees(90.0f));
        x.lock()->setSpeed(bulletSpeed);
      }
    }
  }
}

void Firearm::update(float deltaTime) {
  m_CurrentTimer += deltaTime;
}

Firearm::Firearm(const std::string &name, sf::Transform transform): BaseGameObject(name, transform) {
  m_lastShot = 0.0f;
  m_timer = 0.35f;
  m_CurrentTimer = 0.0f;
  sf::Transform BulletTransform;
  BulletTransform.translate({0.0f, 4.f});
  BulletTransform.scale({100.f, 100.f});
  bulletPrefab = std::make_shared<Arrow>(sf::Transform::Identity);
  bulletPrefab->init();
}

void Firearm::init() {
  sf::Transform tr = sf::Transform::Identity;

  tr.translate({0.0f, 40.0f})
      .scale({100.f, -130.0f});
  emplaceGameObject<ShapeRenderer>("CircleRenderer", tr, std::filesystem::path("Assets/bow_arrow.png"), RenderOrder::PlayerWeapons, GeometryShape::Rectangle);
}
