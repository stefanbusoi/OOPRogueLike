//
// Created by stefa on 5/1/2025.
//

#include "FileException.hpp"

FileException::FileException(const std::string &message):m_message(message ) {
#ifndef NDEBUG
  // __debugbreak();
#endif
}

const char * FileException::what()  const noexcept{
  return m_message.c_str();
}
