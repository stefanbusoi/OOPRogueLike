#pragma once
#include <cmath>

#include "SFML/Graphics/Transform.hpp"

namespace Utils {
  /**
   *
   * @param tr object transform
   * @return position based of the transform
   */
  inline sf::Vector2f getPosition(const sf::Transform &tr) {
    return tr.transformPoint(sf::Vector2f(0, 0));
  }

  /**
   *
   * @param tr object transfrom
   * @return scale based of the transfrom
   */
  inline sf::Vector2f getSize(const sf::Transform &tr) {
    return sf::Vector2f((tr.transformPoint(sf::Vector2f(1, 0)) - tr.transformPoint({0.0f, 0.0f})).length()
                        , (tr.transformPoint(sf::Vector2f(0, 1)) - tr.transformPoint({0.0f, 0.0f})).length());
  }

  /**
   *
   * @param tr object transform
   * @return rotation based of the transform
   */
  inline sf::Angle getAngle(const sf::Transform &tr) {
    sf::Vector2f point = tr.transformPoint(sf::Vector2f(1.0f, 0.0f)) -
                         tr.transformPoint(sf::Vector2f(0.0f, 0.0f));
    float angle = -atan2(point.y, point.x);
    return sf::radians(angle);
  }
}
