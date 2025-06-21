#pragma once
#include "IRenderable.hpp"
#include "CoreFunctionality/BaseGameObject.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "RenerableGameObject.hpp"
#include "Collisions/Collider.h"

/**
 * used to render a shape to the screen
 */
class ShapeRenderer :  public RendableGameObject {
  /**
   * color of the shape
   */
  sf::Color m_shapeColor;
  /**
   * texture of the shape
   */
  sf::Texture *m_texture;
  /**
   * what shape to render
   */
  GeometryShape m_shape;
  /**
   * 1-renders the texture
   * 0-renders a solid color over the shape
   */
  bool m_IsTexture;

public:
  std::shared_ptr<BaseGameObject> clone() const override;

  /**
   *
   * @param name name of the object
   * @param transform position of the object
   * @param color where is the color
   * @param render_order order of render
   * @param geometry_shape shape of object
   */
  ShapeRenderer(const std::string &name, const sf::Transform &transform, const sf::Color &color, const RenderOrder &render_order, GeometryShape geometry_shape);

  /**
  *
  * @param name name of the object
  * @param transform position of the object
  * @param path path of the texture
  * @param render_order order of render
  * @param geometry_shape shape of object
  */
  ShapeRenderer(const std::string &name, const sf::Transform &transform, const std::filesystem::path &path, const RenderOrder &render_order, GeometryShape geometry_shape);

  void update(float deltaTime) override;

  void render() override;

};
