//NU AM ADAUGAT OPERATOR DE AFISARE DEOARECE ACEASTA CLASA NU E IMPLEMENTATA COMPLET SI NU DORESC SA FIE LUATA IN CALCUL PT MILESTONE 1,
//NU E INCLUS IN CMAKE

#include "PostProcessingShader.h"

#include "Game.hpp"


PostProcessingShader::PostProcessingShader(std::string name, sf::Transform transform, GameObject* game_object): GameObject(name,transform,game_object) {
    m_renderOrder=RenderOrder::PostProcessing;
    m_shader=new sf::Shader();
    if (!m_shader->loadFromFile("Shaders/PostProcessingShader.frag", sf::Shader::Type::Fragment)){
        std::cerr<<"Failed to load fragment shader"<<std::endl;
    }
}

void PostProcessingShader::Render() {
    sf::RenderWindow& window=Game::getInstance()->getWindow();
    sf::RenderTexture& renderTexture=Game::getInstance()->getRenderTexture();
    Camera& camera=Game::getInstance()->getCamera();
    static sf::RenderTexture renderTextureB(window.getSize());

    sf::RectangleShape fullscreenQuad(sf::Vector2f(window.getSize().x, window.getSize().y));
    fullscreenQuad.setPosition({0, 0});

    renderTexture.display();
    float time=Game::getInstance()->getTotalTime();
    m_shader->setUniform("tex", renderTexture.getTexture());
    m_shader->setUniform("time", time);
    m_shader->setUniform("resolution",sf::Vector2f(window.getSize().x,window.getSize().y));
    m_shader->setUniform("position",camera.getTransform().transformPoint({0,0}));
    renderTextureB.draw(fullscreenQuad,m_shader);
    renderTextureB.display();
    m_shader->setUniform("tex", renderTextureB.getTexture());
    renderTexture.draw(fullscreenQuad,m_shader);
}

void PostProcessingShader::update([[maybe_unused]]float deltaT) {

}
