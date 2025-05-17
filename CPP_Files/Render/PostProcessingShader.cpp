
#include "PostProcessingShader.h"

#include "../Game.hpp"
#include "../Exceptions/FileException.hpp"


void PostProcessingShader::print(std::ostream &os) const {
    os<<"Class PPShader: Shader:"<<m_path.filename()<<",";
    GameObject::print(os);
}

PostProcessingShader::PostProcessingShader(std::string name, std::filesystem::path ShaderPath): GameObject(name,sf::Transform::Identity) {
    m_renderOrder=RenderOrder::PostProcessing;
    m_path=ShaderPath;
        if (!m_shader.loadFromFile(ShaderPath, sf::Shader::Type::Fragment)){
           throw FileException("Failed to load fragment shader:\""+ShaderPath.string()+"\"");
        }
}

void PostProcessingShader::Render() {
    sf::RenderWindow& window=Game::getInstance()->getWindow();
    sf::RenderTexture& renderTexture=Game::getInstance()->getRenderTexture();
    std::weak_ptr<Camera> camera = Game::getInstance()->getCamera();
    static sf::RenderTexture renderTextureB(window.getSize());

    sf::RectangleShape fullscreenQuad(sf::Vector2f(window.getSize().x, window.getSize().y));
    fullscreenQuad.setPosition({0, 0});

    renderTexture.display();
    float time=Game::getInstance()->getTotalTime();
    m_shader.setUniform("tex", renderTexture.getTexture());
    m_shader.setUniform("time", time);
    m_shader.setUniform("resolution",sf::Vector2f(window.getSize().x,window.getSize().y));
    m_shader.setUniform("position",camera.lock()->getTransform().transformPoint({0,0}));
    renderTextureB.draw(fullscreenQuad,&m_shader);
    renderTextureB.display();
    m_shader.setUniform("tex", renderTextureB.getTexture());
    renderTexture.draw(fullscreenQuad,&m_shader);
}

void PostProcessingShader::AddGameObjectToGame() {
    GameObject::AddGameObjectToGame();
    IRenderable::AddToRenderObjects();
}

void PostProcessingShader::RemoveGameObjectFromGame() {
    GameObject::RemoveGameObjectFromGame();
    IRenderable::RemoveFromRenderObjects();
}

