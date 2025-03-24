//
// Created by stefa on 3/23/2025.
//

#ifndef POSTPROCESSINGSHADER_H
#define POSTPROCESSINGSHADER_H
#include "GameObject.hpp"
#include "IRenderable.hpp"
#include "SFML/Graphics/Shader.hpp"


class PostProcessingShader:public GameObject,public IRenderable {
    sf::Shader* m_shader;
    public:
    PostProcessingShader(std::string name,sf::Transform transform,GameObject* game_object);
    void Render() override;
    void update(float deltaT) override;
};



#endif //POSTPROCESSINGSHADER_H
