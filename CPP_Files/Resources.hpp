//
// Created by stefa on 4/28/2025.
#pragma once

#include "SFML/Graphics/Font.hpp"


/**
 * This class is used to store assets and to avalable for the program
 */
class Resources {
private:
    static sf::Font font;
public:
    static sf::Font& getFont() {
        return font;
    }
};