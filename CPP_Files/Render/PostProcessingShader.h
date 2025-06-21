#pragma once
#include "CoreFunctionality/BaseGameObject.hpp"
#include "IRenderable.hpp"
#include "RenerableGameObject.hpp"
#include "SFML/Graphics/Shader.hpp"

/**
 * Manages the shader witch are rendered over the screen
 */
class PostProcessingShader : public RendableGameObject {


protected:
  sf::Shader m_shader;
  std::filesystem::path m_path;
  void print(std::ostream &os) const override;

public:
  /**
   *
   * @param name name of the shader(used for debug)
   * @param ShaderPath path of the shader
   */
  PostProcessingShader(const std::string& name,const std::filesystem::path& ShaderPath);

  void render() override;
};
