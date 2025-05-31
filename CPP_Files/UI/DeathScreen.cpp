//
// Created by fanel012 on 5/31/25.
//

#include "DeathScreen.h"

DeathScreen::DeathScreen() {
}

void DeathScreen::AddGameObjectToGame() {
    BaseGameObject::AddGameObjectToGame();
    IRenderable::AddToRenderObjects();
}

void DeathScreen::RemoveGameObjectFromGame() {
    BaseGameObject::RemoveGameObjectFromGame();
    IRenderable::RemoveFromRenderObjects();
}

void DeathScreen::Render() {
}
