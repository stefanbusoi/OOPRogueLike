#pragma once
#include "Slider.h"
#include "Entityies/Player.hpp"

/**
 * a bar witch show the player dash cooldown to the screen
 */
class DashBar:public Slider {
  std::weak_ptr<Player> player;
public:
  void update(float deltaT) override;
  void render() override;

  DashBar();
};

