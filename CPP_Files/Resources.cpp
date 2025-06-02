//
// Created by stefa on 4/28/2025.
//

#include "Resources.hpp"


std::map<std::filesystem::path, std::unique_ptr<sf::Texture>> Resources::m_texture;
sf::Font Resources::m_font= sf::Font("Minecraft.ttf");

sf::Font & Resources::getFont() {
  return m_font;
}

sf::Texture * Resources::getTexture(const std::filesystem::path &path) {
  if (!m_texture.contains(path)) {
    m_texture[path]=std::make_unique<sf::Texture>(path.string());
  }
  return m_texture[path].get();
}
