//
// Created by fanel012 on 5/31/25.
//

#include "EnemySpawnerManager.h"

#include "BasicEnemy.hpp"
#include "EntitySpawner.hpp"
#include "CoreFunctionality/Game.hpp"
#include "Utilityies/RandomNumberGenerator.h"

void EnemySpawnerManager::update(float deltaT) {
    Timer+=deltaT;
    while (Timer>spawnTimer) {
        Timer-=spawnTimer;
        sf::Transform tr;
        tr.translate({RandomNumberGenerator::GetRandomNumber(-1600,1600),RandomNumberGenerator::GetRandomNumber(-1600.f,1600.f)});
        std::shared_ptr<BasicEnemy> enemy= std::make_shared<BasicEnemy>("Enemy");
        Game::getInstance()->EmplaceGameObject<EntitySpawner>(tr,2.0f,enemy);
    }
}
