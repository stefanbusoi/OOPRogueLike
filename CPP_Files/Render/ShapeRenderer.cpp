//
// Created by stefa on 5/2/2025.
//

#include "ShapeRenderer.hpp"

#include "SFML/Graphics/CircleShape.hpp"
#include "../Game.hpp"
#include "Camera.hpp"
ShapeRenderer::ShapeRenderer(const std::string &name,const sf::Transform& transform,const sf::Color& color,const RenderOrder& render_order,GeometryShape geometry_shape) {
  m_transform=transform;
  m_name=name;
  m_circleColor=color;
  m_renderOrder=render_order;
  m_shape=geometry_shape;
}

void ShapeRenderer::update(float deltaTime) {
  GameObject::update(deltaTime);
}

void ShapeRenderer::Render() {
  const Camera& camera=Game::getInstance()->getCamera();
  sf::Transform transform=getGlobalTransform();
  if (m_shape==GeometryShape::Circle) {
    sf::CircleShape shape(1.0f);
    shape.setOrigin({1, 1});
    shape.setFillColor(m_circleColor);
    camera.draw(shape,transform);
    return;
  }
  if (m_shape==GeometryShape::Square) {
    sf::RectangleShape shape({1.0f,1.0f});
    shape.setOrigin({0.5, 0.5});
    shape.setFillColor(m_circleColor);
    camera.draw(shape,transform);
    return;
  }
}

void ShapeRenderer::AddGameObjectToGame() {
  IRenderable::AddToRenderObjects();
}
void ShapeRenderer::RemoveGameObjectFromGame() {
  IRenderable::RemoveFromRenderObjects();
}
