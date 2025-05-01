//
// Created by stefa on 4/28/2025.
//

#ifndef RESOURCES_HPP
#define RESOURCES_HPP
#include "SFML/Graphics/Font.hpp"


class Resources {
private:
    static sf::Font font;
public:
    static sf::Font& getFont() {
        return font;
    }
};

#endif //RESOURCES_HPP
