//
// Created by stefa on 5/30/2025.
//

#include "EntitySpawner.hpp"

#include <CoreFunctionality/Game.hpp>

#include "Render/ShapeRenderer.hpp"

EntitySpawner::EntitySpawner(sf::Transform transform,float Time,std::shared_ptr<BaseGameObject> Entity):
  BaseGameObject("EntitySpawner",transform),
  m_Entity(Entity)
  {
    m_SpawnTimer=Time;
  }

void EntitySpawner::init() {
  sf::Transform transform;
  transform.scale({100.0f,100.0f});
  emplaceGameObject<ShapeRenderer>("ShapeRenderer",transform,"Assets/SpawnIcon.png",RenderOrder::Player,GeometryShape::Rectangle);
}

void EntitySpawner::update(float deltaT) {
  m_Time+=deltaT;
  if (m_Time>=m_SpawnTimer) {
    auto entity=Game::getInstance()->emplaceClone(m_Entity,m_transform);
    entity->init();

    SetParent(nullptr);
  }
}
