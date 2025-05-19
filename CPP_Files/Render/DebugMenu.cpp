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

void DebugMenu::Render() {
    sf::Text text(Resources::getFont());
    text.setFillColor(sf::Color::White);
  text.setCharacterSize(20);
    int pos=30;

    for (auto& p : m_printList) {
      text.setPosition(sf::Vector2f(30,pos));
      pos+=20;
      if (p.type==Type::FLOAT) {
        text.setString(std::vformat(p.formatString,std::make_format_args(p.m_float)));
        Game::getInstance()->getRenderTexture().draw(text);
        continue;
      }
      if (p.type==Type::INT) {
        text.setString(std::vformat(p.formatString,std::make_format_args(p.m_int)));
        Game::getInstance()->getRenderTexture().draw(text);
        continue;
      }
      if (p.type==Type::INT2F) {
        text.setString(std::vformat(p.formatString,std::make_format_args(p.m_float2.x,p.m_float2.y)));
        Game::getInstance()->getRenderTexture().draw(text);
        continue;
      }
      throw GameLogicException("Type not implemented");

    }
}

void DebugMenu::update(float deltaT) {
  timer+=deltaT;
  if (timer>0.5f) {
    timer-=0.5f;
    for (auto& p : m_printList) {
      switch(p.type){
        case Type::FLOAT:
          p.m_float=*static_cast<float*>(p.pt);
        break;
        case Type::INT:
          p.m_int=*static_cast<int*>(p.pt);
        break;
        case Type::DOUBLE:
          p.m_double=*static_cast<double*>(p.pt);
        break;
        case Type::INT2I:
          p.m_int2=*static_cast<sf::Vector2i*>(p.pt);
        break;
        case Type::INT2F:
          p.m_float2=*static_cast<sf::Vector2f*>(p.pt);
        break;
      default:
        throw GameLogicException("Type not implemented");
      }
    }
  }
}

void DebugMenu::AddPrintList(const std::string &formatString, void *pointer, Type type) {
  m_printList.emplace_back(formatString,pointer,type);
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
