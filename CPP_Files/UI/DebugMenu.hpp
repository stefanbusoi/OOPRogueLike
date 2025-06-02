#pragma once

#include "CoreFunctionality/BaseGameObject.hpp"
#include <format>

enum class Type {
  none = 0,
  INT = 1,
  FLOAT = 2,
  DOUBLE = 3,
  INT2I = 4,
  INT2F = 5,
};

struct PrintList {
  std::string formatString;
  void *pt;
  Type type;
  PrintList(const std::string &formatString, void *pt, Type type) {
    this->formatString = formatString;
    this->pt = pt;
    this->type = type;
  }

  union {
    int m_int;
    float m_float;
    double m_double;
    sf::Vector2i m_int2;
    sf::Vector2f m_float2;
  };
};

class DebugMenu : public BaseGameObject, public IRenderable {
  std::vector<PrintList> m_printList;
  float m_timer = 0;

protected:
  void print(std::ostream &os) const override;

public:
  DebugMenu(const std::string &name = "NONNAME", const sf::Transform &transform = sf::Transform::Identity);

  void render() override;

  void update(float deltaT) override;

  void AddPrintList(const std::string &formatString, void *pointer, Type type);

  void addGameObjectToGame() override;

  void removeGameObjectFromGame() override;

  friend std::ostream &operator<<(std::ostream &os, const DebugMenu &obj);
};
