//
// Created by stefa on 5/2/2025.
//

#include "ShapeRenderer.hpp"
#include "Resources.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "CoreFunctionality/Game.hpp"
#include "Camera.hpp"

std::shared_ptr<BaseGameObject> ShapeRenderer::clone() const {
  std::shared_ptr<ShapeRenderer> clone;
  if (m_IsTexture) {
    clone = std::make_shared<ShapeRenderer>(m_name, m_transform, m_circleColor, m_renderOrder, m_shape);
    clone->m_texture = m_texture;
    clone->m_IsTexture = m_IsTexture;
  } else {
    clone = std::make_shared<ShapeRenderer>(m_name, m_transform, m_circleColor, m_renderOrder, m_shape);
    clone->m_IsTexture = m_IsTexture;
  }
  for (auto i: m_children) {
    clone->emplaceClone(i);
  }
  clone->m_name = m_name;
  clone->m_parent.reset();
  clone->m_updateOrder = m_updateOrder;
  return clone;
}

ShapeRenderer::ShapeRenderer(const std::string &name, const sf::Transform &transform, const sf::Color &color, const RenderOrder &render_order, GeometryShape geometry_shape)
  :BaseGameObject(name,transform),
  m_circleColor(color),
  m_shape(geometry_shape),
  m_IsTexture(false)
{
  m_renderOrder = render_order;;
}

ShapeRenderer::ShapeRenderer(const std::string &name, const sf::Transform &transform, const std::filesystem::path &path, const RenderOrder &render_order, GeometryShape geometry_shape)
  :BaseGameObject(name,transform),
  m_shape(geometry_shape),
  m_IsTexture(true),
  m_texture(Resources::getTexture(path))
{
  m_renderOrder = render_order;
}

void ShapeRenderer::update(float deltaTime) {
  BaseGameObject::update(deltaTime * 0.005f);
}

void ShapeRenderer::render() {
  std::weak_ptr<Camera> camera = Game::getInstance()->getCamera();
  sf::Transform transform = getGlobalTransform();

  if (m_shape == GeometryShape::Circle) {
    sf::CircleShape shape(1.f);
    shape.setOrigin({1, 1});
    if (m_IsTexture) {
      shape.setTexture(m_texture);
    } else {
      shape.setFillColor(m_circleColor);
    }
    camera.lock()->draw(shape, transform);
    return;
  }
  if (m_shape == GeometryShape::Rectangle) {
    sf::RectangleShape shape({1.0f, 1.0f});
    shape.setOrigin({0.5, 0.5});
    if (m_IsTexture) {
      shape.setTexture(m_texture);
    } else {
      shape.setFillColor(m_circleColor);
    }
    camera.lock()->draw(shape, transform);
  }
}

void ShapeRenderer::addGameObjectToGame() {
  IRenderable::addToRenderObjects();
}

void ShapeRenderer::removeGameObjectFromGame() {
  IRenderable::removeFromRenderObjects();
}
