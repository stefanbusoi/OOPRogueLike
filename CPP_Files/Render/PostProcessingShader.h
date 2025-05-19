#pragma once
#include "../GameObject.hpp"
#include "IRenderable.hpp"
#include "SFML/Graphics/Shader.hpp"

class PostProcessingShader:public GameObject,public IRenderable {
    sf::Shader m_shader;
    std::filesystem::path m_path;

protected:
    void print(std::ostream &os) const override;

public:
    PostProcessingShader(std::string name, std::filesystem::path ShaderPath);

    void Render() override;

    void AddGameObjectToGame() override;
    void RemoveGameObjectFromGame() override;
};
