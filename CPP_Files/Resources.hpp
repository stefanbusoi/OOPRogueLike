#pragma once

#include <map>

#include "SFML/Graphics/Font.hpp"


/**
 * This class is used to store assets and to avalable for the program
 */
class Resources {
    static sf::Font font;
    static std::map<std::filesystem::path, std::unique_ptr<sf::Texture>> texture;
public:
    static sf::Font& getFont() {
        return font;
    }
    static sf::Texture* getTexture(const std::filesystem::path &path) {
        if (!texture.contains(path)) {
            texture[path]=std::make_unique<sf::Texture>(path.string());
        }
        return texture[path].get();
    }
};