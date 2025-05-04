//
// Created by stefa on 5/4/2025.
//

#include "Firearm.hpp"
#include "../Render/ShapeRenderer.hpp"
Firearm::Firearm(const std::string &name, sf::Transform transform):GameObject(name,transform,nullptr) {
    sf::Transform tr=sf::Transform::Identity;
    tr.translate(sf::Vector2f(0.0f,25.0f)).scale(sf::Vector2f(10.0f,52.0f));
    EmplaceGameObject<ShapeRenderer>("CircleRenderer",tr, sf::Color(20,20,20), RenderOrder::PostProcessing,GeometryShape::Square);
}

