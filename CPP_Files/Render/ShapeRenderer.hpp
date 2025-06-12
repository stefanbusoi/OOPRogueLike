#pragma once
#include "IRenderable.hpp"
#include "CoreFunctionality/BaseGameObject.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "RenerableGameObject.hpp"
#include "Collisions/Collider.h"

class ShapeRenderer :  public RendableGameObject {
  sf::Color m_shapeColor;
  sf::Texture *m_texture;
  GeometryShape m_shape;
  bool m_IsTexture;

public:
  std::shared_ptr<BaseGameObject> clone() const override;

  ShapeRenderer(const std::string &name, const sf::Transform &transform, const sf::Color &color, const RenderOrder &render_order, GeometryShape geometry_shape);

  ShapeRenderer(const std::string &name, const sf::Transform &transform, const std::filesystem::path &path, const RenderOrder &render_order, GeometryShape geometry_shape);

  void update(float deltaTime) override;

  void render() override;

};
