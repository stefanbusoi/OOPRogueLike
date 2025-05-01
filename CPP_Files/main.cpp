#include <iostream>
#include <chrono>
#include <functional>
#include <thread>

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "GameMap.hpp"
#include "Player.hpp"
#include "Resources.hpp"

int main() {
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
    return 0;
}
