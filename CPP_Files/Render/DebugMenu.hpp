#pragma once
#include <ostream>

#include "../GameObject.hpp"

enum class Type{
  none=0,
  INT=1,
  FLOAT=2,
  DOUBLE=3,
  INT2I=4,
  INT2F=5,
};
struct PrintList {
  std::string formatString;
  void* pt;
  Type type;

};
class DebugMenu : public GameObject ,public IRenderable{
  std::vector<PrintList> m_printList;
public:
  DebugMenu(  const std::string &name="NONNAME", const sf::Transform &transform=sf::Transform::Identity);
  void Render() override;
  void AddPrintList(PrintList p) {
    m_printList.push_back(p);
  }

protected:
  friend std::ostream & operator<<(std::ostream &os, const DebugMenu &obj) ;
  void print(std::ostream &os) const override;

public:
  void AddGameObjectToGame() override;
  void RemoveGameObjectFromGame() override;
};
