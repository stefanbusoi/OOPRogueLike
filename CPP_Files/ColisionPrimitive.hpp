//
// Created by stefa on 4/10/2025.
//

#ifndef COLISIONPRIMITIVE_HPP
#define COLISIONPRIMITIVE_HPP
#include "GameObject.hpp"
#include "SFML/Graphics/Transform.hpp"


class ColisionPrimitive :public GameObject{

    enum class GeometryShape{
      Square=0,
      Circle=1,
    };
    GeometryShape m_shape;

};



#endif //COLISIONPRIMITIVE_HPP
