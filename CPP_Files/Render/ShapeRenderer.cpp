//
// Created by stefa on 5/2/2025.
//

#include "ShapeRenderer.hpp"
#include "../Resources.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "../Game.hpp"
#include "Camera.hpp"
  std::shared_ptr<GameObject> ShapeRenderer::clone() const{
    std::shared_ptr<ShapeRenderer> clone;
    if (texture) {
      clone=std::make_shared <ShapeRenderer>(m_name,m_transform,m_circleColor,m_renderOrder,m_shape);
      clone->m_texture=m_texture;
      clone->texture=texture;
    }else {
      clone=std::make_shared <ShapeRenderer>(m_name,m_transform,m_circleColor,m_renderOrder,m_shape);
      clone->texture=texture;
    }
    for (auto i:m_children) {
      clone->EmplaceClone(*i);
    }
    clone->m_name =m_name;
    clone->m_parent.reset();
    clone->m_updateOrder = m_updateOrder;
    return clone;
  }

ShapeRenderer::ShapeRenderer(const std::string &name,const sf::Transform& transform,const sf::Color& color,const RenderOrder& render_order,GeometryShape geometry_shape) {
  m_transform=transform;
  m_name=name;
  m_circleColor=color;
  m_renderOrder=render_order;
  m_shape=geometry_shape;
  texture=false;
}

ShapeRenderer::ShapeRenderer(const std::string &name, const sf::Transform &transform, const std::filesystem::path &path, const RenderOrder &render_order, GeometryShape geometry_shape) {
  m_transform=transform;
  m_name=name;
  m_renderOrder=render_order;
  m_shape=geometry_shape;
  texture=true;
  m_texture=Resources::getTexture(path);
}

void ShapeRenderer::update(float deltaTime) {
  GameObject::update(deltaTime);
}

void ShapeRenderer::Render() {
  std::weak_ptr<Camera> camera = Game::getInstance()->getCamera();
  sf::Transform transform=getGlobalTransform();

  if (m_shape==GeometryShape::Circle) {
    sf::CircleShape shape(1.0f);
    shape.setOrigin({1, 1});
  if (texture) {
    shape.setTexture(m_texture);
  }else {
    shape.setFillColor(m_circleColor);
  }
    camera.lock()->draw(shape,transform);
    return;
  }
  if (m_shape==GeometryShape::Square) {
    sf::RectangleShape shape({1.0f,1.0f});
    shape.setOrigin({0.5, 0.5});
    if (texture) {
      shape.setTexture(m_texture);
    }else {
      shape.setFillColor(m_circleColor);
    }
    camera.lock()->draw(shape,transform);
  }
}

void ShapeRenderer::AddGameObjectToGame() {
  IRenderable::AddToRenderObjects();
}
void ShapeRenderer::RemoveGameObjectFromGame() {
  IRenderable::RemoveFromRenderObjects();
}
