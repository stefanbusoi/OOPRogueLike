#include <iostream>
#include <chrono>
#include <functional>
#include <thread>

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "GameMap.hpp"
#include "Player.hpp"
#include "Resources.hpp"
#include "Exceptions/FileException.hpp"
#include "Exceptions/GameLogicException.hpp"
#include "Exceptions/ShaderExceptions.hpp"

int main() {
    try {
        Game game(sf::VideoMode({1920, 1080}), "RogueLike");
        std::cout<<game<<"\n";
        for (const auto* i:game.getGameObjects()) {
            std::cout<<*i<<"\n";
        }
        for (const auto* i:game.getRenderObjects()) {
            std::cout<<*i<<"\n";
        }
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
