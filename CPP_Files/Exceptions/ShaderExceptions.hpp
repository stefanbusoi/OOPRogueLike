#pragma once
#include <string>


class ShaderExceptions:public std::exception {
private:
  std::string m_message;
public:

  explicit ShaderExceptions(const std::string& message);
  const char* what()const noexcept ;
};

