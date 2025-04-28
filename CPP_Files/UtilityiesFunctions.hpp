#pragma once
#include <cmath>

#include "SFML/Graphics/Transform.hpp"

namespace Utils{
  inline sf::Vector2f getPosition(const sf::Transform& tr) {
    return tr.transformPoint(sf::Vector2f(0, 0));
  }
  inline sf::Vector2f getSize(const sf::Transform& tr) {
    return sf::Vector2f(tr.transformPoint(sf::Vector2f(1,0)).length(),tr.transformPoint(sf::Vector2f(0,1)).length());
  }

  inline sf::Angle getAngle(const sf::Transform& tr) {
    sf::Vector2f point=tr.transformPoint(sf::Vector2f( 1.0f,0.0f))-
                       tr.transformPoint(sf::Vector2f(0.0f,0.0f));
    float angle=-atan2(point.y,point.x);
    return sf::radians(angle);
  }


}