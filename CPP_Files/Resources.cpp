//
// Created by stefa on 4/28/2025.
//

#include "Resources.hpp"


std::map<std::filesystem::path, std::unique_ptr<sf::Texture>> Resources::texture;
sf::Font Resources::font= sf::Font("Minecraft.ttf");

sf::Font & Resources::getFont() {
  return font;
}

sf::Texture * Resources::getTexture(const std::filesystem::path &path) {
  if (!texture.contains(path)) {
    texture[path]=std::make_unique<sf::Texture>(path.string());
  }
  return texture[path].get();
}
