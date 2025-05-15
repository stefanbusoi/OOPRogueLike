//
// Created by stefa on 4/28/2025.
//

#include "DebugMenu.hpp"


#include "../Game.hpp"
#include "../Resources.hpp"
#include "../Exceptions/GameLogicException.hpp"

DebugMenu::DebugMenu( const std::string &name, const sf::Transform &transform):
GameObject(name, transform){
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
      if (p.type==Type::INT2F) {
        text.setString(std::vformat(p.formatString,std::make_format_args(static_cast<sf::Vector2f*>(p.pt)->x,static_cast<sf::Vector2f*>(p.pt)->y)));
        Game::getInstance()->getRenderTexture().draw(text);
        continue;      }
      throw GameLogicException("Type not implemented");

    }
}

void DebugMenu::print(std::ostream &os) const {
  os<<"Class DebugMenu:";
  GameObject::print(os);
}

void DebugMenu::AddGameObjectToGame() {
  GameObject::AddGameObjectToGame();
  IRenderable::AddToRenderObjects();
}

void DebugMenu::RemoveGameObjectFromGame() {
  GameObject::RemoveGameObjectFromGame();
  IRenderable::RemoveFromRenderObjects();
}

std::ostream & operator<<(std::ostream &os, const DebugMenu &obj) {
    obj.print(os);
    return os;
}
