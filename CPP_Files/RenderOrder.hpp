//
// Created by stefa on 3/19/2025.
//

#ifndef RENDERORDER_H
#define RENDERORDER_H

enum class RenderOrder {
    Terrain=10,
    Default=40,
    Player=60,
    PostProcessing=100,
};
#endif //RENDERORDER_H
