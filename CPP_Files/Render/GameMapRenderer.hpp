//
// Created by stefa on 3/16/2025.
//

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "CoreFunctionality/BaseGameObject.hpp"
#include "IRenderable.hpp"
#include "RenerableGameObject.hpp"
#include "SFML/Graphics/Shader.hpp"

class GameMapRenderer :public RendableGameObject {
  sf::Shader m_shader;

protected:
  void print(std::ostream &os) const override;

public:
  explicit GameMapRenderer(const std::string &name = "NONNAME", const sf::Transform &transform = sf::Transform::Identity);

  void render() override;

  void update(float deltaT) override;

};


#endif //GAMEMAP_H
