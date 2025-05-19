//
// Created by stefa on 3/16/2025.
//

#include "GameMap.hpp"

#include <iostream>

#include "Game.hpp"

void GameMap::print(std::ostream &os) const {
  os << "CLASS GameMap:";
  GameObject::print(os);
}

void GameMap::Render() {
  Game &instance = *Game::getInstance();
  std::weak_ptr<Camera> camera = instance.getCamera();

  sf::RenderWindow &window = instance.getWindow();
  sf::RenderTarget &render_texture = instance.getRenderTexture();
  sf::RectangleShape fullscreenQuad(sf::Vector2f(window.getSize()));
  fullscreenQuad.setPosition({0, 0});
  float totalTime = instance.getTotalTime();
  m_shader.setUniform("resolution", sf::Vector2f(window.getSize()));
  m_shader.setUniform("position", camera.lock()->getTransform().transformPoint({0, 0}));
  m_shader.setUniform("time", totalTime);
  render_texture.draw(fullscreenQuad, &m_shader);
}

GameMap::GameMap(const std::string &name, const sf::Transform &transform): GameObject(name, transform) {
  m_renderOrder = RenderOrder::Terrain;
  m_updateOrder = UpdateOrder::Default;
  if (!m_shader.loadFromFile("Shaders/fragment.frag", sf::Shader::Type::Fragment)) {
    std::cerr << "Failed to load fragment shader" << std::endl;
  }
}


void GameMap::update(float deltaT) {
  (void) deltaT;
}

void GameMap::AddGameObjectToGame() {
  GameObject::AddGameObjectToGame();
  IRenderable::AddToRenderObjects();
}

void GameMap::RemoveGameObjectFromGame() {
  GameObject::RemoveGameObjectFromGame();
  IRenderable::RemoveFromRenderObjects();
}
