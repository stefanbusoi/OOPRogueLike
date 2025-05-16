//
// Created by stefa on 5/1/2025.
//

#include "GameLogicException.hpp"

GameLogicException::GameLogicException(const std::string &message):m_message(message ) {
#ifndef NDEBUG
  //__debugbreak();
#endif
}

const char * GameLogicException::what() const noexcept{
  return m_message.c_str();
}
