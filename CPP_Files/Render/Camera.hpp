#pragma once
#include <SFML/Graphics.hpp>

#include "CoreFunctionality/BaseGameObject.hpp"
#include "Entityies/Player.hpp"

/**
 * Camera uned to render the scene
 * it follow the player
 */
class Camera : public BaseGameObject {
  sf::RenderWindow *m_window;
  std::weak_ptr<Player> m_player;

protected:
  void print(std::ostream &os) const override;

public:
  friend std::ostream &operator<<(std::ostream &os, const Camera &obj);

  explicit Camera(const std::string &name = "Camera", const sf::Transform &transform = sf::Transform::Identity);

  sf::Transform &getTransform();

  /**
   *
   * @param drawable what to draw on the screen
   * @param transform where to draw on the screen
   */
  void draw(const sf::Drawable &drawable, const sf::Transform &transform) const;

  void update(float deltaT) override;

};
