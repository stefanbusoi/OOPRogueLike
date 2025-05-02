//
// Created by stefa on 5/1/2025.
//

#include "FileException.hpp"

const char * FileException::what()  {
  return m_message.c_str();
}
