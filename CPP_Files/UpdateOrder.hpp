#pragma once

enum class UpdateOrder {
  Default = 127,
  PhisicsUpdate = 140,
  Collisions = 150,
  Camera = 170,
  PostProcessing = 185,
  UI = 200,
};
