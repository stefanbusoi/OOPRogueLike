#pragma once
#include "CoreFunctionality/BaseGameObject.hpp"
#include "IRenderable.hpp"
#include "SFML/Graphics/Shader.hpp"

class PostProcessingShader : public BaseGameObject, public IRenderable {
  sf::Shader m_shader;
  std::filesystem::path m_path;

protected:
  void print(std::ostream &os) const override;

public:
  PostProcessingShader(std::string name, std::filesystem::path ShaderPath);

  void render() override;

  void addGameObjectToGame() override;

  void removeGameObjectFromGame() override;
};
