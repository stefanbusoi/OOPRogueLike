//NU AM ADAUGAT OPERATOR DE AFISARE DEOARECE ACEASTA CLASA NU E IMPLEMENTATA COMPLET SI NU DORESC SA FIE LUATA IN CALCUL PT MILESTONE 1,
//NU E INCLUS IN CMAKE

#ifndef POSTPROCESSINGSHADER_H
#define POSTPROCESSINGSHADER_H
#include "GameObject.hpp"
#include "IRenderable.hpp"
#include <SFML/Graphics.hpp>


class PostProcessingShader:public GameObject,public IRenderable {
    sf::Shader* m_shader;
    public:
    PostProcessingShader(std::string name,sf::Transform transform);
    void Render() override;
    void update(float deltaT) override;

    void AddGameObjectToGame() override;

    void RemoveGameObjectFromGame() override;
};



#endif //POSTPROCESSINGSHADER_H
