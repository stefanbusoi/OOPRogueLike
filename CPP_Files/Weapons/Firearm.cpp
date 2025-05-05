//
// Created by stefa on 5/4/2025.
//

#include "Firearm.hpp"
#include "../Render/ShapeRenderer.hpp"
Firearm::Firearm(const std::string &name, sf::Transform transform):GameObject(name,transform,nullptr) {
    sf::Transform tr=sf::Transform::Identity;
    tr.translate(sf::Vector2f(0.0f,40.0f)).scale(sf::Vector2f(100.f, -130.0f));
    EmplaceGameObject<ShapeRenderer>("CircleRenderer",tr, std::filesystem::path("../Assets/bow_arrow.png"), RenderOrder::PostProcessing,GeometryShape::Square);
}

