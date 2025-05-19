#pragma once
#include "IRenderable.hpp"
#include "../GameObject.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../Collisions/Collider.h"
class ShapeRenderer:public IRenderable, public GameObject{
  sf::Color m_circleColor;
  sf::Texture* m_texture;
  GeometryShape m_shape;
  bool texture;
public:
  std::shared_ptr<GameObject> clone() const override;

  ShapeRenderer(const std::string& name,const sf::Transform& transform,const sf::Color& color,const RenderOrder& render_order,GeometryShape geometry_shape);
  ShapeRenderer(const std::string& name,const sf::Transform& transform,const std::filesystem::path& path,const RenderOrder& render_order,GeometryShape geometry_shape);

  void update(float deltaTime) override;
  void Render() override;

  void AddGameObjectToGame() override;
  void RemoveGameObjectFromGame() override;
};

