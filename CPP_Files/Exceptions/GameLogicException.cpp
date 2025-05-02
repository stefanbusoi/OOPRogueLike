//
// Created by stefa on 5/1/2025.
//

#include "GameLogicException.hpp"

const char * GameLogicException::what() const{
  return m_message.c_str();
}
