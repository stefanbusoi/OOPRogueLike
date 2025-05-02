#pragma once


#include <exception>
#include <iostream>
#include <string>


class GameLogicException:public std::exception {
private:
  std::string m_message;
public:
  explicit GameLogicException(const std::string& message):m_message(message ){
#ifndef NDEBUG
    //__debugbreak();
#endif
  }

  const char *what() {
    return m_message.c_str();
  }
};
