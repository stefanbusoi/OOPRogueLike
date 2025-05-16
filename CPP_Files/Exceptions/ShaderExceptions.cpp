//
// Created by stefa on 5/1/2025.
//

#include "ShaderExceptions.hpp"

ShaderExceptions::ShaderExceptions(const std::string &message):m_message(message ) {
#ifndef NDEBUG
  //__debugbreak();
#endif
}

const char * ShaderExceptions::what() const noexcept {
  return m_message.c_str();
}
