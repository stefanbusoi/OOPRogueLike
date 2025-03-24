#ifndef POSTPROCESSINGSHADER_H
#define POSTPROCESSINGSHADER_H
#include "GameObject.hpp"
#include "IRenderable.hpp"


class PostProcessingShader:public GameObject,public IRenderable {
    sf::Shader* m_shader;
    public:
    PostProcessingShader(std::string name,sf::Transform transform,GameObject* game_object);
    void Render() override;
    void update(float deltaT) override;
};



#endif //POSTPROCESSINGSHADER_H
