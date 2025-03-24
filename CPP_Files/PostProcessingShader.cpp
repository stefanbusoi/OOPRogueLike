//NU AM ADAUGAT OPERATOR DE AFISARE DEOARECE ACEASTA CLASA NU E IMPLEMENTATA COMPLET SI NU DORESC SA FIE LUATA IN CALCUL PT MILESTONE 1,
//NU E INCLUS IN CMAKE

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
