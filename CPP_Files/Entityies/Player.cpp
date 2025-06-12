#include "Player.hpp"


#include "EntityHealth.hpp"
#include "CoreFunctionality/Game.hpp"
#include "Collisions/PhysicObject.hpp"
#include "Render/PostProcessingShader.h"
#include "Utilityies/TransformUtilityies.hpp"
#include "Render/ShapeRenderer.hpp"
#include "UI/DeathScreen.h"
#include "Weapons/Firearm.hpp"


void Player::update(float deltaT) {
  sf::Vector2i pos = sf::Mouse::getPosition(Game::getInstance()->getWindow());

  pos -= sf::Vector2i(Game::getInstance()->getWindow().getSize())/2;
  sf::Angle ang = Utils::getAngle(m_transform);
  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    m_firearm->fire();
  }
  if (isKeyPressed(sf::Keyboard::Scancode::G)) {
    m_firearm->setActive(false);
  }
  if (isKeyPressed(sf::Keyboard::Scancode::F)) {
    m_firearm->setActive(true);
  }
  m_transform.rotate(sf::radians(atan2f(-pos.x, pos.y) + ang.asRadians()));
  PlayerMovement(deltaT);
}

void Player::init() {
  BaseGameObject::init();
  sf::Transform tr = sf::Transform::Identity;
  tr.scale(sf::Vector2f(40.0f, 40.0f));

  emplaceGameObject<ShapeRenderer>("CircleRenderer", tr, sf::Color(0, 255, 0), RenderOrder::Player, GeometryShape::Circle);
  emplaceGameObject<Collider>(ColliderMask::Player, GeometryShape::Circle, tr);
  auto playerHealth=emplaceGameObject<EntityHealth>(100.0f);
  playerHealth->setOnDeath([](EntityHealth* e) {
      e->getParent().lock()->SetParent(nullptr);
      Game::getInstance()->emplaceGameObject<DeathScreen>();
      Game::getInstance()->emplaceGameObject<PostProcessingShader>("DeathShader",std::filesystem::path("Shaders/DeathShader.frag"));
  });
  playerHealth->setImunityTime(0.6f);

  m_phisicsObject = emplaceGameObject<PhysicObject>(100.0f, 12.f, 0.0f);
  m_firearm = emplaceGameObject<Firearm>("Firearm", sf::Transform::Identity);
}

void Player::print(std::ostream &os) const {
  os << "CLASS Player:";
  BaseGameObject::print(os);
}


void Player::addGameObjectToGame() {
  BaseGameObject::addGameObjectToGame();
}

void Player::PlayerMovement(float deltaT) {

  float SpeedConst = 7000;
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
  m_CurrentCooldown -= deltaT;
  m_CurrentCooldown=std::max(m_CurrentCooldown,0.0f);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space)&&m_CurrentCooldown<=0.0f&&speed!=sf::Vector2f(0.0f,0.0f)) {
    m_CurrentCooldown = m_DashCooldown;
    m_phisicsObject->setSpeed(speed+m_phisicsObject->getSpeed());
  }
  m_phisicsObject->setAcceleration(speed);
}



void Player::removeGameObjectFromGame() {
  BaseGameObject::removeGameObjectFromGame();
}

Player::Player(const std::string &name, const sf::Transform &transform): BaseGameObject(name, transform) {
  m_updateOrder = UpdateOrder::Default;
}
