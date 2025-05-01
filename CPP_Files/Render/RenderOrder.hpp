#pragma once
#include "IRenderable.hpp"
enum class RenderOrder {
    Terrain=10,
    Default=40,
    Player=60,
    UIPreProcessing=80,
    PostProcessing=100,
    UIPostProcessing=150,
};

