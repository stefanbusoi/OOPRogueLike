#pragma once
#include "Slider.h"
#include "Entityies/Player.hpp"

class DashBar:public Slider {
  std::weak_ptr<Player> player;
public:
  void update(float deltaT) override;
  void render() override;

  DashBar();
};

