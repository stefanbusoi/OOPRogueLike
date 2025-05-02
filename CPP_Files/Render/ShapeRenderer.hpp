#pragma once
#include "IRenderable.hpp"
#include "../GameObject.hpp"
#include <SFML/Graphics/Color.hpp>

#include "../Collider.h"

class ShapeRenderer: public IRenderable,public GameObject{
  sf::Color m_circleColor;
  GeometryShape m_shape;
public:
  ShapeRenderer(const std::string& name,const sf::Transform& transform,const sf::Color& color,const RenderOrder& render_order,GeometryShape geometry_shape);
  void update(float deltaTime) override;
  void Render() override;
  void AddGameObjectToGame() override;
  void RemoveGameObjectFromGame() override;
};

