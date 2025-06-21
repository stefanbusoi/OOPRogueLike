#include "Camera.hpp"


#include "CoreFunctionality/Game.hpp"
#include "Utilityies/TransformUtilityies.hpp"

void Camera::print(std::ostream &os) const {
  os << "Class Camera";
  BaseGameObject::print(os);
}


Camera::Camera(const std::string &name, const sf::Transform &transform):
  BaseGameObject(name, transform),
m_window(&Game::getInstance()->getWindow()),
  m_player(Game::getInstance()->getGameObjectOfType<Player>()){
  m_updateOrder = UpdateOrder::Camera;
}

sf::Transform &Camera::getTransform() {
  return m_transform;
}

void Camera::update([[maybe_unused]] float deltaT) {
  if (m_player.expired()) {
    m_player = Game::getInstance()->getGameObjectOfType<Player>();
  } else {
    sf::Transform transform = sf::Transform::Identity;
    m_transform = transform.translate(Utils::getPosition(m_player.lock()->getGlobalTransform()));
  }
}


void Camera::draw(const sf::Drawable &drawable, const sf::Transform &transform) const {
  sf::Transform viewTransform = m_transform;
  viewTransform.translate(sf::Vector2f(m_window->getSize())/-2.0f);

  sf::Transform finalTransform = viewTransform.getInverse() * transform;
  Game::getInstance()->getRenderTexture().draw(drawable, finalTransform);
}

std::ostream &operator<<(std::ostream &os, const Camera &obj) {
  os << "CLASS Camera " << static_cast<const BaseGameObject &>(obj);
  return os;
}
