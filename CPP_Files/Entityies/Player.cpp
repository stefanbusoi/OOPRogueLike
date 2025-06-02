#include "Player.hpp"


#include "EntityHealth.hpp"
#include "CoreFunctionality/Game.hpp"
#include "Collisions/PhysicObject.hpp"
#include "Utilityies/TransformUtilityies.hpp"
#include "Render/ShapeRenderer.hpp"
#include "UI/DeathScreen.h"
#include "Weapons/Firearm.hpp"


void Player::update(float deltaT) {
  float SpeedConst = 7000;
  sf::Vector2i pos = sf::Mouse::getPosition(Game::getInstance()->getWindow());
  sf::Vector2f speed;
  if (isKeyPressed(sf::Keyboard::Scancode::A)) {
    speed += sf::Vector2f({-1.0f, 0.0f});
  }
  if (isKeyPressed(sf::Keyboard::Scancode::D)) {
    speed += sf::Vector2f({1.0f, 0.0f});
  }
  if (isKeyPressed(sf::Keyboard::Scancode::W)) {
    speed += sf::Vector2f({0.0f, -1.0f});
  }
  if (isKeyPressed(sf::Keyboard::Scancode::S)) {
    speed += sf::Vector2f({0.0f, 1.0f});
  }
  if (speed.x != 0 || speed.y != 0) {
    speed = speed.normalized();
    speed = speed * SpeedConst;
  }
  static float dashCooldown=2.0f;
  dashCooldown -= deltaT;
  static float dashTimer=0.1f;
  dashTimer -= deltaT;
  static sf::Vector2f dashDirection={0.0f,0.0f};
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space)&&dashCooldown<0.0f&&speed!=sf::Vector2f(0.0f,0.0f)) {
    dashCooldown = 2.0f;
    dashTimer = 3.0f;
    dashDirection=speed.normalized();
    m_phisicsObject->setSpeed(speed+m_phisicsObject->getSpeed());
  }
  m_phisicsObject->setAcceleration(speed);
  pos -= sf::Vector2i(Game::getInstance()->getWindow().getSize())/2;
  sf::Angle ang = Utils::getAngle(m_transform);
  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    m_firearm->Fire();
  }
  if (isKeyPressed(sf::Keyboard::Scancode::G)) {
    m_firearm->setActive(false);
  }
  if (isKeyPressed(sf::Keyboard::Scancode::F)) {
    m_firearm->setActive(true);
  }
  m_transform.rotate(sf::radians(atan2f(-pos.x, pos.y) + ang.asRadians()));
  (void) deltaT;
}

void Player::Init() {
  BaseGameObject::Init();
  sf::Transform tr = sf::Transform::Identity;
  tr.scale(sf::Vector2f(40.0f, 40.0f));

  EmplaceGameObject<ShapeRenderer>("CircleRenderer", tr, sf::Color(0, 255, 0), RenderOrder::Player, GeometryShape::Circle);
  EmplaceGameObject<Collider>(ColliderMask::Player, GeometryShape::Circle, tr);
  auto playerHealth=EmplaceGameObject<EntityHealth>(100.0f);
  playerHealth->setOnDeath([](EntityHealth* e) {
      e->getParent().lock()->SetParent(nullptr);
      Game::getInstance()->EmplaceGameObject<DeathScreen>();
  });
  playerHealth->setImunityTime(0.6f);

  m_phisicsObject = EmplaceGameObject<PhysicObject>(100.0f, 12.f, 0.0f);
  m_firearm = EmplaceGameObject<Firearm>("Firearm", sf::Transform::Identity);
}

void Player::print(std::ostream &os) const {
  os << "CLASS Player:";
  BaseGameObject::print(os);
}


void Player::AddGameObjectToGame() {
  BaseGameObject::AddGameObjectToGame();
}

void Player::RemoveGameObjectFromGame() {
  BaseGameObject::RemoveGameObjectFromGame();
}

Player::Player(const std::string &name, const sf::Transform &transform): BaseGameObject(name, transform) {
  m_updateOrder = UpdateOrder::Default;
}
