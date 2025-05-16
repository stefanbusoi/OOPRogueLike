#include <iostream>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Resources.hpp"
#include "Exceptions/FileException.hpp"
#include "Exceptions/GameLogicException.hpp"
#include "Exceptions/ShaderExceptions.hpp"

int main() {
    try {
        Game game(sf::VideoMode({1920, 1080}), "RogueLike");
        while(game.isRunning()) {
            game.processGameFrame();
        }
    }catch (GameLogicException& l) {
        std::cerr<<"GAME LOGIC ERROR:"+std::string(l.what());
        return EXIT_FAILURE;
    }catch (FileException& l) {
        std::cerr<<"FILES LOGIC ERROR:"+std::string(l.what());
        return EXIT_FAILURE;
    }catch (ShaderExceptions& l) {
        std::cerr<<"SHADER ERROR:"+std::string(l.what());
        return EXIT_FAILURE;
    }
    return 0;
}
