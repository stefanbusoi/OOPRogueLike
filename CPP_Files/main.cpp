#include <iostream>
#include <chrono>
#include <functional>
#include <thread>

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "GameMap.hpp"
#include "Player.hpp"

int main() {
    Game game(sf::VideoMode({1920, 1080}), "RogueLike");
    std::cout<<game<<"\n";
    sf::Font font("../Minecraft.ttf");

    while(game.IsRunning()) {
        float time=game.ProcessGameFrame();
        while(const std::optional event = game.getWindow().pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                game.Exit();
            }
            else if (event->is<sf::Event::Resized>()) {
                std::cout << "New width: " << game.getWindow().getSize().x << '\n'
                          << "New height: " << game.getWindow().getSize().y << '\n';
            }
            else if (event->is<sf::Event::KeyPressed>()) {
                const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
                if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    game.Exit();
                }
            }else if (event->is<sf::Event::MouseButtonPressed>()) {
                const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>();
                std::cout << "X: " << (keyPressed->position.x)<<",Y: "<<keyPressed->position.y ;
            }
        }

        sf::Text text(font);
        text.setString(std::to_string(time));
        text.setPosition(sf::Vector2f(30,30));
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(20);
        game.getWindow().draw(text);

        text.setString(std::to_string((int)(1/time)));
        text.setPosition(sf::Vector2f(30,50));
        game.getWindow().draw(text);
       // std::cout<<1/time<<"\n";
    }

    return 0;
}
