//
// Created by stefa on 4/28/2025.
//

#include "DebugMenu.hpp"

#include <format>

#include "../Game.hpp"
#include "../Resources.hpp"

DebugMenu::DebugMenu( const std::string &name, const sf::Transform &transform,GameObject* parent):
GameObject(name, transform,parent)
{
  m_renderOrder=RenderOrder::UIPostProcessing;
  m_updateOrder=UpdateOrder::UI;

}
void DebugMenu::update( float deltaT) {
  (void)deltaT;
}
void DebugMenu::Render() {
    sf::Text text(Resources::getFont());
    text.setFillColor(sf::Color::White);
  text.setCharacterSize(20);
    int pos=30;

    for (auto& p : m_printList) {
      text.setPosition(sf::Vector2f(30,pos));
      pos+=20;
      if (p.type==Type::FLOAT) {
        text.setString(std::vformat(p.formatString,std::make_format_args(*static_cast<float*>(p.pt))));
        Game::getInstance()->getRenderTexture().draw(text);
        continue;
      }
      if (p.type==Type::INT) {
        text.setString(std::vformat(p.formatString,std::make_format_args(*static_cast<int*>(p.pt))));
        Game::getInstance()->getRenderTexture().draw(text);
        continue;
      }
      throw std::runtime_error("Type not implemented");

    }
}

void DebugMenu::AddGameObjectToGame() {
  GameObject::AddGameObjectToGame();
  IRenderable::AddToRenderObjects();
}

void DebugMenu::RemoveGameObjectFromGame() {
  GameObject::RemoveGameObjectFromGame();
  IRenderable::RemoveFromRenderObjects();
}
