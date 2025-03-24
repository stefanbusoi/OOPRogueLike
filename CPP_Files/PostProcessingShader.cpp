//
// Created by stefa on 3/23/2025.
//

#include "PostProcessingShader.h"

#include "Game.hpp"


PostProcessingShader::PostProcessingShader(std::string name, sf::Transform transform, GameObject* game_object): GameObject(name,transform,game_object) {
    m_shader=new sf::Shader();
    if (!m_shader->loadFromFile("../Shaders/fragment.frag", sf::Shader::Type::Fragment)){
        std::cerr<<"Failed to load fragment shader"<<std::endl;
    }
}

void PostProcessingShader::Render() {

}

void PostProcessingShader::update([[maybe_unused]]float deltaT) {

}
