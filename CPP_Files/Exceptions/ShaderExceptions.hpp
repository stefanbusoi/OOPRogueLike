#pragma once
#include <string>


class ShaderExceptions:public std::exception {
private:
  std::string m_message;
public:
  explicit ShaderExceptions(const std::string& message):m_message(message ){
#ifndef NDEBUG
    //__debugbreak();
#endif
  }
  const char *what() {
    return m_message.c_str();
  }
};

