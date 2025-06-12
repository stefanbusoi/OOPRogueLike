#pragma once
#include "CoreFunctionality/BaseGameObject.hpp"
#include "IRenderable.hpp"
#include "RenerableGameObject.hpp"
#include "SFML/Graphics/Shader.hpp"

class PostProcessingShader : public RendableGameObject {


protected:
  sf::Shader m_shader;
  std::filesystem::path m_path;
  void print(std::ostream &os) const override;

public:
  PostProcessingShader(std::string name, std::filesystem::path ShaderPath);

  void render() override;
};
