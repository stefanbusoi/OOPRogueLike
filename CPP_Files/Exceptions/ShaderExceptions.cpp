//
// Created by stefa on 5/1/2025.
//

#include "ShaderExceptions.hpp"

const char * ShaderExceptions::what()  {
  return m_message.c_str();
}
