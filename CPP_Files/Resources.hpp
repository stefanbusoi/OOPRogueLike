#pragma once

#include <map>

#include "SFML/Graphics/Font.hpp"


/**
 * This class is used to store assets and to avalable for the program
 *
 */
class Resources {
  static sf::Font m_font;
  static std::map<std::filesystem::path, std::unique_ptr<sf::Texture> > m_texture;

public:
  /**
   *
   * @return get a reference to the font of the program, current font used is Minecraft.ttf
   */
  static sf::Font &getFont();

  /**
   *
   * @param path Path of the texture
   * @return get a pointer to the texture at that path, if that texture already is loaded it gives a reference to the already loaded texture
   */
  static sf::Texture *getTexture(const std::filesystem::path &path);
};
