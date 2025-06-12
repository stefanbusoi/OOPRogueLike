//
// Created by stefa on 3/16/2025.
//

#include "GameMapRenderer.hpp"

#include <iostream>

#include "CoreFunctionality/Game.hpp"

void GameMapRenderer::print(std::ostream &os) const {
  os << "CLASS GameMap:";
  BaseGameObject::print(os);
}

void GameMapRenderer::render() {
  Game &instance = *Game::getInstance();
  std::weak_ptr<Camera> camera = instance.getCamera();

  sf::RenderTarget &render_texture = instance.getRenderTexture();
  sf::RectangleShape fullscreenQuad(sf::Vector2f(render_texture.getSize()));
  fullscreenQuad.setPosition({0, 0});
  float totalTime = instance.getTotalTime();
  m_shader.setUniform("resolution", sf::Vector2f(render_texture.getSize()));
  m_shader.setUniform("position", camera.lock()->getTransform().transformPoint({0, 0}));
  m_shader.setUniform("time", totalTime);
  render_texture.draw(fullscreenQuad, &m_shader);
}

GameMapRenderer::GameMapRenderer(const std::string &name, const sf::Transform &transform):
  RendableGameObject(name, transform,RenderOrder::Terrain)
{
  m_updateOrder = UpdateOrder::Default;
  if (!m_shader.loadFromFile("Shaders/fragment.frag", sf::Shader::Type::Fragment)) {
    std::cerr << "Failed to load fragment shader" << std::endl;
  }
}


void GameMapRenderer::update(float deltaT) {
  (void) deltaT;
}

